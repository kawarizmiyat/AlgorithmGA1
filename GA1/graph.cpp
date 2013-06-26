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
#include "range.h"


graph::graph() {
	nodes_range = DEFAULT_NODE_RANGE;
	interrogation_range = DEFAULT_INT_RANGE;
}

graph::graph(const graph& g) {
	this->nodes = g.nodes;
	this->nodes_range = g.nodes_range;
	this->tags = g.tags;
	this->active_tags = g.active_tags;
}

graph::~graph() {

}

void graph::print() {

	printf("graph -->");
	printf("active tags:");
	for (unsigned int i = 0; i < this->active_tags.size(); i++)
		printf("%d ", this->active_tags[i]);
	printf("\n");

	printf("tags:");
	for (unsigned int i = 0; i < this->tags.size(); i++)
		printf("%d ", this->tags[i]);
	printf("\n");


	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		nodes.at(i).print();
		printf("\n");
	}
}

void graph::create_graph(vector<point>& points) {
	create_graph(points, NULL);
}

void graph::create_graph(vector<point>& points, vector<int>* ids) {

	// printf("at %s with %d points (range: %f) \n", __FUNCTION__, points.size(),
	//		this->nodes_range);

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

graph graph::deactivate_nodes(vector<int>& to_remove_ids) {

	vector<int> all_ids;
	vector<int> induced_ids;
	vector<int> induced_indices;
	vector<point> points;
	vector<int>::iterator it;

	for (unsigned int i = 0; i < nodes.size(); i++) {
		all_ids.push_back(nodes.at(i).id);
	}

	induced_ids.resize(all_ids.size());

	it = set_difference(all_ids.begin(), all_ids.end(),
			to_remove_ids.begin(), to_remove_ids.end(), induced_ids.begin());

	induced_ids.resize(distance(induced_ids.begin(), it));

	return this->induce_graph(induced_ids);

/*
	induced_indices = find_indices(induced_ids);

	for (unsigned int i = 0; i < induced_indices.size(); i++) {
		points.push_back(nodes[induced_indices[i]].location);
	}

	this->create_graph(points, induced_ids);
*/

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
	vector<double> weights;
	vector<vector<int> > active_tags;
	vector<vector<int> > tags;

	for (unsigned int i = 0; i < indices.size(); i++) {
		points.push_back(this->nodes.at(indices.at(i)).location);
		weights.push_back(this->nodes.at(indices.at(i)).weight);
		active_tags.push_back(this->nodes.at(indices.at(i)).active_tag_neighbors);
		tags.push_back(this->nodes.at(indices.at(i)).tag_neighbors);
	}

	graph g;
	g.tags = this->tags;
	g.active_tags = this->active_tags;
	g.nodes_range = this->nodes_range;
	g.create_graph(points, &ids);


	// copying the weights, active_tags, active_neighbors;
	for (unsigned int j = 0; j < ids.size(); j++) {
		for (unsigned int i = 0; i < g.nodes.size(); i++) {
			if (g.nodes.at(i).id == ids.at(j)) {
				g.nodes.at(i).weight = weights.at(j);
				g.nodes.at(i).active_tag_neighbors = active_tags.at(j);
				g.nodes.at(i).tag_neighbors = tags.at(j);
			}
		}
	}

	return g;

}


void graph::deactivate_tags(vector<int>& list) {

	sort(list.begin(), list.end());
	vector<int>* t_list = 0;
	vector<int> intersection_result;
	vector<int>::iterator it;

	for (unsigned int i = 0; i < nodes.size(); i++) {

		t_list = &(nodes.at(i).active_tag_neighbors);
		intersection_result.clear();
		intersection_result.resize(t_list->size());


		// maybe unnecessary -- snce they are already sorted.
		// sort(t_list->begin(), t_list->end());
			it = set_difference(
					t_list->begin(), t_list->end(),
					list.begin(), list.end(),
					intersection_result.begin());

			intersection_result.resize(distance(intersection_result.begin(), it));

			*(t_list) = intersection_result;
			nodes.at(i).weight = intersection_result.size();

#if 0
		printf("new active tags of %d \n", nodes.at(i).id);
		for (unsigned int c = 0; c < t_list->size(); c++) {
			printf("%d ", t_list->at(c));
		}
		printf("\n");
#endif

	}

	vector<int> temp_active_tags;
	temp_active_tags.resize(this->tags.size());
	it = set_difference(active_tags.begin(), active_tags.end(),
			list.begin(), list.end(), temp_active_tags.begin());
	temp_active_tags.resize(distance(temp_active_tags.begin(), it));
	active_tags = temp_active_tags;



}

/*
void graph::copy_weights(const graph& g) {

	if (g.nodes.size() != this->nodes.size()) { return; }

	for (int i = 0; i < g.nodes.size(); i++) {
		this->nodes.at(i).weight = g.nodes.at(i).weight;
	}

}
*/

int graph::find_index(int id) {
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		if (nodes.at(i).id == id) { return i; }
	}
	return -1;
}

