#include "AdjacencySet.h"

struct PathNode
{
	int destinationIndex;
	int previousIndex;
	int cost;
	bool marked;

	PathNode()
	{
		destinationIndex = -1;
		previousIndex = -1;
		cost = -1;
		marked = false;
	}

	PathNode(int d, int p, int c)
	{
		destinationIndex = d;
		previousIndex = p;
		cost = c;
		marked = false;
	}
};


AdjacencySet::AdjacencySet(int numNodes)
{
	weights = new int*[numNodes];

	for (int row = 0; row < numNodes; row++)
	{
		weights[row] = new int[numNodes];
		
		for (int column = 0; column < numNodes; column++) 
		{
			weights[row][column] = -1; //initially all weights are less than zero; meaning disconnected
		}
	}
	_validLinks = 0;
	_numNodes = numNodes;
}

AdjacencySet::AdjacencySet(const AdjacencySet& other)
{
	for (int row = 0; row < other._numNodes; row++)
	{
		for (int column = 0; column < _numNodes; _numNodes++)
		{
			weights[row][column] = other.weights[row][column];
		}
	}
}

void AdjacencySet::UpdateWeight(int srcId, int destId, int weight)
{
	if (weights[srcId-1][destId-1] < 0)
	{
		if (weight > 0)
		{
			_validLinks++;
		}
	}
	else
	{
		if (weight < 0)
		{
			_validLinks--;
		}
	}

	weights[srcId-1][destId-1] = weight;
}

int AdjacencySet::GetNextNode(int srcId, int destId)
{
	PathNode* pathNodes = new PathNode[_numNodes];
	PathNode* considered = new PathNode[_validLinks];
	int numNotVisited = _numNodes - 1;
	int numConsideredEdges = 0;

	int srcIndex = srcId - 1;
	int destIndex = destId - 1;

	pathNodes[srcIndex] = PathNode(srcIndex, -1, 0);
	pathNodes[srcIndex].marked = true;

	for (int node = 0; node < _numNodes; node++)
	{
		if (node != srcIndex)
		{
			if (weights[srcIndex][node] >= 0)
			{
				considered[numConsideredEdges] = PathNode(node, srcIndex, weights[srcIndex][node] + pathNodes[srcIndex].cost);
				numConsideredEdges++;
			}
		}
	}

	while (numNotVisited > 0)
	{
		PathNode* leastEdge = &considered[0];

		for (int consideredEdge = 1; consideredEdge < numConsideredEdges; consideredEdge++)
		{
			if (leastEdge->marked)
			{
				leastEdge = &considered[consideredEdge];
			}
		}	

		for (int consideredEdge = 0; consideredEdge < numConsideredEdges; consideredEdge++)
		{
			if (!considered[consideredEdge].marked && considered[consideredEdge].cost < leastEdge->cost)
			{
				leastEdge = &considered[consideredEdge];
			}
		}

		int nodeIndex = leastEdge->destinationIndex;

		for (int consideredEdge = 0; consideredEdge < numConsideredEdges; consideredEdge++)
		{
			if (considered[consideredEdge].destinationIndex == nodeIndex)
			{
				considered[consideredEdge].marked = true;
			}
		}

		// copy information from edge
		pathNodes[nodeIndex] = *leastEdge;
		numNotVisited--;

		// push all edges that come from this node
		for (int node = 0; node < _numNodes; node++)
		{
			if (node != nodeIndex && !pathNodes[node].marked)
			{
				if (weights[nodeIndex][node] >= 0)
				{
					considered[numConsideredEdges] = PathNode(node, nodeIndex, weights[nodeIndex][node] + pathNodes[nodeIndex].cost);
					numConsideredEdges++;
				}
			}
		}

	}

	// follow the tree back to the node right before the starting position
	int nextIndex = destIndex;
	while (pathNodes[nextIndex].previousIndex != srcIndex)
	{
		nextIndex = pathNodes[nextIndex].previousIndex;
	}

	return(nextIndex);
}