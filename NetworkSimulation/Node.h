#pragma once

#include "Packet.h"

class Node
{
protected:
	int _nodeId;
public:
	Node(int id);
	int GetId();
	void ReceivePacket(Packet* packet);
	void SendPacket(Packet* packet, int destId);
};
