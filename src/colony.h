/*
 * colony.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef COLONY_H_
#define COLONY_H_

#include "alist.h"
#include "population.h"

typedef struct colony *Colony;

Colony newColony(Population *pt);

void freeColony(Colony c);

void initColony(Colony c, int count, int time, int (*idGenerator)(void));

void setColonyAnimals(Colony c, AList al);

AList getColonyAnimals(Colony c);

void updateColony(Colony c, int time);

int getColonyCount(Colony c);

AList trimColony(Colony c, int newCount);

void printfColony(Colony c);

#endif /* COLONY_H_ */
