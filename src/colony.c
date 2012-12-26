/*
 * colony.c
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <stdio.h>

#include "lists.h"
#include "colony.h"
#include "rlist.h"
#include "smath.h"

struct colony {

	/** repository for the Rabbits */
	RList rl;

	/** number of breads for the year */
	int yearBreads;

	int inBreedSeason;
};

/***/
/** número médio de ninhadas por temporada */
static int avgBreedsBySeason;
/** numero médio de crias por ninhada */
static int avgRabbitsByCouple;

/** gerador aleatório de ninhadas por mês */
static PoDistri rabbitBreedsByMonth;

static int getBreedsByMonth() {

	return nextPoDistriRandom(rabbitBreedsByMonth);
}

int getRabbitsByCouple() {

	return avgRabbitsByCouple;
}

void initColony() {

	avgBreedsBySeason = 9;
	/** numero médio de crias por ninhada */
	avgRabbitsByCouple = 5;

	rabbitBreedsByMonth =
			newPoDistri(
					(float) avgBreedsBySeason
							/ (getEndRabbitBreedMonth()
									- getStartRabbitBreedMonth() + 1));
}

/**
 * Cria uma nova Colónia
 *
 * @param initCount número inicial de coelhos
 * @param time		tempo em que a Colónia é criada
 * @return			ponteiro para uma nova Colónia
 */
Colony newColony(int initCount, int time) {

	Colony nc = malloc(sizeof(struct colony));

	if (nc == NULL )
		return NULL ;

	nc->rl = newRabbitList();
	if (nc->rl == NULL ) {
		free(nc);
		return NULL ;
	}

	int i;
	Rabbit r;
	for (i = 1; i <= initCount; ++i)
		insertRabbit(nc->rl, newRabbit(&r, time - getNextRabbitTimeLife()));

	return nc;
}

void freeColony(Colony c) {

	if (c == NULL )
		return;

	freeRabbitList(c->rl);

	free(c);
}

void updateColony(Colony c, int time) {

	/* breed rabbits */

	/* calc number of couple rabbits */
	int nCouples = getRabbitsAdultsCount(c->rl, time) / 2;

	/* number of breeds in this time/month */
	int nBreeds = getBreedsByMonth(), i;
	for (i = 1; i <= nBreeds; ++i)
		insertNewRabbits(c->rl, nCouples * getRabbitsByCouple(), time);

	printf("nc = %d  nb = %d\n", nCouples, nBreeds);

	deleteOldRabbits(c->rl, time);

}

int huntRabbit(Colony c) {

	if (c == NULL )
		return 0;

	int count = getRabbitsCount(c->rl);
	if (count == 0)
		return 0;

	/* generate a uniform distribution with the number of rabbits */
	UDistri d = newUDistri(1, count);

	removeRabbit(c->rl, nextUDistriRandom(d));

	return 1;
}

void printfColony(Colony c) {
	printfRabbitList(c->rl);
}
