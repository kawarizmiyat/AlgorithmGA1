/*
 * range.h
 *
 *  Created on: Jun 26, 2013
 *      Author: ahmed
 */

#ifndef RANGE_H_
#define RANGE_H_



struct range {
	double begin;
	double end;

	range() { }
	range(const range& n) {
		this->begin = n.begin;
		this->end = n.end;
	}

	void print() {
		printf("%2.2f -- %2.2f ", this->begin, this->end);
	}
};

#endif /* RANGE_H_ */
