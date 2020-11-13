#include "shell.h"

int *gap(int n) {
  static int arr[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0 }; // store gap intervals
  int i = 0;
  while (n > 1) {
    if (n <= 2) {
      n = 1;
      arr[i] = n;
      i++;
    } else {
      n = (5 * n) / 11; // gap equation used
      arr[i] = n;
      i++;
    }
  }
  return arr;
}

void shell_sort(uint32_t arr[], int length, int arr2[]) {
  static int i = 0;
  static int step
      = 0; // retain values of step and access in array of gap interval
  for (; (step = arr2[i]); i++) {
    for (int i = step; i < length; i++) {
      for (int j = i; j >= step; j -= step) {
        if (arr[j]
            < arr[j - step]) // after stepping through gaps swap if not sorted
        {
          int temp = arr[j];
          arr[j] = arr[j - step];
          arr[j - step] = temp;
        }
      }
    }
  }
}
