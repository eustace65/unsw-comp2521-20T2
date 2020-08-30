// COMP2521 20T2 Final Exam Q2
// Check graph property

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Constants

#define MAXVERTICES 20
#define MAXLINE 100

// Directed graph as adjacency matrix
// The matrix is *not* symmetric
typedef struct _graph_rep {
	int   nV; 
	bool  edge[MAXVERTICES][MAXVERTICES];
} DiGraph;

// Helper functions
void readGraph(FILE *, DiGraph *);
bool graphIsBinTree(DiGraph);
void showGraph(FILE *, DiGraph);

int main(int argc, char **argv)
{
	DiGraph g;  // graph struct
	FILE *in;   // input file handle

	// handle command-line arguments
	if (argc < 2) {
		fprintf(stderr,"Usage: %s GraphFile\n", argv[0]);
		exit(1);
	}
	if ((in = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't read %s\n", argv[1]);
		exit(1);
	}

	// main program
	readGraph(in, &g);
	showGraph(stdout, g);
	printf("\nGraph is ");
	if (!graphIsBinTree(g)) printf("not ");
	printf("a tree\n");
	
	// clean up
	return 0;
}

// Sort "n" records in the "stu" array by order
// Always in ascending order
// If order == BY_ZID, sort numerically on unique "zid" field
// If order == BY_NAME, sort lexicographically on "name" field
//    names are, perhaps unrealistically, assumed to be unique
bool graphIsBinTree(DiGraph g)
{
	// TODO
	int incoming[MAXVERTICES] = {0};
	bool exist[MAXVERTICES] = {false};
	for (int i = 0; i < MAXVERTICES; i++) {
	    int counter = 0;
	    for (int j = 0; j < MAXVERTICES; j++) {
	        if (g.edge[i][j]) {
	            counter++;
	            incoming[j] += 1;
	            exist[i] = true;
	            exist[j] = true;
	        }  
	    }
	    if (counter > 2)
	        return false;
	}
	int num_0_incoming = 0;
	for (int i = 0; i < MAXVERTICES; i++) {
	    if (incoming[i] > 1)
	        return false;
	    if (incoming[i] == 0 && exist[i])
	        num_0_incoming++;
	}
	if (num_0_incoming != 1)
	    return false;
	return true;
}

// Read Graph from "in" file
// Read into DiGraph struct referenced by "g"
void readGraph(FILE *in, DiGraph *g)
{
	char *c, line[MAXLINE];
	int  n, v, nV;
	bool first;

	for (int v = 0; v < MAXVERTICES; v++) {
		for (int w = 0; w < MAXVERTICES; w++)
			g->edge[v][w] = false;
	}
	nV = 0;
	while (fgets(line, MAXLINE, in) != NULL) {
		c = line; first = true;
		while (*c != '\0') {
			// find next number in line
			while (*c != '\0' && !isdigit(*c)) c++;
			if (*c == '\0') break;
			sscanf(c,"%d", &n);
			if (first)
				{ v = n; first = false; }
			else
				g->edge[v][n] = true;
			// skip number we just scan'd
			while (*c != '\0' && isdigit(*c)) c++;
		}
		nV++;
	}
	g->nV = nV;
}

// Print graph info on output file "out"
void showGraph(FILE *out, DiGraph g)
{
	printf("V    Connected to\n");
	printf("--   ------------\n");
	int v, w;
	for (v = 0; v < g.nV; v++) {
		int nout = 0;
		printf("%-3d ",v);
		for (w = 0; w < g.nV; w++) {
			if (g.edge[v][w]) {
				printf(" %d",w);
				nout++;
			}
		}
		if (nout == 0) printf(" -");
		printf("\n");
	}
}
