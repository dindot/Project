#include "quick.h"

int partition(int arr[], int left, int right)
{
  int pivot = arr[left];  // let the pivot value be first in array
  int lo = left + 1;
  int hi = right;

  while(1)
  {
    while(lo<= hi && arr[hi] >= pivot)  // compare based on indices to find the values out of place
    {
      hi -=1;
    }
   while(lo<= hi && arr[lo] <= pivot)
   {
      lo+=1;
    }
   if(lo <= hi)  // the low index will now be the low element to be swapped out
   {
       int temp = arr[lo];
       arr[lo] = arr[hi];
       arr[hi] = temp;
    }
    else
   {
       break;
    }


  }
   // since arr[hi] contains the lowest element swap it out with the one higher than it in arr[left]
   int temp = arr[left];
   arr[left] = arr[hi];
   arr[hi]  = temp;
   return hi;
}

void quick_sort(int arr[], int left, int right)
{
   if(left<right)
    {
      int index = partition(arr, left, right);  // index of the paritioned value
      quick_sort(arr,left,index-1);  // sort the left subarry from start just before partition
     quick_sort(Arr, index+1, right);  // sort the right subarray from one after partition to end
   }

}
