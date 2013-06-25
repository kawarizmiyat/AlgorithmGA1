/*
 * circle_fill_objects.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */

/*
 * circle_draw.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */


// include headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;


// include my headers:
#include "element.h"
#include "point.h"

// define macos

#define RI 10

// define functions
void run();
void init_matrix(element**&, int max_x, int max_y);
void draw_pixel(int x, int y, element** matrix, point& p);
void fill_circle(element** matrix, int xc, int yc, int r, point& p);

void print_matrix(element**, int max_x, int max_y);
void delete_matrix(element**, int max_y);
inline char str_bool(bool);
vector<element> find_subelements(element**, int max_x, int max_y);


// define global variables:
double width = 100, length = 100;
int global_id = 1;
int MAX_X = 99;
int MAX_Y = 50;

#if 0
int main() {

 	run_circle_fill();

}
#endif


void insert_reader(point& p, element** matrix) {

	printf("length: %2.3f, width: %2.3f, max_x:%d, max_y: %d \n",
			length, width, MAX_X, MAX_Y);
	printf("length/max_x: %2.3f ... width/max_y: %2.3f \n",
			(length / MAX_X), (length / MAX_X) );

	int rx = floor(p.x / (length / MAX_X));
	int ry = floor(p.y / (width / MAX_Y));
	p.id = global_id ++;

	printf("inserting reader %s at region (%d,%d) \n",
			p.to_string(), rx, ry);

	fill_circle(matrix, ry, rx, RI, p);

}



// if there is an empty subelement in vector<element> then the network is not covering. 
vector<element> find_subelements(element** matrix, int max_x, int max_y) {

	vector<element> all_subelements;
	vector<element>::iterator it;

	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			sort(matrix[i][j].v.begin(), matrix[i][j].v.end());
			all_subelements.push_back(matrix[i][j]);
		}
	}


	sort(all_subelements.begin(), all_subelements.end());
	it = unique(all_subelements.begin(), all_subelements.end());
	all_subelements.resize(distance(all_subelements.begin(), it));

	return all_subelements;

}

void run_circle_fill() {

	element** matrix = 0;
	init_matrix(matrix, MAX_X, MAX_Y);
	int  id = 3;


	// insert_reader == fill_circle.



	// fill_circle(matrix, 0, 0, 10, id ++);
	// fill_circle(matrix, 0, 5, 10, id++);
	// fill_circle(matrix, 20, 20, 10, id++);
	// fill_circle(matrix, 40, 40, 10, id++);

	point p;
	p.x = 1.2;
	p.y = 1.3;
	insert_reader(p, matrix);


	p.x = 40;
	p.y = 40;
	insert_reader(p, matrix);


	p.x = 60; p.y = 75;
	insert_reader(p, matrix);

	p.x = 58.7; p.y = 67.5;
	insert_reader(p, matrix);

	print_matrix(matrix, MAX_X, MAX_Y);

	vector<element> all_subelements = find_subelements(matrix, MAX_X, MAX_Y);

	for (unsigned int i = 0; i < all_subelements.size(); i++) {
		all_subelements.at(i).id = i;
	}

	for (unsigned int i = 0; i < all_subelements.size(); i++) {
		all_subelements.at(i).print();
		printf("\n");
	}


	delete_matrix(matrix, MAX_Y);
}


void init_matrix(element**& matrix, int max_x, int max_y) {

	printf("at %s \n", __FUNCTION__);

	matrix = new element*[max_y];
	for (int i = 0; i < max_y; i++) {
		matrix[i] = new element[max_x];
	}


	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			matrix[i][j] = element();
		}
	}


}


void fill_circle(element** matrix, int xc, int yc, int r, point& p) {

	for (int x = -r; x < r ; x++)
	{
    	int height = (int)sqrt(r * r - x * x);

    	for (int y = -height; y < height; y++)
        	draw_pixel(x + xc, y + yc, matrix, p);

	}

}

void draw_pixel(int x, int y, element** matrix, point& p) {

	// printf("draw pixel at %d and %d \n", x, y);

	if (x < 0 || x >= MAX_Y || y < 0 || y > MAX_X) { return; }


	matrix[x][y].covered = true;
	matrix[x][y].add_covering_node(p);
	// add if to matrix[x][y].add_covered(id);
}

void print_matrix(element** matrix, int max_x, int max_y) {


	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			// printf("%c ", str_bool(matrix[i][j].covered));
			printf("%d ", matrix[i][j].max);
		}
		printf("\n");

	}

}

inline char str_bool(bool b) {

	if (b) {
		return '1';
	}
	return '0';
}

void delete_matrix(element** matrix, int max_y) {
	for (int i = 0; i < max_y; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

