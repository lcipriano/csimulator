/*
 * zones.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stddef.h>

#include "colony.h"
#include "zone.h"
#include "smath.h"

struct zone {

	Colony c;

	int max;

};

AList updateZone(Zone z, int time) {

	if (z == NULL )
		return NULL ;

	if (z->c == NULL )
		return NULL ;

	updateColony(z->c, time);

	/* return excedents rabbits */

	int count = getColonyCount(z->c);

	if (count <= z->max)
		return NULL ;

	AList list = newAnimalList();
	if (list == NULL )
		return NULL ;

	Animal a;
	UDistri d;
	while (count > z->max) {
		d = newUDistri(1, count);
		/*removeFromColony(z->c, &a, nextUDistriRandom(d)); */
		insertAnimal(list, &a);
		count--;
	}

	return list;
}

Colony getZoneColony(Zone z) {
	return z->c;
}

void setZoneColony(Zone z, Colony c) {
	z->c = c;
}

int huntRabbit(Zone z) {
	return 1;
}
