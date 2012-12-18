/*
 * rabbits.c
 *
 *  Created on: Dec 18, 2012
 *      Author: lcipriano
 */

#include <LinkedList.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rabbits.h"

struct rabbitList {
	LinkedListIterator theIterator;
	int filter;
};

static LinkedList rabbits = NULL;
static int nextRabbitID = 0;

static LinkedListIterator newRabbitsIter() {

	return newLinkedListIterator(rabbits);
}

static RabbitList newRabbitList(LinkedListIterator theIter, int theFilter) {

	if (theIter == NULL || theFilter < 1)
		return NULL ;

	RabbitList rl = malloc(sizeof(struct rabbitList));

	if (rl != NULL ) {
		rl->theIterator = theIter;
		rl->filter = theFilter;
	}

	return rl;
}

static void exitRabbits() {

	freeLinkedList(rabbits);
}

int initRabbits() {

	rabbits = newLinkedList(sizeof(Rabbit));
	nextRabbitID = 1;
	atexit(exitRabbits);

	return rabbits == NULL ? 1 : 0;
}

Rabbit *newRabbit(int birthTime, int colony) {

	Rabbit r = { nextRabbitID, birthTime, colony };
	Rabbit *pr = addLinkedListLast(rabbits, &r);

	if (pr != NULL )
		nextRabbitID++;

	return pr;
}

int getRabbitTime(Rabbit *r, int time) {

	return time - r->birthTime;
}

RabbitList getRabbitsByColony(int colID) {

	LinkedListIterator iter = newRabbitsIter();

	return iter == NULL ? NULL : newRabbitList(iter, colID);

}

Rabbit *nextRabbit(RabbitList rl, Rabbit *r) {

	if (rl == NULL || r == NULL )
		return NULL ;

	Rabbit nr;
	Rabbit *pr;
	while ((pr = LinkedListIteratorNext(rl->theIterator, &nr)) != NULL ) {
		/*printf("*ID = %d Col = %d\n", pr->id, pr->colony);*/
		if (pr->colony == rl->filter)
			break;
	}

	memmove(r, &nr, sizeof(Rabbit));
	return pr;
}

void freeRabbitList(RabbitList rl) {

	if (rl != NULL ) {
		freeLinkedListIterator(rl->theIterator);
		free(rl);
	}
}

