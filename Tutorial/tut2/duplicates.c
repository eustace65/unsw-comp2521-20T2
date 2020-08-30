// Print the duplicated numbers in an array. 
// You can assume all values in the array are between 0 and n-1.
// Written by Dylan Blecher on June 10, 2019
// d.blecher@unsw.edu.au

#include <stdio.h> 
#include <stdlib.h> 

#define SIZE 3

void printDuplicates0(int size, int nums[]);
void printDuplicates1(int size, int nums[]);
void printDuplicates2(int size, int nums[]);

int main(void) { 
	int nums[] = {2, 2, 1}; 
	printf("The repeating elements are: \n"); 
	printDuplicates0(SIZE, nums);
	// printDuplicates1(SIZE, nums);
	// printDuplicates2(SIZE, nums);
	return 0; 
}

// Time complexity: O(n^2)
// Space complexity: We're not using any space so O(0) ~ O(C)
void printDuplicates0(int size, int nums[]) { 	// time complexity = O(n^2)
	for (int i = 0; i < size; i++) 				// 1, n, n
		for (int j = 0; j < size; j++)			// n, n^2, n^2
			if (nums[i] == nums[j] && i != j) {	// 2n^2
				printf("%d\n", nums[i]);		// n^2
			} 									// Total = O(5n^2 + 3n + 1) ~= O(n^2)
}

// Time complexity: O(n)
// Space complexity: O(n)
void printDuplicates1(int size, int nums[]) { 	
	int counts[SIZE] = {0};
	for (int i = 0; i < size; i++) {
		counts[nums[i]]++; 				
		if (counts[nums[i]] == 2) {	
			printf("%d\n", nums[i]);		
		} 				
	}					
}

// Scroll down to have your mind blown.













// Time complexity: O(n)
// Space complexity: O(0) ~= O(C)
void printDuplicates2(int size, int nums[]) { 
	int i; 
	for (i = 0; i < size; i++) { 
		if (nums[abs(nums[i])] >= 0) 
  			nums[abs(nums[i])] = -nums[abs(nums[i])]; 
		else
  			printf(" %d ", abs(nums[i])); 
	} 
}