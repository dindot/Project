#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include "stack.h"
#define OPTIONS "srn:"


void recursive(int disk_num, char A, char B, char C);
int move_counter(int n);

void stack_manipulator(int moves, int disks);

int main(int argc, char **argv)
{
char A = 'A', B = 'B', C = 'C';
 char *next_input = NULL;
 bool s, r, n, x;
 int default_disk = 0;
 s = r = n = false;
 int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1)

{
  switch(c)
  { 
   case 's':
      s = true;
      break;
   case 'r':
      r = true;
      break;
   case 'n':
      n = true;
      next_input = optarg;
      puts(next_input);
      default_disk = atoi(next_input);
      break;
   default:
     puts("Character not defined in string");
     return -1;
      

  }

  if (s == true)
  {  if(n== false)
     {
          default_disk = 5;
      } 

   printf("================================\n");
      printf("--------   STACKS   ---------\n");
      printf("================================\n");
   int num_moves = move_counter(default_disk);
   stack_manipulator(num_moves, default_disk); 
  
 }

    if(r == true)
    {  
      if(n == false)
      {
        default_disk = 5;
      }
      printf("================================\n");
      printf("--------   RECURSION   ---------\n");
      printf("================================\n");
      recursive(default_disk, A, B, C);
      int num_moves = move_counter(default_disk);
      printf("\nNumber of moves: %d", num_moves);

   }
}







return 0;
}



void recursive(int disks, char A, char B, char C)
{
if (disks == 0)
{
   return;
}
else
{
  // cited, used general idea from AlgoData see README.md
  recursive(disks-1, A, C, B);
  printf("Move disk %d from peg %c to peg %c\n", disks, A, B);
  recursive(disks-1, C, B, A);
}
}

int move_counter(int n)
{
  if(n == 0)
   {
      return 0;
    }
   else
   {

    return 2*move_counter(n-1)+1;
   }
}



void stack_manipulator(int moves, int disks)
{
   Stack *StackA = stack_create(disks, 'A');
   Stack *StackB = stack_create(disks, 'B');
   Stack *StackC = stack_create(disks, 'C');


   for(int i = disks; i>= 1; i--)
   {
     stack_push(StackA, i);
     
   }
    
  // stack_push(StackB, stack_pop(StackA));
   //stack_push(StackC, stack_pop(StackA));
   
   int popped_val =0;
   //if (moves % 2 == 0)
   //{

     //StackC= StackB;
  // }
   for(int i =1; i<=moves; i++)
    { 
     printf("val at A %d i is %d", stack_peek(StackA), i);
     if(i%3 == 1) 
     {
           if(stack_empty(StackB))
            {
                   stack_push(StackB, stack_pop(StackA));

        printf("Move disk %d from %c to %c\n", stack_peek(StackB), StackA->name, StackB->name);
            }
         else if(stack_empty(StackA))
           {
                 stack_push(StackA, stack_pop(StackC));
       printf("Move disk %d from %c to %c\n", stack_peek(StackA), StackC->name, StackA->name);
          }
           else if (stack_peek(StackA) < stack_peek(StackB))
	    {
                 stack_push(StackB, stack_pop(StackA));

        printf("Move disk %d from %c to %c\n", stack_peek(StackB), StackA->name, StackB->name);
	    }
            else if (stack_peek(StackB) < stack_peek(StackA))
            {
                 stack_push(StackA, stack_pop(StackB));

        printf("Move disk %d from %c to %c\n", stack_peek(StackA), StackB->name, StackA->name);
            }
     
      }
     if(i%3 == 2)
      {
        if(stack_empty(StackC))
          {


            
               stack_push(StackC, stack_pop(StackA));
        printf("Move disk %d from %c to %c\n", stack_peek(StackC), StackA->name, StackC->name);
          }
         else  if(stack_empty(StackA))
     {
          stack_push(StackA, stack_pop(StackC));
       printf("Move disk %d from %c to %c\n", stack_peek(StackA), StackC->name, StackA->name);

     }
      else  if(stack_peek(StackA) < stack_peek(StackC))
       {
               stack_push(StackC, stack_pop(StackA));
        printf("Move disk %d from %c to %c\n", stack_peek(StackC), StackC->name, StackA->name);
       }

   else if(stack_peek(StackC) < stack_peek(StackA))
	{


         stack_push(StackA, stack_pop(StackC));
        printf("Move disk %d from %c to %c\n", stack_peek(StackA), StackC->name, StackA->name);
         }

   // popped_val= stack_pop(StackA);
       // stack_push(StackC, stack_pop(StackA));
       // printf("Move disk %d from %c to %c\n", stack_peek(StackC), StackA->name, StackC->name);

      }
     if(i%3 == 0)

    { 
       if( (stack_peek(StackB) !=0) && (stack_peek(StackB) <  stack_peek(StackC)))
       {
           stack_push(StackC, stack_pop(StackB));
        printf("Move disk %d from %c to %c\n", stack_peek(StackC), StackB->name, StackC->name);
       }
	else if (stack_empty(StackA))
      {
          stack_push(StackA, stack_pop(StackC));
       printf("Move disk %d from %c to %c\n", stack_peek(StackA), StackC->name, StackA->name);
        }
     else 
      {
        stack_push(StackB, stack_pop(StackC));
          printf("Move disk %d from %c to %c\n", stack_peek(StackB), StackC->name, StackB->name);

    }
      //popped_val= stack_pop(StackC);
      //  stack_push(StackC, stack_pop(StackB));
    //    printf("Move disk %d from %c to %c\n", stack_peek(StackC), StackB->name, StackC->name);    
   }
}           
}
