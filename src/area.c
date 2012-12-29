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

typedef struct {
	float xb, yb, tx, ty;
	int nx, ny;
	UDistri XDistri, YDistri;
	Colony foxs;
	Zone **zones;
} Area;

static Area area;

void setArea(float x1, float y1, float x2, float y2, int nx, int ny,
		Population f, Population r) {

	area.xb = x1;
	area.yb = y1;
	area.tx = x2;
	area.ty = y2;
	area.nx = nx;
	area.ny = ny;

	area.XDistri = newUDistri(x1, x2);
	area.YDistri = newUDistri(y1, y2);

	area.foxs = newColony(&f);

	int i;
	area.zones = calloc(ny, sizeof(Zone));
	for (i = 0; i < nx; ++i)
		area.zones[i] = calloc(nx, sizeof(Zone));
}

void getRandomCoords(float *x, float *y) {

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

void updateArea(int time) {

	int i, j;
	AList newRabbitList;
	Zone destZone;

	/* update the zones with the rabbits */
	for (i = 0; i < area.nx; ++i) {

		for (j = 0; j < area.ny; ++j) {

			/* update the zone */
			newRabbitList = updateZone(area.zones[i][j], time);

			/* if rabbit pop of the zone more then 20 move excess to new zone */
			/* PUT A WHILE HERE IF LIST BIGGET THEN 20 */
			if (newRabbitList != NULL ) {
				destZone = nextFreeZone(j, i);
				/* if found creat a new colony in zone */

			}
		}
	}

	/* update the foxs */
	updateColony(area.foxs, time);

	/* foxes are hunting */

}
