/*
 * rabbit.h
 *
 *  Created on: Dec 18, 2012
 *      Author: lcipriano
 */

#ifndef RABBIT_H_
#define RABBIT_H_

typedef struct rabbitList *RabbitList;

typedef struct {
	int id, birthTime, adultTime, deathTime, colony;
} Rabbit;

int initRabbits();

Rabbit *newRabbit(int birthDate, int colony);

int getRabbitTime(Rabbit *r, int time);

RabbitList getRabbitsByColony(int colID);

void printfRabbitsByColony(int colID);

Rabbit *nextRabbit(RabbitList rl, Rabbit *r);

void freeRabbitList(RabbitList rl);

int getRabbitAvgAge();

int removeRabbitByID(int ID);

void removeOldRabbits(int colID, int time);

#endif /* RABBIT_H_ */
