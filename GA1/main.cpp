/*
 * main.cpp
 *
 *  Created on: Jun 25, 2013
 *      Author: ahmed
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;


#include "point.h"
#include "graph.h"
#include "node.h"
#include "point.h"


// global functions

void test_graph_mis();
void create_some_points(vector<point>*, int);

int main() {

	test_graph_mis();

}


void test_graph_mis() {

	vector<point> points;
	create_some_points(&points, 5);

	printf("printing points \n");
	for (unsigned int i = 0; i < points.size(); i++) {
		printf("%s \n", points.at(i).to_string());
	}

	graph g;
	g.nodes_range = 1;
	g.create_graph(points);

	printf("printing graph g \n");
	g.print();

	int ids_arr[] = {2,0};
	vector<int> ids_vec (ids_arr, ids_arr + sizeof(ids_arr) / sizeof(int) );


	printf("printing induced gprah ind_g \n");
	graph ind_g = g.induce_graph(ids_vec);
	ind_g.print();

	g.calculate_weight_nr();
	vector<int> mis = ind_g.maximal_set();

	printf("mis: ");
	for (unsigned int i = 0; i < mis.size(); i++)
		printf("%d ", mis.at(i));
	printf("\n");


}


void create_some_points(vector<point>* points, int n) {


	point p;

	p.x = 1; p.y = 0;
	points->push_back(p);

	p.x = 2; p.y = 0;
	points->push_back(p);

	p.x = 3; p.y = 0;
	points->push_back(p);

	p.x = 2; p.y = 1;
	points->push_back(p);

}
