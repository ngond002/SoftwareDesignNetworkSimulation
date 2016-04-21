#include "Router.h"
#include "Graph.h"
#include <iostream>
#include <assert.h>
using namespace std;

class Router::GenerateEvent : public Event
{
	Router* _router;

public:
	GenerateEvent(Router* router)
	{
		_router = router;
	}

	void Execute()
	{
		_router->Generate();
	}
};

class Router::NodeSendEvent : public Event
{
	Router* _router;
	Packet* _packet;
public:
	NodeSendEvent(Router* router, Packet* packet)
	{
		_router = router;
		_packet = packet;
	}

	void Execute()
	{
		_router->NodeSend(_packet);
	}
};

Router::Router(int id, Distribution* serviceTime, Distribution* generationRate, int linkCount, AdjacencySet* initialSet) : Node(id)
{
	_numLinks = linkCount;
	_serviceTime = serviceTime;
	_generationRate = generationRate;
	_queues = new FIFOQueue[_numLinks];
	_routerIdle = true; 
	_packetsInProcess = 0;
	_lastIdleTime = GetCurrentSimTime();
	_runningServiceTimes = 0;
	_numberExited = 0;
	_localAdjacencySet = new AdjacencySet(*initialSet); // copy from external set

	// Unique name for each queue
	for (int queue = 0; queue < _numLinks; queue++)
	{
		char name[64];
		sprintf_s(name, 64, "Router %i Queue %i", _nodeId, queue + 1);
		_queues[queue].SetName(string(name));
	}

	int numOtherLinks = 0;
	otherLinks = new int[_numLinks - 1];

	// get all other links that are not ours
	for (int link = 1; link <= _numLinks; link++) 
	{
		if (link != _nodeId)
		{
			otherLinks[numOtherLinks] = (link);
			numOtherLinks++;
		}
	}

	// schedule first generation of a packet
	double delay = _generationRate->GetRV();
	ScheduleEventIn(delay, new GenerateEvent(this));
}

void Router::Generate()
{
	// assign a random destination in network
	// generate rn
	double rn = (((double)rand()) / (((double)RAND_MAX) + 1.0));

	int numOtherLinks = _numLinks - 1;
	int destId;

	// transform from discrete distribution
	if (rn == 0.0)
	{
		destId = otherLinks[0];
	}
	else
	{
		for (int n = 0; n < numOtherLinks; n++)
		{
			double lowerLimit = (n / (double)numOtherLinks);
			double upperLimit = (n + 1) / (double)numOtherLinks;

			if (rn > lowerLimit && rn <= upperLimit)
			{
				// assign destination to this link
				destId = otherLinks[n];
			}
		}
	}

	// create a new packet
	Packet* packet = new Packet;
	packet->_destId = destId;

	//log addition
	cout << GetCurrentSimTime() << ", Router<" << _nodeId <<
		"> Generate, Packet " << packet->_id << " for Router<" << destId << ">" << endl;

	// add to internal queue
	_queues[_nodeId - 1].Enqueue(packet);
	_packetsInProcess++;

	// schedule next generation of a packet
	double delay = _generationRate->GetRV();
	ScheduleEventIn(delay, new GenerateEvent(this));

	// check if router is idle
	if (_routerIdle)
	{
		//if idle, set the current queue and process the queue
		_currentQueue = _nodeId-1;

		//set router to busy
		_lastIdleTime = GetCurrentSimTime();
		_routerIdle = false;

		//start processing immediately
		Process();
	}
	else
	{
		//else, do nothing
	}
}

void Router::NodeReceive(Packet* packet)
{
	int previous = packet->_prevId;

	cout << GetCurrentSimTime() << ", Router<" << _nodeId <<
		"> Receive Packet " << packet->_id << " from Router<" << previous << ">" << endl;

	// add packet to correct queue based on previous id
	_queues[previous-1].Enqueue(packet);
	_packetsInProcess++;

#if defined USE_GLOBAL_MATRIX
	// update global adjacency set due to enqueue
	int weight = _queues[previous-1].Size();
	Graph::Instance()->GetGlobalAdjacency().UpdateWeight(previous, _nodeId, weight);
#endif

	// check if router is idle
	if (_routerIdle)
	{
		//if idle, set the current queue and process the queue
		_currentQueue = previous-1;

		//set router to busy
		_lastIdleTime = GetCurrentSimTime();
		_routerIdle = false;

		//start processing immediately
		Process();
	}
	else
	{
		//else, do nothing
	}

}

