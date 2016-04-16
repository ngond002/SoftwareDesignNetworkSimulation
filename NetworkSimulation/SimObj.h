#pragma once

typedef double Time;


void RunSimulation();
void RunSimulation(Time endTime);

class Event
{
public:
	virtual void Execute() = 0;
};

class SimObj
{
public:
	//friend Time GetCurrentSimTime();
	friend void RunSimulation();
	friend void RunSimulation(Time endTime);
protected:
	SimObj();
	void ScheduleEventIn(Time delta, Event *evt);
	void ScheduleEventAt(Time time, Event *evt);
	Time GetCurrentSimTime();
private:
	static Time _currentSimTime;
	class EventSet;
	static EventSet _eventSet;
};
