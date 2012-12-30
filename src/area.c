/*
 * area.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdio.h>
#include <stdlib.h>

#include "area.h"
#include "smath.h"
#include "alist.h"
#include "zone.h"
#include "rabbit.h"

typedef struct {
	float xb, yb, tx, ty;
	int nx, ny;
	UDistri XDistri, YDistri;
	Colony foxs;
	Zone **zones;
} Area;

static Area area;

static void setAreaZones() {

	int i, j;

	area.zones = calloc(area.ny, sizeof(Zone));
	for (i = 0; i < area.ny; ++i)
		area.zones[i] = calloc(area.nx, sizeof(Zone));

	for (i = 0; i < area.ny; ++i)
		for (j = 0; j < area.nx; ++j)
			area.zones[i][j] = newZone(i, j);
}

void setArea(float x1, float y1, float x2, float y2, int nx, int ny,
		Population *f, Population *r) {

	area.xb = x1;
	area.yb = y1;
	area.tx = x2;
	area.ty = y2;
	area.nx = nx;
	area.ny = ny;

	area.XDistri = newUDistri(x1, x2);
	area.YDistri = newUDistri(y1, y2);

	area.foxs = newColony(f);

	setAreaZones();

	Colony c = newColony(r);
	initColony(c, 20, 0, getRabbitID);
	setZoneColony(area.zones[nx / 2][ny / 2], c);

}

static void freeAreaZones() {

	int i, j;

	for (i = 0; i < area.ny; ++i)
		for (j = 0; j < area.nx; ++j)
			freeZone(area.zones[i][j]);

	for (i = 0; i < area.ny; ++i)
		free(area.zones[i]);

	free(area.zones);

}

void freeArea() {

	freeColony(area.foxs);
	freeAreaZones();
}

void getAreaRandomCoords(float *x, float *y) {

	*x = nextUDistriRandom(area.XDistri);
	*y = nextUDistriRandom(area.YDistri);
}

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

static Zone nextFreeZone(int y0, int x0) {

	int x, y;

	int d = 1, inside = 1;
	while (inside) {

		inside = 0;

		int northy = y0 - d;
		int westx = x0 - d;
		int southy = y0 + d;
		int eastx = x0 + d;

		/* scan north line of the square */

		int xmax = min(eastx,area.nx-1);
		int xmin = max(westx,0);

		if (0 <= northy) {

			inside = 1;
			y = northy;
			for (x = xmin; x <= xmax; ++x) {
				if (getZoneColony(area.zones[y][x]) == NULL ) {
					printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
							y0, x, y, d);
					return area.zones[y][x];
				}
			}
		}

		/* scan east line of the square */

		int ymin = max(0,northy+1);
		int ymax = min(area.ny-1,southy);

		if (eastx < area.nx) {

			inside = 1;
			x = eastx;
			for (y = ymin; y <= ymax; ++y) {
				if (getZoneColony(area.zones[y][x]) == NULL ) {
					printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
							y0, x, y, d);
					return area.zones[y][x];
				}
			}
		}

		/* scan south line of the square */

		if (southy < area.ny) {

			inside = 1;
			y = southy;
			for (x = xmax - 1; x >= xmin; --x) {
				if (getZoneColony(area.zones[y][x]) == NULL ) {
					printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
							y0, x, y, d);
					return area.zones[y][x];
				}
			}
		}

		/* scan west line of the square */

		if (0 <= westx) {

			inside = 1;
			x = westx;
			for (y = ymax - 1; y >= ymin; --y) {
				if (getZoneColony(area.zones[y][x]) == NULL ) {
					printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
							y0, x, y, d);
					return area.zones[y][x];
				}
			}
		}

		d++;
	}

	return NULL ;
}

static void updateZones(int time) {

	int x, y;
	AList newRabbitList;
	Zone destZone;

	/* only update zones with old colonies */
	for (x = 0; x < area.nx; ++x)
		for (y = 0; y < area.ny; ++y)
			setZoneUpdate(area.zones[x][y]);

	/* update the zones with the rabbits */
	for (y = 0; y < area.ny; ++y) {

		for (x = 0; x < area.nx; ++x) {

			/* update the zone */
			newRabbitList = updateZone(area.zones[y][x], time);

			/* if rabbit pop of the zone more then 20 move excess to new zone */
			while (newRabbitList != NULL ) {
				printf("nrl = %d\n", getAnimalsCount(newRabbitList));

				destZone = nextFreeZone(y, x);

				/* if found an empty zone creat a new colony */
				if (destZone != NULL ) {

					Colony nc = newColony(getRabbitPop());
					setColonyAnimals(nc, newRabbitList);
					setZoneColony(destZone, nc);

					/* trim the new Colony */
					newRabbitList = trimColony(nc, getZoneMax(destZone));

				} else {

					/* no empty zone destroy  list */
					freeAnimalList(newRabbitList);
					newRabbitList = NULL;
				}

				printfArea();

			} /* while (newRabbitList != NULL ) */
		} /* for j */
	} /* for i */

}

static void updateFoxes(int time) {

	/* update the foxs */
	updateColony(area.foxs, time);
}

static void huntRabbbit() {
}

void updateArea(int time) {

	updateZones(time);

	/*updateFoxes(time);*/

	/* foxes are hunting */

}

void printfArea() {

	int i, j;

	for (i = 0; i < area.ny; ++i)
		for (j = 0; j < area.nx; ++j)
			printfZone(area.zones[i][j]);

}
