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
	// printf ("\n#nodes = %d,  ", BSTreeNumNodes (T));
	// printf ("#leaves = %d\n", BSTreeNumLeaves (T));

	// printf ("Infix  : "); BSTreeInfix (T); printf ("\n");
	// printf ("Prefix : "); BSTreePrefix (T); printf ("\n");
	// printf ("Postfix: "); BSTreePostfix (T); printf ("\n");
	// printf ("ByLevel: "); BSTreeLevelOrder (T); printf ("\n");

	// Check correctness of tree

	// assume no duplicates => each value produces a node
	assert (nvals == BSTreeNumNodes (T));

	// every inserted value can be found
	for (int i = 0; i < nvals; i++)
		assert (BSTreeFind (T, v[i]) != 0);

	// (hopefully) non-existent value cannot be found
	assert (BSTreeFind (T, -7654321) == 0);

	///////////
	// tut03 //
	///////////
	
	// printf("Tree has %d internal nodes\n", countInternal(T));
	// printf("Node 3's depth is %d\n", nodeDepth(T, 3));
	// printf("Max branch length = %d\n", BSTreeMaxBranchLen(T));
	// printf("Tree's width is %d\n", BSTWidth(T));

	///////////
	// tut04 //
	///////////
	
	printf("Tree height = %d\n\n", printHeightDiff(T));
	// printf("Tree height = %d\n\n", printHeightDiff2(T));
	
	int result = isAVL(T);
	if (result == -1) printf("Not an AVL tree!");
	else			  printf("AVL tree height = %d", result);
	printf("\n");

	dropBSTree (T);
	return EXIT_SUCCESS;
}
