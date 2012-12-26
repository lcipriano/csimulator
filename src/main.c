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

#include "smath.h"
#include "rcolony.h"

int main(void) {

	int i;
	int n = 3;

	initRabbits();
	initRColony();

	RColony c = newRColony(16, 0);
	printfRColony(c);

	for (i = 1; i <= n; ++i) {
		printf("time : %d\n", i);
		updateRColony(c, i);
		printfRColony(c);
	}

	freeRColony(c);

	exit(0);
}
