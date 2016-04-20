#pragma once

#include "Packet.h"
#include "FIFOQueue.h"
#include "AdjacencySet.h"
#include "Node.h"
#include "SimObj.h"

#define USE_GLOBAL_MATRIX

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
	//				generationRate - the number of packets to create per time unit
	//				numLinks
	Router(int id, double serviceTime, double generationRate);

	//Method: NodeReceive
	//Parameters: Packet* packet - packet to receive from upper Graph layer
	//Called from Node base class. Handles receive event from Routing model
	void NodeReceive(Packet* packet);

	//Method: NodeSend
	//Parameters: Packet* packet - packet to send to upper Graph layer
	//Determines where to send a processed packet. Handles the send event from Routing model.
	void NodeSend(Packet* packet);

};
