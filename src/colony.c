/*
 * colony.c
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>

#include "lists.h"
#include "colony.h"
#include "rabbits.h"
#include "smath.h"

struct colony {

	/** repository for the Rabbits */
	RList rl;

	/** number of breads for the year */
	int yearBreads;
};

UDistri breads;

void initColony() {

	breads = newUDistri(0, 8);
}

static int getBreads() {

	return nextUDistriRandom(breads);
}
/**
 * Cria uma nova Colónia
 *
 * @param initCount Número inicial de coelhos
 * @param time		Tempo em que a Colónia é criada
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
		insertRabbit(nc->rl, newRabbit(&r, time - getRabbitDeathTime()));

	/* calc how many breeds for the rest of the year */

	/* how many mounths left in the year */
	time = 11 - time % 12;

	nc->yearBreads = getBreads() * time / 12;

	printfRabbitList(nc->rl);

	return nc;
}

void freeColony(Colony c) {

	if (c == NULL )
		return;

	freeRabbitList(c->rl);

	free(c);
}

void updateColony(Colony c, int time) {

	insertNewRabbits(c->rl, getAdultsCount(c->rl, time) * 5 / 2, time);

	deleteOldRabbits(c->rl, time);

	printfRabbitList(c->rl);

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
