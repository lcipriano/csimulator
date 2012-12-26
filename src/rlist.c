/*
 * rabbits.c
 *
 *  Created on: Dec 18, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "rlist.h"
#include "smath.h"
#include "lists.h"
#include "date.h"

struct rList {
	List list;
};

/** */

RList newRabbitList() {

	RList rl = malloc(sizeof(struct rList));

	if (rl == NULL )
		return NULL ;

	rl->list = newList(sizeof(Rabbit));

	return rl;
}

void freeRabbitList(RList rl) {

	if (rl != NULL ) {
		freeList(rl->list);
		free(rl);
	}
}

Rabbit *insertRabbit(RList rl, Rabbit *pr) {

	if (rl == NULL || pr == NULL )
		return NULL ;

	return addListTail(rl->list, pr);
}

void insertNewRabbits(RList rl, int count, int birthTime) {

	int i;

	if (rl == NULL )
		return;

	Rabbit r;
	for (i = 1; i <= count; ++i)
		insertRabbit(rl, newRabbit(&r, birthTime));
}

int getRabbitsAdultsCount(RList rl, int time) {

	if (rl == NULL )
		return -1;

	int count = 0;
	ListIter iter = newListIter(rl->list);
	Rabbit *pr;

	if (iter != NULL ) {

		while ((pr = ListIterNext(iter, NULL )) != NULL )
			if (pr->adultTime <= time)
				count++;

		freeListIter(iter);
	}

	return count;
}

int getRabbitsCount(RList rl) {

	return getListCount(rl->list);
}

void deleteOldRabbits(RList rl, int timeLimit) {

	if (rl == NULL )
		return;

	List tmp = newList(sizeof(Rabbit));

	if (tmp == NULL )
		return;

	ListIter iter = newListIter(rl->list);

	if (iter == NULL ) {
		freeList(tmp);
		return;
	}

	/* copy young rabits to a tmp list */
	Rabbit *pr;
	while ((pr = ListIterNext(iter, NULL )) != NULL )
		if (pr->deathTime > timeLimit)
			addListTail(tmp, pr);
	freeListIter(iter);

	/* free actual list */
	freeList(rl->list);

	/* set the young list the actual rabbit list */
	rl->list = tmp;

}

void printfRabbitList(RList rl) {

	if (rl == NULL )
		return;

	ListIter iter = newListIter(rl->list);

	if (iter == NULL )
		return;

	Rabbit r;
	while (ListIterNext(iter, &r) != NULL )
		printfRabbit(&r);
	freeListIter(iter);

}

void removeRabbit(RList rl, int index) {

	Rabbit r;

	removeList(rl->list, &r, index);
}
