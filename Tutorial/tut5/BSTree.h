// BSTree.h ... interface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H

typedef struct BSTNode *BSTree;

// create an empty BSTree
BSTree newBSTree (void);
// free memory associated with BSTree
void dropBSTree (BSTree);
// display a BSTree
void showBSTree (BSTree);
// display BSTree root node
void showBSTreeNode (BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert (BSTree, int);

///////////
// tut05 //
///////////
int height(BSTree t);
int isAVL(BSTree t);
int BSTWidth(BSTree t);

#endif