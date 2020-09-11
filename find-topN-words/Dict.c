// COMP2521 20T2 Assignment 1
// Dict.c ... implementsation of Dictionary ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dict.h"
#include "WFreq.h"

#define MAXWORD 100

typedef struct _DictNode *Link;

typedef struct  _DictNode {
   WFreq  *data;
   Link   left;
   Link   right;
   int height;
} DictNode;

struct _DictRep {
   Link tree;
};



//Function Declaration
static Link newNode(WFreq *data);
static Link doInsert(Link node, WFreq *w);
static int height(Link n);
static int max(int a, int b);
static Link rotateRight(Link n);
static Link rotateLeft(Link n);
static Link doFind(Link node, char *w);
static void show(Link node);
static void doFindTop(Link node, WFreq *wfs, int n, int *outputNum);
static void insertTopN(Link node, WFreq *wfs, int n, int *outputNum);

// create new empty Dictionary
Dict newDict()
{
   // TODO
   Dict new = malloc(sizeof(*new));
   assert(new != NULL);
   new->tree = NULL;
   return new;
}

// insert new word into Dictionary
// return pointer to the (word,freq) pair for that word
WFreq *DictInsert(Dict d, char *w)
{
   // TODO
   WFreq *new = malloc(sizeof(*new));
   assert(new != NULL);
   //allocate memory
   new->word = (char *) malloc(MAXWORD);
   strcpy(new->word, w);
   new->freq = 1;
   d->tree = doInsert(d->tree, new);
   return new;
}

// find Word in Dictionary
// return pointer to (word,freq) pair, if found
// otherwise return NULL
WFreq *DictFind(Dict d, char *w)
{
   // TODO
   Link n = doFind(d->tree, w);
   if (n != NULL) 
      return n->data;
            
   return NULL;
}

// find top N frequently occurring words in Dict
// input: Dictionary, array of WFreqs, size of array
// returns: #WFreqs in array, modified array
int findTopN(Dict d, WFreq *wfs, int n)
{
   // TODO
   int outputNum = 0;
   // Initialize the array
   for (int i = 0; i < n; i++) {
      wfs[i].word = (char *) malloc(MAXWORD);
      wfs[i].freq = 0; 
   }
   doFindTop(d->tree, wfs, n, &outputNum);
   if (outputNum > n)
      return n;
   return outputNum;
}

//---------------------------Auxiliary Functions------------------------

// print a dictionary
void showDict(Dict d)
{
   // TODO if you need to display Dict's for debugging
   show(d->tree);
   return;
}

//Insert top N frequently occurring words to an array
static void insertTopN(Link node, WFreq *wfs, int n, int *outputNum) 
{
   for (int i = 0; i < n; i++) {
      if (node->data->freq >= wfs[i].freq) {
         // shift the data right
         for (int j = n - 1; j > i; j--) {
            wfs[j].freq = wfs[j - 1].freq;
            strcpy(wfs[j].word, wfs[j - 1].word);
         }
         // insert
         wfs[i].freq = node->data->freq;
         strcpy(wfs[i].word, node->data->word);
         *outputNum += 1;
         break;
      }
   }
}

//Tranverse the tree and insertTopN
static void doFindTop(Link node, WFreq *wfs, int n, int *outputNum) 
{
   if (node != NULL) {
      doFindTop(node->right, wfs, n, outputNum);
      insertTopN(node, wfs, n, outputNum);
      doFindTop(node->left, wfs, n, outputNum);
   }
}

// find Word in Dictionary
// return node of the word, if found
// Otherwise return NULL
static Link doFind(Link node, char *w) 
{
   if (node == NULL)
      return NULL;
      
   int cmp = strcmp(w, node->data->word); 
   if (cmp < 0) {
      // left subtree
      return doFind(node->left, w);
   } else if (cmp > 0) {
      // right subtree
      return doFind(node->right, w);
   } else {
      return node;
   }
}

// Insert (word,freq) pair into the node
// Using AVL tree to balance
// Return tree node
static Link doInsert(Link node, WFreq *w) 
{
   if (node == NULL) {
      return newNode(w);
   }
   int cmp = strcmp(w->word, node->data->word);
   if (cmp < 0) {
      // left subtree
      node->left = doInsert(node->left, w);
   } else if (cmp > 0) {
      // right subtree
      node->right = doInsert(node->right, w);
   }
   
   // adjust height
   node->height = 1 + max(height(node->left), height(node->right));
   // rotate to form an AVL tree
   if (height(node->left) - height(node->right) > 1) {
      if (strcmp(w->word, node->left->data->word) > 0) {
         node->left = rotateLeft(node->left);
      }
      node = rotateRight(node);
   } else if (height(node->right) - height(node->left) > 1) {
      if (strcmp(w->word, node->right->data->word) < 0) {
         node->right = rotateRight(node->right);
      }
      node = rotateLeft(node);
   }
   return node;
}

// Initialize a new node and allocate memory
// Insert (word,freq) pair into node
static Link newNode(WFreq *data) 
{
   Link node = malloc(sizeof(*node));
   assert(node != NULL);
   node->left = NULL;
   node->right = NULL;
   node->data = data;
   node->height = 0;
   return node;
}

// Return height of a node
static int height(Link n) 
{
   if (n == NULL) {
      return -1;
   } else {
      return n->height;
   }
}

// Return max number of two integers
static int max(int a, int b) 
{
   return a > b ? a : b;
}

// Rotate left from a node
static Link rotateLeft(Link n) 
{
   if (n == NULL || n->right == NULL)
      return n;
   Link n1 = n->right;
   n->right = n1->left;
   n1->left = n;
   n->height = 1 + max(height(n->left), height(n->right));
   n1->height = 1 + max(height(n1->left), height(n1->right));
   return n1;
}

// Rotate right from a node
static Link rotateRight(Link n) 
{
   if (n == NULL || n->left == NULL)
      return n;
   Link n1 = n->left;
   n->left = n1->right;
   n1->right = n;
   n->height = 1 + max(height(n->left), height(n->right));
   n1->height = 1 + max(height(n1->left), height(n1->right));
   return n1;
}

// print a dictionary
static void show(Link node) 
{
   if (node != NULL) {
      show(node->right);  
      printf("%s %d\n", node->data->word, node->data->freq); 
      show(node->left);
   }
}

