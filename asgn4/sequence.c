#include <stdio.h>
#include "sieve.h"
#include "bv.h"

int fib(int num);
uint8_t base_to_bin(uint32_t a);

int main(void)
{

int inputnum = 100;
BitVector *bv = bv_create(inputnum);
sieve(bv);


int num = 6;
int x = 0;
//printf("%d: size, \n", bv_get_len(bv));
for (int i =0; i<= inputnum; i+=8)
{
uint8_t byte = bv->vector[i/8];
uint8_t binnum =  base_to_bin(byte);
}

//if(v->vector[i/8)])
//{ 
 // bv_get_bit(bv,i)
  //printf("%d: prime, \n", i);
//}
 //  x = fib(i);
 // if (x == bv_get_bit(bv, i))
//{
  // printf("%d    is a fib", i);
////}
 







return 0;
}

int fib(int num)
{
   if(num == 0 || num == 1)
    {
      return num;
   }
 
else
{
return fib(num-1) +fib(num-2);
}

}



uint8_t base_to_bin(uint32_t a)
{
static int countprimes =0;
 char c;
 char string[20000];
int counter = 0;
  while (a > 0)
  {
      int x = a;
      a= (a/ 2);
      int remainder = x % 2;
     // printf("a: %d remainder: %d\n", a, remainder);
for (int i =0; i<8; i++)
{
 if( ((a >> i)  & 0x01) == 1)
  {
         
  }
}  
 



          printf("%d is a prime\n", (countprimes-1));
      
      c = remainder + '0';
      string[counter] = c;
     
  counter++;
      }
     // printf("string : %c \n", *string);
     //   }
     //
        counter--;
      //   printf("bit_number is :");
     //     //printf("counter is :%d\n", counter);
          for (int i = counter; i >=0; i--)
          {
            printf("%c", string[i]);
            }
            printf("\n");
            return 0;
}
