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

typedef struct {
	float mean;
	flinear f;
} PoDistri;

UDistri newUDistri(float a, float sb);
float nextUDistriRandom(UDistri ud);

ExDistri newExDistri(float mean);
float nextExDistriRandom(ExDistri ed);

PoDistri newPoDistri(float mean);
int nextPoDistriRandom(PoDistri po);

flinear newflinear(float x1, float y1, float x2, float y2);
float y(flinear fl, float x);

unsigned gmod(int a, unsigned b);

#endif /* SMATH_H */
