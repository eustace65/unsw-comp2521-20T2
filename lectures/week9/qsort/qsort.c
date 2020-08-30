// read numbers from stdin into array
// qsort them
// write them out

#include <stdlib.h>
#include <stdio.h>

#define MAX 10000

int intCompare(const void *x, const void *y)
{
	int xval = *((int *)x);
	int yval = *((int *)y);
#if 1
	return (xval - yval);
#else
	if (xval < yval)
		return -2;
	else if (xval > yval)
		return 2;
	else
		return 0;
#endif
}

int main(int argc, char **argv)
{
	int a[MAX], n = 0, val;

	while (scanf("%d", &val) == 1) a[n++] = val;

	qsort(a, n, sizeof(int), intCompare);

	// f(1,2,3) ... fn call
	// f  or  &f ... pointer to function

	for (int i = 0; i < n; i++)
		printf("%d\n", a[i]);

	return 0;
}
