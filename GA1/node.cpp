/*
 * node.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */


#include <stdio.h>

#include "node.h"



node::node() {

}

node::node(const node& n) {
	this->adj_neighbors = n.adj_neighbors;
	this->list_neighbors = n.list_neighbors;
	this->location = n.location;
	this->weight = n.weight;
	this->id = n.id;
}

node::~node() {}

void node::print() {
	printf("%d:[", this->id);
	for (unsigned int i = 0; i < this->list_neighbors.size(); i++) {
		printf("%d", this->list_neighbors.at(i));
		if (i < this->list_neighbors.size() - 1) { printf(","); }
	}
	printf("]");
}
