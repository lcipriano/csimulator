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

	PopType rabbits;
	newPopType(&rabbits, 1, 8, 3, 24, 9, 5);
	Colony c = newColony(&rabbits, 20, 0);

	freeColony(c);

	exit(0);
}
