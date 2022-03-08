//adapted from: https://www.techiedelight.com/graph-implementation-using-stl/
//and https://www.includehelp.com/cpp-tutorial/dijkstras-algorithm.aspx

#include <iostream>
#include <vector>
#include "../_include/Road.h"
#include "../_include/Graph.h"
#include <chrono>
using namespace std;
using namespace chrono;

// Graph Implementation using STL
int main()
{
	// time the entire operation
	auto start = high_resolution_clock::now();

	vector<Road<int>> roads;
	Road<int> r;
	r.setSrcDstWeight(0, 1, 200, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(0, 4, 350, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(1, 0, 200, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(1, 2, 150, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(2, 1, 150, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(2, 3, 100, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(2, 6, 200, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(3, 2, 100, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(4, 5, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(4, 8, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(5, 6, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(5, 4, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(5, 1, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(6, 7, 200, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(6, 5, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(6, 10, 150, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(7, 6, 200, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(7, 3, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(8, 9, 350, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(8, 12, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(9, 8, 350, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(9, 10, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(9, 5, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(10, 9, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(10, 11, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(10, 14, 100, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(11, 10, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(11, 7, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(12, 13, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(13, 14,250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(13, 12, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(13, 9, 300, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(14, 15, 200, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(14, 13, 250, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(15, 14, 200, 1, 10); roads.push_back(r);
	r.setSrcDstWeight(15, 11, 200, 1, 10); roads.push_back(r);

	// construct graph
	Graph<int> graph(roads);

	// print adjacency list representation of graph
	graph.printAdjList();
	
	// calculate shortest path from node s=0 to node t=10 
	graph.calculateSP(1, 12);
	
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Time for operation: " << duration.count() << " milliseconds" << endl;


	system("pause");
	return 0;
}