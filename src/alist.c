/*
 * alist.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "alist.h"
#include "smath.h"
#include "lists.h"
#include "date.h"

struct aList {
	List list;
};

/** */

AList newAnimalList() {

	AList al = malloc(sizeof(struct aList));

	if (al == NULL )
		return NULL ;

	al->list = newList(sizeof(Animal));

	return al;
}

void freeAnimalList(AList al) {

	if (al != NULL ) {
		freeList(al->list);
		free(al);
	}
}

Animal *insertAnimal(AList al, Animal *pr) {

	static int counter = 1;

	if (al == NULL || pr == NULL )
		return NULL ;

	Animal *nr;
	if ((nr = addListTail(al->list, pr)) != NULL )
		nr->id = counter++;
	return nr;
}

void insertNewAnimals(AList al, int count, int birthTime, PopType *pt) {

	int i;

	if (al == NULL )
		return;

	Animal r;
	for (i = 1; i <= count; ++i)
		insertAnimal(al, newAnimal(&r, pt, birthTime));
}

int getAdultsCount(AList al, int time) {

	if (al == NULL )
		return -1;

	int count = 0;
	ListIter iter = newListIter(al->list);
	Animal *pr;

	if (iter != NULL ) {

		while ((pr = ListIterNext(iter, NULL )) != NULL )
			if (pr->adultTime <= time)
				count++;

		freeListIter(iter);
	}

	return count;
}

int getAnimalsCount(AList al) {

	return getListCount(al->list);
}

void deleteOldAnimals(AList al, int timeLimit) {

	if (al == NULL )
		return;

	List tmp = newList(sizeof(Animal));

	if (tmp == NULL )
		return;

	ListIter iter = newListIter(al->list);

	if (iter == NULL ) {
		freeList(tmp);
		return;
	}

	/* copy youngs to a tmp list */
	Animal *pr;
	while ((pr = ListIterNext(iter, NULL )) != NULL )
		if (pr->deathTime > timeLimit)
			addListTail(tmp, pr);
	freeListIter(iter);

	/* free actual list */
	freeList(al->list);

	/* set the young list the actual Animal list */
	al->list = tmp;

}

void printfAnimalList(AList al) {

	if (al == NULL )
		return;

	ListIter iter = newListIter(al->list);

	if (iter == NULL )
		return;

	Animal r;
	while (ListIterNext(iter, &r) != NULL )
		printfAnimal(&r);
	freeListIter(iter);

}

void removeAnimal(AList al, int index) {

	Animal r;

	removeList(al->list, &r, index);
}
