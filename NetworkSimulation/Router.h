#pragma once

#include "Packet.h"
#include "FIFOQueue.h"
#include "AdjacencySet.h"
#include "Node.h"
#include "SimObj.h"

#define USE_GLOBAL_MATRIX;

class Router : virtual public Node, public SimObj
{
private:
	FIFOQueue* _queues;
	bool _routerIdle;
	int _currentQueue;
	int _packetsInProcess;
	double _serviceTime;
	double _generationRate;
	AdjacencySet _localAdjacencySet;
	int _numLinks;
private:
	void Generate();
	void Process();
	class GenerateEvent;
	class NodeSendEvent;
public:
	Router(int id, double serviceTime, double generationRate, int numLinks);
	void NodeReceive(Packet* packet);
	void NodeSend(Packet* packet);

};
