/*
 * circle_draw.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */


// include headers
#include <stdio.h>

// define macos
#define MAX_NUM 4



// define functions
void run();
void init_matrix(bool**, int size);
void draw_circle();
void print_matrix(bool**, int size);
void delete_matrix(bool**, int size);
inline char str_bool(bool);

// define global variables:
bool** matrix;

int main() {

	run();

}

void run() {
	init_matrix(matrix, MAX_NUM);
	draw_circle();
	print_matrix(matrix, MAX_NUM);
	delete_matrix(matrix, MAX_NUM);
}


void init_matrix(bool** matrix, int n) {

	matrix = new bool*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new bool[n];
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			matrix[i][j] = false;
	}

}

void draw_circle() {

}

void print_matrix(bool** matrix, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%c  ", str_bool(matrix[i][j]));
		printf("\n");
	}

}

inline char str_bool(bool b) {
	if (b) {
		return '1';
	} else {
		return '0';
	}

}

void delete_matrix(bool** matrix, int n) {
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
