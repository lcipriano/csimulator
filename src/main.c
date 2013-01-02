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
#include "date.h"
#include "message.h"

int main(void) {

	/* area const */
	float x1 = 0.0;
	float y1 = 0.0;
	float x2 = 1000.0;
	float y2 = 1000.0;
	int nx = 4;
	int ny = 4;

	setArea(x1, y1, x2, y2, nx, ny, getFoxSpecimen(), getRabbitSpecimen());
	printfArea("Init");

	int i, max = 120;
	char str[32];
	Date d = newDate(1, 1, 2009);
	FILE *output = fopen("/home/lcipriano/workspace64/scanPop/input.txt", "w");

	for (i = 1; i <= max; ++i) {
		updateArea(i);
		printf("\n\n");
		sendMsgTo(output, getDateMsg(d));
		sendMsgTo(output, getAreaMsg());
		sendZonesMsgTo(output);
		sendFoxsMsgTo(output);

		/*
		 sprintf(str, "Iteração %d\n", i);
		 printfArea(str);
		 */
		d = incDateMonth(d);
	}

	fclose(output);
	freeArea();

	exit(0);
}
