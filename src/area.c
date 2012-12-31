/*
 * area.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "area.h"
#include "smath.h"
#include "zone.h"
#include "rabbit.h"
#include "fox.h"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

typedef struct {
	float bottomx, bottomy, topx, topy;
	int nx, ny;
	UDistri XDistri, YDistri;
	Colony foxs;
	Zone **zones;
} Area;

static Area area;

static void setAreaZones() {

	int i, j;

	/* CAUTION WITH MEMORY */
	area.zones = calloc(area.ny, sizeof(Zone));
	for (i = 0; i < area.ny; ++i)
		area.zones[i] = calloc(area.nx, sizeof(Zone));

	flinear xscale = newflinear(0, area.bottomx, area.nx, area.topx);
	flinear yscale = newflinear(area.ny, 0, 0, area.topy);

	for (i = area.ny - 1; i >= 0; --i) {
		for (j = 0; j < area.nx; ++j) {

			float bx = y(xscale, j);
			float tx = y(xscale, j + 1);
			float by = y(yscale, i + 1);
			float ty = y(yscale, i);

			area.zones[i][j] = newZone(bx, by, tx, ty, i, j);
			/*printfZone(area.zones[i][j]);*/
		}
	}

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

		int xmax = min(eastx, area.nx - 1);
		int xmin = max(westx, 0);

		if (0 <= northy) {

			inside = 1;
			y = northy;
			for (x = xmin; x <= xmax; ++x) {
				if (getZoneColony(area.zones[y][x]) == NULL ) {
					/*printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
					 y0, x, y, d); */
					return area.zones[y][x];
				}
			}
		}

		/* scan east line of the square */

		int ymin = max(0, northy + 1);
		int ymax = min(area.ny - 1, southy);

		if (eastx < area.nx) {

			inside = 1;
			x = eastx;
			for (y = ymin; y <= ymax; ++y) {
				if (getZoneColony(area.zones[y][x]) == NULL ) {
					/*printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
					 y0, x, y, d); */
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
					/*printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
					 y0, x, y, d);*/
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
					/*printf("x0 = %d  y0 = %d  fx = %d  fy = %d d = %d\n", x0,
					 y0, x, y, d);*/
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
				/*printf("nrl = %d\n", getAnimalsCount(newRabbitList));*/

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

			} /* while (newRabbitList != NULL ) */
		} /* for j */
	} /* for i */

}

static float getAreaRandomX() {

	return nextUDistriRandom(area.XDistri);

}

static float getAreaRandomY() {

	return nextUDistriRandom(area.YDistri);

}

static void initFoxColony(Colony c, int initCount, int time,
		int (*idGenerator)(void)) {

	if (c == NULL )
		return;

	initColony(c, initCount, time, idGenerator);

	/* set the coords */
	AList f = getColonyAnimals(c);
	ListIter fi = newListIter(f);
	if (fi == NULL )
		return;

	Animal *pa;
	while ((pa = ListIterNext(fi, NULL )) != NULL ) {
		pa->x = getAreaRandomX();
		pa->y = getAreaRandomY();
		pa->energy = 0.95;
	}
	freeListIter(fi);
}

static void updateFoxes(int time) {

	/* update the foxs */
	updateColony(area.foxs, time);
}

static void printfFox(Animal *a, const char *prefix) {

	printf("Fox %-32s E:%.2f ", prefix, a->energy);
	printfAnimal(a);
}

static List getAreaZonesWithRabbits() {

	List zl = newList(sizeof(Zone));

	if (zl == NULL )
		return NULL ;

	int x, y;
	for (y = 0; y < area.ny; ++y)
		for (x = 0; x < area.nx; ++x)
			if (getZoneColony(area.zones[y][x]) != NULL )
				addListTail(zl, &(area.zones[y][x]));

	if (getListCount(zl) == 0) {
		freeList(zl);
		return NULL ;
	}

	return zl;

}

