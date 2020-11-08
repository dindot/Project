#include "sieve.h"
#include "bv.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#define OPTIONS "spn:"
int fib(int num);
int lucas(int num);
int mersenne(int num);
bool is_mersenne(int current);
bool is_lucas(int current);
bool is_fib(int current);
void prime_printer(BitVector *bv);
char* decimal_to_basex(uint8_t num);


int main(int argc, char **argv)
{
bool s, p, n;
int default_prime = 0;
s = p = n = false;
char *next_input = NULL;
int c = 0;

while ((c = getopt(argc, argv, OPTIONS))
         != -1) // parse user input to get options input

  {
    switch (c) {
    case 's':
      s = true;
      break;
    case 'p':
      p = true;
      break;
    case 'n':
      n = true;
      next_input = optarg; // when supplied with number argument of disks
      default_prime = atoi(
          next_input); // convert string to integer to be set as disk number
      break;
    default:
      puts(
          "Character not defined in string"); // when user enters invalid option
      return -1;
    }
  }

if (argc == 1) { // user must enter an option in order for program to run
    puts("Error: no arguments supplied!");
    return -1;
  }


 if(s == true)
{
if(n == false)
{ 
   default_prime = 1000;
 
 }

 BitVector *bv = bv_create(default_prime);
sieve(bv);
prime_printer(bv);



}



char* x = decimal_to_basex(43);
      printf("%s", x);



return 0;
}

void prime_printer(BitVector *bv)
{
for (int i = 2; i < bv->length; i++)
{
   bool isfib = is_fib(i);
   bool islucas = is_lucas(i);
   bool ismers = is_mersenne(i);
   if(bv_get_bit(bv,i) == 1)
   {
       if (ismers == 1 && islucas == 1 && isfib == 1)
       {
          printf("%d: prime, mersenne, lucas, fibonacci\n", i);
       }
       if (islucas == 1 && isfib == 0 && ismers == 0)
       {
       printf("%d: prime, lucas\n", i);
       }
       if (islucas == 0 && isfib == 1 && ismers == 0)
       {
       printf("%d: prime, fibonacci\n", i);
       }
        if (islucas == 0 && isfib == 0 && ismers == 1)
       {
       printf("%d: prime, mersenne\n", i);
       }
       if (islucas == 0 && isfib == 1 && ismers == 1)
       {
       printf("%d: prime, mersenne, fibonacci\n", i);
       }
      if (islucas == 1 && isfib == 0 && ismers == 1)
       {
       printf("%d: prime, mersenne, lucas\n", i);
       }
       if (islucas == 1 && isfib == 1 && ismers ==0 )
       {
       printf("%d: prime, lucas, fibonacci\n", i);
       }
       if (islucas == 0 && isfib == 0 && ismers ==0)
       {
       printf("%d: prime\n", i);
       }  
  }
} 



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


bool is_fib(int current)
{
  bool found_fib = false;
  for(int i =0; i<20; i++)
  {
    int fibnum = fib(i);
    if (fibnum == current)
    {
      found_fib = true;
    }
  }

 return found_fib;
}

int lucas(int num)
{
  if (num == 0)
  {
    return 2;
  }
  else if (num == 1)
  {
    return num;
  }
  else
  {
    return lucas(num-1) + lucas(num-2);

  }
}

bool is_lucas(int current)
{
  bool found_lucas = false;
  for(int i =0; i<20; i++)
  {
    int lucasnum = lucas(i);
    if (lucasnum == current)
    {
      found_lucas = true;
    }
  }

 return found_lucas;
}

int mersenne(int num)
{
 int val = 0;
 if(num == 2)
  { 
     return 3;
   }
  if (num%2 != 0)
  {

    val= (pow(2,num)-1);
   }
return val;
 }


bool is_mersenne(int current)
{
 bool found_mersenne = false;
  for(int i =0; i< 20; i++)
  {
    int mersennenum = mersenne(i);
    if (mersennenum == current)
    {
      found_mersenne= true;
    }

}
return found_mersenne;
}



char* decimal_to_basex(uint8_t num)
{
 char *base_string = NULL;
 char c;
 char string[8] = "00000000";
 char newstring[8];
int counter = 0;
  while (num > 0)
  {
      int x = num;
      num= (num/ 2);
      int remainder = x % 2;
      c = remainder + '0';
      string[counter] = c;
     
      counter++; 
      }
     
      counter--;
     for (int i = counter, k = 0; i >=0; i--, k++)
{
  newstring[k] = string[i];
}
  base_string = newstring;           
           return base_string;
 }
