/*
 ============================================================================
 Name        : sisMonit.c
 Author      : Ana Margarida Cipriano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "colony.h"
#include "fox.h"
#include "rabbit.h"

int main(void) {

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

	Population rabbits, foxs;

	newPopulation(&rabbits, rstartBreedTime, rendBreedTime, radultAge,
			ravgTimeAge, ravgBreedsBySeason, ravgKitsByCouple);

	newPopulation(&foxs, fstartBreedTime, fendBreedTime, fadultAge, favgTimeAge,
			favgBreedsBySeason, favgKitsByCouple);

	Colony r = newColony(&rabbits);
	initColony(r, 20, 0, getRabbitID);
	printfColony(r);

	int i, max = 1;
	for (i = 0; i <= max; ++i) {
		updateColony(r, i);
		printf("time : %d\n", i);
		printfColony(r);
	}

	freeColony(r);

	exit(0);
}
