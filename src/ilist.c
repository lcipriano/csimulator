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

#include "ilist.h"
#include "smath.h"

IList newIndividualList() {

	return newList(sizeof(Individual));
}

void freeIndividualList(IList al) {

	freeList(al);
}

Individual *insertIndividual(IList al, Individual *pr) {

	return addListTail(al, pr);
}

Individual *getAnimal(IList al, Individual *a, int index) {

	return getListAt(al, a, index);

}

int getAdultsCount(IList al, int time) {

	ListIter iter = newListIter(al);
	if (iter == NULL )
		return -1;

	Individual *pr;
	int count = 0;

	while ((pr = ListIterNext(iter, NULL )) != NULL )
		if (time >= pr->adultTime)
			count++;
	freeListIter(iter);

	return count;
}

int getIndividualsCount(IList al) {

	return getListCount(al);
}

IList removeOldIndividuals(IList actual, int timeLimit) {

	if (actual == NULL )
		return NULL ;

	IList new = newIndividualList();
	if (new == NULL )
		return NULL ;

	ListIter iter = newListIter(actual);
	if (iter == NULL ) {
		freeList(new);
		return NULL ;
	}

	/* copy youngs to a new list */
	Individual *pr;
	while ((pr = ListIterNext(iter, NULL )) != NULL ) {
		/*printf("death\n");
		 printfAnimal(pr);*/
		if (pr->deathTime > timeLimit)
			insertIndividual(new, pr);
	}
	freeListIter(iter);

	/* free actual list */
	freeList(actual);

	return new;

}

void printfIndividualList(IList al) {

	ListIter iter = newListIter(al);
	if (iter == NULL )
		return;

	printf("AList Total = %d\n", getIndividualsCount(al));

	Individual r;
	while (ListIterNext(iter, &r) != NULL )
		printfIndividual(&r);
	freeListIter(iter);
}

Individual *removeIndividual(IList al, Individual *a, int index) {

	return removeListAt(al, a, index);
}

Individual *removeRandIndividual(IList al, Individual *a) {

	int count = getIndividualsCount(al);

	if (count <= 0)
		return NULL ;

	/* generate a uniform distribution with the number of Animals */
	UDistri d = newUDistri(1, count);

	return removeIndividual(al, a, nextUDistriRandom(d));
}

IList trimIndividualList(IList al, int newCount) {

	int actualCount = getListCount(al);

	/* !(1<= newCount < actualCount) */

	if (!(1 <= newCount && newCount < actualCount))
		return NULL ;

	IList list = newIndividualList();
	if (list == NULL )
		return NULL ;

	Individual a;
	int i;
	for (i = newCount + 1; i <= actualCount; ++i)
		insertIndividual(list, removeRandIndividual(al, &a));

	return list;
}
