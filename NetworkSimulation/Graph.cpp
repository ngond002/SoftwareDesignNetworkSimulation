#include "Graph.h"
#include "Router.h"
#include "Distribution.h"
#include <iostream>

Graph* Graph::_instance = nullptr;

Graph::Graph()
{
	// create the graph nodes
	//_numNodes = 3;
	_numNodes = 10;
	_nodes = new Node*[_numNodes];
	
	// initialize the adjacency set
	_globalAdjacencySet = new AdjacencySet(_numNodes);
	//_globalAdjacencySet->UpdateWeight(1, 2, 0);
	//_globalAdjacencySet->UpdateWeight(2, 1, 0);
	//_globalAdjacencySet->UpdateWeight(2, 3, 0);
	//_globalAdjacencySet->UpdateWeight(3, 2, 0);

	_globalAdjacencySet->UpdateWeight(1, 2, 0);
	_globalAdjacencySet->UpdateWeight(1, 4, 0);
	_globalAdjacencySet->UpdateWeight(2, 3, 0);
	_globalAdjacencySet->UpdateWeight(2, 4, 0);
	_globalAdjacencySet->UpdateWeight(2, 5, 0);
	_globalAdjacencySet->UpdateWeight(3, 2, 0);
	_globalAdjacencySet->UpdateWeight(3, 6, 0);
	_globalAdjacencySet->UpdateWeight(4, 1, 0);
	_globalAdjacencySet->UpdateWeight(4, 2, 0);
	_globalAdjacencySet->UpdateWeight(4, 10, 0);
	_globalAdjacencySet->UpdateWeight(5, 2, 0);
	_globalAdjacencySet->UpdateWeight(5, 6, 0);
	_globalAdjacencySet->UpdateWeight(5, 8, 0);
	_globalAdjacencySet->UpdateWeight(6, 5, 0);
	_globalAdjacencySet->UpdateWeight(6, 7, 0);
	_globalAdjacencySet->UpdateWeight(7, 6, 0);
	_globalAdjacencySet->UpdateWeight(7, 8, 0);
	_globalAdjacencySet->UpdateWeight(8, 5, 0);
	_globalAdjacencySet->UpdateWeight(8, 7, 0);
	_globalAdjacencySet->UpdateWeight(8, 9, 0);
	_globalAdjacencySet->UpdateWeight(9, 8, 0);
	_globalAdjacencySet->UpdateWeight(9, 10, 0);
	_globalAdjacencySet->UpdateWeight(10, 4, 0);
	_globalAdjacencySet->UpdateWeight(10, 9, 0);

	//_nodes[0] = new Router(1, new Triangular(0.9, 1.0, 1.1), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	//_nodes[1] = new Router(2, new Triangular(0.8, 0.8, 0.8), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	//_nodes[2] = new Router(3, new Triangular(0.9, 0.9, 0.9), new Exponential(3.0), _numNodes, _globalAdjacencySet);

	//create the node routers of the network
	_nodes[0] = new Router(1, new Triangular(0.9, 1.0, 1.1), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[1] = new Router(2, new Triangular(0.8, 0.8, 0.8), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[2] = new Router(3, new Triangular(0.9, 1.0, 1.1), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[3] = new Router(4, new Triangular(0.9, 0.9, 0.9), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[4] = new Router(5, new Triangular(0.9, 0.9, 0.9), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[5] = new Router(6, new Triangular(0.9, 0.9, 0.9), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[6] = new Router(7, new Triangular(0.9, 1.0, 1.1), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[7] = new Router(8, new Triangular(0.9, 0.9, 0.9), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[8] = new Router(9, new Triangular(0.9, 1.0, 1.1), new Exponential(3.0), _numNodes, _globalAdjacencySet);
	_nodes[9] = new Router(10, new Triangular(0.9, 1.0, 1.1), new Exponential(3.0), _numNodes, _globalAdjacencySet);

}

Node* Graph::GetNode(int id)
{
	return(_nodes[id-1]);
}

AdjacencySet& Graph::GetGlobalAdjacency()
{
	return(*_globalAdjacencySet);
}

Graph* Graph::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new Graph;
	}

	return(_instance);
}

int Graph::NodeCount()
{
	return(_numNodes);
}

void Graph::PrintStats()
{
	//std::cout << std::endl;
	//std::cout << "Graph Statistics:*************" << std::endl;
	for (int node = 0; node < _numNodes; node++)
	{
		this->_nodes[node]->PrintStats();
	}

	Packet::PrintStats();
	
}


