#include "bubble.h"

void bubble_sort(int arr[], int length)
{
  for (int i = 0; i < length -1; i++)
  {
    int j = length - 1;
    while (j > i)
    {
        if (arr[j] < arr[j-1])  // if previous element > than current, swap them
	{
		int temp = arr[j-1];
		arr[j-1] = arr[j];
		arr[j] = temp;
	}
	j--;
    }
  }
}
