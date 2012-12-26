/*
 * alist.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef ALIST_H
#define ALIST_H

#include "animal.h"

typedef struct aList *AList;

AList newAnimalList();

void freeAnimalList(AList rl);

Animal *insertAnimal(AList rl, Animal *r);

void insertNewAnimals(AList rl, int count, int birthTime, PopType *pt);

void removeAnimal(AList rl, int index);

int getAnimalsCount(AList rl);

int getAdultsCount(AList rl, int time);

void deleteOldAnimals(AList rl, int timeLimit);

void printfAnimalList(AList rl);

#endif /* ALIST_H */
