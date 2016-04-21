#include "Packet.h"
#include "SimObj.h"
#include <iostream>

double Packet::_runningWaitTime = 0.0;
double Packet::_runningTotalTime = 0.0;
int Packet::_numberConsumed = 0;
int Packet::_nextId = 1;

Packet::Packet()
{
	_id = _nextId++;
	_prevId = -1;
	_destId = -1;
	_prevQueueSize = -1;
	_creationTime = GetCurrentSimTime();
	_waitTime = 0.0;
}

void Packet::PrintStats()
{
	std::cout << std::endl;
	std::cout << "Packets" << ":\n";
	std::cout << "AvgTotalTime: " << _runningTotalTime / _numberConsumed << std::endl;
	std::cout << "AvgWaitTime: " << _runningWaitTime / _numberConsumed << std::endl;
	std::cout << "NumberConsumed: " << _numberConsumed << std::endl;
}
