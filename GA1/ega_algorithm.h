/*
 * ega_algorithm.h
 *
 *  Created on: Jun 26, 2013
 *      Author: ahmed
 */

#ifndef EGA_ALGORITHM_H_
#define EGA_ALGORITHM_H_

#include <vector>
using namespace std;

#include "range.h"
#include "graph.h"

vector<range> find_horizontal_strips(double, double, double);
void wmis_ptas(graph& g, vector<int>& max_mis, vector<int>& max_mis_tags);
void algorithm_ga1(graph& g, vector<vector<int> >& colored_nodes);

#endif /* EGA_ALGORITHM_H_ */
