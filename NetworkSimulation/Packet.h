#pragma once

class Packet
{
	friend class Router;
	friend class FIFOQueue;

	static double _runningWaitTime;
	static double _runningTotalTime;
	static int _numberConsumed;
	static int _nextId;

	int _id;
	int _prevId;
	int _destId;
	int _prevQueueSize;
	double _creationTime;
	double _waitTime;

public:
	Packet();
	static void PrintStats();
};
