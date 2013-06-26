/*
 * subelements_grid.h
 *
 *  Created on: Jun 25, 2013
 *      Author: ahmed
 */

#ifndef SUBELEMENTS_GRID_H_
#define SUBELEMENTS_GRID_H_


#include "element.h"
#include "point.h"
#include "node.h"

class subelements_grid {
public:
	subelements_grid();
	virtual ~subelements_grid();


	void init_grid();
	void delete_grid();
	void print_grid();
	void draw_pixel(int x, int y, node& p);
	void fill_circle(int xc, int yc, int r, node& p);
	void insert_reader(node& p);
	void find_subelements();
	vector<element> get_subelements();
	void set_interrogation_range(double);

	inline char str_bool(bool b) {

		if (b) {
			return '1';
		}
		return '0';
	}

	// global variables:
	element** grid;
	double width, length;
	double interrogation_range;
	int scaled_interrogation_range;

	int max_x, max_y;
	int global_id;

	vector<element> all_subelements;

private:
	bool is_in(vector<int>, int);

};

#endif /* SUBELEMENTS_GRID_H_ */
