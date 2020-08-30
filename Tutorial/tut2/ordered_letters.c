// Weird time complexity example
// Take a sorted array A[1..n] of characters, and output all 2-letter...
// ...words νω such that ν ≤ ω.
// Written by Dylan Blecher on June 10, 2019 (shit was that last night?)
// d.blecher@unsw.edu.au

#include <stdio.h>
#define SIZE 5

void print_ordered_combos(int n, char sorted_letters[n]);

int main(void) {
	char sorted_letters[SIZE] = {'a', 'b', 'g', 'p', 'z'};
	print_ordered_combos(SIZE, sorted_letters);
	return 0;
}

void print_ordered_combos(int n, char sorted_letters[n]) {			// Time Complexity Analysis
	for (int i = n - 1; i >= 0; i--)								// 1, n, n = 2n + 1
		for (int j = n - 1; j >= i; j--)							// (2n+1)(1), (2n+1)(n - i), (2n+1)(n - i) = (2n+1)(2n - 2i + 1) = 4n^2 + 4ni + 4n - 2i + 1
			printf("%c%c\n", sorted_letters[i], sorted_letters[j]);	// (2n+1)(n - i) = 2n^2 - 2ni + n - i
}																	// Total: O(6n^2 + (7 - 6i)n + (2 - 3i)) ~= O(n^2)