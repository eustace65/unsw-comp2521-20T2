#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include "List.h"


// Practice graph questions for Week 12 Prac Exam
// Written by Paul Wochnowski and Brittany Evat

/* --------------- README --------------
 * A quick note before you begin these questions,
 * it's very strongly recommended that you work these out on pen and paper
 * before actually coding, figure out what edge cases there are, and just
 * work through some of those logically on paper.
 * These questions (tree questions) in particular are typical interview questions.
 * If you're into role playing (or not), try and practice speaking out your thoughts
 * the whole time as you're doing these questions on paper/coding. This is what
 * the interviewer wants to see, your thinking process. It'll also help you maintain
 * focus and pick up errors which you would otherwise miss.
 *
 * https://en.wikipedia.org/wiki/Rubber_duck_debugging is pretty legit
 *
 * glhf
 */


// graph representation for you to play around with (adjacency matrix)
typedef struct GraphRep {
   int   nV;    // #vertices
   int   nE;    // #edges
   int **edges; // matrix of booleans
} GraphRep;

/* 
 * Easy/Medium Questions 
 * - Likely to be asked in a prac exam 
 */

// write a function that takes an undirected Graph g, a vertex v, and returns
// the total number of nodes connected to that vertex
// a node is "connected" if it is reachable from the source vertex v

int bfsConnected(Graph g, int v) {
    
    return 0;
}


// write a function that takes a graph, a source vertex and a
// destination vertex and finds the number of unique paths 
// (that don't contain a cycle) from the source to the destination
/*
void numPathsDFS(Graph g, Vertex curr, Vertex dest, int *visited, int *nPaths);

int numPaths(Graph g, int src, int dest) {
    // Mark all the vertices as not visited
    int *visited = calloc(g->nV, sizeof(int));
    visited[src] = 1;

    // Call the recursive helper function to print all paths 
    int nPaths = 0;
    numPathsDFS(g, src, dest, visited, &nPaths);
    
    return nPaths;
}

void numPathsDFS(Graph g, Vertex curr, Vertex dest, int *visited, int *nPaths) {
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[curr][i] && !visited[i]) {
            // If i is same as destination, we've found a new path
            if (i == dest) {
                (*nPaths)++;
            } else {
                // Recurse for all the vertices adjacent to current vertex 
                visited[i] = 1;
                numPathsDFS(g, i, dest, visited, nPaths);
            }
        }
    }

    // Mark current vertex as unvisited. 
    // This line of code makes the magic happen.
    // For each path, we find, we undo the visited nodes,
    // so we can re-visit them on another path :)
    visited[curr] = 0;
}
*/

// Solve the same problem but use BFS instead of recursive DFS
int numPaths(Graph g, int src, int dest) {
    int nPaths = 0;

    // keep track of each visited node FOR each visited node
	int *visited = calloc(g->nV, sizeof(int));
	assert(visited != NULL); // ran out of memory?

	Queue q = newQueue();
	assert(q != NULL); // ran out of memory?
	enterQueue(q, src);

	// int totalBranches = 0;

	while (!emptyQueue(q)) {
		Vertex x = leaveQueue(q);
		visited[x] = 1;

		// get all adjacent vertices that haven't...
		// ... been visited in ascending order
		// int localBranches = -1;
		for (Vertex y = 0; y < g->nV; y++) {
			if (g->edges[x][y] && !visited[y]) {
				// localBranches++;
				if (y == dest) nPaths++;
				enterQueue(q, y);
			}
		}
		
		// if (localBranches > 0) totalBranches += localBranches;
	}

	free(visited);
	disposeQueue(q);
    
    return nPaths;
}


// (13s1 final exam question)
// write a function that takes a graph and returns the number of components
int max(int *array, int size);

int numComponents(Graph g) {
    int *componentsArray = components(g);
    int maximum = max(componentsArray, g->nV) + 1;
    free(componentsArray);
    return maximum;
}


int max(int *array, int size) {
    if (size == 0) return 0;
    
    int maximum = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > maximum) {
            maximum = array[i];
        }
    }

    return maximum;
}


/*
 * Cycle detection.
 *
 * Write a function which takes in an undirected Graph g, and returns 1 if
 
 * the graph has a cycle, 0 otherwise
 *
 */

int hasCycleDFS(Graph g, Vertex curr, int *visited);

int hasCycle(Graph g) {
    // We must look for cycles starting from each possible vertex in case...
    // ... we have a disconnected graph! (a graph with multiple components)
    // This is because DFS will only search one component.
    for (int startVertex = 0; startVertex < g->nV; startVertex++) {
        // initialise parent array to -1
        int *parent = calloc(g->nV, sizeof(int));
        for (int i = 0; i < g->nV; i++) {
          parent[i] = -1;
        }

        parent[startVertex] = startVertex;
        // conduct DFS from each startVertex
        if (hasCycleDFS(g, startVertex, parent)) return 1;
        free(parent);
    }

    return 0;
}

int hasCycleDFS(Graph g, Vertex curr, int *parent) {
    // if we find a neighbour that has been visited, we've found a cycle
    // UNLESS the neighbour is where we came from 
    // (because this would be a cycle between only 2 nodes)
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[curr][i]) {
            if (parent[i] != -1 && parent[curr] != i) {
                return 1;
            }
            // if it hasn't been visited, recurse from there
            if (parent[i] == -1) {
                parent[i] = curr;
                if (hasCycleDFS(g, i, parent)) return 1;
            }
        }
    }

    return 0;
}

