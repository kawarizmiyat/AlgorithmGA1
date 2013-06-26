/*
 * subelements_grid.cpp
 *
 *  Created on: Jun 25, 2013
 *      Author: ahmed
 */

#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

#include "subelements_grid.h"


subelements_grid::subelements_grid() {

	grid = 0;

	max_x = 50; max_y = 50;
	width = 100; length = 100;

	set_interrogation_range(10);
	global_id = 1;

}

subelements_grid::~subelements_grid() {
	// TODO Auto-generated destructor stub
}


void subelements_grid::init_grid() {

	printf("at %s \n", __FUNCTION__);

	this->grid = new element*[max_y];
	for (int i = 0; i < max_y; i++) {
		this->grid[i] = new element[max_x];
	}


	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			this->grid[i][j] = element();
		}
	}

}



void subelements_grid::fill_circle(int xc, int yc, int r, node& n) {

	for (int x = -r; x < r ; x++)
	{
    	int height = (int)sqrt(r * r - x * x);

    	for (int y = -height; y < height; y++)
        	draw_pixel(x + xc, y + yc, n);

	}

}

void subelements_grid::draw_pixel(int x, int y, node& n) {

	// printf("draw pixel at %d and %d \n", x, y);

	//TODO: fix these confusions
	if (x < 0 || x >= max_y|| y < 0 || y >= max_x) { return; }


	this->grid[x][y].covered = true;
	this->grid[x][y].add_covering_node(n);
}

bool subelements_grid::is_in(vector<int> list, int id) {
	for (unsigned int i = 0; i < list.size(); i ++) {
		if (list.at(i) == id) return true;
	}
	return false;
}

void subelements_grid::print_grid() {


	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			// printf("%c ", str_bool(matrix[i][j].covered));
			printf("%d ", this->grid[i][j].max);
		}
		printf("\n");

	}

}



void subelements_grid::delete_grid() {
	for (int i = 0; i < max_y; i++) {
		delete[] this->grid[i];
	}
	delete[] this->grid;
}


void subelements_grid::insert_reader(node& n) {

	printf("length: %2.3f, width: %2.3f, max_x:%d, max_y: %d \n",
			length, width, max_x, max_y);
	printf("length/max_x: %2.3f ... width/max_y: %2.3f \n",
			(length / max_x), (length / max_y) );

	int rx = floor(n.location.x / (length / max_x));
	int ry = floor(n.location.y / (width / max_y));
	// n.id = global_id ++;

	printf("inserting reader %s at region (%d,%d) \n",
			n.to_string(), rx, ry);

	fill_circle(ry, rx, scaled_interrogation_range, n);

}

// if there is an empty subelement in vector<element> then the network is not covering.
void subelements_grid::find_subelements() {

	// vector<element> all_subelements;
	vector<element>::iterator it;

	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			sort(this->grid[i][j].v.begin(), this->grid[i][j].v.end());
			all_subelements.push_back(this->grid[i][j]);
		}
	}


	sort(all_subelements.begin(), all_subelements.end());
	it = unique(all_subelements.begin(), all_subelements.end());
	all_subelements.resize(distance(all_subelements.begin(), it));


}

vector<element> subelements_grid::get_subelements() {
	return all_subelements;
}

void subelements_grid::set_interrogation_range(double r) {
	this->interrogation_range = r;
	this->scaled_interrogation_range = r * this->max_x / this->width;
	// we assume here that max_x = max_y and width = length;
}
