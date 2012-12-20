/*
 * distributions.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef SMATH_H
#define SMATH_H

typedef struct {
	float m, b;
} flinear;

typedef struct {
	flinear f;
} UDistri;

typedef struct {
	float mean;
	flinear f;
} ExDistri;

UDistri newUDistri(float a, float sb);
float nextUDistriRandom(UDistri ud);

ExDistri newExDistri(float mean);
float nextExDistriRandom(ExDistri ed);

flinear newflinear(float x1, float y1, float x2, float y2);
float y(flinear fl, float x);

#endif /* SMATH_H */
