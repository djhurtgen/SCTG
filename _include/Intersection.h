#ifndef INTERSECTION_CLASS_
#define INTERSECTION_CLASS_

#include<iostream>

template<class V>
class Intersection {
    V value;
	int weight;
    Intersection<V> *next;

public:
    Intersection():value(nullptr), weight(0), next(nullptr) {};
    Intersection(V& val) :value(val), weight(0), next(nullptr) {};
    Intersection(V& val, int W):value(val), weight(W), next(nullptr) {};
    Intersection(V& val, int W, Intersection<V> *nextIntersection):
        value(val), weight(W), next(nextIntersection) {};
    

    Intersection<V>* getNextIntersection() const;
    void setNextIntersection(Intersection<V>*);
    V getIntersectionValue() const;
    void setIntersectionValue(V);
	V getIntersectionWeight() const;
	void setIntersectionWeight(int);
};

template<class V>
Intersection<V>* Intersection<V>::getNextIntersection() const{
    return next;
}

template<class V>
void Intersection<V>::setNextIntersection(Intersection<V>* nextIntersection){
    next = nextIntersection;
}

template<class V>
V Intersection<V>::getIntersectionValue() const{
    return value;
}

template<class V>
void Intersection<V>::setIntersectionValue(V val){
    value = val;
}

template<class V>
V Intersection<V>::getIntersectionWeight() const {
	return weight;
}

template<class V>
void Intersection<V>::setIntersectionWeight(int val) {
	weight = val;
}

#endif
