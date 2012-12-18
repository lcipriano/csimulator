/*
 * colony.c
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>

#include <LinkedList.h>
#include "colony.h"

struct colony {
	int id;
	int rabbitCount;
	int rabbitID;
};

Colony newColony(int initCount) {
	return NULL ;
}

void breedRabbits(Colony c, int time) {

	int newRabbits = c->rabbitCount * 5 / 2;
	int i;

	for (i = 1; i <= newRabbits; i++) {
		/*newRabbit(time, c->id);*/
	}
}
