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

#include "rabbits.h"
#include "smath.h"
#include "colony.h"

int main(void) {

	int i;
	int n = 3;

	initRabbits();

	Colony c = newColony(16, 0);

	for (i = 1; i <= n; ++i) {
		printf("time : %d\n", i);
		updateColony(c, i);
	}

	freeColony(c);

	exit(0);
}
