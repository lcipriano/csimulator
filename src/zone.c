/*
 * zones.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <stdio.h>

#include "colony.h"
#include "zone.h"
#include "smath.h"

struct zone {

	Colony c;

	int max;

	float x0, y0, x1, y1;

	int x, y;

	int noUpdate;

};

Zone newZone(int x, int y) {

	Zone nz = malloc(sizeof(struct zone));

	if (nz == NULL )
		return NULL ;

	nz->c = NULL;
	nz->max = 20;
	nz->x = x;
	nz->y = y;
	nz->noUpdate = 1;

	return nz;

}

void freeZone(Zone z) {

	if (z == NULL )
		return;

	freeColony(z->c);
}

AList updateZone(Zone z, int time) {

	if (z == NULL )
		return NULL ;

	if (z->c == NULL || z->noUpdate)
		return NULL ;

	updateColony(z->c, time);

	/* return excess rabbits */
	return trimColony(z->c, z->max);
}

Colony getZoneColony(Zone z) {

	return z == NULL ? NULL : z->c;
}

void setZoneColony(Zone z, Colony c) {

	if (z == NULL )
		return;

	if (z->c != NULL )
		return;

	z->c = c;
}

int huntRabbit(Zone z) {
	return 1;
}

int getZoneMax(Zone z) {

	return z == NULL ? -1 : z->max;
}

void printfZone(Zone z) {

	if (z == NULL )
		return;

	printf("Zone Animals = %d x = %d  y = %d\n", getColonyCount(z->c), z->x,
			z->y);
}

void setZoneUpdate(Zone z) {

	if (z == NULL )
		return;

	if (z->c != NULL )
		z->noUpdate = 0;

}
