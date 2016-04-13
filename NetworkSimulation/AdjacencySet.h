#pragma once

class AdjacencySet
{
	double** weights;
public:
	AdjacencySet(int numNodes);
	AdjacencySet(AdjacencySet& other);
	int GetNextNode(int srcId, int destId);
	void UpdateWeight(int srcId, int destId, int weight);
};
