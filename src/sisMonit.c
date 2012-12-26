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
#include "colony.h"

int main(void) {

	int i;
	int n = 3;

	initRabbits();
	initColony();

	Colony c = newColony(16, 0);
	printfColony(c);

	for (i = 1; i <= n; ++i) {
		printf("time : %d\n", i);
		updateColony(c, i);
		printfColony(c);
	}

	freeColony(c);

	exit(0);
}
