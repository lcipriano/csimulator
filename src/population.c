/*
 * population.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>

#include "population.h"

Population *newPopulation(Population *p, int sbt, int ebt, int at, int atl,
		int abs, int akc) {

	if (p == NULL )
		p = malloc(sizeof(Population));

	if (p == NULL )
		return NULL ;

	p->nextID = 1;

	/** início da temporada de gestação */
	p->startBreedTime = sbt;

	/** fim da temporada de gestação */
	p->endBreedTime = ebt;

	/** idade adulta */
	p->adultTime = at;

	/** tempo médio de vida */
	p->avgTimeLife = atl;

	/** número médio de ninhadas por temporada */
	p->avgBreedsBySeason = abs;

	/** numero médio de crias por casal */
	p->avgKitsByCouple = akc;

	/** gerador aleatório de ninhadas por mês */
	p->breedsDistri = newPoDistri((float) (ebt - sbt + 1) / abs);

	/** gerador aleatório de tempo de vida */
	p->timeLifeDistri = newUDistri(0, 2 * atl);

	/** gerador aleatório de crias por casal */
	p->kitsDistri = newPoDistri(akc);

	return p;

}

int getNextID(Population *p) {
	return p != NULL ? p->nextID++ : -1;
}

int getStartBreedTime(Population *p) {
	return p != NULL ? p->startBreedTime : -1;
}

int getEndBreedTime(Population *p) {
	return p != NULL ? p->endBreedTime : -1;
}

int getLifeDuration(Population *p) {
	return p != NULL ? nextUDistriRandom(p->timeLifeDistri) : -1;
}

int getBreeds(Population *p) {
	return p != NULL ? nextPoDistriRandom(p->breedsDistri) : -1;
}

int getKits(Population *p) {
	return p != NULL ? nextPoDistriRandom(p->kitsDistri) : -1;
}
