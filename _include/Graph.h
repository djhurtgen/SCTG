#ifndef _GRAPH
#define _GRAPH

#include <iostream>
#include <vector>
#include <algorithm>
#include "Road.h"
#include "Intersection.h"
using namespace std;

const int inf = 1000;
const int no_intersections = 16;

template<class V>
class Graph
{
	vector<Intersection<V>*> adjListV;			//vector of Nodes									
	int adj_matrix[no_intersections][no_intersections];	//2D mapping of congestion at intersections

public:
	//Constructor (populates graph)
	Graph(vector<Road<V>> const &roads);
	int findLeastCongestedIntersection(bool[], int[]);
	void calculateSP(const V&, const V&);
	void printAdjList() const;
	void printAdjMatrix() const;
};


//constructor
template<class V>
Graph<V>::Graph(vector<Road<V>> const &roads) {
	// add edges to the directed graph
	for (auto &road : roads)
	{
		bool nodeExists = false;
		V src = road.getSrc();
		V dest = road.getDst();
		int weight = road.getWeight();
		cout << "adding: " << src << "----w(" << weight << ")----" << dest << endl;
		

		if (!adjListV.empty()) {
			for (Intersection<V> *node : adjListV) {		//for every Node in the adjacency list
				if (src == node->getIntersectionValue()) {
					nodeExists = true;				//if Node already exists, assign "true" and break
					break;							
				}
			}
		}

		cout << src << (nodeExists ? " exists" : " does not exist") << endl;

		//modify this to create priority queue
		if (nodeExists) {
			Intersection<V> *curr = adjListV.at(src);
			//if node has lower weight than first node in the LL
			if (weight < curr->getIntersectionWeight())
				Intersection<V>* temp = new Intersection<V>(dest, weight, curr);

			//otherwise, advance until spot is found
			else {
				while (curr->getNextIntersection() != nullptr) {
					if (curr->getNextIntersection()->getIntersectionWeight() > weight)
						break;
					else
						curr = curr->getNextIntersection();
				}
				Intersection<V>* temp = new Intersection<V>(dest, weight, curr->getNextIntersection());
				curr->setNextIntersection(temp);
			}
		}
		else {
			//if first node
			adjListV.push_back(new Intersection<V>(src));
			Intersection<V> *curr = adjListV.at(src);
			curr->setNextIntersection(new Intersection<V>(dest, weight));
			cout << "new node and destination added." << endl;
		}
	}
}


template<class V>
void Graph<V>::calculateSP(const V& s, const V& t) {

	bool visited[no_intersections];		//array of boolean values... visited or not
	int distance[no_intersections];		//array of distances, which are weights in this case

	//init adj_matrix, adj = 0, all others at inf
	for (int i = 0; i < no_intersections; i++)
		for (int j = 0; j < no_intersections; j++)
			if (i == j) adj_matrix[i][j] = 0;
			else adj_matrix[i][j] = inf;

	//populate adj_matrix from adjListV with weight values
	if (!adjListV.empty()) {
		for (Intersection<V> *node : adjListV) {	//for each Node in adjListV
			Intersection<V> *curr = node;

			while(curr->getNextIntersection() != nullptr) {		//traverse its linked list and insert weights
				adj_matrix[node->getIntersectionValue()][curr->getNextIntersection()->getIntersectionValue()] =
					curr->getNextIntersection()->getIntersectionWeight();
				curr = curr->getNextIntersection();
			}
		}
	}

	printAdjMatrix();

	// calculate distance
																	
	for (int k = 0; k < no_intersections; k++) {
		visited[k] = false;
		distance[k] = inf;
	}

	distance[s] = 0;

	for (int count = 0; count < no_intersections; count++){

		int v = findLeastCongestedIntersection(visited, distance);		//v is to be added next
		visited[v] = true;											//add v to visited nodes

		if (v == t) {
			cout << "Lowest cost path from " << s << " to " << t << ": " << distance[v] << endl;
			break;
		}

		for (int i = 0; i < no_intersections; i++){
			if (!visited[i] && adj_matrix[v][i] != inf && distance[v] != inf)
				if(distance[v] + adj_matrix[v][i] < distance[i])
					distance[i] = distance[v] + adj_matrix[v][i];
		}
	}
}


template<class V>
int Graph<V>::findLeastCongestedIntersection(bool visited[], int distance[]) {
		int min = inf, smallest_weight_node;		//same as int min = inf; int smallest_weight_node;
		for (int i = 0; i < no_intersections; i++){
			if (!visited[i] && distance[i] <= min){
				min = distance[i];
				smallest_weight_node = i;
			}
		}
		return smallest_weight_node;
}


// print adjacency list representation of graph
template<class V>
void Graph<V>::printAdjList() const {
	cout << endl << "Adjacency list..." << endl;
	for (Intersection<V> *node : adjListV) {
		// print all neighboring vertices of given vertex
		Intersection<V> *curr = node;
		cout << curr->getIntersectionValue(); //print graph node
		curr = curr->getNextIntersection();
		while (curr != nullptr){
			cout << " --> [" << curr->getIntersectionValue() << ",w(" << curr->getIntersectionWeight() << ")]"; //print adjacent nodes to graph node
			curr = curr->getNextIntersection(); //move to next adjacent node
		}
		cout << endl;
	}
}


// print adjacency matrix representation of graph
template<class V>
void Graph<V>::printAdjMatrix() const {
	cout << endl << "Adjacency matrix..." << endl;
	cout << "\t";
	for (int i = 0; i < no_intersections; i++) {		//column headings are printed (0 - 4)
		cout << i << "\t";
	}
	cout << endl;
	for (int i = 0; i < no_intersections; i++) {
		cout << i << "\t";						//row headings (0 - 4)
		for (int j = 0; j < no_intersections; j++) {	//matrix values
			if (adj_matrix[i][j] == inf) cout << static_cast<unsigned char>(236) << "\t";
			else cout << adj_matrix[i][j] << "\t";
		}
		cout << endl;
	}		
}

#endif