/*
 ============================================================================
 Name        : List.c
 Author      : Lívio Cipriano
 Version     : 1.3 201212
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef void *Container;

struct list {

	/* for the list */
	Container head;
	Container tail;
	int count;
	int dsize;

	/* for iteration */
	Container next;
	int pos;
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

static void *getData(Container c, void *d, int ds) {

	void *p = getDataPointer(c);

	memmove(d, p, ds);

	return p;
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

	free(c);
}

static Container addList(List l, void *data) {

	if (l == NULL || data == NULL )
		return NULL ;

	Container nc = newContainer(l, data);

	if (nc == NULL )
		return NULL ;

	l->count++;

	return nc;

}

static Container *nextContainer(ListIter li) {

	if (li->next == NULL )
		return NULL ;

	Container tmp = li->next;
	li->next = getNext(li->next);
	li->pos++;

	return tmp;
}

static Container getContainerAt(List l, int index) {

	int i;
	Container c = l->head;

	for (i = 1; i < index; ++i)
		c = getNext(c);

	return c;
}

void resetList(List l) {

	if (l == NULL )
		return;

	l->next = l->head;
	l->pos = 0;

}

/**
 * For compatibility with previous versions
 *
 * @param l
 * @return
 */

ListIter getListIter(List l) {

	resetList(l);

	return l;

}

/**
 * Just for compatibility with previous versions
 *
 * @param l
 * @return
 */
ListIter newListIter(List l) {

	return getListIter(l);
}

/**
 * Just for compatibility with previous versions
 *
 * @param li
 */

void freeListIter(ListIter li) {
	return;
}

void *getListNext(List li, void *data) {

	if (li == NULL )
		return NULL ;

	if (li->next == NULL )
		return NULL ;

	Container tmp = li->next;
	li->next = getNext(li->next);
	li->pos++;

	if (data != NULL )
		return getData(tmp, data, li->dsize);

	return getDataPointer(tmp);
}

/**
 * Just for compatibility with previous versions
 *
 * @param li
 * @param data
 */
void *ListIterNext(ListIter li, void *data) {

	return getListNext(li, data);

}

int getListIterNextPos(ListIter li) {

	if (li == NULL )
		return -1;

	if (li->next == NULL )
		return -1;

	return li->pos + 1;
}

int getListIterLastPos(ListIter li) {
	return li == NULL ? -1 : li->pos;
}

static void initList(List l) {

	l->head = NULL;
	l->tail = NULL;
	l->count = 0;
}

List newList(int ds) {

	List l = malloc(sizeof(struct list));

	if (l != NULL ) {
		initList(l);
		l->dsize = ds;
	}

	return l;

}

void clearList(List l) {

	if (l == NULL )
		return;

	Container actual = l->head, next;
	while (actual != NULL ) {
		next = getNext(actual);
		freeContainer(actual);
		actual = next;
	}

	initList(l);

}

void freeList(List l) {

	clearList(l);

	free(l);

}

void *addListHead(List l, void *data) {

	Container nc = addList(l, data);
	newContainer(l, data);

	if (nc == NULL )
		return NULL ;

	if (l->count == 1) {

		l->head = l->tail = nc;

	} else {

		setNext(nc, l->head);
		l->head = nc;
	}

	return getDataPointer(nc);
}

void *addListTail(List l, void *data) {

	Container nc = addList(l, data);

	if (nc == NULL )
		return NULL ;

	if (l->count == 1) {

		l->head = l->tail = nc;

	} else {

		setNext(l->tail, nc);
		l->tail = nc;
	}

	return getDataPointer(nc);
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

void *removeListAt(List l, void *data, int index) {

	if (l == NULL || data == NULL || index < 1)
		return NULL ;

	if (index > l->count)
		return NULL ;

	if (index == 1)
		return removeListHead(l, data);

	/* index between 2 and count  */

	Container previousIndexContainer = getContainerAt(l, index - 1);

	Container indexContainer = getNext(previousIndexContainer);

	Container nextIndexContainer = getNext(indexContainer);

	getData(indexContainer, data, l->dsize);

	freeContainer(indexContainer);

	setNext(previousIndexContainer, nextIndexContainer);

	if (index == l->count)
		l->tail = previousIndexContainer;

	l->count--;

	return data;

}

void *getListAt(List l, void *data, int index) {

	if (l == NULL || index < 1)
		return NULL ;

	if (index > l->count)
		return NULL ;

	Container c = getContainerAt(l, index);

	if (data != NULL )
		return getData(c, data, l->dsize);

	return getDataPointer(c);

}

int getListCount(List l) {

	return l == NULL ? -1 : l->count;

}

void *removeListTail(List l, void *data) {

	return removeListAt(l, data, getListCount(l));
}

