#include "sieve.h"
#include "bv.h"
#include <stdio.h>
#include <stdint.h>

int fib(int num);

int main()
{

int x = fib(5);
printf("%d", x);

 


  return 0;
}

int fib(int num)
{
  if (num == 0 || num == 1)
{
  return num;
}
else
{

return fib(num-1) + fib(num-2);
}

}
