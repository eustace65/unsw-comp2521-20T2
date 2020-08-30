// List ADT interface

// each List Node contains an integer value
typedef struct Node {
	int value;
	List next;
} Node;

// a List is represented as a pointer to the frst Node
typedef Node *List;

// returns a new empty List
List new();
// checks whether L is empty
bool empty(List L);
// returns first element in L
int head(List L);
// returns all but first element in L
List tail(List L);
// returns new list with x as head and L as tail
List insert(int x, List L);
// returns new list with x as last element
List append(List L, int x);
// returns new list which is concatenation of lists L1 and L2
List concat(List L1, List L2);
