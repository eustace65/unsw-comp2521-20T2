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

	if (argc < 4)
		{ fprintf(stderr,"Usage...\n"); exit(1); }

	in1 = openFile(argv[1]); val1 = getNext(in1);
	in2 = openFile(argv[2]); val2 = getNext(in2);
	in3 = openFile(argv[3]); val3 = getNext(in3);

	while (val1 != -1 && val2 != -1 && val3 != -1) {
		switch(least(val1,val2,val3)) {
		case 1: printf("%d\n",val1); val1 = getNext(in1); break;
		case 2: printf("%d\n",val2); val2 = getNext(in2); break;
		case 3: printf("%d\n",val3); val3 = getNext(in3); break;
		default: printf("BUG!\n"); exit(1); break;
		}
	}
	while (val1 != -1 && val2 != -1) {
		if (val1 < val2)
			{ printf("%d\n",val1); val1 = getNext(in1); }
		else
			{ printf("%d\n",val2); val2 = getNext(in2); }
	}
	while (val1 != -1 && val3 != -1) {
		if (val1 < val3)
			{ printf("%d\n",val1); val1 = getNext(in1); }
		else
			{ printf("%d\n",val3); val3 = getNext(in3); }
	}
	while (val2 != -1 && val3 != -1) {
		if (val2 < val3)
			{ printf("%d\n",val2); val2 = getNext(in2); }
		else
			{ printf("%d\n",val3); val3 = getNext(in3); }
	}
	while (val1 != -1) { printf("%d\n",val1); val1 = getNext(in1); }
	while (val2 != -1) { printf("%d\n",val2); val2 = getNext(in2); }
	while (val3 != -1) { printf("%d\n",val3); val3 = getNext(in3); }

	return 0;
}

// attempts to open file for reading
// prints message and exits if can't open
FILE *openFile(char *name)
{
	FILE *f = fopen(name,"r");
	if (f == NULL) {
		fprintf(stderr,"Can't open %s\n", name);
		exit(1);
	}
	return f;

	//fopen(fname,"w") ... truncates any existing fname
	//fopen(fname,"a") ... appends to the named file
}

// returns next integer in file
// returns -1 if no next integer
int getNext(FILE *in)
{
#if 1
   int val = -1;
   fscanf(in, "%d", &val);
   return val;
#else
   int n, val;
   n = fscanf(in, "%d", &val);
   return (n != 1) ? -1 : val;
#endif
   // scanf(fmt,...) == fscanf(stdin,fmt,...)
}

// returns which of 3 ints is smallest
// return value is 1, 2, or 3, NOT the smallest value
int least(int x, int y, int z)
{
	if (x < y) {
		if (x < z) return 1; else return 3;
	}
	else {
		if (y < z) return 2; else return 3;
	}
}
