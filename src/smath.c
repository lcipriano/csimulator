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

PoDistri newPoDistri(float mean) {

	PoDistri pd;

	pd.mean = mean;
	pd.f = newflinear(0, 0, RAND_MAX - 1, 1);

	return pd;
}

/**

 Bibliographic details for "Poisson distribution"

 Page name: Poisson distribution
 Author: Wikipedia contributors
 Publisher: Wikipedia, The Free Encyclopedia.
 Date of last revision: 24 December 2012 01:44 UTC
 Date retrieved: 25 December 2012 13:01 UTC
 Permanent link: http://en.wikipedia.org/w/index.php?title=Poisson_distribution&oldid=529522702
 Primary contributors: Revision history statistics
 Page Version ID: 529522702

 algorithm poisson random number (Knuth):
 init:
 Let L ← e^(−λ), k ← 0 and p ← 1.
 do:
 k ← k + 1.
 Generate uniform random number u in [0,1] and let p ← p × u.
 while p > L.
 return k − 1.

 */
int nextPoDistriRandom(PoDistri pd) {

	float l = exp(-pd.mean), p = 1.0;
	int k = 0;

	do {
		k++;
		p = p * y(pd.f, rand());
	} while (p > l);

	return k-1;

}

unsigned gmod(int a, unsigned b) {

	if (a >= 0)
		return a % b;
	a = -a;
	return (b - a % b) % b;

}

