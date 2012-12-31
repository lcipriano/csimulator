/*
 * area.h
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#ifndef AREA_H_
#define AREA_H_

#include "specimen.h"
#include "message.h"

void setArea(float x1, float y1, float x2, float y2, int nx, int ny,
		Specimen *f, Specimen *r);

void freeArea();

void updateArea(int time);

void printfArea();

Message getAreaMsg();

#endif /* AREA_H_ */
