#ifndef __SHELL_H__
#define __SHELL_H__

// the gap between the elements, that gets reduced and is used for shell sort
// to help move far elements into correct positions. Takes in n as integer,
// which is the length of array, then uses it to calculate gap by performing
// n = (5*n)/1 if n >2, else n = 1. It returns a pointer to integer allowing
// a helper array (in which the gap intervals get placed) to be returned and
// used by the shell sort
int *gap(int n);

// Uses the gaps from gap function to step through the elements in array,
// and compare the elements at the gaps, if they are not in order they 
// get swapped and sorted. Takes in arr as array of integer, which is the array
// to be sorted, its length as integer, and arr2 as array of integer, which contains
// all the gaps that will be stepped through
void shell_sort(int arr[], int length, int arr2[]);

#endif
