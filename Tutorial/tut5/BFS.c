typedef struct GraphRep *Graph;

struct GraphRep {
	int nV;
	// Adjacency matrix called "edges"
	int edges[nV][nV]; // int **edges;
};

void breadthFirst(Graph g, Vertex starting_vertex) 
{
	int *visited = calloc(g->nV, sizeof(int));
	Queue q = newQueue();
	QueueJoin(q, starting_vertex);
	visited[starting_vertex] = 1;

	while (QueueLength(q) > 0) {
		Vertex x = QueueLeave(q);
		printf("%d\n", x);

		// get all adjacent vertices that haven't...
		// ... been visited in ascending order
		for (Vertex y = 0; y < g->nV; y++) {
			if (g->edges[x][y] && !visited[y]) {
				QueueJoin(q, y);
				visited[y] = 1;
			}
		}
	}
	dropQueue(q);
}

void depthFirst(Graph g, Vertex starting_vertex)
{
	int *visited = calloc(g->nV, sizeof(int));
	Stack s = newStack();
	StackPush(s, starting_vertex);
	visited[starting_vertex] = 1;

	while (!StackIsEmpty(s)) {
		Vertex x = StackPop(s);
		printf("%d\n", x);

		// get all adjacent vertices that haven't...
		// ... been visited in ascending order
		for (Vertex y = 0; y < g->nV; y++) {
			if (g->edges[x][y] && !visited[y]) {
				StackPush(s, y);
				visited[y] = 1;
			}
		}
	}
	dropStack(s);
}