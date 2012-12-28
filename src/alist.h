/*
 * alist.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ALIST_H
#define ALIST_H

#include "animal.h"
#include "lists.h"

typedef List AList;

AList newAnimalList();

void freeAnimalList(AList rl);

Animal *insertAnimal(AList rl, Animal *r);

void insertNewAnimals(AList rl, int count, int birthTime, PopType *pt);

Animal *removeAnimal(AList rl, Animal *a, int index);

Animal *removeRandAnimal(AList al, Animal *a);

int getAnimalsCount(AList rl);

int getAdultsCount(AList rl, int time);

AList deleteOldAnimals(AList rl, int timeLimit);

void printfAnimalList(AList rl);

AList trimAnimalList(AList al, int count);

#endif /* ALIST_H */
