/*
 * animal.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ANIMAL_H
#define ANIMAL_H

#include "message.h"

typedef struct {
	int id, birthTime, adultTime, deathTime, specimen;
	float x, y, energy;
} Individual;

void printfIndividual(Individual *r);

int getIndividualAge(Individual *a, int time);

Message getIndividualMsg(Individual *a);

#endif /* ANIMAL_H */
