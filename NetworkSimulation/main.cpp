#include <iostream>
#include "Graph.h"
#include "SimObj.h"
using namespace std;

int main()
{
	srand(10);
	Graph::Instance(); // create the graph
	RunSimulation(60);
	Graph::Instance()->PrintStats();
	cout << "<END SIMULATION>******************************";
	cin.get();
	return(0);
}
