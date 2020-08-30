// bst.c ... client for BSTree ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

#define MAXVALS 1000

int main (void)
{
	// Build tree from values in stdin
	BSTree T = newBSTree ();
	int nvals = 0;
	int v[MAXVALS];
	int n;
	while (nvals < MAXVALS && scanf ("%d", &n) == 1) {
		v[nvals++] = n;
		T = BSTreeInsert (T, n);
	}

	// Display information about constructed tree
	printf ("Tree:\n");
	showBSTree (T);

	printf("Height = %d\n", height(T));
	printf("isAVL returns: %d\n", isAVL(T));
	printf("Width = %d\n", BSTWidth(T));

	dropBSTree (T);
	return 0;
}