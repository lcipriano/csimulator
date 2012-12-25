/*
 * rabbits2.h
 *
 *  Created on: Dec 20, 2012
 *      Author: lcipriano
 */

#ifndef RABBITS_H_
#define RABBITS_H_

/*
 * Rabbit
 */

typedef struct {
	int id, birthTime, adultTime, deathTime;
} Rabbit;

void initRabbits();

int getStartRabbitBreedMonth();

int getEndRabbitBreedMonth();

int getNextRabbitTimeLife();

Rabbit *newRabbit(Rabbit *nr, int birthTime);

/**
 * Rabbit Lists
 */

typedef struct rList *RList;

RList newRabbitList();

void freeRabbitList(RList rl);

Rabbit *insertRabbit(RList rl, Rabbit *r);

void insertNewRabbits(RList rl, int count, int birthTime);

void removeRabbit(RList rl, int index);

int getRabbitsCount(RList rl);

int getAdultsCount(RList rl, int time);

void deleteOldRabbits(RList rl, int timeLimit);

void printfRabbit(Rabbit *r);

void printfRabbitList(RList rl);

#endif /* RABBITS_H_ */
