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
	Node* GetNode(int id);
	AdjacencySet* GetGlobalAdjacency();
	static Graph* Instance();
	int NodeCount();
};