/*
 *
 * Given a unweighted/undirected graph, a starting vertex and a distance, return an array which contains all the vertices that are at most that distance away. 
 * The vertices in the array should be in order of increasing distance, and for vertices that are the same distance away, ordered from smallest to largest. 
 * You should also include the initial vertex in the array and also store the number of vertices in the array you returned in size*.
 *
 
 *  0 -> 1 -> 2
 *  |
 *  v
 *  3
 
 *  within(g,0,1,&n) ==> [0, 3, 1], n == 3
 */
int* within(Graph g, int s, int d, int *size) {

  return NULL;
} 




// Write a function which takes in a Graph g and returns a 
// vertex-indexed connected components array
// e.g. a graph with the following adjacency matrix representation 

// 0 1 0 0

// 1 0 0 0

// 0 0 0 1

// 0 0 1 0
// would return the following array:

// [0, 0, 1, 1]

// i.e. vertices 0 and 1 are in the first connected component (represented by 0 in the array), and
// vertices 2 and 3 are in the second connected component (represented by 1)
#define ALL_SET -1

int lowestUnset(int *parts, int size);
void partsDFS(Graph g, Vertex start, int *parts, int componentNum);

int *components(Graph g) {
    // initialise each node to component -1
    int *parts = calloc(g->nV, sizeof(int));
    for (int i = 0; i < g->nV; i++) {
        parts[i] = -1;
    }

    int componentNum = 0;
    int start = lowestUnset(parts, g->nV);
    while (start != ALL_SET) {
        parts[start] = componentNum;
        partsDFS(g, start, parts, componentNum);
        componentNum++;
        start = lowestUnset(parts, g->nV);
    }

    return parts;
}

int lowestUnset(int *parts, int size) {
    for (int i = 0; i < size; i++) {
        if (parts[i] == -1) return i;
    }
    
    return ALL_SET;
}

void partsDFS(Graph g, Vertex start, int *parts, int componentNum) {
    for (int i = 0; i < g->nV; i++) {
        // for each connected node that hasn't been visited
        if (g->edges[start][i] && parts[i] == -1) {
            parts[i] = componentNum;
            partsDFS(g, i, parts, componentNum);
        }
    }
}

/*
 * Hard Questions
 * - Unlikely to be asked in a prac exam
 */

/* 
  Create a bipartition of the graph.

  Determine whether it is possible to split the vertices of a graph into two lists L1 and L2, such that no pair of vertices in the same list are connected by an edge in the graph. 
  If this is possible, return 1 and store the two partitions seperately in either L1 or L2. There will usually be multiple valid partitions, in this case you may return any valid answer. 
  
  If it is not possible, return 0.

  For example consider the following graph:

  1  -> 2  -> 5
              ^
  |           |
  v           v
  4 <-> 3  -> 6
  bipartation(G, l1, l2) == 1,
  one possible example of a bipartition for G is L1 = [1, 5, 3], L2 = [2, 4, 6]


  1 <-> 2 <-> 3 <---\
        ^           |
        |           |
        v           v 
        4 <-> 6 <-> 7 
  
  bipartition(G, l1, l2) == 0

*/

int bipartition(Graph g, List l1, List l2) {

  return 1;
}


/*
 * =============================================
 * END OF QUESTIONS 
 * ============================================
 */


/*
   You can ignore these methods below, unless you want examples of using the  graph 
   */

// check validity of Vertex 
int validV(Graph g, int v)
{
  
  return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, int v, int w)
{
  assert(g != NULL && validV(g,v) && validV(g,w));
  Edge new = {v,w}; // struct assignment
  return new;
}

// insert a bidirectional edge from v to w
// - sets (v,w) and (w,v)
void insertBEdge(Graph g, int v, int w, int wt)
{
  insertEdge(g,v,w,wt);
  insertEdge(g,w,v,wt);
}

//insert an edge from v to w
// - sets (v,w)
void insertEdge(Graph g, int v, int w, int wt)
{
  assert(g != NULL && validV(g,v) && validV(g,w));
  
  if (g->edges[v][w] == 0) {
    g->edges[v][w] = wt;
    g->nE++;
  }
}
// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, int v, int w)
{
  assert(g != NULL && validV(g,v) && validV(g,w));
  
  if (g->edges[v][w] != 0) {
    
    g->edges[v][w] = 0;
    g->nE--;
  }
}

// create an empty graph
Graph newGraph(int nV)
{
  
  assert(nV > 0);
  int v, w;
  Graph new = malloc(sizeof(GraphRep));
  
  assert(new != 0);
  
  new->nV = nV; new->nE = 0;
  new->edges = malloc(nV*sizeof(int *));
  
  assert(new->edges != 0);
  
  for (v = 0; v < nV; v++) {
    new->edges[v] = malloc(nV*sizeof(int));
    
    assert(new->edges[v] != 0);
    
    for (w = 0; w < nV; w++)
      
      new->edges[v][w] = 0;
  }
  return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
  assert(g != NULL);
  int v;
  
  for (v = 0; v < g->nV; v++) {
    free(g->edges[v]);
  }
  free(g->edges);
  free(g);

}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
  assert(g != NULL);
  printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
  int v, w;
  
  for (v = 0; v < g->nV; v++) {
    printf("%d %s\n",v,names[v]);
    
    for (w = 0; w < g->nV; w++) {
      if (g->edges[v][w]) {
        printf("\t%s (%d)\n",names[w],g->edges[v][w]);
      }
    }
    printf("\n");
  }
}

int adjacent(Graph g, int v, int u) {
  return !!g->edges[v][u] || !!g->edges[u][v];
}
