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

bool adjIntersectionsRemain;
int leastWeightIntersection = 0;

template<class V>
class Graph
{
	vector<Intersection<V>*> adjListV;			//vector of Nodes
	V begin = 0;
	Intersection<V> *pathToDest = new Intersection<V>(begin);				

public:
	//Constructor (populates graph)
	Graph(vector<Road<V>> const &roads);
	void calculateSP(const V&, const V&);
	void printAdjList() const;
	void insertDummyIntersection(const int&);
	int getSmallestAdjWeightValue(int) const;
	int getSmallestAdjWeight(int) const;
	void addToPath(const int&);
	int goBack();
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
	

	for (int k = 0; k < no_intersections; k++) {
		visited[k] = false;
		distance[k] = inf;
	}

	visited[s] = true;
	distance[s] = 0;
	
	leastWeightIntersection = s;
	Intersection<V>* root = pathToDest;
	V begin = s;
	root->setIntersectionValue(begin);
	cout << "First intersection added to path." << endl;
	
	for (int i = 0; i < no_intersections; i++) {
		insertDummyIntersection(i);
	}
	

	while (leastWeightIntersection != t) {
		int marked = inf;
		
		adjIntersectionsRemain = true;
		while (adjIntersectionsRemain) {
			//1st helper function returns smallestAdjWeight node value w/ leastWeightIntersection as parameter
			int smallestAdjWeightValue = getSmallestAdjWeightValue(leastWeightIntersection);
			cout << "Smallest weight intersection is: " << smallestAdjWeightValue << endl;
			//2nd helper function returns smallestAdjWeight w/ leastWeightIntersection as parameter
			int smallestAdjWeight = getSmallestAdjWeight(leastWeightIntersection);
			cout << "Smallest weight is: " << smallestAdjWeight << endl;
			//place weight in distance[] if less than current
			if ((distance[leastWeightIntersection] + smallestAdjWeight < distance[smallestAdjWeightValue]) 
				&& (visited[smallestAdjWeightValue] == false))
				distance[smallestAdjWeightValue] = distance[leastWeightIntersection] + smallestAdjWeight;
			if ((distance[smallestAdjWeightValue] < marked) && (visited[smallestAdjWeightValue] == false))
				marked = smallestAdjWeightValue;
		}
		
		//if there are no unvisited intersections from the current intersection, go back
		if (marked == inf) {
			marked = goBack();
			//mark the current intersection as visited
			visited[leastWeightIntersection] = true;
			cout << "Going back" << endl;
		}
		cout << "Marked is: " << marked << endl;

		//update leastWeightIntersection here from marked
		if (visited[marked] == false) {
			visited[marked] = true;
			leastWeightIntersection = marked;
			addToPath(marked);
		}

		else
			leastWeightIntersection = marked;

		cout << leastWeightIntersection << " is the new least weight intersection." << endl;
	}
	cout << "Lowest cost path from " << s << " to " << t << ": " << distance[leastWeightIntersection] << endl;
}


template<class V>
void Graph<V>::insertDummyIntersection(const int &head) {
	V dummy = inf;
	Intersection<V>* curr = adjListV.at(head);
	while (curr->getNextIntersection() != nullptr)
		curr = curr->getNextIntersection();
	curr->setNextIntersection(new Intersection<V>(dummy));
}


template<class V>
int Graph<V>::getSmallestAdjWeightValue(int lwi) const {
	Intersection<V>* root = adjListV.at(lwi);
	Intersection<V>* curr = root->getNextIntersection();
	int result = curr->getIntersectionValue();
	return result;
}


template<class V>
int Graph<V>::getSmallestAdjWeight(int lwi) const {
	Intersection<V>* root = adjListV.at(lwi);
	Intersection<V>* curr = root;
	Intersection<V>* temp = root->getNextIntersection();

	int result = temp->getIntersectionWeight();
	
	while (curr->getNextIntersection() != nullptr)
		curr = curr->getNextIntersection();
	root->setNextIntersection(temp->getNextIntersection());
	curr->setNextIntersection(temp);
	temp->setNextIntersection(nullptr);

	//check for dummy node, place at end if present, change adjIntersections remain to false
	if (root->getNextIntersection()->getIntersectionValue() == inf) {
		//cout << "Hit the dummy node!" << endl;
		Intersection<V>* curr1 = root;
		Intersection<V>* temp1 = root->getNextIntersection();
		while (curr1->getNextIntersection() != nullptr)
			curr1 = curr1->getNextIntersection();
		root->setNextIntersection(temp1->getNextIntersection());
		curr1->setNextIntersection(temp1);
		temp1->setNextIntersection(nullptr);
		adjIntersectionsRemain = false;
	}
	return result;
}


template<class V>
void Graph<V>::addToPath(const int &mrkd) {
	V toPath = mrkd;
	Intersection<V>* root = pathToDest;
	Intersection<V>* curr = root;
	while (curr->getNextIntersection() != nullptr)
		curr->getNextIntersection();
	curr->setNextIntersection(new Intersection<V>(toPath));
	cout << toPath << " added to path" << endl;
}


template<class V>
int Graph<V>::goBack() {
	Intersection<V>* curr = pathToDest;
	while (curr->getNextIntersection()->getNextIntersection() != nullptr)
		curr->getNextIntersection();
	int result = curr->getIntersectionValue();
	Intersection<V>* temp = curr->getNextIntersection();
	curr->setNextIntersection(nullptr);
	delete temp;
	return result;
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