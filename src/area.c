/*
 * area.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

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
	setZoneColony(area.zones[nx/2][ny/2], c);

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

static Zone nextFreeZone(int x0, int y0) {

	int x, y, d = 1, inside = 1;

	while (inside) {
		inside = 0;
		for (y = y0 - d; y <= y0 + d; ++y) {

			if (0 <= y && y < area.ny) {

				for (x = x0 - d; x <= x0 + d; ++x) {
					if (0 <= x && x < area.nx) {
						inside = 1;
						if (getZoneColony(area.zones[x][x]) == NULL )
							return area.zones[x][x];
					}

				}
			}

		};
		d++;
	}
	return NULL ;
}

static void updateZones(int time) {

	int i, j;
	AList newRabbitList;
	Zone destZone;

	/* update the zones with the rabbits */
	for (i = 0; i < area.nx; ++i) {

		for (j = 0; j < area.ny; ++j) {

			/* update the zone */
			newRabbitList = updateZone(area.zones[i][j], time);

			/* if rabbit pop of the zone more then 20 move excess to new zone */
			while (newRabbitList != NULL ) {

				destZone = nextFreeZone(j, i);

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
