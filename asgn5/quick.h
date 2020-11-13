#ifndef __QSORT_H__
#define __QSORT_H__

// Used to partition the array into subarrays, which are created by placing all
// elements less than a pivot (element selected to start it from) to the left,
// and all elements greater than that pivot to the right. The process repeats until
// the subarray of just one element, and then swaps to sort into asc order.
// Take in arr as integer array, and left and right as integers which are the starting
// and ending index of the array respectively. Returns the index at where pivot is at
int partition(int arr[], int left, int right);

// Uses partition function to recursively split up the array in to subarrays and 
// perform necessary comparisons and swaps to sort in asc order.
void quick_sort(int arr[], int left, int right);

#endif
