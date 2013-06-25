/*
 * node.h
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

#include "point.h"

class node {
public:
	node();
	node(const node& n);
	virtual ~node();

	void print();

	vector<int> list_neighbors;
	vector<bool> adj_neighbors;
	double weight;
	point location;
	int id;

};

#endif /* NODE_H_ */