#pragma once

//Note: Very primitive definition of a packet.
//May want to add more information to facilitate routing operations.

struct Packet
{
	int _id;
	int _prevId;
	int _destId;
	int _prevQueueSize;
};
