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
	this->tag_neighbors = n.tag_neighbors;
	this->active_tag_neighbors = n.active_tag_neighbors;
	// TODO:revision
	this->active_list_neighbors = n.active_list_neighbors;
	this->location = n.location;
	this->weight = n.weight;
	this->id = n.id;
}

node::~node() {}

void node::print() {
	printf("id:%d: n[", this->id);
	for (unsigned int i = 0; i < this->list_neighbors.size(); i++) {
		printf("%d", this->list_neighbors.at(i));
		if (i < this->list_neighbors.size() - 1) { printf(","); }
	}
	printf("] w: %2.2f t:[", this->weight);
	for (unsigned int i = 0; i < this->active_tag_neighbors.size(); i++) {
		printf("%d", this->active_tag_neighbors.at(i));
		if (i < this->active_tag_neighbors.size() - 1) { printf(","); }
	}
	printf("]");

}

char* node::to_string() {
	sprintf(output, "%d (%2.2f:%2.2f)", this->id, this->location.x, this->location.y);
	return output;

}
