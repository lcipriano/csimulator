/*
 * animal.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <stdio.h>

#include "animal.h"

Animal *newAnimal(Animal *nr, PopType *p, int birthTime) {

	if (p == NULL )
		return NULL ;

	if (!isBreedSeason(p, birthTime))
		return NULL ;

	if (nr == NULL )
		nr = malloc(sizeof(Animal));

	if (nr == NULL )
		return NULL ;

	int at, dt;

	nr->birthTime = birthTime;

	dt = birthTime + getLifeAge(p);
	at = birthTime + getAdultAge(p);
	if (dt < at)
		at = dt;
	nr->adultTime = at;
	nr->deathTime = dt;

	return nr;

}

void printfAnimal(Animal *r) {

	printf("ID:%2d BT:%2d AT:%2d DT:%2d\n", r->id, r->birthTime, r->adultTime,
			r->deathTime);
}
