#pragma once

#include "Packet.h"

class Node
{
protected:
	int _nodeId;
public:
	Node(int id);

	int GetId();

	//Method: ReceivePacket
	//Parameters: Packet* packet - packet to receive from external object
	//Called from external object. Sends received packet to lower-layer for more specific processing
	void ReceivePacket(Packet* packet);

	//Method: SendPacket
	//Parameters:	Packet* packet - packet to send
	//				int destId - Id of destination node
	//Called from lower layer. Obtains reference to destination node from Id and calls node's ReceivePacket method
	void SendPacket(Packet* packet, int destId);

	//Method: NodeReceive - virtual
	//Parameters: Packet* packet - packet to receive from upper Graph layer
	//Called from Node base class. Handles receive event from Routing model
	virtual void NodeReceive(Packet* packet) = 0;

	//Method: NodeSend - virtual
	//Parameters: Packet* packet - packet to send to upper Graph layer
	//Determines where to send a processed packet. Handles the send event from Routing model.
	virtual void NodeSend(Packet* packet) = 0;
};
