#include "binary.h"
#include "counters.h"

void binary_insertion_sort(uint32_t arr[], int length) {
  for (int i = 1; i < length; i++) {
   uint32_t value = arr[i];
    int left = 0;
    int right = i;

    while (left < right) {
      int mid = left
                + ((right - left) / 2); // find index of element in mid of array
          ++compares;
	 if (value >= arr[mid]) {

        left = mid
               + 1; // start the left next one over, since value is right half
      } else {
        right
            = mid; // make right the mid index because will be looking in left half
      }
    }

    for (int j = i; j > left; j--) {
      int temp = arr[j - 1];
      ++swaps;
      arr[j - 1] = arr[j];
      ++swaps;
      arr[j] = temp;
      ++swaps;
    }
  }
}
