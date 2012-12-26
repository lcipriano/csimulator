/*
 * rlist.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef RLIST_H_
#define RLIST_H_

#include "rabbit.h"

typedef struct rList *RList;

RList newRabbitList();

void freeRabbitList(RList rl);

Rabbit *insertRabbit(RList rl, Rabbit *r);

void insertNewRabbits(RList rl, int count, int birthTime);

void removeRabbit(RList rl, int index);

int getRabbitsCount(RList rl);

int getRabbitsAdultsCount(RList rl, int time);

void deleteOldRabbits(RList rl, int timeLimit);

void printfRabbitList(RList rl);

#endif /* RLIST_H_ */