void Router::Process()
{
	Packet* packet = nullptr;

	// move to next nonempty queue
	while (_queues[_currentQueue].Size() == 0)
	{
		_currentQueue = (_currentQueue + 1) % _numLinks;
	}
	
	// take next packet out of current queue
	packet = _queues[_currentQueue].Dequeue();
	_packetsInProcess--;

	//log processing
	cout << GetCurrentSimTime() << ", Router<" << _nodeId <<
		"> Process, Packet " << packet->_id << endl;

#ifdef USE_GLOBAL_MATRIX
	if (_currentQueue != (_nodeId - 1)) // don't modify internal weight
	{
		// update global adjacency set due to dequeue - _currentQueue + 1 = id of node associated with queue
		int weight = _queues[_currentQueue].Size();
		Graph::Instance()->GetGlobalAdjacency().UpdateWeight(_currentQueue + 1, _nodeId, weight);
	}
#else
	if (packet->_prevId != -1)
	{
		// update the local table with information from the packet
		int weight = packet->_prevQueueSize;
		_localAdjacencySet->UpdateWeight(_nodeId, packet->_prevId, weight);
	}
#endif

	_currentQueue = (_currentQueue + 1) % _numLinks; // move to next queue

	// determine if packet should be sent
	if (packet->_destId != _nodeId)
	{
		// determine delay and schedule send event
		double delay = _serviceTime->GetRV();
		ScheduleEventIn(delay, new NodeSendEvent(this, packet));
	}
	else
	{
		// consume event
		cout << GetCurrentSimTime() << ", Router<" << _nodeId <<
			"> Consume Packet " << packet->_id << endl;
		
		// update packet time statistics
		Packet::_runningTotalTime += (GetCurrentSimTime() - packet->_creationTime);
		Packet::_runningWaitTime += (packet->_waitTime);
		Packet::_numberConsumed += 1;

		// free memory
		delete(packet);

		// check for more packets
		if (_packetsInProcess > 0)
		{
			Process();
		}
		else
		{
			// no more packets, router is now idle
			_routerIdle = true;

			//keep statistics on processing times
			_runningServiceTimes += (GetCurrentSimTime() - _lastIdleTime);
			_lastIdleTime = GetCurrentSimTime();
		}
	}	
}

void Router::NodeSend(Packet* packet)
{
	// obtain next node to send packet
#if defined USE_GLOBAL_MATRIX
	int nextId = Graph::Instance()->GetGlobalAdjacency().GetNextNode(_nodeId, packet->_destId);
#else
	int nextId = _localAdjacencySet->GetNextNode(_nodeId, packet->_destId);
#endif

	cout << GetCurrentSimTime() << ", Router<" << _nodeId <<
		"> Send Packet " << packet->_id << " to Router<" << nextId << ">" << endl;
	
	// keep information to update next node's adjacency set
	packet->_prevId = _nodeId;
	packet->_prevQueueSize = _queues[nextId - 1].Size();

	// statistics on exited packets
	_numberExited += 1;

	assert(_nodeId != nextId);

	SendPacket(packet, nextId); // call upper layer to send to next node

	// check for more packets
	if (_packetsInProcess > 0)
	{
		Process();
	}
	else
	{
		// no more packets, router is now idle
		_routerIdle = true;

		//keep statistics on processing times
		_runningServiceTimes += (GetCurrentSimTime() - _lastIdleTime);
		_lastIdleTime = GetCurrentSimTime();
	}
}

void Router::PrintStats()
{
	//correction term for service times
	_runningServiceTimes += (GetCurrentSimTime() - _lastIdleTime);
	_lastIdleTime = GetCurrentSimTime();

	std::cout << std::endl;
	std::cout << "Router<" << _nodeId << ">:\n";
	std::cout << "AvgProcessTime: " << _runningServiceTimes / _numberExited << std::endl;
	std::cout << "Utilization: " << _runningServiceTimes / GetCurrentSimTime() << std::endl;

	for (int queue = 0; queue < _numLinks; queue++)
	{
		_queues[queue].PrintStats();		
	}
}
