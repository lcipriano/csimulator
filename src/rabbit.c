/*
 * rabbits.c
 *
 *  Created on: Dec 18, 2012
 *      Author: lcipriano
 */

#include <stdio.h>

#include "rabbit.h"

/** */
static PopType *rabbitType;

void initRabbits(PopType *pt) {

	rabbitType = pt;
}

Rabbit *newRabbit(Rabbit *nr, int birthTime) {

	return newAnimal(nr, rabbitType, birthTime);
}

void printfRabbit(Rabbit *r) {

	printf("Rabbit\n");

	printfAnimal(r);
}
