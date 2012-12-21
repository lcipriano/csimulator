/*
 * rabbits2.h
 *
 *  Created on: Dec 20, 2012
 *      Author: lcipriano
 */

#ifndef RABBITS2_H_
#define RABBITS2_H_

typedef struct rabbitList *RabbitList;

typedef struct {
	int id, birthTime, adultTime, deathTime;
} Rabbit;

void initRabbits();

Rabbit newRabbit(int birthTime);

Rabbit *insertRabbit(RabbitList rl, Rabbit r);

RabbitList newRabbitList();

void freeRabbitList(RabbitList rl);

void insertBornRabbits(RabbitList rl, int count, int birthTime);

int getAdultsCount(RabbitList rl, int time);

void deleteOldRabbits(RabbitList rl, int timeLimit);

void printfRabbit(Rabbit r);

void printfRabbitList(RabbitList rl);

int getDeathTime();

int getAdultCount(RabbitList rl, int time);

#endif /* RABBITS2_H_ */
