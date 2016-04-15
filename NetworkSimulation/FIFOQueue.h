#pragma once

#include "Packet.h"

class FIFOQueue
{
private:
	struct QueueEntry;
	int _queueSize;
	QueueEntry* _head;
	QueueEntry* _tail;
public:
	FIFOQueue();
	void Enqueue(Packet* packet);
	Packet* Dequeue();
	int Size();
};
