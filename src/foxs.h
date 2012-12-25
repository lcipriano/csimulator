/*
 * foxs.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef FOXS_H_
#define FOXS_H_

/**
 * Foxs
 */

typedef struct {
	/* location */
	float x, y;
	int id, birthTime, adultTime, deathTime;
	float energy;

} Fox;

Fox *newFox(Fox *f, int birth, float x, float y);
void eat(Fox *f);

void initFoxs();

int getFoxBreedMonth();

int getNextFoxTimeLife();

/**
 * Fox Lists
 */

typedef struct fList *FList;

FList newFoxList();

void freeFoxList(FList rl);

Fox *insertFox(FList rl, Fox *r);

void insertNewFoxs(FList rl, int count, int birthTime);

void removeFox(FList rl, int index);

int getFoxsCount(FList rl);

int getFoxsAdultsCount(FList rl, int time);

void deleteOldFoxs(FList rl, int timeLimit);

void printfFox(Fox *r);

void printfFoxList(FList rl);

#endif /* FOXS_H_ */
