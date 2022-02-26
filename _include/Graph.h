#ifndef _GRAPH
#define _GRAPH

#include <iostream>
#include <vector>
#include <algorithm>
#include "Edge.h"
#include "Node.h"
using namespace std;

const int inf = 1000;
const int no_nodes = 16;

template<class V>
class Graph
{
	vector<Node<V>*> adjListV;			//vector of Nodes
										
	int adj_matrix[no_nodes][no_nodes];	//2D mapping of congestion at intersections
public:
	//Constructor (populates graph)
	Graph(vector<Edge<V>> const &edges);
	void calculateSP(const V&, const V&);
	int findSmallestUnvisitedNode(bool[], int[]);
	void printAdjList() const;
	void printAdjMatrix() const;
};

//constructor
template<class V>
Graph<V>::Graph(vector<Edge<V>> const &edges) {
	// add edges to the directed graph
	for (auto &edge : edges)
	{
		bool nodeExists = false;
		V src = edge.getSrc();
		V dest = edge.getDst();
		int weight = edge.getWeight();
		cout << "adding: " << src << "----w(" << weight << ")----" << dest << endl;
		

		if (!adjListV.empty()) {
			for (Node<V> *node : adjListV) {		//for every Node in the adjacency list
				if (src == node->getNodeValue()) {
					nodeExists = true;				//if Node already exists, assign "true" and break
					break;							
				}
			}
		}

		cout << src << (nodeExists ? " exists" : " does not exist") << endl;

		if (nodeExists) {
			//node at the end of list connected to vector |  Node  |->... |  Node  |->nullptr
			Node<V> *curr = adjListV.at(src);			//if the src value already exists in the adj list,
														//advance through the LL at src and place
														//a new Node at the end with dest, weight
			while (curr->getNextNode() != nullptr)
				curr = curr->getNextNode();

			curr->setNextNode(new Node<V>(dest, weight));	
			cout << "--> "<< dest << " added." << endl;
		}
		else {
			//add node to vector |  Node  |->nullptr
			adjListV.push_back(new Node<V>(src));			//create new Node in the adjacency list
															//if src value doesn't already exist
															
			//add associated destination to the node |  Node  |->|  Node  |->nullptr
			Node<V> *curr = adjListV.at(src);
			curr->setNextNode(new Node<V>(dest, weight));	//here, edgeWeight is used for Node weight
			cout << "new node and destination added." << endl;
		}
	}
}

template<class V>
void Graph<V>::calculateSP(const V& u, const V& w) {

	bool visited[no_nodes];		//array of boolean values... visited or not
	int distance[no_nodes];		//array of distances, which are weights in this case

	//init adj_matrix, adj = 0, all others at inf
	for (int i = 0; i < no_nodes; i++)
		for (int j = 0; j < no_nodes; j++)
			if (i == j) adj_matrix[i][j] = 0;
			else adj_matrix[i][j] = inf;

	//populate adj_matrix from adjListV with weight values
	if (!adjListV.empty()) {
		for (Node<V> *node : adjListV) {	//for each Node in adjListV
			Node<V> *curr = node;

			while(curr->getNextNode() != nullptr) {		//traverse its linked list and insert weights
				adj_matrix[node->getNodeValue()][curr->getNextNode()->getNodeValue()] = 
					curr->getNextNode()->getNodeWeight();
				curr = curr->getNextNode();
			}
		}
	}

	printAdjMatrix();

	// calculate distance
																	
	for (int k = 0; k < no_nodes; k++) {							
		visited[k] = false;
		distance[k] = inf;
	}
	distance[u] = 0;												//u is starting node to find all paths from
																	//u's distance to itself = 0

	for (int count = 0; count < no_nodes; count++){					//this can be simplified to
																	//"count < no_nodes - 1" because the
																	//last iteration occurs with all members
																	//of "visited[]" as true, making the inner
																	//loop unnecessary

		int v = findSmallestUnvisitedNode(visited, distance);		//v is to be added next
		visited[v] = true;											//add v to visited nodes

		if (v == w) {
			cout << "Lowest cost path from " << u << " to " << w << ": " << distance[v] << endl;
			break;
		}

		for (int i = 0; i < no_nodes; i++){
			/*Update distance[v] if not in dest and there is a path from src to v through u that has 
			distance minimum than current value of dist[v]*/
		
			if (!visited[i] && adj_matrix[v][i] != inf && distance[v] != inf)
				if(distance[v] + adj_matrix[v][i] < distance[i])
					distance[i] = distance[v] + adj_matrix[v][i];
		}
	}
}

/*

*/
template<class V>
int Graph<V>::findSmallestUnvisitedNode(bool visited[], int distance[]) {
		int min = inf, smallest_weight_node;		//same as int min = inf; int smallest_weight_node;
		for (int i = 0; i < no_nodes; i++){
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
	for (Node<V> *node : adjListV) {
		// print all neighboring vertices of given vertex
		Node<V> *curr = node;
		cout << curr->getNodeValue(); //print graph node
		curr = curr->getNextNode();
		while (curr != nullptr){
			cout << " --> [" << curr->getNodeValue() << ",w(" << curr->getNodeWeight() << ")]"; //print adjacent nodes to graph node
			curr = curr->getNextNode(); //move to next adjacent node
		}
		cout << endl;
	}
}

// print adjacency matrix representation of graph
template<class V>
void Graph<V>::printAdjMatrix() const {
	cout << endl << "Adjacency matrix..." << endl;
	cout << "\t";
	for (int i = 0; i < no_nodes; i++) {		//column headings are printed (0 - 4)
		cout << i << "\t";
	}
	cout << endl;
	for (int i = 0; i < no_nodes; i++) {
		cout << i << "\t";						//row headings (0 - 4)
		for (int j = 0; j < no_nodes; j++) {	//matrix values
			if (adj_matrix[i][j] == inf) cout << static_cast<unsigned char>(236) << "\t";
			else cout << adj_matrix[i][j] << "\t";
		}
		cout << endl;
	}
		
}

#endif