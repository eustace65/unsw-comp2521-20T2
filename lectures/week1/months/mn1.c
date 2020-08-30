// mn.c ... convert month ordinal to name
// Written by John Shepherd, July 2015
// This version shows "typical" formatting

#include <stdlib.h>
#include <stdio.h>

void giveUp(char *);
char *monthName(int);

int main(int argc, char **argv)
{
	// argument processing
	if (argc < 2) giveUp(argv[0]);
	int n = atoi(argv[1]);
	if (n < 1 || n > 12) giveUp(argv[0]);

	// compute and print name
	printf("%s\n", monthName(n));

	exit(EXIT_SUCCESS);
}

// pre: defined(integer,monthNum)
// post: ret == ((1 <= monthNum <= 12) ? nameOfMonth[monthNum] : "????")
char *monthName(int monthNum)
{
	switch (monthNum) {
	case 1: return "January";
	case 2: return "February";
	case 3: return "March";
	case 4: return "April";
	case 5: return "May";
	case 6: return "June";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "October";
	case 11: return "November";
	case 12: return "December";
	default: return "????";
	}
}

// pre: defined(string,cmdName)
// post: program has terminated
void giveUp(char *cmdName)
{
	fprintf(stderr, "Usage: %s 1..12\n", cmdName);
	exit(EXIT_FAILURE);
}
