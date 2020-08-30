// Credit Zain Afzal for this code. What a legend.
// Adapted from Zain's code by Dylan Blecher 
// COMP2521 19T2

#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "queue.h"

// vertices denoted by integers 0..N-1
typedef struct graphRep *Graph;
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct { Vertex v; Vertex t; int w; } Edge;

Graph newGraph(int max);
void killGraph(Graph g);
void addEdge(Graph g, int v, int t, int w);
int hasEdge(Graph g, int v, int t);
int edgeWeight(Graph g, int v, int t);
int numEdges(Graph g);
Set reachable(Graph g, Vertex v);

///// Adjacency matrix graph representation
struct graphRep {
    int nV;       // #vertices
    int nE;       // #edges
    int **edges;  // matrix of booleans (0 or 1)
};

int main(void) {
    Graph g = newGraph(10);
    // 1
    addEdge(g,0,2,2);
    addEdge(g,0,4,1);
    addEdge(g,0,3,4);
    // 2
    addEdge(g,2,5,10);
    // 3
    addEdge(g,3,6,5);
    // 4
    addEdge(g,4,3,2);
    addEdge(g,4,6,8);
    addEdge(g,4,7,4);
    addEdge(g,4,5,7);
    addEdge(g,4,2,3);
    // 5
    addEdge(g,5,7,6);
    // 6
    addEdge(g,6,7,1);

    addEdge(g,8,9,1);

    printf("--------------------\n");
    printf("Expected answer is 7.\n");
    printf("--------------------\n");

    Set reached = reachable(g, 0);
    showSet(reached);

    printf("--------------------\n");
    printf("Expected answer is 2.\n");
    printf("--------------------\n");
    
    reached = reachable(g, 8);
    showSet(reached);

    killGraph(g);

    return EXIT_SUCCESS;
}

// Set reachable(Graph g, Vertex v) {
//     // create a queue for nodes to visit
//     Queue q = newQueue();
//     enterQueue(q, v);

//     Set s = newSet();
//     insertInto(s, v);

//     // int visited[g->nV] = {0};
//     int *visited = calloc(g->nV, sizeof(int));
//     visited[v] = 1;

//     // for each node on the queue, look at all surrounding nodes 
//     while (!emptyQueue(q)) {
//         int curr = leaveQueue(q);
//         // add unseen neighbours to "todo" list
//         for (int i = 0; i < g->nV; i++) {
//             if (g->edges[i][curr] && !visited[i]) {
//                 visited[i] = 1;
//                 insertInto(s, i); 
//                 enterQueue(q, i);
//             }
//         }
//     }

//     dropQueue(q);
//     return s;
// }

// Here is an alternative solution that doesn't use a visited array.
// Instead, it uses the "seen" set.

// Set reachable(Graph g, Vertex v) {
//     Set seen = newSet();
//     Queue todo = newQueue();
//     enterQueue(todo, v);
//     insertInto(seen, v);
//     while (!emptyQueue(todo)) {
//         Vertex next = leaveQueue(todo);
//         // add unseen neighbours to "todo" list
//         for (int i = 0; i < g->nV; i++) {
//             if (g->edges[next][i] && !isElem(seen, i)) {
//                 enterQueue(todo, i);
//                 insertInto(seen, i);
//             }
//         }
//     }
//     dropQueue(q);
//     return seen;
// }


// Here is a recursive alternative solution.
void reachableRecursiveDFS(Graph g, Vertex v, Set seen);

Set reachable(Graph g, Vertex v) {
    Set seen = newSet();
    reachableRecursiveDFS(g, v, seen);
    return seen;
}

void reachableRecursiveDFS(Graph g, Vertex v, Set seen) {
    // add item to seen set
    insertInto(seen, v);
    
    // recurse on all neighbours that haven't been seen
    for (Vertex n = 0; n < g->nV; n++)
        if (g->edges[v][n] && !isElem(seen, n))
            reachableRecursiveDFS(g, n, seen);
}

Graph newGraph(int max){
    Graph g = malloc(sizeof(struct graphRep));
    g->nV = max;
    g->nE = 0;
    g->edges = malloc(sizeof(int*)*max);
    for (int i = 0; i < max; i++)
        g->edges[i] = calloc(sizeof(int),max);
    return g;
    }

void killGraph(Graph g) {
    for (int i = 0; i<g->nV; i++)
        free(g->edges[i]);
    
    free(g->edges);
    free(g);
}

void addEdge(Graph g, int v, int t, int w) {
    if (!g->edges[v][t]) g->nE++;
    g->edges[v][t] = w;
    g->edges[t][v] = w;
}

int hasEdge(Graph g, int v, int t) {
    return g->edges[v][t] > 0;
}

int edgeWeight(Graph g, int v, int t) {
    return g->edges[v][t];
}

int numEdges(Graph g) {
    return g->nE;
}