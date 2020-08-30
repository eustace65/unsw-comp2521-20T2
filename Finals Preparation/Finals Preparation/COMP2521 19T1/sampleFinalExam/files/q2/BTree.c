
#include "BTree.h"

int isHeap(BTree  t) {
    int ans;

    if ((data(left(t)) > data(t) || data(right(t)) > data(t))) {return 0;}
    //else {return 1;}

    if (left(t) != NULL) ans = isHeap(left(t));
    if (right(t) != NULL && ans != 0) ans = isHeap(right(t)); // save time

    return ans;
}


int isHeap(BTree  t) {

   // TODO
}





}
