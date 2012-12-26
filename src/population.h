/*
 * animal.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include "date.h"
#include "smath.h"

typedef struct {

	int nextID;

	/** início da temporada de gestação */
	int startBreedTime;

	/** fim da temporada de gestação */
	int endBreedTime;

	/** idade adulta */
	int adultAge;

	/** tempo médio de vida */
	int avgTimeAge;

	/** número médio de ninhadas por temporada */
	int avgBreedsBySeason;

	/** numero médio de crias por casal */
	int avgKitsByCouple;

	/** gerador aleatório de ninhadas por mês */
	PoDistri breedsDistri;

	/** gerador aleatório de tempo de vida */
	UDistri timeLifeDistri;

	/** gerador aleatório de crias por casal */
	PoDistri kitsDistri;

} Population;

Population *newPopulation(Population *p,int sbt, int ebt, int at, int atl, int abs, int akc);

int getNextID(Population *p);

int getLifeAge(Population *p);

int getAdultAge(Population *p);

int getBreeds(Population *p);

int getKits(Population *p);

int isBreedSeason(Population *p,int time);
