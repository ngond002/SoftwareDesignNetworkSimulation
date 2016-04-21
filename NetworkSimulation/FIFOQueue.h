#pragma once
#include <string>
#include "Packet.h"
using namespace std;

class FIFOQueue
{
private:
	struct QueueEntry;
	QueueEntry* _head;
	QueueEntry* _tail;
	string _name;
	double _runningAvgSize;
	double _runningWaitTime;
	double _numberExited;
	int _prevQueueSize;
	int _queueSize;
	int _maxQueueSize;

public:
	FIFOQueue();
	void SetName(string name);
	void Enqueue(Packet* packet);
	Packet* Dequeue();
	int Size();
	void PrintStats();
};
