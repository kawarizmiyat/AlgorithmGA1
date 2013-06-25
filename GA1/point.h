/*
 * point.h
 *
 *  Created on: Jun 24, 2013
 *      Author: ahmed
 */

#ifndef POINT_H_
#define POINT_H_

class point {
public:
	point();
	point(const point& p);
	virtual ~point();
	char* to_string();

	double distance(const point& p);

	double x, y;
	int id;

private:
	char output[20];
};

#endif /* POINT_H_ */
