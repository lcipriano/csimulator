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
};

Colony newColony(int initCount, int atTime) {

	Colony nc = malloc(sizeof(struct colony));

	if (nc == NULL )
		return NULL ;

	nc->id = 1;

	int i;
	UDistri d = newUDistri(0, 2 * getRabbitAvgAge());
	for (i = 1; i <= initCount; ++i) {
		newRabbit(atTime - nextUDistriRandom(d), 1);
	}

	return nc;
}

void breedRabbits(Colony c, int time) {

	int adultRabbits = 0, i;
	RabbitList rl;
	Rabbit nr;

	/* count number of adults in rabbits */
	rl = getRabbitsByColony(c->id);
	while (nextRabbit(rl, &nr) != NULL ) {
		if (time >= nr.adultTime)
			adultRabbits++;
	}

	/* create new rabbits */
	adultRabbits = adultRabbits * (5 / 2);
	for (i = 1; i <= adultRabbits; ++i)
		newRabbit(time, c->id);

	/* remove old rabbits */
	removeOldRabbits(c->id, time);

}
