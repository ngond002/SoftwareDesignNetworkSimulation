#pragma once

typedef double Time;

//Method: RunSimulation
//Executes events in time stamp order until there are no events left in the simulation
void RunSimulation();

//Method: RunSimulation
//Parameters: endTime - The time to stop the simulation
//Executes events in time stamp order until there are no events left in the simulation or
//the simulation time exceeds the end time
void RunSimulation(Time endTime);

//Method: GetCurrentSimTime
//Return: Returns the time of the last event that was executed by the simulation
Time GetCurrentSimTime();

class SimObj
{
	friend void RunSimulation();
	friend void RunSimulation(Time endTime);
	friend Time GetCurrentSimTime();
protected:
	//Method: RunSimulation
	//Parameters:	delay - The delay in which to schedule the event
	//				evt - The event to schedule
	//Records an event with timestamp 'currSimTime + delay' to be executed at that simulation time in the future
	void ScheduleEventIn(Time delay, Event* evt);

	//Method: RunSimulation
	//Parameters:	time - The time to schedule the event
	//				evt - The event to schedule
	//Records an event with timestamp 'time' to be executed at that simulation time in the future
	void ScheduleEventAt(Time time, Event* evt);
};
