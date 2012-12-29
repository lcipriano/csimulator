/*
 * area.h
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#ifndef AREA_H_
#define AREA_H_

#include "population.h"

void setArea(float x1, float y1, float x2, float y2, int nx, int ny,
		Population f, Population r);
void getRandomCoords(float *x, float *y);

void updateArea(int time);

#endif /* AREA_H_ */
