/*
 * distributions.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef DISTRIBUTIONS_H_
#define DISTRIBUTIONS_H_

typedef struct {
} udistri;

udistri newUDistri(float mean);
float nextRandom(udistri ud);

#endif /* DISTRIBUTIONS_H_ */
