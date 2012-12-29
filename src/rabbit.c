/*
 * rabbit.c
 *
 *  Created on: Dec 25, 2012
 *      Author: lcipriano
 */

#include "rabbit.h"

int getRabbitID(void) {

	static int id = 1;

	return id++;
}
