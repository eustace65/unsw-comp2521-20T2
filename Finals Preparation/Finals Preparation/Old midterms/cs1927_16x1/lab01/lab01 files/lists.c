#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"



void printList (link list) {
  link curr = list;
  while (curr != NULL) {
    printf ("[%d]->", curr->item);
    curr = curr->next;
  }
  printf ("[X]\n");
}


int sumListItems (link ls) {
  return 0;
}

void freeList(link list){
   //todo
}

link fromTo (int start, int end) {
  return NULL;
}

dlink doublify (link list) {
  return NULL;
}

void freeDList(dlink list){
   //todo
}