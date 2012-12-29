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

AList newAnimalList() {

	return newList(sizeof(Animal));
}

void freeAnimalList(AList al) {

	freeList(al);
}

Animal *insertAnimal(AList al, Animal *pr) {

	return addListTail(al, pr);
}

Animal *getAnimal(AList al, Animal *a, int index) {

	return getListAt(al, a, index);

}

int getAdultsCount(AList al, int time) {

	ListIter iter = newListIter(al);
	if (iter == NULL )
		return -1;

	Animal *pr;
	int count = 0;

	while ((pr = ListIterNext(iter, NULL )) != NULL )
		if (time >= pr->adultTime)
			count++;
	freeListIter(iter);

	return count;
}

int getAnimalsCount(AList al) {

	return getListCount(al);
}

AList removeOldAnimals(AList actual, int timeLimit) {

	if (actual == NULL )
		return NULL ;

	AList new = newAnimalList();
	if (new == NULL )
		return NULL ;

	ListIter iter = newListIter(actual);
	if (iter == NULL ) {
		freeList(new);
		return NULL ;
	}

	/* copy youngs to a tmp list */
	Animal *pr;
	while ((pr = ListIterNext(iter, NULL )) != NULL ) {
		/*printf("death\n");
		 printfAnimal(pr);*/
		if (pr->deathTime > timeLimit)
			insertAnimal(new, pr);
	}
	freeListIter(iter);

	/* free actual list */
	freeList(actual);

	return new;

}

void printfAnimalList(AList al) {

	ListIter iter = newListIter(al);
	if (iter == NULL )
		return;

	Animal r;
	while (ListIterNext(iter, &r) != NULL )
		printfAnimal(&r);
	freeListIter(iter);
}

Animal *removeAnimal(AList al, Animal *a, int index) {

	return removeListAt(al, a, index);
}

Animal *removeRandAnimal(AList al, Animal *a) {

	int count = getAnimalsCount(al);

	if (count <= 0)
		return NULL ;

	/* generate a uniform distribution with the number of Animals */
	UDistri d = newUDistri(1, count);

	return removeAnimal(al, a, nextUDistriRandom(d));
}

AList trimAnimalList(AList al, int newCount) {

	int actualCount = getListCount(al);

	/* !(1<= newCount < actualCount) */

	if (!(1 <= newCount && newCount < actualCount))
		return NULL ;

	AList list = newAnimalList();
	if (list == NULL )
		return NULL ;

	Animal a;
	int i;
	for (i = newCount + 1; i <= actualCount; ++i) {
		insertAnimal(list, removeRandAnimal(al, &a));
		actualCount--;
	}

	return list;
}
