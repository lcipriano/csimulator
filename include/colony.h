/*
 * colony.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef COLONY_H_
#define COLONY_H_

typedef struct colony *Colony;

Colony newColony(int initCount);
void upDateColony(int time);
int getRabbitCount(Colony);

#endif /* COLONY_H_ */
