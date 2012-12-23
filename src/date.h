/*
 * data.h
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#ifndef DATA_H_
#define DATA_H_

typedef struct {
	int y, m, d;
} date;

date newDate(int y, int m, int d);

#endif /* DATA_H_ */
