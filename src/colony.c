/*
 * colony.c
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#include <stdio.h>
#include <stdlib.h>

#include "colony.h"

struct colony {

	/** repository for the Animals */
	AList animals;

	/** max number of animal in the colony */
	int max;

	/** population type */
	PopType *popType;
};

/**
 *
 * @param pt
 * @return
 */
Colony newColony(PopType *pt) {

	Colony nc = malloc(sizeof(struct colony));

	if (nc == NULL )
		return NULL ;

	nc->animals = newAnimalList();
	if (nc->animals == NULL ) {
		free(nc);
		return NULL ;
	}

	nc->popType = pt;

	return nc;
}

void initColony(Colony c, int count, int time) {

	if (c == NULL )
		return;

	int i = 0;
	Animal r;
	do {
		if (insertAnimal(c->animals,
				newAnimal(&r, c->popType,
						time - getLifeAge(c->popType))) != NULL)
			i++;
	} while (i < count);
}

void setAList(Colony c, AList al) {

	if (c == NULL || al == NULL )
		return;

	freeAnimalList(c->animals);

	c->animals = al;

}

AList getAList(Colony c) {
	return c == NULL ? NULL : c->animals;
}

void freeColony(Colony c) {

	if (c == NULL )
		return;

	freeAnimalList(c->animals);

	free(c);
}

void updateColony(Colony c, int time) {

	/* breed Animals */

	/* calc number of couple Animals */
	int nCouples = getAdultsCount(c->animals, time) / 2;

	/* number of breeds in this time/month */
	int nBreeds = getBreeds(c->popType), i;
	for (i = 1; i <= nBreeds; ++i)
		insertNewAnimals(c->animals, nCouples * getKits(c->popType), time,
				c->popType);

	printf("nc = %d  nb = %d\n", nCouples, nBreeds);

	deleteOldAnimals(c->animals, time);

}

void printfColony(Colony c) {
	printfAnimalList(c->animals);
}

Colony newColonyWithRabbits(AList rl) {
	return NULL ;
}

void removeFromColony(Colony c, Animal *a, int index) {

	if (c == NULL )
		return;

	removeAnimal(c->animals, a, index);
}

int getColonyCount(Colony c) {
	return c == NULL ? -1 : getAnimalsCount(c->animals);
}
