/*
 * graph.h
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

#include "node.h"
#include "point.h"
#include "range.h"


#define DEFAULT_NODE_RANGE 10
#define DEFAULT_INT_RANGE 5

class graph {
public:
	graph();
	graph(const graph& g);
	virtual ~graph();


	void create_graph(vector<point>& points);
	void create_graph(vector<point>& points, vector<int>* ids);

	void interconnect_nodes();
	graph induce_graph(vector<int> ids);
	int find_index(int id);
	vector<int> find_indices(vector<int>& list);
	void sort_by_weight();

	// void copy_weights(const graph& g);
	void calculate_weight_nr();
	void calculate_weight_nt();
	vector<int> extract_active_tags(vector<int>&);

	void assign_tags(vector<vector<int> > ntags);

	vector<int> maximal_set();
	vector<int> h_strip_maximal_set(range&);
	graph split_graph_y_axis(range& r);
	vector<int> nodes_hstrip(range& r);
	vector<int> eliminate_nodes_hstrip(vector<range>& hstrips, int i, int k);


	graph deactivate_nodes(vector<int>&);
	void deactivate_tags(vector<int>&);


	void print();

	vector<int> tags, active_tags;
 	vector<node> nodes;
	double nodes_range;
	double interrogation_range;


private:
	bool is_in(vector<int> list, int id);


};

void insert_into(vector<int>& big_list, vector<int>& small_list);
bool weight_compare(node i, node j);
bool point_y_compare(node i, node j);

#endif /* GRAPH_H_ */
