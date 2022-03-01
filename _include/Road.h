#ifndef _ROAD
#define _ROAD

#include <iostream>
using namespace std;

template <class V>
class Road {
	V src;
	V dst;
	int roadWeight;
	//add...
	//int no_cars
	//float no_miles
	//int avg_speed
	//use calculateCF for roadWeight
	

public:
	Road() {
		src = 0;
		dst = 0;
		roadWeight = 0;
	}

	Road(const V& s, const V& d) {
		src = s;
		dst = d;
		roadWeight = 0;
	}

	Road(const V& s, const V& d, const int& w) {
		src = s;
		dst = d;
		roadWeight = w;
	}

	void setSrcDst(const V& s, const V& d) {
		src = s;
		dst = d;
	}
	void setSrcDstWeight(const V& s, const V& d, const int& w) {
		src = s;
		dst = d;
		roadWeight = w;
	}

	void setWeight(const V& w) {
		roadWeight = w;
	}

	V getSrc() const {
		return src;
	}

	V getDst() const {
		return dst;
	}
	
	int getWeight() const {
		return roadWeight;
	}

	float calculateCF(const int& no_cars, const float& miles, const int& avg_speed) {
		float cf;
		cf = (no_cars / 352 * miles) / avg_speed;
		return cf;
	}

};

#endif