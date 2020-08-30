#define TRUE 1
#define FALSE 0
#define ARRAY_SIZE 5

#include <stdio.h>

int non_decreasing(int n, int a[n]);
void print_answer(int n, int a[n]);

int main(void) {
	int a[ARRAY_SIZE] = {1, 2, 3, 4, 5}; // yes
	int b[ARRAY_SIZE] = {1, 2, 3, 3, 5}; // yes
	int c[ARRAY_SIZE] = {2, 4, 1, 3, 0}; // no
	int d[ARRAY_SIZE] = {3, 5, 3, 3, 10};// no

	print_answer(ARRAY_SIZE, a);
	print_answer(ARRAY_SIZE, b);
	print_answer(ARRAY_SIZE, c);
	print_answer(ARRAY_SIZE, d);
	
	return 0;
}


// return 1 if the array is non-decreasing
// otherwise return 0

// recursive solution
int non_decreasing(int n, int a[n]) {
    // base case (when to stop)
    if (n == 0 || n == 1) return TRUE;
    if (a[0] > a[1]) return FALSE;
    
    // recursive case (where we call non_decreasing)
    return non_decreasing(n - 1, &a[1]);
}

/*
// iterative solution
int non_decreasing(int n, int a[n]) {
    int i = 0;
    while (i < n - 1) {
        if (a[i] > a[i+1]) {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}
*/

void print_answer(int n, int arr[n]) {
	printf("Array (");
	
	// Print array
	int i;
	for (i = 0; i < n - 1; i++) {
		printf("%d ", arr[i]);
	}
	// different formatting for final element of array
	printf("%d)", arr[n - 1]); 
	
	if (non_decreasing(n, arr)) {
		printf(" is non-decreasing\n");
	} else {
		printf(" is NOT non-decreasing\n");
	}
}