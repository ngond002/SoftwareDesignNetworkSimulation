#pragma once

typedef double Time;

//Method: RunSimulation
//Executes events in timestamp order until no events are left
void RunSimulation();

//Method: RunSimulation
//Parameters: Time endTime - Time stamp to stop the simulation
//Executes events in timestamp order until no events are left or end time is reached
void RunSimulation(Time endTime);

//Method: GetCurrentSimTime
//Obtain current simulation time
Time GetCurrentSimTime();

class Event
{
public:
	virtual void Execute() = 0;
};

class SimObj
{
public:
	friend Time GetCurrentSimTime();
	friend void RunSimulation();
	friend void RunSimulation(Time endTime);
protected:
	SimObj();
	void ScheduleEventIn(Time delta, Event *evt);
	void ScheduleEventAt(Time time, Event *evt);
private:
	static Time _currentSimTime;
	class EventSet;
	static EventSet _eventSet;
};
