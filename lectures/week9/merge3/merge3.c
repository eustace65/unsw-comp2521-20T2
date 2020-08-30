// Three-way file merge
// Each file contains ...
// +ve integers, one per line, in ascending order
// Output contains ...
// all values from all files, in ascending order

#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *);
int getNext(FILE *in);
int least(int, int, int);

int main(int argc, char **argv)
{
	int  val1, val2, val3;
	FILE *in1, *in2, *in3;

	// handle command-line arguments
	if (argc < 4) {
		fprintf(stderr, "Usage: %s File1 File2 File3\n", argv[0]);
		exit(1);
	}
	in1 = openFile(argv[1]);
	in2 = openFile(argv[2]);
	in3 = openFile(argv[3]);

	// merge files
	val1 = getNext(in1);
	val2 = getNext(in2);
	val3 = getNext(in3);

	// merge step while all three files are open
	while (val1 > 0 && val2 > 0 && val3 > 0) {
		; // etc. etc.
	}

	return 0;
}

// attempts to open file for reading
// prints message and exits if can't open
FILE *openFile(char *name)
{
	FILE *f = fopen(name, "r");
	if (f == NULL) {
		fprintf(stderr, "Can't open %s\n", name);
		exit(1);
	}
	return f;
}

// returns next integer in file
// returns -1 if no next integer
int getNext(FILE *in)
{
	int n, val;
	n = fscanf(in, "%d", &val);
	return (n == 0) ? -1 : val;
}

// returns which of 3 ints is smallest
// return value is 1, 2, or 3, NOT the smallest value
int least(int x, int y, int z)
{
	if (x < y)
		{ if (x < z) return 1; else return 3; }
	else
		{ if (y < z) return 2; else return 3; }
}
