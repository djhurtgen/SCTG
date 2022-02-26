//adapted from: https://www.techiedelight.com/graph-implementation-using-stl/
//and https://www.includehelp.com/cpp-tutorial/dijkstras-algorithm.aspx

#include <iostream>
#include <vector>
#include "../_include/Edge.h"
#include "../_include/Graph.h"
#include <chrono>
using namespace std;
using namespace chrono;

typedef pair<int, int> Pair;

// Graph Implementation using STL
int main()
{
	// time the entire operation
	auto start = high_resolution_clock::now();

	vector<Edge<int>> edges;
	Edge<int> e;
	e.setSrcDstWeight(0, 1, 4); edges.push_back(e);
	e.setSrcDstWeight(0, 4, 6); edges.push_back(e);
	e.setSrcDstWeight(1, 0, 4); edges.push_back(e);
	e.setSrcDstWeight(1, 2, 3); edges.push_back(e);
	e.setSrcDstWeight(2, 1, 3); edges.push_back(e);
	e.setSrcDstWeight(2, 3, 2); edges.push_back(e);
	e.setSrcDstWeight(2, 6, 4); edges.push_back(e);
	e.setSrcDstWeight(3, 2, 2); edges.push_back(e);
	e.setSrcDstWeight(4, 5, 5); edges.push_back(e);
	e.setSrcDstWeight(4, 8, 5); edges.push_back(e);
	e.setSrcDstWeight(5, 6, 4); edges.push_back(e);
	e.setSrcDstWeight(5, 4, 5); edges.push_back(e);
	e.setSrcDstWeight(5, 1, 5); edges.push_back(e);
	e.setSrcDstWeight(6, 7, 3); edges.push_back(e);
	e.setSrcDstWeight(6, 5, 4); edges.push_back(e);
	e.setSrcDstWeight(6, 10, 3); edges.push_back(e);
	e.setSrcDstWeight(7, 6, 3); edges.push_back(e);
	e.setSrcDstWeight(7, 3, 5); edges.push_back(e);
	e.setSrcDstWeight(8, 9, 6); edges.push_back(e);
	e.setSrcDstWeight(8, 12, 4); edges.push_back(e);
	e.setSrcDstWeight(9, 8, 6); edges.push_back(e);
	e.setSrcDstWeight(9, 10, 5); edges.push_back(e);
	e.setSrcDstWeight(9, 5, 4); edges.push_back(e);
	e.setSrcDstWeight(10, 9, 5); edges.push_back(e);
	e.setSrcDstWeight(10, 11, 4); edges.push_back(e);
	e.setSrcDstWeight(10, 14, 2); edges.push_back(e);
	e.setSrcDstWeight(11, 10, 4); edges.push_back(e);
	e.setSrcDstWeight(11, 7, 4); edges.push_back(e);
	e.setSrcDstWeight(12, 13, 5); edges.push_back(e);
	e.setSrcDstWeight(13, 14, 4); edges.push_back(e);
	e.setSrcDstWeight(13, 12, 5); edges.push_back(e);
	e.setSrcDstWeight(13, 9, 3); edges.push_back(e);
	e.setSrcDstWeight(14, 15, 3); edges.push_back(e);
	e.setSrcDstWeight(14, 13, 4); edges.push_back(e);
	e.setSrcDstWeight(15, 14, 3); edges.push_back(e);
	e.setSrcDstWeight(15, 11, 3); edges.push_back(e);

	// construct graph
	Graph<int> graph(edges);

	// print adjacency list representation of graph
	graph.printAdjList();
	
	// calculate shortest path from node s=0 to node t=10 
	graph.calculateSP(0, 15);
	
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Time for operation: " << duration.count() << " milliseconds" << endl;

	system("pause");
	return 0;
}