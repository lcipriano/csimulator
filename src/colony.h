/*
 * colony.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef COLONY_H_
#define COLONY_H_

#include "alist.h"
#include "poptype.h"

typedef struct colony *Colony;

Colony newColony(PopType *pt);
void initColony(Colony c, int count, int time);
void setAList(Colony c, AList al);
AList getAList(Colony c);
void freeColony(Colony c);
void updateColony(Colony c, int time);
int getColonyCount(Colony c);
void printfColony(Colony c);
void removeFromColony(Colony c, Animal *a, int index);

#endif /* COLONY_H_ */
