/*
 * List.h
 *
 *  Created on: May 31, 2009
 *      Author: lcipriano
 */

#ifndef LIST_H_
#define LIST_H_

/*
 * List
 */

typedef struct list *List;

/**
 * creates a new list
 *
 * @param ds	size of the object to store in the list
 * @return		a new list or NULL if can't allocate memory space for the list
 */
List newList(int ds);

/**
 * frees the memory allocated to the list
 *
 * @param l		a list variable
 */
void freeList(List l);

void *getListAt(List l, void *data, int index);

void *removeListAt(List l, void *data, int index);

void *addListTail(List l, void *data);

void *addListHead(List l, void *data);

void *removeListHead(List l, void *data);

void *removeListTail(List l, void *data);

int getListCount(List l);

void clearList(List l);

/*
 * List Iterator
 */

typedef struct listIter *ListIter;

ListIter newListIter(List l);

void freeListIter(ListIter li);

void *ListIterNext(ListIter li, void *data);

int getListIterNextPos(ListIter li);

int getListIterLastPos(ListIter li);

#endif /* LIST_H_ */
