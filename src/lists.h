/*
 * LinkedList.h
 *
 *  Created on: May 31, 2009
 *      Author: lcipriano
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/*
 * LinkedList
 */

typedef struct linkedList *List;

List newList(int ds);

void freeList(List theList);

void *addList(List theList, void *data, int index);

void *getList(List theList, void *data, int index);

void *removeList(List theList, void *data, int index);

void *addListTail(List theList, void *data);

void *addListHead(List theList, void *data);

void *removeListHead(List l, void *data);

void *removeListTail(List l, void *data);

int getListCount(List theList);

void clearList(List theList);

/*
 * Iterator
 */

typedef struct listIterator *ListIter;

ListIter newListIter(List l);

void freeListIter(ListIter li);

void *ListIterNext(ListIter li, void *data);

int getListIterPos(ListIter li);

#endif /* LINKEDLIST_H_ */
