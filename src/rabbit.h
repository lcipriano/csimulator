/*
 * rabbit.h
 *
 *  Created on: Dec 20, 2012
 *      Author: lcipriano
 */

#ifndef RABBIT_H_
#define RABBIT_H_

typedef struct {
	int id, birthTime, adultTime, deathTime;
	float x, y;
} Rabbit;

void initRabbits();

int getStartRabbitBreedMonth();

int getEndRabbitBreedMonth();

int getNextRabbitTimeLife();

Rabbit *newRabbit(Rabbit *nr, int birthTime);

int getNextRabbitID();

void printfRabbit(Rabbit *r);

#endif /* RABBIT_H_ */
