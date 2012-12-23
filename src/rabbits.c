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

#include "rabbits.h"
#include "smath.h"
#include "lists.h"

#define R_ADULT_AGE 3
#define R_AVG_AGE 24

struct rList {
	List list;
};

static int nextRabbitID;
static UDistri rabbitDeathDistri;

static int isRabbitBreedSeason(int time) {
	printf("1- %d ", time);
	time = gmod(time, 12);
	/* consider between FEV and SET */
	printf("2- %d\n", time);
	return 1 <= time && time <= 8 ? 1 : 0;

}

static int getID() {
	return nextRabbitID++;
}

static int getAdultTime() {
	return 3;
}

int getRabbitDeathTime() {
	return nextUDistriRandom(rabbitDeathDistri);
}

void initRabbits() {
	nextRabbitID = 1;
	rabbitDeathDistri = newUDistri(0, 24);
}

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

Rabbit *newRabbit(Rabbit *nr, int birthTime) {

	if (!isRabbitBreedSeason(birthTime))
		return NULL ;

	if (nr == NULL )
		nr = malloc(sizeof(Rabbit));

	if (nr == NULL )
		return NULL ;

	int at, dt;

	nr->birthTime = birthTime;

	dt = birthTime + getRabbitDeathTime();
	at = birthTime + getAdultTime();
	if (dt < at)
		at = dt;
	nr->adultTime = at;
	nr->deathTime = dt;

	return nr;

}

Rabbit *insertRabbit(RList rl, Rabbit *pr) {

	if (rl == NULL || pr == NULL )
		return NULL ;

	if ((pr = addListTail(rl->list, pr)) != NULL )
		pr->id = getID();

	return pr;
}

void insertNewRabbits(RList rl, int count, int birthTime) {

	int i;

	if (rl == NULL )
		return;

	Rabbit r;
	for (i = 1; i <= count; ++i)
		insertRabbit(rl, newRabbit(&r, birthTime));
}

int getAdultsCount(RList rl, int time) {

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

void printfRabbit(Rabbit *r) {

	printf("ID:%2d BT:%2d AT:%2d DT:%2d\n", r->id, r->birthTime, r->adultTime,
			r->deathTime);
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
