/*
 * ega_algorithm.cpp
 *
 *  Created on: Jun 26, 2013
 *      Author: ahmed
 */

#include <stdio.h>
#include <vector>
using namespace std;



#include "range.h"
#include "graph.h"
#include "ega_algorithm.h"


void algorithm_ga1(graph& g, vector<vector<int> >& colored_nodes) {

	vector<int> mis_tags, mis;
	int ga1_iteration = 0;

	while (g.active_tags.size() > 0) {
		printf("starting iteration %d \n", ga1_iteration);
		wmis_ptas(g, mis, mis_tags);

		printf("final result of wmis_ptas: ");
		for (unsigned int c = 0; c < mis.size(); c++ ) {
			printf("%d ", mis[c]);
		} printf("\n");


		printf("before deactication at iteration %d: \n", ga1_iteration);
		g.print();


		printf("after deactivation at iteration %d \n", ga1_iteration);
		graph temp_g = g.deactivate_nodes(mis);
		g = temp_g;
		g.deactivate_tags(mis_tags);
		g.print();


		colored_nodes.push_back(mis);

		ga1_iteration ++;
	}

}

vector<range> find_horizontal_strips(double grid_length, double irange, double crange) {
	double length = grid_length;
	double max_2ts = (2*irange > crange) ? 2*irange : crange;

	printf("irange: %2.2f, .. crange: %2.2f \n", irange, crange);
	printf("length: %2.2f .. max2ts: %2.2f \n", length, max_2ts);


	range r;
	vector<range> result;
	int i = 0;
	bool exit = false;
	while (! exit) {
		r.begin = i * max_2ts;
		r.end = (i + 1) * max_2ts;
		if (r.end >= length) {
			r.end = length;
			exit = true;
		}
		result.push_back(r);
		i ++ ;
	}

#if 1
	printf("horizontal strips :\n");
	for (unsigned int i = 0; i < result.size(); i ++ ) {
		printf("%d: ", i);
		result.at(i).print();
		printf("\n");
	}
#endif

	return result;
}


void wmis_ptas(graph& g, vector<int>& max_mis, vector<int>& max_mis_tags) {

	graph split_graph;
	vector<int> mis, mis_tags, non_eliminated_ids;
	int weight_nt_mis, max_weight_nt_mis = -1;

	const int max_k = 2;
	double irange = g.interrogation_range;
	double crange = g.nodes_range;
	double length = 30;

	vector<range> horizontal_strips = find_horizontal_strips(length, irange, crange);

	for (int i = 0; i <= max_k; i++) {

		printf("at iteration i:%d \n", i);

		non_eliminated_ids = g.eliminate_nodes_hstrip(
				horizontal_strips, i, max_k);

		printf("non-eliminated nodes: \n");
		for (unsigned int i = 0; i < non_eliminated_ids.size(); i++)
			printf("%d ", non_eliminated_ids.at(i));
		printf("\n");


		graph split_graph = g.induce_graph(non_eliminated_ids);
		mis = split_graph.maximal_set();

		printf("mis at iteration %d :", i );
		for (unsigned int c = 0; c < mis.size(); c++)
			printf("%d ", mis.at(c));
		printf("\n");

		// vector<int> mis_tags = g.extrat_active_tags(mis);
		mis_tags = g.extract_active_tags(mis);
		weight_nt_mis = mis_tags.size();

		printf("mis tags at iteration %d :", i );
		for (unsigned int c = 0; c < mis_tags.size(); c++)
			printf("%d ", mis_tags.at(c));
		printf("\n");

		if (weight_nt_mis > max_weight_nt_mis) {
			max_weight_nt_mis = weight_nt_mis;
			max_mis_tags = mis_tags;
			max_mis = mis;
		}
	}

}
