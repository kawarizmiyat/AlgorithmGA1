/*
 * element.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */

#include "element.h"
#include <stdio.h>

element::element() {
	this->covered = false;
	this->max = 0;
	this->id = -1;
}

element::~element() {
}

void element::add_covering_node(point& p) {
	v.push_back(p.id);
	points.push_back(p);

	id = p.id;
	if (id > max) {
		max = id;
	}
}

bool element::get_covered() {
	return this->covered;
}

void element::set_covered(bool& c) {
	this->covered = c;
}

char* element::to_string() {
	if (covered) {
		return "1";
	}

	return "0";
}

void element::print() {
	printf("%d: [", this->id);
	for (int i = 0; i < v.size(); i++) {
		printf("%d ", this->v.at(i));
	}
	printf("]");
}

bool element::operator ==(const element& input) const {
	if (input.v.size() != this->v.size()) { return false; }

	// we can eliminate this btw: (but we make sure it is sorted)
	// sort(input.v.begin(), input.v.end());
	// sort(this->v.begin(), this->v.end());

	for (int i = 0; i < input.v.size(); i++) {
		if (input.v.at(i) != this->v.at(i)) { return false; }
	}

	return true;
}

bool element::operator <(const element& input) const {
	if (v.size() < input.v.size()) { return true; }
	if (v.size() == input.v.size()) {

		for (int i = 0; i < v.size(); i++) { 
			if (v.at(i) < input.v.at(i)) { return true; }
			if (v.at(i) > input.v.at(i)) { return false; }
		}

	}

	return false;
}
