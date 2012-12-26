/*
 * foxs.c
 *
 *  Created on: Dec 25, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "foxs.h"
#include "smath.h"
#include "lists.h"
#include "date.h"
#include "area.h"

struct fList {
	List list;
};

/** */
static int nextFoxID;
static UDistri foxDeathDistri;

/** Fox Constansts */
static int breedMonth;
static int averageFoxLife;

int getFoxBreedMonth() {
	return breedMonth;
}

static int isFoxBreedSeason(int time) {

	return gmod(time, 12) == breedMonth ? 1 : 0;
}

static int getNextFoxID() {
	return nextFoxID++;
}

static int getNextFoxAdultAge() {
	return 12;
}

int getNextFoxTimeLife() {
	return nextUDistriRandom(foxDeathDistri);
}

void initFoxs() {

	nextFoxID = 1;
	/** time in months */
	averageFoxLife = 60;
	breedMonth = ABR;

	foxDeathDistri = newUDistri(0, averageFoxLife * 2);
}

FList newFoxList() {

	FList fl = malloc(sizeof(struct fList));

	if (fl == NULL )
		return NULL ;

	fl->list = newList(sizeof(Fox));

	return fl;
}

void freeFoxList(FList fl) {

	if (fl != NULL ) {
		freeList(fl->list);
		free(fl);
	}
}

Fox *newFox(Fox *nf, int birthTime, float x, float y) {

	if (!isFoxBreedSeason(birthTime))
		return NULL ;

	if (nf == NULL )
		nf = malloc(sizeof(Fox));

	if (nf == NULL )
		return NULL ;

	int at, dt;

	nf->birthTime = birthTime;

	dt = birthTime + getNextFoxTimeLife();
	at = birthTime + getNextFoxAdultAge();
	if (dt < at)
		at = dt;
	nf->adultTime = at;
	nf->deathTime = dt;
	nf->x = x;
	nf->y = y;

	return nf;

}

Fox *insertFox(FList fl, Fox *pr) {

	if (fl == NULL || pr == NULL )
		return NULL ;

	if ((pr = addListTail(fl->list, pr)) != NULL )
		pr->id = getNextFoxID();

	return pr;
}

void insertNewFoxs(FList fl, int count, int birthTime) {

	if (fl == NULL )
		return;

	Fox r;
	int i;
	float x, y;
	getRandomCoords(&x, &y);
	for (i = 1; i <= count; ++i)
		insertFox(fl, newFox(&r, birthTime, x, y));
}

int getFoxsAdultsCount(FList fl, int time) {

	if (fl == NULL )
		return -1;

	int count = 0;
	ListIter iter = newListIter(fl->list);
	Fox *pr;

	if (iter != NULL ) {

		while ((pr = ListIterNext(iter, NULL )) != NULL )
			if (pr->adultTime <= time)
				count++;

		freeListIter(iter);
	}

	return count;
}

int getFoxsCount(FList fl) {

	return getListCount(fl->list);
}

void deleteOldFoxs(FList fl, int timeLimit) {

	if (fl == NULL )
		return;

	List tmp = newList(sizeof(Fox));

	if (tmp == NULL )
		return;

	ListIter iter = newListIter(fl->list);

	if (iter == NULL ) {
		freeList(tmp);
		return;
	}

	/* copy young rabits to a tmp list */
	Fox *pr;
	while ((pr = ListIterNext(iter, NULL )) != NULL )
		if (pr->deathTime > timeLimit)
			addListTail(tmp, pr);
	freeListIter(iter);

	/* free actual list */
	freeList(fl->list);

	/* set the young list the actual Fox list */
	fl->list = tmp;

}

void printfFox(Fox *r) {

	printf("ID:%2d BT:%2d AT:%2d DT:%2d\n", r->id, r->birthTime, r->adultTime,
			r->deathTime);
}

void printfFoxList(FList fl) {

	if (fl == NULL )
		return;

	ListIter iter = newListIter(fl->list);

	if (iter == NULL )
		return;

	Fox r;
	while (ListIterNext(iter, &r) != NULL )
		printfFox(&r);
	freeListIter(iter);

}

void removeFox(FList fl, int index) {

	Fox r;

	removeList(fl->list, &r, index);
}

