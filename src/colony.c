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

	int ID;

	/** population type */
	Population *pop;

	/** repository for the Animals */
	AList animals;

	/* id animal generator */
	int (*getAnimalID)(void);

};

static Animal *newAnimal(Colony c, Animal *nr, int birthTime) {

	if (!isBreedSeason(c->pop, birthTime))
		return NULL ;

	if (nr == NULL ) {
		nr = malloc(sizeof(Animal));
		if (nr == NULL )
			return NULL ;
	}

	int adultTime = birthTime + getAdultAge(c->pop);
	int deathTime = birthTime + getLifeAge(c->pop);
	if (deathTime < adultTime)
		adultTime = deathTime;

	nr->birthTime = birthTime;
	nr->adultTime = adultTime;
	nr->deathTime = deathTime;

	return nr;

}

static Animal *insertAnimalInColony(Colony c, Animal *a) {

	Animal *storedAnimal = insertAnimal(c->animals, a);

	if (storedAnimal != NULL )
		storedAnimal->id = c->getAnimalID();

	return storedAnimal;

}

/**
 *
 * @param pt
 * @return
 */
Colony newColony(Population *pt) {

	Colony nc = malloc(sizeof(struct colony));

	if (nc == NULL )
		return NULL ;

	nc->animals = newAnimalList();
	if (nc->animals == NULL ) {
		free(nc);
		return NULL ;
	}

	nc->pop = pt;

	return nc;
}

void initColony(Colony c, int count, int time, int (*idGenerator)(void)) {

	if (c == NULL )
		return;

	c->getAnimalID = idGenerator;

	int i = 0;
	Animal a;
	do {
		/* create new animal */
		if (newAnimal(c, &a, time - getLifeAge(c->pop)) != NULL ) {
			/* check if animal alive */
			if (a.deathTime >= time)
				if (insertAnimalInColony(c, &a) != NULL )
					i++;
		}
	} while (i < count);
}

void setColonyAnimals(Colony c, AList al) {

	if (c == NULL || al == NULL )
		return;

	freeAnimalList(c->animals);

	c->animals = al;

}

void freeColony(Colony c) {

	if (c == NULL )
		return;

	freeAnimalList(c->animals);

	free(c);
}

void updateColony(Colony c, int time) {

	if (c == NULL )
		return;

	if (!isBreedSeason(c->pop, time))
		return;

	/* breed Animals */

	/* calc number of couple Animals */
	int nCouples = getAdultsCount(c->animals, time) / 2;

	/* number of breeds in this time/month */
	int nBreeds = getBreeds(c->pop), i, j;
	int K = getKits(c->pop);
	/* number of total kits */
	int nKits = nCouples * K;

	printf("couples = %d breads = %d kits = %d\n", nCouples, nBreeds, K);

	Animal a;
	for (i = 1; i <= nBreeds; ++i)
		for (j = 1; j <= nKits; ++j)
			insertAnimalInColony(c, newAnimal(c, &a, time));

	c->animals = removeOldAnimals(c->animals, time);

}

void printfColony(Colony c) {

	printfAnimalList(c->animals);
}

int getColonyCount(Colony c) {
	return c == NULL ? -1 : getAnimalsCount(c->animals);
}

AList trimColony(Colony c, int newCount) {

	return c == NULL ? NULL : trimAnimalList(c->animals, newCount);
}
