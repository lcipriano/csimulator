/*
 ============================================================================
 Name        : sisMonit.c
 Author      : Ana Margarida Cipriano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "colony.h"
#include "fox.h"
#include "rabbit.h"
#include "area.h"

int main(void) {

	/* area const */
	float x1 = 0.0;
	float y1 = 0.0;
	float x2 = 1000.0;
	float y2 = 1000.0;
	int nx = 4;
	int ny = 4;

	setArea(x1, y1, x2, y2, nx, ny, getFoxSpecimen(), getRabbitSpecimen());
	printfArea("set");

	int i, max = 4;
	char str[32];

	for (i = 1; i <= max; ++i) {
		updateArea(i);
		sprintf(str, "Iteração %d", i);
		printfArea(str);

	}

	updateArea(1);

	freeArea();

	exit(0);
}
