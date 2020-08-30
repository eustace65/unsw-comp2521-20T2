// Determine if a sorting algorithm is stable or not by comparing
// the original array with the sorted array.
// tut09, COMP2521, 19T2
// Dylan Blecher, d.blecher@unsw.edu.au

#define TRUE 1
#define FALSE !TRUE

// Assume the list was sorted on "a"
typedef struct { int a; int b; } item;

// lo is the lowest index, hi is the highest index
int isStableSort(item original[], item sorted[], int lo, int hi) {
	// For all items in the sorted list
	for (int i = lo; i <= hi; i++) {
		// for all following items with the same value
		for (int j = i + 1; j <= hi && sorted[i].a == sorted[j].a; j++) {
			// if they're inverted in the original array, it's not a stable sort
			if (inverted(original, lo, hi, sorted[i], sorted[j])) return FALSE;
		}
	}

	return TRUE;
}

// Finds if "a" or "b" is first in the given array.
// returns FALSE if "a" is before "b" in the array (i.e. it's not inverted)
// returns TRUE if "a" is after "b" in the array (i.e. it is inverted)
int inverted(item array[], int lo, int hi, item a, item b) {
	for (int i = lo; i <= hi; i++) {
		if (array[i] == a) return FALSE;
		if (array[i] == b) return TRUE;
	}
}

////////////////
//            //
//  Analysis  //
//            //
////////////////

// This algorithm is O(n^3)
// aaaaaaahhhhhhhhhhhhhhhhhhhhhhh :'(

// More efficient algorithm: 
// 		stable-merge sort the original list in O(n log n)
// 		check if the two sorted lists are identical in O(n)
// Total time complexity: O(n log n + n) ~= O(n log n) 
// :)
// 
// Check out excel table comparisons...