/*
 * rabbits.c
 *
 *  Created on: Dec 18, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "date.h"
#include "smath.h"
#include "rabbit.h"

/** */
static int nextRabbitID;
static UDistri rabbitDeathDistri;

/** Rabbit Constansts in months */
static int startBreedMonth;
static int endBreedMonth;
static int averageRabbitLife;

void initRabbits() {

	nextRabbitID = 1;
	averageRabbitLife = 24;
	startBreedMonth = FEV;
	endBreedMonth = SET;

	rabbitDeathDistri = newUDistri(0, averageRabbitLife * 2);
}

int getStartRabbitBreedMonth() {
	return startBreedMonth;
}

int getEndRabbitBreedMonth() {
	return endBreedMonth;
}

static int isRabbitBreedSeason(int time) {

	time = gmod(time, 12);
	return getStartRabbitBreedMonth() <= time
			&& time <= getEndRabbitBreedMonth() ? 1 : 0;
}

static int getNextRabbitID() {
	return nextRabbitID++;
}

static int getNextRabitAdultAge() {
	return 3;
}

int getNextRabbitTimeLife() {
	return nextUDistriRandom(rabbitDeathDistri);
}

Rabbit *newRabbit(Rabbit *nr, int birthTime) {

	if (!isRabbitBreedSeason(birthTime))
		return NULL ;

	if (nr == NULL )
		nr = malloc(sizeof(Rabbit));

	if (nr == NULL )
		return NULL ;

	int at, dt;

	nr->birthTime = birthTime;

	dt = birthTime + getNextRabbitTimeLife();
	at = birthTime + getNextRabitAdultAge();
	if (dt < at)
		at = dt;
	nr->adultTime = at;
	nr->deathTime = dt;
	nr->id = getNextRabbitID();

	return nr;

}

void printfRabbit(Rabbit *r) {

	printf("Rabbit#%2d BT:%2d AT:%2d DT:%2d\n", r->id, r->birthTime,
			r->adultTime, r->deathTime);
}
