#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"

// insert proper tests here
int main (int argc, const char * argv[]) {
  link list = fromTo (1, 10);
  printList (list);
  return 0;
}