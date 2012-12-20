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
	int n = 12;
	Rabbit *pr;

	initRabbits();

	Colony c = newColony(100, 0);

	printfRabbitsByColony(1);

	for (i = 1; i <= n; ++i) {
		breedRabbits(c, i);
		printf("time : %d\n", i);
		/*printfRabbitsByColony(1);*/
	}

	exit(0);
}
