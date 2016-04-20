#include "Graph.h"
#include "Router.h"

Graph* Graph::_instance = nullptr;

Graph::Graph()
{
	// create the graph nodes
	_numNodes = 2;
	_nodes = new Node*[2];
	
	for (int i = 0; i < _numNodes; i++)
	{
		_nodes[i] = new Router(i, 1, 1);
	}

	// initialize the adjacency set
	_globalAdjacencySet = new AdjacencySet(_numNodes);
	_globalAdjacencySet->UpdateWeight(0, 1, 0);
	_globalAdjacencySet->UpdateWeight(1, 0, 0);
}

Node* Graph::GetNode(int id)
{
	return(_nodes[id]);
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