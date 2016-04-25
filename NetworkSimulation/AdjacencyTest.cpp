//#include "AdjacencySet.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
// // Prologue: set up test network with weights
//	AdjacencySet set(4);
//	set.UpdateWeight(1, 2, 5);
//	set.UpdateWeight(2, 1, 5);
//	set.UpdateWeight(1, 3, 2);
//	set.UpdateWeight(3, 1, 2);
//	set.UpdateWeight(2, 3, 2);
//	set.UpdateWeight(3, 2, 2);
//	set.UpdateWeight(2, 4, 5);
//	set.UpdateWeight(4, 2, 5);
//
//	// Test moving from source to destination
//	int srcId = 2;
//	int destId = 1;
//	int nextIndex = set.GetNextNode(srcId, destId);
//	cout << "From #" << srcId << " to #" << destId << " go next to #" << nextIndex + 1 << endl;
//	cin.get();
//	return(0);
//}
