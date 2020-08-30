// Recursively find a fibonacci number. 
// Use cached array to speedup computation :)
// This technique is known as "memoization", 
// typically used in dynamic programming.
// Dynamic programming is not really part of this course, 
// but you'll learn more about it in algos!
// Dylan Blecher, d.blecher@unsw.edu.au
// COMP2521, 19T2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int fibFast(int n);
int fibR(int n, int *knownFib);

int fibSlow(int n);

// woah woah woah are those global variable?
int nCalls = 0;

int main(void) {
	int n;
	printf("Which index of the fibonacci sequence would you like? ");
	scanf("%d", &n);

	// int result = fibFast(n);
	int result = fibSlow(n);

	printf("fib[%d] = %d\n", n, result);
	printf("Calculated with %d calls\n", nCalls);

	return 0;
}

// Dynamic programming approach
// Wrapper around the recursive fib function below
// Set fib array up
int fibFast(int n) {
	assert (n > 0);
	// array of cached fib(n) values, used for memoization
	int *knownFib = calloc (n + 1, sizeof (int)); 

	assert (knownFib != NULL);
	
	knownFib[1] = 1;
	knownFib[2] = 1;
	
	int f = fibR(n, knownFib);
	
	free (knownFib);
	return f;
}

// Recursively find fibonacci
int fibR(int n, int *knownFib) {
	nCalls++;
	assert (n > 0);
	if (n == 1) return 1;
	if (n == 2) return 1;
    if (knownFib[n] != 0) return knownFib[n];

	if (knownFib[n - 1] == 0) knownFib[n - 1] = fibR(n - 1, knownFib);
	if (knownFib[n - 2] == 0) knownFib[n - 2] = fibR(n - 2, knownFib);

	return knownFib[n - 1] + knownFib[n - 2];
}

// See how slow this is with input "40"
int fibSlow(int n) {
	nCalls++;
	assert (n > 0);
	if (n == 1) return 1;
	if (n == 2) return 1;
	return (fibSlow(n - 1) + fibSlow(n - 2));
}






/*
----------
fib(2) return 1
----------
fib(1) return 1
----------
fib(2) return 1
----------
fib(3) return 1 + 1 = 2
----------
fib(4) return 2 + 1 = 3
----------
fib(5) return 3 + fib(3)
----------
STACK
*/