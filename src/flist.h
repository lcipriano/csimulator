/*
 * flist.h
 *
 *  Created on: Dec 16, 2012
 *      Author: lcipriano
 */

#ifndef FLIST_H_
#define FLIST_H_

#include "fox.h"

typedef struct fList *FList;

FList newFoxList();

void freeFoxList(FList rl);

Fox *insertFox(FList rl, Fox *r);

void insertNewFoxs(FList rl, int count, int birthTime);

void removeFox(FList rl, int index);

int getFoxsCount(FList rl);

int getFoxsAdultsCount(FList rl, int time);

void deleteOldFoxs(FList rl, int timeLimit);

void printfFoxList(FList rl);

#endif /* FOX_H_ */
