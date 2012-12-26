/*
 * foxs.c
 *
 *  Created on: Dec 25, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "fox.h"
#include "smath.h"
#include "date.h"
#include "area.h"

static PopType *foxType;

void initFoxs(PopType *pt) {

	foxType = pt;
}

Fox *newFox(Fox *nr, int birthTime) {

	return newAnimal(nr, foxType, birthTime);
}

void printfFoxt(Fox *r) {

	printf("Fox\n");

	printfAnimal(r);
}
