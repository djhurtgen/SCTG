#ifndef _ROAD
#define _ROAD

#include <iostream>
using namespace std;

template <class V>
class Road {
	V src;
	V dst;
	//int roadWeight;
	//add...
	int no_cars;
	float no_miles;
	int avg_speed;
	//use calculateCF for roadWeight
	

public:
	Road() {
		src = 0;
		dst = 0;
		no_cars = 0;
		no_miles = 0;
		avg_speed = 0;
	}

	Road(const V& s, const V& d) {
		src = s;
		dst = d;
		no_cars = 0;
		no_miles = 0;
		avg_speed = 0;
	}

	Road(const V& s, const V& d, const int& c, const int& m, const int& v) {
		src = s;
		dst = d;
		no_cars = c;
		no_miles = m;
		avg_speed = v;
	}

	void setSrcDst(const V& s, const V& d) {
		src = s;
		dst = d;
	}
	
	void setAllParameters(const V& s, const V& d, const int& c, const int& m, const int& v) {
		src = s;
		dst = d;
		no_cars = c;
		no_miles = m;
		avg_speed = v;
	}

	V getSrc() const {
		return src;
	}

	V getDst() const {
		return dst;
	}
	
	int getNumCars() const{
		return no_cars;
	}
	
	float getNumMiles() const{
		return no_miles;
	}

	int getAvgSpeed() const{
		return avg_speed;
	}
};

#endif