static float distance(float x1, float y1, float x2, float y2) {

	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

static Zone getNearZone(List zl, float x, float y) {

	if (getListCount(zl) == 0)
		return NULL ;

	ListIter zi = newListIter(zl);
	if (zi == NULL )
		return NULL ;

	int minIndex;
	Zone aux;
	float actualDist, minDist;

	/* get the Zone within minimum distance */
	ListIterNext(zi, &aux);
	minDist = distance(x, getZoneCenterX(aux), y, getZoneCenterX(aux));
	minIndex = 1;
	while (ListIterNext(zi, &aux) != NULL ) {
		actualDist = distance(x, y, getZoneCenterX(aux), getZoneCenterY(aux));
		if (actualDist < minDist) {
			minDist = actualDist;
			minIndex = getListIterLastPos(zi);
		}
	}
	freeListIter(zi);

	removeListAt(zl, &aux, minIndex);

	return aux;

}

static void removeDeadFoxs() {

	AList new = newAnimalList();
	if (new == NULL )
		return;

	ListIter iter = newListIter(getColonyAnimals(area.foxs));
	if (iter == NULL ) {
		freeList(new);
		return;
	}

	/* copy non dead foxs to a new list */
	Animal *pr;
	while ((pr = ListIterNext(iter, NULL )) != NULL )
		if (pr->energy > 0.0)
			insertAnimal(new, pr);
	freeListIter(iter);

	/* free actual list */
	setColonyAnimals(area.foxs, new);

}

static void huntRabbit(Animal *fox) {

	/* request the set of Zones with rabbits */
	List huntingZones = getAreaZonesWithRabbits();

	if (huntingZones == NULL ) {
		fox->energy = -1.0;
		return;
	}

	int minRabbits = 10, huntedRabbits = 0, state = 0, hunting = 1;
	Zone huntingZone = NULL;
	printfFox(fox, "start hunting");
	while (hunting) {

		switch (state) {

		case 0:

			/* adquire hunting zone */

			huntingZone = getNearZone(huntingZones, fox->x, fox->y);
			if (huntingZone == NULL ) {
				hunting = 0;
			} else {

				/* fox moves to random point in hunting zone */

				fox->x = getZoneRandomX(huntingZone);
				fox->y = getZoneRandomY(huntingZone);

				printfFox(fox, "moved to hunting zone");
				printfZone(huntingZone);

				if (huntedRabbits < minRabbits)
					state = 1;
				else
					state = 2;
			}

			break;

		case 1:

			/* get the minimum rabbits */
			if (huntZoneRabbit(huntingZone)) {
				huntedRabbits++;
				printfFox(fox, "hunted min rabbits");
				if (huntedRabbits == minRabbits) {
					state = 2;
				}
			} else {
				state = 0;
			}

			break;

		case 2:

			/* get above minimum rabbits */
			if (fox->energy > 0.95) {
				if (fox->energy > 1.0)
					fox->energy = 1.0;
				hunting = 0;
			} else {

				if (huntZoneRabbit(huntingZone)) {
					fox->energy += 0.1;
					huntedRabbits++;
					printfFox(fox, "hunting for energy");

				} else {
					state = 0;
				}
			}
			break;
		}
	} /* while hunting */

	if (huntedRabbits < minRabbits) {
		fox->energy -= 0.1 * (minRabbits - huntedRabbits);
	}

	printfFox(fox, "finish hunting");
	printf("hunted rabbits = %d\n", huntedRabbits);
	printfArea();

	freeList(huntingZones);
}

static void huntRabbits(int time) {

	ListIter foxs = newListIter(getColonyAnimals(area.foxs));
	if (foxs == NULL )
		return;

	Animal *pf;
	while ((pf = ListIterNext(foxs, NULL )) != NULL )
		/* only adult foxs hunt */
		if (time >= pf->adultTime)
			huntRabbit(pf);
	freeListIter(foxs);

	removeDeadFoxs();
}

static void setAreaFoxs() {

	area.foxs = newColony(getFoxPop());
	initFoxColony(area.foxs, 4, 0, getFoxID);
}

void setArea(float x1, float y1, float x2, float y2, int nx, int ny,
		Population *f, Population *r) {

	area.bottomx = x1;
	area.bottomy = y1;
	area.topx = x2;
	area.topy = y2;
	area.nx = nx;
	area.ny = ny;

	area.XDistri = newUDistri(x1, x2);
	area.YDistri = newUDistri(y1, y2);

	setAreaFoxs();

	setAreaZones();

	Colony c = newColony(r);
	initColony(c, 20, 0, getRabbitID);
	setZoneColony(area.zones[nx / 2][ny / 2], c);

}

void freeArea() {

	freeColony(area.foxs);
	freeAreaZones();
}

void updateArea(int time) {

	updateZones(time);
	printfArea();

	updateFoxes(time);
	printfArea();

	/* foxes are hunting */

	huntRabbits(time);
	printfArea();

}

void printfArea() {

	int i, j;

	/* draw area */

	Colony c;

	printf("\n-");
	for (j = 0; j < area.nx; ++j) {
		printf("----");
	}
	printf("\n");
	for (i = 0; i < area.ny; ++i) {
		printf("|");
		for (j = 0; j < area.nx; ++j) {
			c = getZoneColony(area.zones[i][j]);
			printf("%3d|", c == NULL ? 0 : getColonyCount(c));
		}
		printf("\n-");

		for (j = 0; j < area.nx; ++j) {
			printf("----");
		}
		printf("\n");
	}

	printf("Foxs %d ", getColonyCount(area.foxs));

	int zoneTotalCount = 0, count;

	for (i = 0; i < area.ny; ++i)
		for (j = 0; j < area.nx; ++j)
			if ((count = getZoneCount(area.zones[i][j])) != -1)
				zoneTotalCount += count;

	printf("Rabbits %d\n", zoneTotalCount);

}
