/*
 * rabbits.c
 *
 *  Created on: Dec 18, 2012
 *      Author: lcipriano
 */

#include <stddef.h>

#include "rlist.h"

RList newRabbitList() {
	return newAnimalList();
}

Rabbit *insertRabbit(RList rl, Rabbit *pr) {
	return insertAnimal(rl, pr);
}

void insertNewRabbits(RList rl, int count, int birthTime) {

	int i;
	Rabbit r;

	for (i = 1; i <= count; ++i)
		insertRabbit(rl, newRabbit(&r, birthTime));
}

int getRabbitsAdultsCount(RList rl, int time) {
	return getAdultsCount(rl, time);
}

int getRabbitsCount(RList rl) {
	return getAnimalsCount(rl);
}

void deleteOldRabbits(RList rl, int timeLimit) {
	return deleteOldAnimals(rl, timeLimit);
}

void printfRabbitList(RList rl) {

	printfAnimalList(rl);

}

void removeRabbit(RList rl, int index) {
	return removeAnimal(rl, index);
}
