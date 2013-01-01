/*
 * animal.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdio.h>

#include "individual.h"

void printfIndividual(Individual *r) {

	printf("ID:%4d  BT:%4d  AT:%4d  DT:%4d X:%.1f  Y:%.1f\n", r->id,
			r->birthTime, r->adultTime, r->deathTime, r->x, r->y);
}

int getIndividualAge(Individual *a, int time) {

	if (a == NULL )
		return -1;

	return time < a->birthTime ? -1 : time - a->birthTime;

}

Message getIndividualMsg(Individual *a) {

	Message nm;

	if (a == NULL ) {
		nm.str[0] = '\0';
	} else {
		sprintf(nm.str, "INDIVIDUO %d %d %f %f", a->specimen, a->id, a->x,
				a->y);
	}

	return nm;

}

void setIndividualPos(Individual *i, float x, float y) {

	if (i == NULL )
		return;

	i->x = x;
	i->y = y;

}

void displaceIndividual(Individual *i, float dx, float dy) {

	if (i == NULL )
		return;

	i->x += dx;
	i->y += dy;

}

void sendIndividualMsg(Individual *i) {

	sendMsg(getIndividualMsg(i));

}

void sendIndividualMsgTo(FILE *f, Individual *i) {

	sendMsgTo(f, getIndividualMsg(i));

}
