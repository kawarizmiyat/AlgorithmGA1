/*
 * point.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */


#include <stdio.h>
#include <math.h>

#include "point.h"

point::point() {
	x = -1; y = -1;
	id = -1;
}

point::point(const point& p) {
	this->x = p.x;
	this->y = p.y;
	this->id = p.id;
}

point::~point() {
	// TODO Auto-generated destructor stub
}

char* point::to_string() {

	sprintf(output, "%d (%2.2f:%2.2f)", this->id, this->x, this->y);
	return output;
}


double point::distance(const point& p) {
	double dx_2 = (this->x - p.x) * (this->x - p.x);
	double dy_2 = (this->y - p.y) * (this->y - p.y);
	return sqrt(dx_2 + dy_2);
}
