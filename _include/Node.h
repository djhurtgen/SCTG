#ifndef NODE_CLASS_
#define NODE_CLASS_

#include<iostream>

template<class V>
class Node {
    V value;
	int weight;
    Node<V> *next;
public:
    Node():value(nullptr), weight(0), next(nullptr){};
	Node(V& val) :value(val), weight(0), next(nullptr) {};
	Node(V& val, int W):value(val), weight(W), next(nullptr){};
    Node(V& val, int W, Node<V> *nextNode):value(val), weight(W), next(nextNode){};
    
    Node<V>* getNextNode() const;
    void setNextNode(Node<V>*);
    V getNodeValue() const;
    void setNodeValue(V);
	V getNodeWeight() const;
	void setNodeWeight(int);
};

template<class V>
Node<V>* Node<V>::getNextNode() const{
    return next;
}

template<class V>
void Node<V>::setNextNode(Node<V>* nextNode){
    next = nextNode;
}

template<class V>
V Node<V>::getNodeValue() const{
    return value;
}

template<class V>
void Node<V>::setNodeValue(V val){
    value = val;
}

template<class V>
V Node<V>::getNodeWeight() const {
	return weight;
}

template<class V>
void Node<V>::setNodeWeight(int val) {
	weight = val;
}

#endif
