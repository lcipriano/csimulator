/*
 * smath.c
 *
 *  Created on: Dec 19, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <math.h>

#include "smath.h"

/**
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return A new flinear object
 */
flinear newflinear(float x1, float y1, float x2, float y2) {

	flinear fl;

	fl.m = (y2 - y1) / (x2 - x1);
	fl.b = y1 - fl.m * x1;

	return fl;
}

float y(flinear fl, float x) {
	return fl.m * x + fl.b;
}

UDistri newUDistri(float a, float b) {

	UDistri ud;

	ud.f = newflinear(0, a, RAND_MAX - 1, b);

	return ud;
}

float nextUDistriRandom(UDistri ud) {
	return y(ud.f, rand());
}

ExDistri newExDistri(float mean) {

	ExDistri ed;

	ed.mean = mean;
	ed.f = newflinear(0, 0, RAND_MAX - 1, 1);

	return ed;
}

float nextExDistriRandom(ExDistri ed) {

	int r;

	while ((r = rand()) == 0)
		;
	return -ed.mean * log(y(ed.f, r));
}
