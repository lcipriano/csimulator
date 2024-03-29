/*
 * data.h
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#ifndef DATA_H_
#define DATA_H_

#include "message.h"

enum {
	JAN, FEV, MAR, ABR, MAI, JUN, JUL, AGO, SET, OCT, NOV, DEC
};

typedef struct {
	int y, m, d;
} Date;

Date newDate(int y, int m, int d);

Date incDateMonth(Date d);

Message getDateMsg(Date d);

void sendDateMsg(Date d);

void sendAreaMsgTo(FILE *f);

#endif /* DATA_H_ */
