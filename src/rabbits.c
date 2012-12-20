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
#include <time.h>

#include "rabbits.h"
#include "smath.h"

#define R_ADULT_AGE 3
#define R_AVG_AGE 24

struct rabbitList {
	LinkedListIterator theIterator;
	int filter;
};

/*
 * rabbits dbase vars
 */
static LinkedList rabbits = NULL;
static int nextRabbitID = 0;
static UDistri rabbitDeathDistri;

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
	UDistri newUDistri(float a, float sb);
	srand(time(NULL ));
	rabbitDeathDistri = newUDistri(0, 2 * R_AVG_AGE);
	atexit(exitRabbits);

	return rabbits == NULL ? 1 : 0;
}

Rabbit *newRabbit(int birthTime, int colony) {

	Rabbit r;
	int at, dt;

	r.id = nextRabbitID;
	r.birthTime = birthTime;
	r.colony = colony;

	dt = birthTime + nextUDistriRandom(rabbitDeathDistri);
	at = birthTime + R_ADULT_AGE;
	if (dt < at)
		at = dt;

	r.adultTime = at;
	r.deathTime = dt;

	Rabbit *pr;
	if ((pr = addLinkedListTail(rabbits, &r)) != NULL )
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
		if (pr->colony == rl->filter) {
			memmove(r, &nr, sizeof(Rabbit));
			return pr;
		}
	}

	freeRabbitList(rl);

	return pr;
}

void freeRabbitList(RabbitList rl) {

	if (rl != NULL ) {
		freeLinkedListIterator(rl->theIterator);
		free(rl);
	}
}

int getRabbitAvgAge() {
	return R_AVG_AGE;
}

int removeRabbitByID(int ID) {

	LinkedListIterator iter = newRabbitsIter();

	if (iter == NULL )
		return 1;

	Rabbit *pr;
	Rabbit nr;
	while ((pr = LinkedListIteratorNext(iter, &nr)) != NULL ) {
		if (pr->id == ID) {
			removeLinkedList(rabbits, &nr, getLinkedListIteratorPos(iter) - 1);
			return 0;
		}
	}

	return 1;
}

void printfRabbitsByColony(int colID) {

	RabbitList rl = getRabbitsByColony(colID);
	Rabbit r;

	printf("\n");
	while (nextRabbit(rl, &r) != NULL ) {
		printf("Col:%2d ID:%2d BT:%2d AT:%2d DT:%2d\n", r.colony, r.id,
				r.birthTime, r.adultTime, r.deathTime);

	}

}

void removeOldRabbits(int colID, int time) {

	LinkedList indexs = newLinkedList(sizeof(int));
	LinkedListIterator r = newLinkedListIterator(rabbits);
	Rabbit nr;
	int index, count;

	while (LinkedListIteratorNext(r, &nr) != NULL ) {
		if (time >= nr.deathTime) {
			index = getLinkedListIteratorPos(r) - 1;
			addLinkedListTail(indexs, &index);
		}
	}

	freeLinkedListIterator(r);
	count = 0;
	while (removeLinkedListHead(indexs, &index) != NULL ) {
		removeLinkedList(rabbits, &nr, index - count);
		count++;
	}

	freeLinkedList(indexs);
}
