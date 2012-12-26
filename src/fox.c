/*
 * foxs.c
 *
 *  Created on: Dec 25, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "fox.h"
#include "smath.h"
#include "date.h"
#include "area.h"

/** */
static int nextFoxID;
static UDistri foxDeathDistri;

/** Fox Constansts */
static int breedMonth;
static int averageFoxLife;

int getFoxBreedMonth() {
	return breedMonth;
}

static int isFoxBreedSeason(int time) {

	return gmod(time, 12) == breedMonth ? 1 : 0;
}

static int getNextFoxID() {
	return nextFoxID++;
}

static int getNextFoxAdultAge() {
	return 10;
}

int getNextFoxTimeLife() {
	return nextUDistriRandom(foxDeathDistri);
}

void initFoxs() {

	nextFoxID = 1;
	/** time in months */
	averageFoxLife = 60;
	breedMonth = ABR;

	foxDeathDistri = newUDistri(0, averageFoxLife * 2);
}

Fox *newFox(Fox *nf, int birthTime, float x, float y) {

	if (!isFoxBreedSeason(birthTime))
		return NULL ;

	if (nf == NULL )
		nf = malloc(sizeof(Fox));

	if (nf == NULL )
		return NULL ;

	int at, dt;

	nf->birthTime = birthTime;

	dt = birthTime + getNextFoxTimeLife();
	at = birthTime + getNextFoxAdultAge();
	if (dt < at)
		at = dt;
	nf->adultTime = at;
	nf->deathTime = dt;
	nf->x = x;
	nf->y = y;
	nf->id = getNextFoxID();

	return nf;

}

void printfFox(Fox *r) {

	printf("Fox#%2d BT:%2d AT:%2d DT:%2d\n", r->id, r->birthTime, r->adultTime,
			r->deathTime);
}

