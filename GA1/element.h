/*
 * element.h
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <vector>
using namespace std;


#include "point.h"
#include "node.h"

class element {
public:
	element();
	virtual ~element();

	// additional functions:
	void add_covering_node(node& p);
	void set_covered(bool& c);
	bool get_covered();
	char* to_string();
	void print();

	bool operator==(const element& input) const;
	bool operator<(const element& input) const;


	// variables:
	vector<int> v;
	vector<point> points;
	bool covered;
	int max;
	int id;


};

#endif /* ELEMENT_H_ */
