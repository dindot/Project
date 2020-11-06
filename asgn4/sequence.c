#include "sieve.h"
#include "bv.h"
#include <stdio.h>
#include <stdint.h>

int fib(int num);

int main()
{

int x = fib(5);
printf("%d", x);

  for (int i =0; i


  return 0;
}

int fib(int num)
{
  if (k == 0 || k == 1)
{
  return k;
}
else
{

return fib(num-1) + fib(num-2)
}

}
