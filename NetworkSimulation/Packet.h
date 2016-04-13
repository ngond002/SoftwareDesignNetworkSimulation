#pragma once

struct Packet
{
	int _id;
	int _prevId;
	int _destId;
	int _prevQueueSize;
};
