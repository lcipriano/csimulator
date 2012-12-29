/*
 * foxs.c
 *
 *  Created on: Dec 25, 2012
 *      Author: lcipriano
 */

#include "fox.h"

int getFoxID(void) {

	static int id = 1;

	return id++;
}
