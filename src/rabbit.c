/*
 * rabbit.c
 *
 *  Created on: Dec 25, 2012
 *      Author: lcipriano
 */

#include "rabbit.h"

/* RABBITS */

/** início da temporada de gestação */
int rstartBreedTime = 1;
/** fim da temporada de gestação */
int rendBreedTime = 8;
/** idade adulta */
int radultAge = 3;
/** tempo médio de vida */
int ravgTimeAge = 24;
/** número médio de ninhadas por temporada */
int ravgBreedsBySeason = 9;
/** numero médio de crias por casal */
int ravgKitsByCouple = 5;

static Population rabbits;
static int first = 1;

static void initRabbits() {

	if (first) {
		newPopulation(&rabbits, rstartBreedTime, rendBreedTime, radultAge,
				ravgTimeAge, ravgBreedsBySeason, ravgKitsByCouple);
		first = 0;
	}
}

int getRabbitID(void) {

	static int id = 1;

	return id++;
}

Population *getRabbitPop() {

	initRabbits();

	return &rabbits;
}
