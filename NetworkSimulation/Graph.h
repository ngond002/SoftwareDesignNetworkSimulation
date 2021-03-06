#pragma once

#include "Node.h"
#include "AdjacencySet.h"

class Graph
{
private:
	Graph();
private:
	Node** _nodes;
	AdjacencySet* _globalAdjacencySet;
	static Graph* _instance;
	int _numNodes;
public:
	//Method: GetNode
	//Parameters: id - id of node to return
	//Return - pointer to node
	Node* GetNode(int id);

	//Method: GetGlobalAdjacency
	//Return - reference to Graph Adjacency Set
	AdjacencySet& GetGlobalAdjacency();

	//Method: Instance
	//Return - reference to global Graph object
	static Graph* Instance();

	//Method: NodeCount
	//Return - number of nodes in the Graph
	int NodeCount();

	// Display stats for entire graph system
	void PrintStats();
};
