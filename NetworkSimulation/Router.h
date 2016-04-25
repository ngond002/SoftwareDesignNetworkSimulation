#pragma once

#include "Packet.h"
#include "FIFOQueue.h"
#include "AdjacencySet.h"
#include "Node.h"
#include "SimObj.h"
#include "Distribution.h"

extern bool USE_GLOBAL_MATRIX;

class Router : virtual public Node, public SimObj
{
private:
	FIFOQueue* _queues;
	bool _routerIdle;
	int _currentQueue;
	int _packetsInProcess;
	Distribution* _serviceTime;
	Distribution* _generationRate;
	AdjacencySet* _localAdjacencySet;
	int _numLinks;
	int* otherLinks;

	double _runningServiceTimes;
	Time _lastIdleTime;
	int _numberExited;

private:

	//Method: Generate
	//Handles generate event from Routing model. Creates and stores a new packet
	void Generate();

	//Method: Process
	//Handles packet processing. May decide to consume or send a packet
	void Process();

	class GenerateEvent;
	class NodeSendEvent;
public:

	//Constructor
	//Parameters:	id - id given to this Router
	//				serviceTime - delay to apply between processing and sending a packet
	//				interGenerationRate - the time delay between generating packets
	//				numLinks
	Router(int id, Distribution* serviceTime, Distribution* interGenerationRate, int linkCount, AdjacencySet* initialSet);

	void NodeReceive(Packet* packet);
	void NodeSend(Packet* packet);
	void PrintStats();
};
