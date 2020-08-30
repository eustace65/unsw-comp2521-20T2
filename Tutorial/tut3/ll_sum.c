// This program sums the values of a linked list
// Written by Dylan Blecher, June 2019
// d.blecher@unsw.edu.au

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ll_sum.h"

int main(int argc, char *argv[]) {
   char *list1[] = {"2", "4", "8", "16"};
   Node *head = strings_to_list(4, list1);
   printf("sum = %d\n", sum(head));
   return 0;
}


// Sum the values of a linked list using a while loop
int sum(Node *head) {
    int total = 0;
    
    Node *curr = head;
    while (curr != NULL) {
        total += curr->value;
        curr = curr->next;
    }
    
    return total;
}

// Sum the values of a linked list using a for loop
int sum(Node *head) {
    int total = 0;

    for (Node *curr = head; curr != NULL; curr = curr->next)
        total += curr->value;
    
    return total;
}


// Sum the values of a linked list recursively
2 -> 4 -> 8 -> NULL
int sum(Node *head) {
    // base case
    if (head == NULL) return 0;

    // recursive case
    return head->value + sum(head->next);
}

// return 1
// ----------------
// head = NULL return 0
// ----------------
// head = 8 return 8 + 0 = 8
// ----------------
// head = 4 return 4 + 8 = 12
// ----------------
// head = 2 return 2 + 12 = 14
// ----------------

// create linked list from array of strings
Node *strings_to_list(int len, char *strings[]) {
    struct _Node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        Node *n = malloc(sizeof(Node));
        assert(n != NULL);
        n->next = head;
        n->value = atoi(strings[i]);
        head = n;
        i = i - 1;
    }
    return head;
}

// print linked list in python style (i.e. [1, 2, 3, 4])
void print_list(Node *head) {
    Node *curr = head;
    printf("[");
    while (curr != NULL) {
    	printf("%d", curr->value);
    	if (curr->next != NULL) {
    		printf(", ");
    	}
    	curr = curr->next;
    }
    printf("]\n");
}

// free the memory used by the linked list
void free_list(Node *head) {
    while (head != NULL) {
    	Node *free_me = head;
    	head = head->next;
    	free(free_me);
    }
}