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

Colony newColony(PopType *pt, int initCount, int atTime);
void freeColony(Colony c);
Colony newColonyWithRabbits(AList rl);
void updateColony(Colony c, int time);
int huntRabbit(Colony rl);
void printfColony(Colony c);

#endif /* COLONY_H_ */
