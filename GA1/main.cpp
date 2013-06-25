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
#include "graph_extractor.h"
#include "subelements_grid.h"
#include "grid_graph_functions.h"


// global functions

void test_graph_mis();
void create_some_points(vector<point>*, int);
void main_run_circle_fill();
graph split_graph_y_axis(double b_range, double e_range, graph& g);


int main() {

	test_graph_mis();
	// main_run_circle_fill();
}

void main_run_circle_fill() {

	subelements_grid grid;

	// set parameters before calling init_grid:
	grid.init_grid();

	node n;
	point p;
	p.x = 1.2;
	p.y = 1.3;
	n.id = 1;
	n.location = p;
	grid.insert_reader(n);


	p.x = 40;
	p.y = 40;
	n.id = 2;
	n.location = p;
	grid.insert_reader(n);


	p.x = 60; p.y = 75;
	n.id = 3;
	n.location = p;
	grid.insert_reader(n);

	p.x = 58.7; p.y = 67.5;
	n.location = p;
	grid.insert_reader(n);


	grid.print_grid();

	grid.find_subelements();
	vector<element> all_subelements = grid.get_subelements();

	for (unsigned int i = 0; i < all_subelements.size(); i++) {
		all_subelements.at(i).id = i;
	}

	for (unsigned int i = 0; i < all_subelements.size(); i++) {
		all_subelements.at(i).print();
		printf("\n");
	}


	grid.delete_grid();
}



void test_graph_mis() {

	vector<point> points;
	vector<int> mis;
	// create_some_points(&points, 5);

	extract_points(points, "graphs/sample_points_2.txt");


	printf("printing points \n");
	for (unsigned int i = 0; i < points.size(); i++) {
		printf("%s \n", points.at(i).to_string());
	}

	graph g;
	g.nodes_range = 1.5;
	g.create_graph(points);

	subelements_grid gc = create_grid(g);
	calculate_grid_weights(g, gc);
	g.print();

	mis = g.maximal_set();
	printf("mis: ( ");
	for (unsigned int i = 0; i < mis.size(); i++) {
		printf("%d ", mis[i]);
	}
	printf(")\n");



	graph split_graph = split_graph_y_axis(1.00, 3.00, g);


	printf("the split graph (1.00, 2.00) \n");
	split_graph.print();

	printf("weights \n");
	for (unsigned int i = 0; i < split_graph.nodes.size(); i++) {
		printf("w(%d): %f \n", split_graph.nodes.at(i).id,
				split_graph.nodes.at(i).weight);
	}

	mis = split_graph.maximal_set();

	printf("mis: ( ");
	for (unsigned int i = 0; i < mis.size(); i++) {
		printf("%d ", mis[i]);
	}
	printf(")\n");
}

graph split_graph_y_axis(double b_range, double e_range, graph& g) {

	vector<int> ids;
	for (unsigned int i = 0; i < g.nodes.size(); i++) {
		if (g.nodes.at(i).location.y > b_range && g.nodes.at(i).location.y <= e_range) {
			ids.push_back(g.nodes.at(i).id);
		}
	}

	return g.induce_graph(ids);

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
