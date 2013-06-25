/*
 * graph.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */

#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;


#include "graph.h"


graph::graph() {
	nodes_range = DEFAULT_RANGE;
}

graph::graph(const graph& g) {
	this->nodes = g.nodes;
	this->nodes_range = g.nodes_range;
}

graph::~graph() {

}

void graph::print() {
	printf("at %s \n", __FUNCTION__);

	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		nodes.at(i).print();
		printf("\n");
	}
}

void graph::create_graph(vector<point>& points) {
	create_graph(points, NULL);
}

void graph::create_graph(vector<point>& points, vector<int>* ids) {

	printf("at %s with %d points (range: %f) \n", __FUNCTION__, points.size(),
			this->nodes_range);

	bool there_is_ids = true;
	if (! ids) { there_is_ids = false; }

	if (there_is_ids) {
		if (ids->size() != points.size()) {
			there_is_ids = false;
		}
	}

	int graph_size = points.size();
	node n;
	for (int i = 0; i < graph_size; i++) {
		n.adj_neighbors.resize(graph_size, false);
		n.location = points.at(i);
		n.weight = 0;

		if (there_is_ids) {
			n.id = ids->at(i);
		} else {
			n.id = i;
		}

		this->nodes.push_back(n);
	}


	interconnect_nodes();

}


graph graph::induce_graph(vector<int> ids) {


	// the easy way:
	// 1. find indices and create graph ... it could be cheaper
	// on average [need to verify this though].
	int index;
	vector<int> indices;
	for (unsigned int i = 0; i < ids.size(); i ++) {
		index = find_index(ids.at(i));
		if (index > -1) {
			indices.push_back(index);
		}
	}

	vector<point> points;
	for (unsigned int i = 0; i < indices.size(); i++) {
		points.push_back(this->nodes.at(indices.at(i)).location);
	}

	graph g;
	g.nodes_range = this->nodes_range;
	g.create_graph(points, &ids);
	return g;

}

int graph::find_index(int id) {
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		if (nodes.at(i).id == id) { return i; }
	}
	return -1;
}

void graph::interconnect_nodes() {

	printf("at %s \n", __FUNCTION__);

	int i_id, j_id;

	for (unsigned int i = 0; i < nodes.size(); i++) {

		i_id = nodes.at(i).id;

		for (unsigned int j = i+1; j < nodes.size(); j++) {
			j_id = nodes.at(j).id;

			double dist = nodes.at(i).location.distance(nodes.at(j).location);
			printf("comparing node %d with node %d dist: %f \n", i_id, j_id, dist);

			if (dist <= this->nodes_range) {
				nodes.at(i).list_neighbors.push_back(j_id);
				nodes.at(j).list_neighbors.push_back(i_id);

				nodes.at(i).adj_neighbors.at(j) = true;
				nodes.at(j).adj_neighbors.at(i) = true;
			}
		}

	}
}


void graph::calculate_weight_nr() {
	vector<node>::iterator it = this->nodes.begin();
	while (it != this->nodes.end()) {
		it->weight = it->list_neighbors.size();

		printf("weight of %d is set to %f \n", it->id, it->weight);

		it ++;
	}
}

vector<int> graph::maximal_set() {

	printf("at %s \n", __FUNCTION__);


	this->sort_by_weight();
	vector<int> mis, visited;
	vector<int>::iterator it_visited;
	int v;


	vector<node>::iterator it = this->nodes.begin();
	while (it != this->nodes.end()) {


		v = it->id;
		printf("v: %d \n", v);

		if (! this->is_in(visited, v)) {

			printf("v(%d) is not in visited \n", v);

			// adding
			mis.push_back(v);

			visited.push_back(v);
			for (unsigned int i  = 0; i < it->list_neighbors.size(); i++) {
				visited.push_back(it->list_neighbors.at(i));
			}

			// remove redundancies from to_remove
			sort(visited.begin(), visited.end());
			it_visited = unique(visited.begin(), visited.end());
			visited.resize(distance(visited.begin(), it_visited));
		}

		it ++;
	}


	return mis;
}

bool graph::is_in(vector<int> list, int id) {
	for (unsigned int i = 0; i < list.size(); i++) {
		if (list.at(i) == id)  return true;
	}
	return false;
}

void graph::sort_by_weight() {

	sort(this->nodes.begin(), this->nodes.end(), weight_compare);
	reverse(this->nodes.begin(), this->nodes.end());

}

bool weight_compare(node i, node j) { return (i.weight < j.weight); }
bool point_y_compare(node i, node j) { 	return (i.location.y < j.location.y); }
