#ifndef __BINARY_H__
#define __BINARY_H__
#include <stdint.h>
// Uses binary search in insertion sort to provide faster insertion of elements due to
// the lookup of their exact locations, halfing the array, by choosing the mid element
// and then using it to compare and compute the specific index of where the element will
// go if less (left) than or greater (right) than the chosen middle. So the element wish
// to be placed is found its index based on all elements to left of it. Take in arr as array
// of int, which is the array to be sorted, and its length as integer length.

void binary_insertion_sort(uint32_t arr[], int length);

#endif
