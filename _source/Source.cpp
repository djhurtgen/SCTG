//adapted from: https://www.techiedelight.com/graph-implementation-using-stl/
//and https://www.includehelp.com/cpp-tutorial/dijkstras-algorithm.aspx

#include <iostream>
#include <vector>
#include "../_include/Road.h"
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

	vector<Road<int>> roads;
	Road<int> r;
	r.setSrcDstWeight(0, 1, 4); roads.push_back(r);
	r.setSrcDstWeight(0, 4, 6); roads.push_back(r);
	r.setSrcDstWeight(1, 0, 4); roads.push_back(r);
	r.setSrcDstWeight(1, 2, 3); roads.push_back(r);
	r.setSrcDstWeight(2, 1, 3); roads.push_back(r);
	r.setSrcDstWeight(2, 3, 2); roads.push_back(r);
	r.setSrcDstWeight(2, 6, 4); roads.push_back(r);
	r.setSrcDstWeight(3, 2, 2); roads.push_back(r);
	r.setSrcDstWeight(4, 5, 5); roads.push_back(r);
	r.setSrcDstWeight(4, 8, 5); roads.push_back(r);
	r.setSrcDstWeight(5, 6, 4); roads.push_back(r);
	r.setSrcDstWeight(5, 4, 5); roads.push_back(r);
	r.setSrcDstWeight(5, 1, 5); roads.push_back(r);
	r.setSrcDstWeight(6, 7, 3); roads.push_back(r);
	r.setSrcDstWeight(6, 5, 4); roads.push_back(r);
	r.setSrcDstWeight(6, 10, 3); roads.push_back(r);
	r.setSrcDstWeight(7, 6, 3); roads.push_back(r);
	r.setSrcDstWeight(7, 3, 5); roads.push_back(r);
	r.setSrcDstWeight(8, 9, 6); roads.push_back(r);
	r.setSrcDstWeight(8, 12, 4); roads.push_back(r);
	r.setSrcDstWeight(9, 8, 6); roads.push_back(r);
	r.setSrcDstWeight(9, 10, 5); roads.push_back(r);
	r.setSrcDstWeight(9, 5, 4); roads.push_back(r);
	r.setSrcDstWeight(10, 9, 5); roads.push_back(r);
	r.setSrcDstWeight(10, 11, 4); roads.push_back(r);
	r.setSrcDstWeight(10, 14, 2); roads.push_back(r);
	r.setSrcDstWeight(11, 10, 4); roads.push_back(r);
	r.setSrcDstWeight(11, 7, 4); roads.push_back(r);
	r.setSrcDstWeight(12, 13, 5); roads.push_back(r);
	r.setSrcDstWeight(13, 14, 4); roads.push_back(r);
	r.setSrcDstWeight(13, 12, 5); roads.push_back(r);
	r.setSrcDstWeight(13, 9, 3); roads.push_back(r);
	r.setSrcDstWeight(14, 15, 3); roads.push_back(r);
	r.setSrcDstWeight(14, 13, 4); roads.push_back(r);
	r.setSrcDstWeight(15, 14, 3); roads.push_back(r);
	r.setSrcDstWeight(15, 11, 3); roads.push_back(r);

	// construct graph
	Graph<int> graph(roads);

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