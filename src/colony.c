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

	float x, y;

	/** population type */
	Specimen *pop;

	/** repository for the Individuals */
	IList Individuals;

	/* id Individual generator */
	int (*getIndividualID)(void);

};

static Individual *newIndividual(Colony c, Individual *nr, int birthTime) {

	if (!isBreedSeason(c->pop, birthTime))
		return NULL ;

	if (nr == NULL ) {
		nr = malloc(sizeof(Individual));
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
	nr->specimen = getSpecimenID(c->pop);

	return nr;

}

static Individual *insertIndividualInColony(Colony c, Individual *a) {

	Individual *storedIndividual = insertIndividual(c->Individuals, a);

	if (storedIndividual != NULL )
		storedIndividual->id = c->getIndividualID();

	return storedIndividual;

}

/**
 *
 * @param pt
 * @return
 */
Colony newColony(Specimen *pt, int (*idGenerator)(void)) {

	static int nextID = 1;

	Colony nc = malloc(sizeof(struct colony));

	if (nc == NULL )
		return NULL ;

	nc->Individuals = newIndividualList();
	if (nc->Individuals == NULL ) {
		free(nc);
		return NULL ;
	}

	nc->pop = pt;
	nc->getIndividualID = idGenerator;
	nc->ID = nextID++;

	return nc;
}

void initColony(Colony c, int count, int time) {

	if (c == NULL )
		return;

	int i = 0;
	Individual a;
	do {
		/* create new Individual */
		if (newIndividual(c, &a, time - getLifeAge(c->pop)) != NULL ) {
			/* check if Individual alive */
			if (a.deathTime >= time)
				if (insertIndividualInColony(c, &a) != NULL )
					i++;
		}
	} while (i < count);
}

ListIter getColonyIter(Colony c) {
	return c == NULL ? NULL : newListIter(c->Individuals);
}

IList getColonyIndividuals(Colony c) {
	return c == NULL ? NULL : c->Individuals;
}

void setColonyIndividuals(Colony c, IList al) {

	if (c == NULL || al == NULL )
		return;

	freeIndividualList(c->Individuals);

	c->Individuals = al;

}

void setColonyPos(Colony c, float x, float y) {

	if (c == NULL )
		return;

	c->x = x;
	c->y = y;

	ListIter animals = getColonyIter(c);
	if (animals == NULL )
		return;

	Individual *pi;
	while ((pi = ListIterNext(animals, NULL )) != NULL )
		setIndividualPos(pi, x, y);
	freeListIter(animals);

}

void freeColony(Colony c) {

	if (c == NULL )
		return;

	freeIndividualList(c->Individuals);

	free(c);
}

void updateColony(Colony c, int time) {

	if (c == NULL )
		return;

	if (!isBreedSeason(c->pop, time))
		return;

	/* breed Individuals */

	/* calc number of couple Individuals */
	int nCouples = getAdultsCount(c->Individuals, time) / 2;

	/* number of breeds in this time/month */
	int nBreeds = getBreeds(c->pop), i, j;
	int K = getKits(c->pop);
	/* number of total kits */
	int nKits = nCouples * K;

	/*printf("couples = %d breads = %d kits = %d\n", nCouples, nBreeds, K);*/

	Individual a;
	for (i = 1; i <= nBreeds; ++i)
		for (j = 1; j <= nKits; ++j)
			insertIndividualInColony(c, newIndividual(c, &a, time));

	c->Individuals = removeOldIndividuals(c->Individuals, time);

}

void printfColony(Colony c) {

	printfIndividualList(c->Individuals);
}

int getColonyCount(Colony c) {
	return c == NULL ? -1 : getIndividualsCount(c->Individuals);
}

IList trimColony(Colony c, int newCount) {

	return c == NULL ? NULL : trimIndividualList(c->Individuals, newCount);
}

Message getColonyMsg(Colony c) {

	Message nm;

	if (c == NULL ) {
		nm.str[0] = '\0';
	} else {
		nm.str[0] = '\0';
		sprintf(nm.str, "COLONIA %2d %2d %3d %.1f %.1f", c->pop->type, c->ID,
				getColonyCount(c), c->x, c->y);
	}

	return nm;

}

void sendColonyMsg(Colony c) {

	sendMsg(getColonyMsg(c));

}

void sendColonyMsgTo(FILE *f, Colony c) {

	sendMsgTo(f, getColonyMsg(c));

}
