/*
 ============================================================================
 Name        : LinkedList.c
 Author      : Lívio Cipriano
 Version     : 1.0
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lists.h"

typedef void *Container;

struct linkedList {

	Container head, tail;
	int count, dsize;

};

struct listIterator {
	Container next;
	int pos;
	int dsize;
};

static Container getNext(Container c) {

	Container aux;
	memmove(&aux, c, sizeof(Container));
	return aux;

}

static void setNext(Container c, Container n) {

	memmove(c, &n, sizeof(Container));

}

static void *getDataPointer(Container c) {
	return (Container *) c + 1;
}

static void getData(Container c, void *d, int ds) {

	if (d == NULL )
		return;

	memmove(d, getDataPointer(c), ds);
}

static void setData(Container c, void *d, int ds) {

	memmove(getDataPointer(c), d, ds);
}

static Container newContainer(List l, void *d) {

	Container nc = malloc(sizeof(Container) + l->dsize);

	if (nc != NULL ) {
		setNext(nc, NULL );
		setData(nc, d, l->dsize);
	}

	return nc;

}

static void freeContainer(Container c) {

	if (c != NULL )
		free(c);
}

List newList(int ds) {

	List l = malloc(sizeof(struct linkedList));

	if (l != NULL ) {
		l->head = NULL;
		l->tail = NULL;
		l->dsize = ds;
		l->count = 0;
	}

	return l;

}

void clearList(List theList) {

	if (theList == NULL )
		return;

	Container actual = theList->head, next;
	while (actual != NULL ) {
		next = getNext(actual);
		freeContainer(actual);
		actual = next;
	}

}

void freeList(List theList) {

	if (theList == NULL )
		return;

	clearList(theList);

	free(theList);

}

ListIter newListIter(List l) {

	if (l == NULL )
		return NULL ;

	if (l->head == NULL )
		return NULL ;

	ListIter li = malloc(sizeof(struct listIterator));

	if (li != NULL ) {
		li->next = l->head;
		li->pos = 1;
		li->dsize = l->dsize;
	}

	return li;
}

void freeListIter(ListIter li) {

	if (li != NULL )
		free(li);
}

static Container *nextContainer(ListIter li) {

	if (li->next == NULL )
		return NULL ;

	Container tmp = li->next;
	li->next = getNext(li->next);
	li->pos++;

	return tmp;
}

static Container getContainer(List l, int index) {

	if (l == NULL || index < 1)
		return NULL ;

	if (index > l->count)
		return NULL ;

	ListIter li = newListIter(l);

	if (li == NULL )
		return NULL ;

	int i;
	Container c;

	for (i = 1; i <= index; i++)
		c = nextContainer(li);

	freeListIter(li);

	return c;
}

void *ListIterNext(ListIter li, void *data) {

	Container c = nextContainer(li);

	if (c == NULL )
		return NULL ;

	getData(c, data, li->dsize);

	return getDataPointer(c);

}

void *getList(List l, void *data, int index) {

	Container c = getContainer(l, index);

	if (c == NULL )
		return NULL ;

	if (data != NULL )
		setData(c, data, l->dsize);

	return getDataPointer(c);

}

void *removeListHead(List l, void *data) {

	if (l == NULL || data == NULL )
		return NULL ;

	if (l->count == 0)
		return NULL ;

	getData(l->head, data, l->dsize);

	Container tmp = l->head;

	l->head = getNext(l->head);

	freeContainer(tmp);

	l->count--;

	return data;
}

void *removeList(List l, void *data, int index) {

	if (l == NULL || data == NULL || index < 1)
		return NULL ;

	if (index > l->count)
		return NULL ;

	if (index == 1)
		return removeListHead(l, data);

	Container previousIndexContainer = getContainer(l, index - 1);

	if (previousIndexContainer == NULL )
		return NULL ;

	Container indexContainer = getNext(previousIndexContainer);

	if (indexContainer == NULL )
		return NULL ;

	Container nextIndexContainer = getNext(indexContainer);

	getData(indexContainer, data, l->dsize);

	freeContainer(indexContainer);

	setNext(previousIndexContainer, nextIndexContainer);

	l->count--;

	return data;

}

void *removeListTail(List l, void *data) {
	return removeList(l, data, getListCount(l));
}

void *addListTail(List l, void *data) {

	if (l == NULL || data == NULL )
		return NULL ;

	Container nc = newContainer(l, data);

	if (nc == NULL )
		return NULL ;

	l->count++;

	if (l->count == 1) {

		l->head = l->tail = nc;

	} else {

		setNext(l->tail, nc);
		l->tail = nc;
	}

	return getDataPointer(nc);
}

void *addListHead(List l, void *data) {

	if (l == NULL || data == NULL )
		return NULL ;

	Container nc = newContainer(l, data);

	if (nc == NULL )
		return NULL ;

	l->count++;

	if (l->count == 1) {

		l->head = l->tail = nc;

	} else {

		setNext(nc, l->head);
		l->head = nc;
	}

	return getDataPointer(nc);
}

int getListCount(List l) {

	return l == NULL ? -1 : l->count;

}

int getListIterPos(ListIter li) {
	return li == NULL ? -1 : li->pos;
}
