#pragma once
#include <string>
#include "Packet.h"
using namespace std;

class FIFOQueue
{
private:
	struct QueueEntry;
	int _queueSize;
	QueueEntry* _head;
	QueueEntry* _tail;
	string _name;
public:
	FIFOQueue();
	void Enqueue(Packet* packet);
	Packet* Dequeue();
	int Size();
	void SetName(string name);
};
