/*
 * date.c
 *
 *  Created on: Dec 22, 2012
 *      Author: lcipriano
 */

#include "date.h"

date newDate(int y, int m, int d) {

	date nd = { y, m, d };

	return nd;
}
