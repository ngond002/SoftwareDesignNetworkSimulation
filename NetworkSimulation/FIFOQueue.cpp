#include "FIFOQueue.h"
#include "SimObj.h"
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

	cout << GetCurrentSimTime() << ", queue " << _name << ", Enqueue, Entity , queue size, " << _queueSize << endl;
	_queueSize++; // incr size
	cout << GetCurrentSimTime() << ", queue " << _name << ", Enqueue, Entity , queue size, " << _queueSize << endl;
	
}

Packet* FIFOQueue::Dequeue()
{
	QueueEntry* entry = _head;
	_head = _head->_next;
	Packet* packet = _head->_packet;
	delete(entry); //free memory

	cout << GetCurrentSimTime() << ", queue " << _name << ", Dequeue, Entity , queue size, " << _queueSize << endl;
	_queueSize--; //decr size
	cout << GetCurrentSimTime() << ", queue " << _name << ", Dequeue, Entity , queue size, " << _queueSize << endl;

	return(packet);
}

int FIFOQueue::Size()
{
	return(_queueSize);
}