/*
 * alist.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ALIST_H
#define ALIST_H

#include "individual.h"
#include "list.h"

typedef List IList;

/**
 * create a new Animal List
 *
 * @return a new Animal List or NULL if can't allocate memory
 */
IList newIndividualList();

void freeIndividualList(IList rl);

Individual *insertIndividual(IList rl, Individual *r);

Individual *removeIndividual(IList rl, Individual *a, int index);

Individual *removeRandIndividual(IList al, Individual *a);

int getIndividualsCount(IList rl);

int getAdultsCount(IList rl, int time);

IList removeOldIndividuals(IList rl, int timeLimit);

void printfIndividualList(IList rl);

/**
 * trims a list to a new size
 *
 * @param the list to trim
 * @param the new list size less then the original size
 * @return a new list with the excess elements
 */

IList trimIndividualList(IList al, int newCount);

#endif /* ALIST_H */
