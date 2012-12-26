/*
 * RColony.c
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <stdio.h>

#include "lists.h"
#include "rcolony.h"
#include "rlist.h"
#include "smath.h"

struct rColony {
	/** repository for the Rabbits */
	RList rl;

};

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

void initRColony() {

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
RColony newRColony(int initCount, int time) {

	RColony nc = malloc(sizeof(struct rColony));

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

void freeRColony(RColony c) {

	if (c == NULL )
		return;

	freeRabbitList(c->rl);

	free(c);
}

void updateRColony(RColony c, int time) {

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

int huntRabbit(RColony c) {

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

void printfRColony(RColony c) {
	printfRabbitList(c->rl);
}