void graph::interconnect_nodes() {

	// printf("at %s \n", __FUNCTION__);

	int i_id, j_id;

	for (unsigned int i = 0; i < nodes.size(); i++) {

		i_id = nodes.at(i).id;

		for (unsigned int j = i+1; j < nodes.size(); j++) {
			j_id = nodes.at(j).id;

			double dist = nodes.at(i).location.distance(nodes.at(j).location);
			// printf("comparing node %d with node %d dist: %f \n", i_id, j_id, dist);

			if (dist <= this->nodes_range) {
				nodes.at(i).list_neighbors.push_back(j_id);
				nodes.at(j).list_neighbors.push_back(i_id);

				nodes.at(i).adj_neighbors.at(j) = true;
				nodes.at(j).adj_neighbors.at(i) = true;
			}
		}

	}

	for (unsigned int i = 0; i < nodes.size(); i++ ) {
		sort(nodes.at(i).list_neighbors.begin(),
				nodes.at(i).list_neighbors.end());
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

void graph::calculate_weight_nt() {
	vector<node>::iterator it = this->nodes.begin();
	while (it != this->nodes.end()) {
		it->weight = it->active_tag_neighbors.size();

		printf("weight of %d is set to %f \n", it->id, it->weight);

		it ++;
	}
}

vector<int> graph::extract_active_tags(vector<int>& list) {

	vector<int>* p_list = 0;
	vector<int> indices = find_indices(list);
	vector<int> all_tags = this->nodes[indices[0]].active_tag_neighbors;
	for (unsigned int i = 1; i < indices.size(); i ++) {
		p_list = &(this->nodes[indices[i]].active_tag_neighbors);
		for (unsigned int j = 0; j < p_list->size(); j++) {
			all_tags.push_back(p_list->at(j));
		}
		sort(all_tags.begin(), all_tags.end());
		all_tags.resize(distance(all_tags.begin(),
						unique(all_tags.begin(), all_tags.end())));

	}

#if 0
	printf("the tags of the list are: \n");
	for (unsigned int i = 0; i < all_tags.size(); i++)
		printf("%d ", all_tags[i]);
	printf("\n");
#endif

	return all_tags;


}

vector<int> graph::find_indices(vector<int>& list) {
	int index;
	vector<int> indices;
	for (unsigned int i = 0; i < list.size(); i++) {
		index = this->find_index(list[i]);
		if (index == -1) {
			printf("error: index is -1 in %s \n", __FUNCTION__);
		} else {
			indices.push_back(index);
		}

	}

	return indices;
}

vector<int> graph::h_strip_maximal_set(range& r) {

	printf("at %s with range: (%2.2f, %2.2f) \n",
			__FUNCTION__, r.begin, r.end);

	graph induced_graph = split_graph_y_axis(r);
	return induced_graph.maximal_set();


}


graph graph::split_graph_y_axis(range& r) {

	return this->induce_graph(nodes_hstrip(r));

}

vector<int> graph::nodes_hstrip(range& r) {

	printf("finding nodes in the hstrip (%2.2f, %2.2f) \n",
			r.begin, r.end);

	vector<int> ids;
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		if (this->nodes.at(i).location.y >= r.begin &&
				this->nodes.at(i).location.y < r.end) {
			ids.push_back(this->nodes.at(i).id);
		}
	}

	return ids;

}


// this function is for algorithm GA-1 and its siblings ..
vector<int> graph::eliminate_nodes_hstrip(vector<range>& hstrips, int i, int k) {


	vector<int> ids, subset_ids;


	if (i < 0 || i > k) { return ids; }

	for (unsigned int j = 0; j < hstrips.size(); j++) {

		subset_ids.clear();

		if ((j % (k+1)) != i) {
			subset_ids = this->nodes_hstrip(hstrips[j]);

			for (unsigned int c = 0; c < subset_ids.size(); c++) {
				ids.push_back(subset_ids[c]);
			}

		}
	}

	sort(ids.begin(), ids.end());
	return ids;

}



vector<int> graph::maximal_set() {

	// printf("at %s \n", __FUNCTION__);

	this->sort_by_weight();
	vector<int> mis, visited;
	vector<int>::iterator it_visited;
	int v;


	vector<node>::iterator it = this->nodes.begin();
	while (it != this->nodes.end()) {


		v = it->id;

		if (! this->is_in(visited, v)) {

			// printf("v(%d) is not in visited \n", v);

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

#if 0
	printf("after sorting ! \n");
	this->print();
#endif

}


void graph::assign_tags(vector<vector<int> > ntags) {

	if (ntags.size() == 0) {return ; }

	if (ntags.size() != nodes.size()) {
		printf("mismatching sizes at %s (ntags:%d != nodes:%d) \n",
				__FUNCTION__, ntags.size(), nodes.size());
		abort();
	}



	for (unsigned int i = 0; i < ntags.size(); i++) {
		this->nodes.at(i).tag_neighbors = ntags[i];
		this->nodes.at(i).active_tag_neighbors = ntags[i];
	}

	vector<int>::iterator it;
	this->tags = ntags[0];
	for (unsigned int i = 0; i < ntags.size(); i++) {
		insert_into(this->tags, ntags[i]);
		sort(this->tags.begin(), this->tags.end());
		it = unique(this->tags.begin(), this->tags.end());
		this->tags.resize( distance(this->tags.begin(), it) );

	}

	this->active_tags = this->tags;


#if 1
	printf("active tags after %s \n", __FUNCTION__);
	for (unsigned int i = 0; i < this->active_tags.size(); i++)
		printf("%d ", this->active_tags[i]);
	printf("\n");
#endif
}

void insert_into(vector<int>& big_list, vector<int>& small_list) {
	for (unsigned int i = 0; i < small_list.size(); i++) {
		big_list.push_back(small_list[i]);
	}
}

//Note: itis supposed to be outside the class. see how it is defined.
bool weight_compare(node i, node j) {
	if (i.weight == j.weight) { return (i.id < j.id); }
	return (i.weight < j.weight);
}

bool point_y_compare(node i, node j) {
	if (i.location.y == j.location.y) { return (i.location.x < j.location.x); }
	return (i.location.y < j.location.y);
}


