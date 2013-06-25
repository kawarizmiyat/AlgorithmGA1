/*
 * grid_graph_functions.h
 *
 *  Created on: Jun 25, 2013
 *      Author: ahmed
 */

#ifndef GRID_GRAPH_FUNCTIONS_H_
#define GRID_GRAPH_FUNCTIONS_H_

#include "graph.h"
#include "subelements_grid.h"

subelements_grid create_grid(graph& g);
void calculate_grid_weights(graph& g, subelements_grid& grid);
bool is_in(vector<int>& list, int id);

#endif /* GRID_GRAPH_FUNCTIONS_H_ */
