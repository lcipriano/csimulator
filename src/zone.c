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

	float xc, yc;

	int noUpdate;

	UDistri XDistri, YDistri;

	int line, col;

};

static void removeColony(Zone z) {

	if (getZoneCount(z) < 2) {
		freeColony(z->c);
		z->c = NULL;
	}
}

Zone newZone(float x0, float y0, float x1, float y1, int line, int col) {

	Zone nz = malloc(sizeof(struct zone));

	if (nz == NULL )
		return NULL ;

	nz->c = NULL;
	nz->max = 20;
	nz->xc = (x0 + x1) / 2;
	nz->yc = (y0 + y1) / 2;
	nz->x0 = x0;
	nz->x1 = x1;
	nz->y0 = y0;
	nz->y1 = y1;
	nz->noUpdate = 1;
	nz->XDistri = newUDistri(x0, x1);
	nz->YDistri = newUDistri(y0, y1);
	nz->line = line;
	nz->col = col;

	return nz;
}

void freeZone(Zone z) {

	if (z == NULL )
		return;

	freeColony(z->c);

	free(z);
}

AList updateZone(Zone z, int time) {

	if (z == NULL )
		return NULL ;

	if (z->c == NULL || z->noUpdate)
		return NULL ;

	updateColony(z->c, time);

	removeColony(z);

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

int huntZoneRabbit(Zone z) {

	if (z == NULL )
		return 0;

	Animal a, *pa;
	pa = removeRandAnimal(getColonyAnimals(z->c), &a);

	removeColony(z);

	return pa == NULL ? 0 : 1;
}

int getZoneMax(Zone z) {

	return z == NULL ? -1 : z->max;
}

void printfZone(Zone z) {

	if (z == NULL )
		return;

	printf("Zone(%2d,%2d) Rabbits = %d ,x0=%.1f y0=%.1f x1=%.1f y1=%.1f\n",
			z->line, z->col, getColonyCount(z->c), z->x0, z->y0, z->x1, z->y1);
	/*
	 printf("Zone Animals = %d x0=%.3f y0=%.3f x1=%.3f y1=%.3f\n",
	 getColonyCount(z->c), z->x0, z->y0, z->x1, z->y1);
	 */
}

void setZoneUpdate(Zone z) {

	if (z == NULL )
		return;

	if (z->c != NULL )
		z->noUpdate = 0;

}

float getZoneCenterX(Zone z) {
	return z == NULL ? 0.0 : z->xc;
}

float getZoneCenterY(Zone z) {
	return z == NULL ? 0.0 : z->yc;
}

float getZoneRandomX(Zone z) {

	return z == NULL ? -1.0 : nextUDistriRandom(z->XDistri);

}

float getZoneRandomY(Zone z) {

	return z == NULL ? -1.0 : nextUDistriRandom(z->YDistri);

}

int getZoneCount(Zone z) {

	return z == NULL ? -1 : getColonyCount(z->c);

}
