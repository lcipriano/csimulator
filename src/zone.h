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

Zone newZone(float x0, float y0, float x1, float y1, int line, int col);

void freeZone(Zone z);

IList updateZone(Zone z, int time);

Colony getZoneColony(Zone z);

void setZoneColony(Zone z, Colony c);

int getZoneMax(Zone z);

float getZoneCenterX(Zone z);

float getZoneCenterY(Zone z);

float getZoneRandomX(Zone z);

float getZoneRandomY(Zone z);

int getZoneCount(Zone z);

int huntZoneRabbit(Zone z);

void printfZone(Zone z);

void setZoneUpdate(Zone z);

#endif /* ZONE_H_ */
