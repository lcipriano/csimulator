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
	int id, birthTime, colony;
} Rabbit;

int initRabbits();

Rabbit *newRabbit(int birthDate, int colony);

int getRabbitTime(Rabbit *r, int time);

RabbitList getRabbitsByColony(int colID);

Rabbit *nextRabbit(RabbitList rl, Rabbit *r);

void freeRabbitList(RabbitList rl);

#endif /* RABBIT_H_ */
