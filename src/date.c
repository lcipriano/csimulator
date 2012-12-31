/*
 * date.c
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#include <stdio.h>

#include "date.h"

Date newDate(int y, int m, int d) {

	Date nd = { y, m, d };

	return nd;
}

Date incrementMonth(Date d) {

	Date nd = d;

	nd.m++;
	if (nd.m > DEC) {
		nd.m = JAN;
		nd.y++;
	}

	return nd;
}

Message getDateMsg(Date d) {

	Message nm;

	sprintf(nm.str, "DATA %d %d %d", d.d, d.m, d.y);

	return nm;

}
