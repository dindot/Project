#ifndef __BUBBLE_H__
#define __BUBBLE_H__
#include <stdint.h>
#include "bubble.h"

// bubble sort algorithm takes in an integer array with integer length
// and proceeds to sort by going through element comparing it with the next
// element, for each element and swapping them to sort the array in asc order
void bubble_sort(uint32_t arr[], int length);

#endif
