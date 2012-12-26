/*
 * foxs.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef FOX_H_
#define FOX_H_

#include "animal.h"
#include "poptype.h"

typedef Animal Fox;

void initFoxs(PopType *pt);

Fox *newFox(Fox *nr, int birthTime);

void printfFox(Fox *r);

#endif /* FOX_H_ */
