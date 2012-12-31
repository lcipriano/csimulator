/*
 * colony.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef COLONY_H_
#define COLONY_H_

#include "ilist.h"
#include "specimen.h"

typedef struct colony *Colony;

Colony newColony(Specimen *pt);

void freeColony(Colony c);

void initColony(Colony c, int count, int time, int (*idGenerator)(void));

void setColonyIndividuals(Colony c, IList al);

IList getColonyIndividuals(Colony c);

void setColonyX(Colony c, float x);

void setColonyY(Colony c, float y);

void updateColony(Colony c, int time);

int getColonyCount(Colony c);

IList trimColony(Colony c, int newCount);

void printfColony(Colony c);

#endif /* COLONY_H_ */
