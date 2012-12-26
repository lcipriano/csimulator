/*
 * rabbit.h
 *
 *  Created on: Dec 20, 2012
 *      Author: lcipriano
 */

#ifndef RABBIT_H_
#define RABBIT_H_

#include "animal.h"
#include "poptype.h"

typedef Animal Rabbit;

void initRabbits(PopType *pt);

Rabbit *newRabbit(Rabbit *nr, int birthTime);

void printfRabbit(Rabbit *r);

#endif /* RABBIT_H_ */
