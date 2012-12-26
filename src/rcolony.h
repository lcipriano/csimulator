/*
 * rcolony.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef RCOLONY_H_
#define RCOLONY_H_

#include "rlist.h"

typedef struct rColony *RColony;

void initRColony();
RColony newRColony(int initCount, int atTime);
void freeRColony(RColony c);
RColony newColonyWithRabbits(RList rl);
void updateRColony(RColony c, int time);
int huntRabbit(RColony rl);
void printfRColony(RColony c);

#endif /* RCOLONY_H_ */
