// set.c ... simple, inefficient Set of Strings
// Written by John Shepherd, September 2015

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "set.h"

typedef struct Node *Link;

typedef struct Node {
	int val;
	Link next;
} Node;

typedef struct SetRep {
	int nelems;
	Link elems;
} SetRep;

// Function signatures

static Link newNode (int);
static void dropNode (Link);
static int findNode (Link, int, Link *, Link *);

// newSet()
// - create an initially empty Set
Set newSet (void)
{
	Set new = malloc (sizeof *new);
	if (new == NULL)
		err (EX_OSERR, "couldn't allocate Set");
	*new = (SetRep){.nelems = 0, .elems = NULL};
	return new;
}

// dropSet(Set)
// - clean up memory associated with Set
void dropSet (Set s)
{
	if (s == NULL)
		return;
	Link curr = s->elems;
	while (curr != NULL) {
		Link next = curr->next;
		dropNode (curr);
		curr = next;
	}

	free (s);
}

// insertInto(Set,val)
// - ensure that val is in Set
void insertInto (Set s, int val)
{
	assert (s != NULL);
	Link curr, prev;
	int found = findNode (s->elems, val, &curr, &prev);
	if (found)
		return; // already in Set

	Link new = newNode (val);
	s->nelems++;
	if (prev == NULL) {
		// add at start of list of elems
		new->next = s->elems;
		s->elems = new;
	} else {
		// add into list of elems
		new->next = prev->next;
		prev->next = new;
	}
}

// dropFrom(Set,val)
// - ensure that val is not in Set
void dropFrom (Set s, int val)
{
	assert (s != NULL);
	Link curr, prev;
	int found = findNode (s->elems, val, &curr, &prev);
	if (!found)
		return;
	s->nelems--;
	if (prev == NULL)
		s->elems = curr->next;
	else
		prev->next = curr->next;
	dropNode (curr);
}

// isElem(Set,val)
// - check whether val is contained in Set
int isElem (Set s, int val)
{
	assert (s != NULL);
	Link curr, prev;
	return findNode (s->elems, val, &curr, &prev);
}

// nElems(Set)
// - return # elements in Set
int nElems (Set s)
{
	assert (s != NULL);
	return s->nelems;
}

// showSet(Set)
// - display Set (for debugging)
void showSet (Set s)
{
	Link curr;
	if (s->nelems == 0)
		printf ("Set is empty\n");
	else {
		printf ("Set has %d elements:\n", s->nelems);
		int id = 0;
		curr = s->elems;
		while (curr != NULL) {
			printf ("[%03d] %d\n", id, curr->val);
			id++;
			curr = curr->next;
		}
	}
}

// Helper functions

static Link newNode (int val)
{
	Link new = malloc (sizeof (Node));
	assert (new != NULL);
	new->val = val;
	new->next = NULL;
	return new;
}

static void dropNode (Link curr)
{
	assert (curr != NULL);
	free (curr);
}

// findNode(L,Str)
// - finds where Str could be added into L
// - if already in L, curr->val == Str
// - if not already in L, curr and prev indicate where to insert
// - return value indicates whether Str found or not
static int findNode (Link list, int val, Link *cur, Link *pre)
{
	Link curr = list, prev = NULL;
	while (curr != NULL && curr->val < val) {
		prev = curr;
		curr = curr->next;
	}
	*cur = curr;
	*pre = prev;
	return (curr != NULL && val == curr->val);
}
