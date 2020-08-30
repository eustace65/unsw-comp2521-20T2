// Demonstrates 2 examples of recursive Depth First Search (DFS) 
// Checkout reach() and reachable()
// The idea with recursive DFS is to just go through each...
// ... unvisited neighbour, set it to visited and then recurse.
// Written by Dylan Blecher COMP2521 19T2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// vertices denoted by integers 0..N-1
typedef int Vertex;
typedef struct graphRep *Graph;

// Adjacency matrix undirected graph representation
struct graphRep {
    int nV;       // #vertices
    int **edges;  // matrix of booleans (0 or 1)
};

void testIsReachable(Graph g);
Graph createExampleGraph(void);
Graph newGraph(int size);
void killGraph(Graph g);
void addEdge(Graph g, int from, int to);

void printReachable(Graph g, Vertex start);
void reach(Graph g, Vertex start, int visited[]);

int isReachable(Graph g, Vertex start, Vertex end);
int reachable(Graph g, Vertex start, Vertex end, int seen[]);

int main(void) {
    Graph g = createExampleGraph();
    printReachable(g, 0);
    testIsReachable(g);
    killGraph(g);
    return 0;
}

////////////////////////////////////////////////////////
// print all vertexes reachable from the start vertex //
////////////////////////////////////////////////////////

// wrapper around reach()
void printReachable(Graph g, Vertex start) {
    printf("Nodes reachable from start vertex %d: ", start);
    int *visited = calloc(g->nV, sizeof(int));
    visited[start] = 1;
    reach(g, start, visited);
    printf("\n\n");
    free(visited);
}

// Using recursive DFS, reach and print all nodes from start vertex
// Note that for DFS, there's no real base case. 
// Recursion stops once all nodes have been visited.
void reach(Graph g, Vertex start, int visited[]) {
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[start][i] && !visited[i]) {
            visited[i] = 1;
            printf("%d ", i);
            reach(g, i, visited);
        }
    }
}

//////////////////////////////////////////////////////////////
// See if the end vertex is reachable from the start vertex //
//////////////////////////////////////////////////////////////

// wrapper around reachable()
int isReachable(Graph g, Vertex start, Vertex end) {
    int *visited = calloc(g->nV, sizeof(int));
    visited[start] = 1;
    int result = reachable(g, start, end, visited);
    free(visited);
    return result;
}

// print each reachable vertex from a given start vertex "v"
// Implemented with recursive DFS
int reachable(Graph g, Vertex start, Vertex end, int visited[]) {
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[start][i] && !visited[i]) {
            visited[i] = 1;
            if (i == end) return 1;
            if (reachable(g, i, end, visited)) return 1;
        }
    }

    // We will only reach here after all possible recursions are complete
    // so we would've already returned 1 if "end" was reachable
    return 0;
}

void testIsReachable(Graph g) {
    printf("Testing isReachable():\n");
    assert(isReachable(g, 0, 2));
    printf("Test 1 passed!\n");
    assert(!isReachable(g, 0, 9));
    printf("Test 2 passed!\n");
    assert(isReachable(g, 2, 7));
    printf("Test 3 passed!\n");
    assert(!isReachable(g, 0, 1));
    printf("Test 4 passed!\n\nAll tests passed!\n");
}

////////////////////////////////////
// Graph implementation and setup //
////////////////////////////////////

Graph createExampleGraph(void) {
    Graph g = newGraph(10); // nodes 0...9
    addEdge(g,0,2);
    addEdge(g,0,4);
    addEdge(g,0,3);
    addEdge(g,2,5);
    addEdge(g,3,6);
    addEdge(g,4,3);
    addEdge(g,4,6);
    addEdge(g,4,7);
    addEdge(g,4,5);
    addEdge(g,4,2);
    addEdge(g,5,7);
    addEdge(g,6,7);
    addEdge(g,8,9);
    return g;
}

Graph newGraph(int size){
    Graph g = malloc(sizeof(struct graphRep));
    g->nV = size;

    g->edges = calloc(sizeof(int *), size);
    for (int i = 0; i < g->nV; i++) {
        g->edges[i] = calloc(sizeof(int), size);
    }

    return g;
}

void killGraph(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    
    free(g->edges);
    free(g);
}

void addEdge(Graph g, int from, int to) {
    g->edges[from][to] = 1;
    g->edges[to][from] = 1;
}
