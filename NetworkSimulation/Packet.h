#pragma once

//Note: Very primitive definition of a packet.
//May want to add more information to facilitate routing operations.

class Packet
{
	friend class Router;
private:
	static int _nextId;
	int _id;
	int _prevId;
	int _destId;
	int _prevQueueSize;
public:
	Packet()
	{
		_id = _nextId++;
	}

};
