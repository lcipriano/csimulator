/*
 * animal.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ANIMAL_H
#define ANIMAL_H

typedef struct {
	int id, birthTime, adultTime, deathTime;
	float x, y, energy;
} Animal;

void printfAnimal(Animal *r);

int getAnimalAge(Animal *a,int time);

#endif /* ANIMAL_H */
