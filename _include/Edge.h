#ifndef _EDGE
#define _EDGE

#include <iostream>
using namespace std;

template <class V>
class Edge {
	V src;
	V dst;
	int edgeWeight;
	

public:
	Edge() {
		src = 0;
		dst = 0;
		edgeWeight = 0;
	}

	Edge(const V& s, const V& d) {
		src = s;
		dst = d;
		edgeWeight = 0;
	}

	Edge(const V& s, const V& d, const int& w) {
		src = s;
		dst = d;
		edgeWeight = w;
	}

	void setSrcDst(const V& s, const V& d) {
		src = s;
		dst = d;
	}
	void setSrcDstWeight(const V& s, const V& d, const int& w) {
		src = s;
		dst = d;
		edgeWeight = w;
	}

	void setWeight(const V& w) {
		edgeWeight = w;
	}

	V getSrc() const {
		return src;
	}

	V getDst() const {
		return dst;
	}
	
	int getWeight() const {
		return edgeWeight;
	}

};

#endif