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

int main(void) {

	int i, j;
	int n = 10;

	initRabbits();

	for (i = 1; i <= n; i++)
		newRabbit(i, 1);

	for (i = 1; i <= n; i++)
		newRabbit(2*i, 2);

	RabbitList rl = getRabbitsByColony(2);
	Rabbit r;

	while (nextRabbit(rl, &r) != NULL )
		printf("ID1 = %d Col = %d Age = %d\n", r.id, r.colony,r.birthTime);

	exit(0);
}
