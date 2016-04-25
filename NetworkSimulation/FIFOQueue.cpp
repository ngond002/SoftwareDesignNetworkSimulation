#include "FIFOQueue.h"
#include "SimObj.h"
#include <iostream>

struct FIFOQueue::QueueEntry
{
	QueueEntry* _next;
	Packet* _packet;
	Time _entryTime;

	QueueEntry(Packet* packet)
	{
		_packet = packet;
		_next = nullptr;
		_entryTime = GetCurrentSimTime();
	}
};

FIFOQueue::FIFOQueue()
{
	_head = nullptr;
	_tail = nullptr;
	_queueSize = 0;
	_runningAvgSize = 0;
	_runningWaitTime = 0;
	_numberExited = 0;
	_prevQueueSize = 0;
	_queueSize = 0;
	_maxQueueSize = -1;
}

void FIFOQueue::SetName(string name)
{
	_name = name;
}

void FIFOQueue::Enqueue(Packet* packet)
{
	if (_head == nullptr) // empty queue
	{
		_head = new QueueEntry(packet);
		_tail = _head;
	}
	else
	{
		_tail->_next = new QueueEntry(packet);
		_tail = _tail->_next;
	}
	
	//compute running sum when size changes
	_queueSize += 1;
	_runningAvgSize += GetCurrentSimTime()*(_prevQueueSize - _queueSize);
	_prevQueueSize = _queueSize;

	// keep max size
	if (_prevQueueSize > _maxQueueSize)
	{
		_maxQueueSize = _prevQueueSize;
	}

	//cout << GetCurrentSimTime() << "\tQueue" << _name << "\tEnqueue Entity\tqueue size " << _queueSize << endl;
	
}

Packet* FIFOQueue::Dequeue()
{
	QueueEntry* entry = _head;
	_head = _head->_next;
	Packet* packet = entry->_packet;

	//compute running sum when size changes
	_queueSize -= 1;
	_runningAvgSize += GetCurrentSimTime()*(_prevQueueSize - _queueSize);
	_prevQueueSize = _queueSize;

	// keep max size
	if (_prevQueueSize > _maxQueueSize)
	{
		_maxQueueSize = _prevQueueSize;
	}

	//compute running waitTime
	_runningWaitTime += (GetCurrentSimTime() - entry->_entryTime);
	_numberExited += 1;
	packet->_waitTime += (GetCurrentSimTime() - entry->_entryTime);	

	//cout << GetCurrentSimTime() << ", queue " << _name << ", Dequeue, Entity , queue size, " << _queueSize << endl;

	delete(entry); //free memory

	return(packet);
}

int FIFOQueue::Size()
{
	return(_queueSize);
}

void FIFOQueue::PrintStats()
{
	// queue was not used
	if (_maxQueueSize < 0)
	{
		return;
	}
	
	

	// correction term
	_runningAvgSize += GetCurrentSimTime()*(_queueSize);

	std::cout << std::endl;
	std::cout << _name << ":\n";
	std::cout << "MaxQueueSize: " << _maxQueueSize << std::endl;
	std::cout << "AvgQueueSize: " << _runningAvgSize / GetCurrentSimTime() << std::endl;
	std::cout << "AvgQueueWait: " << _runningWaitTime / _numberExited << std::endl;
}