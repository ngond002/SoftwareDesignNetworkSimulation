#include "Graph.h"

Node::Node(int id)
{
	_nodeId = id;
}

int Node::GetId()
{
	return(_nodeId);
}

void Node::ReceivePacket(Packet* packet)
{
	NodeReceive(packet);
}

void Node::SendPacket(Packet* packet, int destId)
{
	Node* recv = Graph::Instance()->GetNode(destId);
	recv->ReceivePacket(packet);
}