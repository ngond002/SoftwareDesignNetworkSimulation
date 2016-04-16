#include "Router.h"
#include "Graph.h"

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

Router::Router(int id, double serviceTime, double generationRate, int numLinks) :
	Node(id), _localAdjacencySet(numLinks) // Maybe change passing in numLinks to a global call to Graph
{
	_serviceTime = serviceTime;
	_generationRate = generationRate;
	_queues = new FIFOQueue[numLinks];
	_routerIdle = false;
	_packetsInProcess = 0;
	_numLinks = numLinks;
}

void Router::Generate()
{
	// create a new packet
	Packet* packet = new Packet;

	// assign a random destination in network
	int destId = 0;
	packet->_destId = destId;

	// add to internal queue
	_queues[_nodeId].Enqueue(packet);
	_packetsInProcess++;
	
	//log addition

	// schedule next generation of a packet
	Time delay = 1 / _generationRate;
	ScheduleEventIn(delay, new GenerateEvent(this));

	// check if router is idle
	if (_routerIdle)
	{
		//if idle, set the current queue and process the queue
		_currentQueue = _nodeId;
		_routerIdle = false;
		Process();
	}
	else
	{
		//else, do nothing
	}
}

void Router::NodeReceive(Packet* packet)
{
	// add packet to correct queue based on previous id
	int previous = packet->_prevId;
	_queues[previous].Enqueue(packet);
	_packetsInProcess++;

#if defined USE_GLOBAL_MATRIX
	// update global adjacency set
	int weight = _queues[previous].Size();
	Graph::Instance()->GetGlobalAdjacency()->UpdateWeight(previous, _nodeId, weight);
#endif

	// check if router is idle
	if (_routerIdle)
	{
		//if idle, set the current queue and process the queue
		_currentQueue = previous;
		_routerIdle = false;
		Process();
	}
	else
	{
		//else, do nothing
	}

}

void Router::Process()
{
	// no packets available
	if (_packetsInProcess == 0)
	{
		return;
	}

	Packet* packet = nullptr;

	// move to next nonempty queue
	while (_queues[_currentQueue].Size() == 0)
	{
		_currentQueue = (_currentQueue + 1) % _numLinks;
	}
	
	// take next packet out of current queue
	packet = _queues[_currentQueue].Dequeue();
	_packetsInProcess--;

#ifndef USE_GLOBAL_MATRIX
	// update the local table with information about the packet
	int weight = packet->_prevQueueSize;
	_localAdjacencySet.UpdateWeight(packet->_prevId, _nodeId, weight);
#endif

	// determine if packet should be sent
	if (packet->_destId == _nodeId)
	{
		// determine delay and schedule send event
		Time delay = _serviceTime; // constant service time
		ScheduleEventIn(delay, new NodeSendEvent(this, packet));
	}
	else
	{
		// consume event
	}
	
}

void Router::NodeSend(Packet* packet)
{
	// obtain next node to send packet
#if defined USE_GLOBAL_MATRIX
	int nextId = Graph::Instance()->GetGlobalAdjacency()->GetNextNode(_nodeId, packet->_destId);
#else
	int nextId = _localAdjacencySet.GetNextNode(_nodeId, packet->_destId);
#endif

	//This code should be in the Node::SendPacket method-------

	//// obtain reference to node
	//Node* nextNode = Graph::Instance()->GetNode(nextId);

	//// call receive on next node
	//nextNode->ReceivePacket(packet);

	//--------------------------------------------------------

	SendPacket(packet, nextId); // call upper layer send

	if (_packetsInProcess > 0)
	{
		Process();
	}
	else
	{
		_routerIdle = true;
	}
}