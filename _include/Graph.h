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
	bool adjIntersectionsRemain;

public:
	//Constructor (populates graph)
	Graph(vector<Road<V>> const &roads);
	void calculateSP(const V&, const V&);
	void printAdjList() const;
	int getNextAdjWeightValue(int) const;
	int getNextAdjWeight(int);
	int findLeastCongestedIntersection(bool[], int[]);
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

	bool visited[no_intersections];			//array of boolean values... visited or not
	int distance[no_intersections];			//array of distances, which are weights in this case
	int leastWeightIntersection;
	vector<int> pathToDest[no_intersections];	//array of vectors for various paths

	for (int i = 0; i < no_intersections; i++) {
		pathToDest[i].push_back(i);
	}

	for (int j = 0; j < no_intersections; j++) {
		visited[j] = false;
		distance[j] = inf;
	}

	visited[s] = true;
	distance[s] = 0;
	
	leastWeightIntersection = s;
	cout << "First intersection added to path." << endl;

	while (leastWeightIntersection != t) {
		int marked = inf;

		adjIntersectionsRemain = true;
		while (adjIntersectionsRemain) {
			//1st helper function returns smallestAdjWeight node value w/ leastWeightIntersection as parameter
			int nextAdjWeightValue = getNextAdjWeightValue(leastWeightIntersection);
			cout << "Next intersection is: " << nextAdjWeightValue << endl;
			//2nd helper function returns smallestAdjWeight w/ leastWeightIntersection as parameter
			int nextAdjWeight = getNextAdjWeight(leastWeightIntersection);
			cout << "Weight is: " << nextAdjWeight << endl;
			//place weight in distance[] if less than current
			if ((distance[leastWeightIntersection] + nextAdjWeight < distance[nextAdjWeightValue])
				&& (visited[nextAdjWeightValue] == false)) {
				distance[nextAdjWeightValue] = distance[leastWeightIntersection] + nextAdjWeight;
				//update path
				pathToDest[nextAdjWeightValue] = pathToDest[leastWeightIntersection];
				pathToDest[nextAdjWeightValue].push_back(nextAdjWeightValue);
			}
			//mark least congested unvisited intersection in distance[]
			marked = findLeastCongestedIntersection(visited, distance);
			
		}
		
		cout << "Marked is: " << marked << endl;
		
		visited[marked] = true;
		leastWeightIntersection = marked;
		cout << leastWeightIntersection << " is the new least weight intersection." << endl;
	}
	cout << "Lowest cost path from " << s << " to " << t << ": " << distance[t] << endl;
	
	cout << "Path is ";
	
	for (int j = 0; j < pathToDest[t].size(); j++) {
		cout << " --> " << pathToDest[t][j];
	}
			
	cout << endl;
}


template<class V>
int Graph<V>::getNextAdjWeightValue(int lwi) const {
	Intersection<V>* root = adjListV.at(lwi);
	Intersection<V>* curr = root->getNextIntersection();
	int result = curr->getIntersectionValue();
	return result;
}


template<class V>
int Graph<V>::getNextAdjWeight(int lwi) {
	Intersection<V>* root = adjListV.at(lwi);
	Intersection<V>* temp = root->getNextIntersection();
	Intersection<V>* curr = temp->getNextIntersection();

	int result = temp->getIntersectionWeight();
	
	root->setNextIntersection(curr);
	delete temp;
	
	if (curr == nullptr) adjIntersectionsRemain = false;

	return result;
}


template<class V>
int Graph<V>::findLeastCongestedIntersection(bool visited[], int distance[]) {
	int min = inf, least_congested_intersection;
	for (int i = 0; i < no_intersections; i++) {
		if (!visited[i] && distance[i] <= min) {
			min = distance[i];
			least_congested_intersection = i;
		}
	}
	return least_congested_intersection;
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
#endif