/*
 * foxs.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef FOXS_H_
#define FOXS_H_

typedef struct {
	/* location */
	float x, y;
	int id;
	/**/
	int birthDate;
	float energy;

} fox;

fox *newFox(int birth, float x, float y);
void eat(fox *f);

#endif /* FOXS_H_ */
