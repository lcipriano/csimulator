/*
 * poptype.h
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#ifndef POPTYPE_H_
#define POPTYPE_H_

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

} PopType;

PopType *newPopType(PopType *p, int sbt, int ebt, int at, int atl,
		int abs, int akc);

int getNextID(PopType *p);

int getLifeAge(PopType *p);

int getAdultAge(PopType *p);

int getBreeds(PopType *p);

int getKits(PopType *p);

int isBreedSeason(PopType *p, int time);

#endif /* POPTYPE_H_ */
