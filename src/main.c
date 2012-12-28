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

#include "list.h"

int main(void) {

	int i, a, b, c;
	int max = 100;

	List listH = newList(sizeof(int));
	List listT = newList(sizeof(int));

	for (i = 0; i < max; ++i) {

		addListTail(listH, &i);

		addListTail(listT, &i);

		printf("%d %d\n", getListCount(listH), getListCount(listT));

	}

	for (i = 0; i < max; ++i) {

		removeListHead(listH, &a);

		removeListTail(listH, &b);

		removeListAt(listH, &c, getListCount(listH) / 2);

		printf("%d %d %d %d\n", a, b, c, getListCount(listH));

	}

	ListIter iter = newListIter(listT);
	int *p;

	while ((p = ListIterNext(iter, &a)) != NULL ) {
		printf("iter %d %d %d %d\n", a, *p, getListIterNextPos(iter),
				getListIterLastPos(iter));
	}

	/*for (i = 0; i < max + 10; ++i) {

	 removeListTail(listH, &a);

	 removeListHead(listT, &b);

	 printf("remove %d %d %d %d\n", a, b, getListCount(listH),
	 getListCount(listT));
	 a = b = i;

	 }*/

	freeList(listH);
	freeList(listT);

	exit(0);
}
