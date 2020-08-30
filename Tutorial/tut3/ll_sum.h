typedef struct _Node {
	int value;
	struct _Node *next;
} Node;
 
typedef Node *List;  // pointer to first Node

Node *strings_to_list(int len, char *strings[]);
int sum(Node *head);
void print_list(Node *head);
void free_list(Node *head);