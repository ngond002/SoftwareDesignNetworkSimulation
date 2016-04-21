#include <iostream>
#include "Graph.h"
#include "SimObj.h"
using namespace std;

int main()
{
	srand(1);
	Graph::Instance(); // create the graph
	RunSimulation(30.0);
	cout << "*****************************************************";
	cin.get();
	return(0);
}
