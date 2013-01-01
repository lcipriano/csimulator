/*
 * date.c
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#include <stdio.h>

#include "date.h"

Date newDate(int d, int m, int y) {

	Date nd = { y, m, d };

	return nd;
}

Date incDateMonth(Date d) {

	d.m++;
	if (d.m > DEC) {
		d.m = JAN;
		d.y++;
	}

	return d;
}

Message getDateMsg(Date d) {

	Message nm;

	sprintf(nm.str, "DATA %d %d %d", d.d, d.m, d.y);

	return nm;

}

void sendDateMsg(Date d) {

	sendMsg(getDateMsg(d));

}

void sendDateMsgTo(FILE *f, Date d) {

	sendMsgTo(f, getDateMsg(d));

}
