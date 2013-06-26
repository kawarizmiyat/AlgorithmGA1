/*
 * grid_graph_functions.cpp
 *
 *  Created on: Jun 25, 2013
 *      Author: ahmed
 */

#include <stdio.h>

#include "grid_graph_functions.h"


subelements_grid create_grid(graph& g) {


	subelements_grid grid;
	grid.length = 30;
	grid.width = 30;

	grid.set_interrogation_range(5);
	grid.init_grid();



	for (unsigned int i = 0; i < g.nodes.size(); i++) {
		grid.insert_reader(g.nodes.at(i));
	}


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


	// grid.delete_grid();
	return grid;


}


void calculate_grid_weights(graph& g, subelements_grid& grid) {

	int current_id;
	vector<element> subelements = grid.get_subelements();

	for (unsigned int i = 0; i < g.nodes.size(); i++) {

		current_id = g.nodes.at(i).id;
		g.nodes.at(i).weight = 0;
		for (unsigned int j = 0; j < subelements.size(); j++) {
			if (is_in(subelements.at(j).v, current_id)) {
				g.nodes.at(i).weight ++;
			}
		}

		printf("the weight of %d is %f \n", current_id, g.nodes.at(i).weight );

	}
}

bool is_in(vector<int>& list, int id) {
	for (unsigned int i = 0; i < list.size(); i ++) {
		if (list.at(i) == id) return true;
	}
	return false;
 }
