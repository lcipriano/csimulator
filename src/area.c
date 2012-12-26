/*
 * area.c
 *
 *  Created on: Dec 26, 2012
 *      Author: lcipriano
 */

#include <stdlib.h>

#include "area.h"
#include "smath.h"
#include "flist.h"
#include "zones.h"

typedef struct {
	float xb, yb, tx, ty;
	int xgrid, ygrid;
	UDistri XDistri, YDistri;
	FList foxList;
	Zone *zones;
	int nZones;
} Area;

static Area theArea;

void setArea(float x1, float y1, float x2, float y2, int nx, int ny) {

	theArea.xb = x1;
	theArea.yb = y1;
	theArea.tx = x2;
	theArea.ty = y2;
	theArea.xgrid = nx;
	theArea.ygrid = ny;

	theArea.XDistri = newUDistri(x1, x2);
	theArea.YDistri = newUDistri(y1, y2);

	theArea.foxList = newFoxList();

	int nZones = nx * ny;
	theArea.zones = malloc(nZones * sizeof(Zone));

}

void getRandomCoords(float *x, float *y) {

	*x = nextUDistriRandom(theArea.XDistri);
	*y = nextUDistriRandom(theArea.YDistri);
}

void updateArea() {

	int i;

	for (i = 0; i < theArea.nZones; ++i) {
		updateZone(theArea.zones[i]);
	}
}
