#include <iostream>
#include "Graph.h"
#include "SimObj.h"
#include "Router.h"
using namespace std;

bool USE_GLOBAL_MATRIX = true;

int main()
{
	int seed;
	cout << "Enter seed value: ";
	cin >> seed;
	srand(seed);

	char answer;

	cout << "Use Global View <Y> <N>:";
	cin >> answer;
	if (answer == 'Y')
	{
		USE_GLOBAL_MATRIX = true;
	}
	else if (answer == 'N')
	{
		USE_GLOBAL_MATRIX = false;
	}

	Graph::Instance(); // create the graph
	RunSimulation(120);
	Graph::Instance()->PrintStats();

	cout << "<END SIMULATION>******************************";

	cin.ignore(255, '\n');
	cin.get();
	return(0);
}
