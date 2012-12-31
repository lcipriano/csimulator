/*
 * animal.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdio.h>

#include "animal.h"

void printfAnimal(Animal *r) {

	printf("ID:%4d  BT:%4d  AT:%4d  DT:%4d X:%.1f  Y:%.1f\n", r->id,
			r->birthTime, r->adultTime, r->deathTime, r->x, r->y);
}

int getAnimalAge(Animal *a, int time) {

	if (a == NULL )
		return -1;

	return time < a->birthTime ? -1 : time - a->birthTime;

}
