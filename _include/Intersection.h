#ifndef INTERSECTION_CLASS_
#define INTERSECTION_CLASS_

#include<iostream>

template<class V>
class Intersection {
    V value;
	float weight;
    Intersection<V> *next;

public:
    Intersection():value(nullptr), weight(0), next(nullptr) {};
    Intersection(V& val) :value(val), weight(0), next(nullptr) {};
    Intersection(V& val, float W):value(val), weight(W), next(nullptr) {};
    Intersection(V& val, float W, Intersection<V> *nextIntersection):value(val), weight(W), next(nextIntersection) {};
    
    Intersection<V>* getNextIntersection() const;
    void setNextIntersection(Intersection<V>*);
    V getIntersectionValue() const;
    void setIntersectionValue(V);
	float getIntersectionWeight() const;
	void setIntersectionWeight(float);
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
float Intersection<V>::getIntersectionWeight() const {
	return weight;
}

template<class V>
void Intersection<V>::setIntersectionWeight(float val) {
	weight = val;
}

#endif
