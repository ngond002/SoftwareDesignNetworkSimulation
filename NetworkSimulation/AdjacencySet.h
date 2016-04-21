#pragma once

class AdjacencySet
{
	int** weights;
	int _numNodes;
public:
	//Method: Constructor
	//Parameter: numNodes - number of Nodes that make up the graph
	//Allocates memory for a NxN matrix of weights
	AdjacencySet(int numNodes);

	//Method: Copy Constructor
	//Parameter: other - reference to another Adjacency set to copy from
	//sets up weights in table using the other set's weights
	AdjacencySet(const AdjacencySet& other);

	//Method: GetNextNode
	//Parameter:	srcId - the id of the initial node in the path
	//				destId - the id of the goal node in the path
	//Obtains the next node to traverse on a minimal cost path from src to dest
	int GetNextNode(int srcId, int destId);

	//Method: UpdateWeight
	//Parameter:	srcId - the id of the source node on a link
	//				destId - the id of the destination node on a link
	//Modifies the weight value corresponding to the link between source and destination.
	void UpdateWeight(int srcId, int destId, int weight);
};
