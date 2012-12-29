/*
 * alist.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ALIST_H
#define ALIST_H

#include "animal.h"
#include "list.h"

typedef List AList;

/**
 * create a new Animal List
 *
 * @return a new Animal List or NULL if can't allocate memory
 */
AList newAnimalList();

void freeAnimalList(AList rl);

Animal *insertAnimal(AList rl, Animal *r);

Animal *removeAnimal(AList rl, Animal *a, int index);

Animal *removeRandAnimal(AList al, Animal *a);

int getAnimalsCount(AList rl);

int getAdultsCount(AList rl, int time);

AList removeOldAnimals(AList rl, int timeLimit);

void printfAnimalList(AList rl);

AList trimAnimalList(AList al, int newCount);

#endif /* ALIST_H */
