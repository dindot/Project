#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#define OPTIONS "srn:"


void recursive(int disk_num, char A, char B, char C);
int move_counter(int n);

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

  //if (s == true)
 // {  // if(n== false)
 //       

     // call stack with default_disk
     //
     // else call stack with default_disk
 // }
 //
 //
 //
 //
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
