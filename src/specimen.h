/*
 * poptype.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef POPTYPE_H_
#define POPTYPE_H_

#include "smath.h"

typedef struct {

	int type;

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

} Specimen;

Specimen *newPopulation(Specimen *p, int type, int sbt, int ebt, int at,
		int atl, int abs, int akc);

int getSpecimenID(Specimen *p);

int getLifeAge(Specimen *p);

int getAdultAge(Specimen *p);

int getBreeds(Specimen *p);

int getKits(Specimen *p);

int isBreedSeason(Specimen *p, int time);

#endif /* POPTYPE_H_ */
