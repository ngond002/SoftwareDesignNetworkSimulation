#pragma once

typedef double Time;

class SimObj
{
protected:
	void ScheduleEventIn(Time delay, Event* evt);
	void ScheduleEventAt(Time time, Event* evt);
	static void RunSimulation();
	static void RunSimulation(Time endTime);
	static Time GetCurrentSimTime();
};
