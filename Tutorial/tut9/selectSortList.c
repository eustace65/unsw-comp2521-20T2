// Given a linked list, apply select sort to return a new sorted linked list
// tut09, COMP2521, 19T2
// Dylan Blecher, d.blecher@unsw.edu.au

struct node {
	int value;
	struct node *next;
}

typedef struct node *List;

// ls points to the head of the unsorted list
List selectSort(List ls) {
	List sorted = NULL;

	// keep moving the smallest node from ls to sorted until ls is empty
	while (ls != NULL) {
		// Search through list to find smallest item
		struct node *curr = ls;
		struct node *smallest = ls;
		while (curr != NULL) {
			if (curr->value < smallest->value) {
				smallest = curr;
			}
		}

		sorted = appendNode(sorted, smallest);
		ls = removeNode(ls, smallest);
	}

	return sorted;
}

////////////////////////
//                    //
//  Helper functions  //
//                    //
////////////////////////

// return the head of the new list
void appendNode(List list, struct node *appendMe) {
	// Create a new node
	struct node *new = malloc(sizeof(struct node));
	node->next = NULL;
	node->value = appendMe->value;

	// if the list is empty, the list becomes the new node
	if (list == NULL) return new;

	// find the last node, and add the new one after.
	struct node *curr = list;
	while (curr->next != NULL) {
		curr = curr->next;
	}

	curr->next = new;

	return list;
}

// return the head of the new list
void removeNode(List list, struct node *removeMe) {
	// empty list case
	if (list == NULL) return NULL;

	// find the node we wish to delete
	struct node *curr = list;
	struct node *prev = NULL;
	while (curr != removeMe && curr != NULL) {
		prev = curr;
		curr = curr->next;
	}

	// If removeMe is not in the list
	if (curr == NULL) return list;

	// If we're deleting the first item
	if (prev == NULL) {
		free(curr);
		return curr->next;
	}

	// General case
	prev->next = curr->next;
	free(curr);
	return list;
}