#include <iostream>
#include "SimObj.h"

using namespace std;

Time SimObj::_currentSimTime = 0.0;

class SimObj::EventSet
{
public:
	EventSet()
	{
		_head = 0;
	};

	bool HasEvent()
	{
		return(_head != 0);
	}

	void AddEvent(Time time, Event *evt)
	{
		EventNode *en = new EventNode(time, evt);
		if (_head == 0) {
			_head = en;
		}
		else if (time < _head->_time) {
			en->_next = _head;
			_head = en;
		}
		else {
			EventNode *next = _head;
			while (next->_next == 0 ? false : time > next->_next->_time) {
				next = next->_next;
			}
			en->_next = next->_next;
			next->_next = en;
		}
	};

	Event *GetEvent()
	{
		EventNode *en = _head;
		Event *evt = _head->_evt;
		_head = _head->_next;
		delete(en);
		return(evt);
	};

	Time GetTime()
	{
		return(_head->_time);
	};

private:
	struct EventNode
	{
		EventNode(Time time, Event *evt)
		{
			_time = time;
			_evt = evt;
			_next = 0;
		};

		Time _time;
		Event *_evt;
		EventNode *_next;
	};

	EventNode *_head;
};

SimObj::EventSet SimObj::_eventSet;

void RunSimulation()
{
	RunSimulation(-1.0);
}

void RunSimulation(Time endTime)
{
	while (SimObj::_eventSet.HasEvent() && ((SimObj::_currentSimTime <= endTime) || (endTime == -1.0))) {
		SimObj::_currentSimTime = SimObj::_eventSet.GetTime();
		Event *evt = SimObj::_eventSet.GetEvent();
		evt->Execute();
	}
}

SimObj::SimObj()
{
}

void SimObj::ScheduleEventAt(Time time, Event *evt)
{
	_eventSet.AddEvent(time, evt);
}

void SimObj::ScheduleEventIn(Time time, Event *evt)
{
	_eventSet.AddEvent(_currentSimTime + time, evt);
}

Time SimObj::GetCurrentSimTime()
{
	return(_currentSimTime);
}
