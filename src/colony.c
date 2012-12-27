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
	AList rabbitList;

	/** population type */
	PopType *popType;
};

/**
 * Cria uma nova Colónia
 *
 * @param initCount número inicial de coelhos
 * @param time		tempo em que a Colónia é criada
 * @return			ponteiro para uma nova Colónia
 */
Colony newColony(PopType *pt, int initCount, int time) {

	Colony nc = malloc(sizeof(struct colony));

	if (nc == NULL )
		return NULL ;

	nc->rabbitList = newAnimalList();
	if (nc->rabbitList == NULL ) {
		free(nc);
		return NULL ;
	}

	int i;
	Animal r;
	do {
		if (insertAnimal(nc->rabbitList,
				newAnimal(&r, pt, time - getLifeAge(pt))) != NULL )
			i++;
	} while (i < initCount);

	nc->popType = pt;

	printfAnimalList(nc->rabbitList);

	return nc;
}

void freeColony(Colony c) {

	if (c == NULL )
		return;

	freeAnimalList(c->rabbitList);

	free(c);
}

void updateColony(Colony c, int time) {

	/* breed Animals */

	/* calc number of couple Animals */
	int nCouples = getAdultsCount(c->rabbitList, time) / 2;

	/* number of breeds in this time/month */
	int nBreeds = getBreeds(c->popType), i;
	for (i = 1; i <= nBreeds; ++i)
		insertNewAnimals(c->rabbitList, nCouples * getKits(c->popType), time,
				c->popType);

	printf("nc = %d  nb = %d\n", nCouples, nBreeds);

	deleteOldAnimals(c->rabbitList, time);

}

int huntAnimal(Colony c) {

	if (c == NULL )
		return 0;

	int count = getAnimalsCount(c->rabbitList);
	if (count == 0)
		return 0;

	/* generate a uniform distribution with the number of Animals */
	UDistri d = newUDistri(1, count);

	removeAnimal(c->rabbitList, nextUDistriRandom(d));

	return 1;
}

void printfColony(Colony c) {
	printfAnimalList(c->rabbitList);
}
