/*
 * colony.c
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>

#include <LinkedList.h>

#include "colony.h"
#include "rabbits.h"
#include "smath.h"

struct colony {
	int id;
	int rabbitCount;
	int rabbitID;
	RabbitList rl;
};

/**
 * Cria uma nova Colónia
 *
 * @param initCount Número inicial de coelhos
 * @param atTime	Tempo em que a Colónia é criada
 * @return			ponteiro para uma nova Colónia
 */
Colony newColony(int id, int initCount, int atTime) {

	Colony nc = malloc(sizeof(struct colony));

	if (nc == NULL )
		return NULL ;

	nc->rl = newRabbitList();
	if (nc->rl == NULL ) {
		free(nc);
		return NULL ;
	}

	nc->id = id;

	int i;
	Rabbit r;
	for (i = 1; i <= initCount; ++i) {
		r = newRabbit(atTime - getDeathTime());
		insertRabbit(nc->rl, r);
	}

	printfRabbitList(nc->rl);

	return nc;
}

void updateColony(Colony c, int time) {

	insertBornRabbits(c->rl, getAdultsCount(c->rl, time) * 5 / 2, time);

	deleteOldRabbits(c->rl, time);

	printfRabbitList(c->rl);

}
