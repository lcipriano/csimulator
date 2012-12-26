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

#include "flist.h"
#include "smath.h"
#include "lists.h"
#include "date.h"
#include "area.h"

struct fList {
	List list;
};

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

Fox *insertFox(FList fl, Fox *pr) {

	if (fl == NULL || pr == NULL )
		return NULL ;

	return addListTail(fl->list, pr);
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

