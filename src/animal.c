/*
 * animal.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdio.h>

#include "animal.h"

void printfAnimal(Animal *r) {

	printf("ID:%4d  BT:%4d  AT:%4d  DT:%4d\n", r->id, r->birthTime, r->adultTime,
			r->deathTime);
}
