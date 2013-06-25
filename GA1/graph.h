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

#define DEFAULT_RANGE 10

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
	void sort_by_weight();

	void calculate_weight_nr();

	vector<int> maximal_set();

	void print();

	vector<node> nodes;
	double nodes_range;

private:
	bool is_in(vector<int> list, int id);


};

bool weight_compare(node i, node j);
bool point_y_compare(node i, node j);

#endif /* GRAPH_H_ */
