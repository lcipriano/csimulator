/*
 * colony.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef COLONY_H_
#define COLONY_H_

typedef struct colony *Colony;

Colony newColony(int id, int initCount, int atTime);
Colony newColonyWithRabbits();
void updateColony(Colony c, int time);

#endif /* COLONY_H_ */
