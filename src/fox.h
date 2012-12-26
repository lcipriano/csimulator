/*
 * foxs.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef FOX_H_
#define FOX_H_

typedef struct {
	float x, y;
	int id, birthTime, adultTime, deathTime;
	float energy;
} Fox;

void initFoxs();

Fox *newFox(Fox *f, int birth, float x, float y);

void eat(Fox *f);

int getFoxBreedMonth();

int getNextFoxTimeLife();

void printfFox(Fox *r);

#endif /* FOX_H_ */
