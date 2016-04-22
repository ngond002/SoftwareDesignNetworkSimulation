#include <iostream>
#include "Graph.h"
#include "SimObj.h"
using namespace std;

int main()
{
	int seed;
	cout << "Enter seed value: ";
	cin >> seed;
	srand(seed);

	Graph::Instance(); // create the graph
	RunSimulation(120);
	Graph::Instance()->PrintStats();

	//cout << "<END SIMULATION>******************************";

	cin.ignore(255, '\n');
	cin.get();
	return(0);
}
