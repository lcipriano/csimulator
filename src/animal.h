/*
 * animal.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ANIMAL_H
#define ANIMAL_H

#include "population.h"

typedef struct {
	int id, birthTime, adultTime, deathTime;
	float x, y;
} Animal;

Animal *newAnimal(Animal *nr, Population *p,int birthTime);

void printfAnimal(Animal *r);

#endif /* ANIMAL_H */
