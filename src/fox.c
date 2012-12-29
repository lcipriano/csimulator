/*
 * foxs.c
 *
 *  Created on: Dec 25, 2012
 *      Author: lcipriano
 */

#include "fox.h"

/* FOXS */

/** início da temporada de gestação */
int fstartBreedTime = 4;
/** fim da temporada de gestação */
int fendBreedTime = 4;
/** idade adulta */
int fadultAge = 10;
/** tempo médio de vida */
int favgTimeAge = 60;
/** número médio de ninhadas por temporada */
int favgBreedsBySeason = 1;
/** numero médio de crias por casal */
int favgKitsByCouple = 2;

static Population foxs;
static int first = 1;

static void initFoxs() {

	if (first) {
		newPopulation(&foxs, fstartBreedTime, fendBreedTime, fadultAge,
				favgTimeAge, favgBreedsBySeason, favgKitsByCouple);
		first = 0;
	}
}

int getFoxID(void) {

	static int id = 1;

	return id++;
}

Population *getFoxPop() {

	initFoxs();

	return &foxs;
}
