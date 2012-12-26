/*
 * animal.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ANIMAL_H
#define ANIMAL_H

#include "poptype.h"

typedef struct {
	int id, birthTime, adultTime, deathTime;
	float x, y, energy;
} Animal;

Animal *newAnimal(Animal *nr, PopType *p, int birthTime);

void printfAnimal(Animal *r);

#endif /* ANIMAL_H */
