/*
 * zone.h
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#ifndef ZONE_H_
#define ZONE_H_

#include "colony.h"

typedef struct zone *Zone;

Zone newZone(int x, int y);

void freeZone(Zone z);

AList updateZone(Zone z, int time);

Colony getZoneColony(Zone z);

void setZoneColony(Zone z, Colony c);

int getZoneMax(Zone z);

int huntRabbit(Zone z);

void printfZone(Zone z);

void setZoneUpdate(Zone z);

#endif /* ZONE_H_ */
