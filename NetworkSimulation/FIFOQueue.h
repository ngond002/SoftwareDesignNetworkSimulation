#pragma once

#include "Packet.h"

class FIFOQueue
{
private:
	struct QueueEntry
	{
		QueueEntry* _next;
		Packet* _packet;
	};

	int _queueSize;

public:
	FIFOQueue();
	void Enqueue(Packet* packet);
	Packet* Dequeue();
	int Size(); // change from HasEntries() : bool
};
