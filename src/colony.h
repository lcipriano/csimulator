/*
 * colony.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef COLONY_H_
#define COLONY_H_

#include "rabbits.h"

typedef struct colony *Colony;

void initColony();
Colony newColony(int initCount, int atTime);
void freeColony(Colony c);
Colony newColonyWithRabbits(RList rl);
void updateColony(Colony c, int time);
int huntRabbit(Colony rl);
void printfColony(Colony c);

#endif /* COLONY_H_ */
