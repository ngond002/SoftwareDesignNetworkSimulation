#pragma once

#include "Node.h"
#include "AdjacencySet.h"

class Graph
{
private:
	Node* _nodes;
	AdjacencySet _globalAdjacencySet;
	static Graph* _instance;
public:
	Graph();

	//Method: GetNode
	//Parameters: id - id of node to return
	//Return - pointer to node
	Node* GetNode(int id);

	//Method: GetGlobalAdjacency
	//Return - reference to Graph Adjacency Set
	AdjacencySet* GetGlobalAdjacency();

	//Method: Instance
	//Return - reference to global Graph object
	static Graph* Instance();

	//Method: NodeCount
	//Return - number of nodes in the Graph
	int NodeCount();
};
