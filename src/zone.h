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

Zone newZone();

AList updateZone(Zone z, int time);

Colony getZoneColony(Zone z);

void setZoneColony(Zone z, Colony c);

int huntRabbit(Zone z);

#endif /* ZONE_H_ */
