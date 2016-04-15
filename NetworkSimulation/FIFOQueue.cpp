#include "FIFOQueue.h"
#include <iostream>

struct FIFOQueue::QueueEntry
{
	QueueEntry* _next;
	Packet* _packet;

	QueueEntry(Packet* packet)
	{
		_packet = packet;
		_next = nullptr;
	}
};

FIFOQueue::FIFOQueue()
{
	_head = nullptr;
	_tail = nullptr;
	_queueSize = 0;
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

	_queueSize++; // incr size
	
}

Packet* FIFOQueue::Dequeue()
{
	QueueEntry* entry = _head;
	_head = _head->_next;
	Packet* packet = _head->_packet;
	delete(entry); //free memory
	_queueSize--; //decr size
	return(packet);
}

int FIFOQueue::Size()
{
	return(_queueSize);
}