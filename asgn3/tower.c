#include "stack.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define OPTIONS "srn:"

// void function to recursively solve game until the disks from peg A to peg B have all been
// transferred, following the rules. takes in disk_num as integer, which is the total number of
// disks specified by user. A, B, C as characters which are the names of the three pegs.
void recursive(int disk_num, char A, char B, char C);

// returns integer of the total number of moves required based on integer n input of total
// disks, taking into consideration base case of n = 0
int move_counter(int n);

// void function that is used for stack implementation and creation of the three stacks/pegs
// on the heap. It determines if total disks  are even or odd and call stack_caller
// with updated parameters. Takes in moves as integer which is the total number of moves
// required for the integer disks, total disks played with.
void stack_manipulator(int moves, int disks);

// void function performs the iterative steps to solve tower of hanoi game,
// taking into account the odd or even disks when being called, so that a swap between
// peg B and C can be made if needed. Since there are 3 pegs must mod each move by 3
// to ensure proper placement and avoid extra moves. The pegs are individually checked and
// compared so that peg B gets filled in end and that no disk is larger than its previous one.
// Takes in StackA, StackX, and StackY as pointers to Stack struct, to be used for tracking
// and swapping when needed, as well as popping and pushing values, moves as integer of total
// moves needed for the given integer of total disks
void stack_caller(
    Stack *StackA, Stack *StackX, Stack *StackY, int moves, int disks);

int main(int argc, char **argv) {
  char A = 'A', B = 'B', C = 'C';
  char *next_input = NULL;
  bool s, r, n;
  int default_disk = 0;
  s = r = n = false;
  int c = 0;

  while ((c = getopt(argc, argv, OPTIONS))
         != -1) // parse user input to get options input

  {
    switch (c) {
    case 's':
      s = true;
      break;
    case 'r':
      r = true;
      break;
    case 'n':
      n = true;
      next_input = optarg; // when supplied with number argument of disks
      default_disk = atoi(
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

  if (s == true) {
    if (n == false) {
      default_disk
          = 5; // when no value specified by user, default to disks of 5
    }

    printf(
        "================================\n"); // tabular output for stacks implement.
    printf("----------   STACKS   ----------\n");
    printf("================================\n");
    int num_moves = move_counter(
        default_disk); // calculates total moves required for disks
    stack_manipulator(num_moves, default_disk); // perform game rules
    printf("\nNumber of moves: %d\n", num_moves);
  }

  if (r == true) {
    if (n == false) {
      default_disk = 5;
    }
    printf("================================\n");
    printf("--------   RECURSION   ---------\n");
    printf("================================\n");
    recursive(default_disk, A, B, C); // play the game recursively
    int num_moves = move_counter(default_disk);
    printf("\nNumber of moves: %d\n", num_moves);
  }

  return 0;
}

void recursive(int disks, char A, char B, char C) {
  if (disks == 0) {
    return; //base case
  } else {
    // cited, used general idea from AlgoData see README.md
    recursive(disks - 1, A, C,
        B); // move n-1 disks from starting peg to temporary using B
    printf("Move disk %d from peg %c to peg %c\n", disks, A,
        B); // move the nth disk
    recursive(
        disks - 1, C, B, A); // move n-1 disks from temporary to final using A
  }
}

int move_counter(int n) {
  if (n == 0) {
    return 0; // base case of no disks provided
  } else {

    return 2 * move_counter(n - 1)
           + 1; // moves required to be taken based recursively 2^n -1
  }
}

void stack_manipulator(int moves, int disks) {
  Stack *StackA
      = stack_create(disks, 'A'); // create the 3 stacks/peg dynamically
  Stack *StackB = stack_create(disks, 'B');
  Stack *StackC = stack_create(disks, 'C');

  if (disks % 2 == 0) { // check to see if the disks are even or not
    stack_caller(
        StackA, StackC, StackB, moves, disks); // swap peg B with peg C if even
  } else if (disks % 2 != 0) {
    stack_caller(StackA, StackB, StackC, moves, disks); // else keep same
  }
  stack_delete(StackA);
  stack_delete(StackB);
  stack_delete(StackC);
}

void stack_caller(
    Stack *StackA, Stack *StackX, Stack *StackY, int moves, int disks) {

  for (int i = disks; i >= 1; i--) {
    stack_push(StackA,
        i); // initialize the starting peg A from disks# to 1 decrementing
  }
  // cited, used general idea of modding pegs and checking for even/odd moves
  // from StackExchange see README.md

  // perform iterative version of rules checking each peg for disk size
  // for each move printing out the disks and pegs being moved to/from, modding to
  // stay within "circle" of the 3 pegs
  for (int i = 1; i <= moves;
       i++) { // perform until reached max# of moves for the disks
    if (i % 3 == 1) {
      if (stack_empty(StackX)) {
        stack_push(StackX, stack_pop(StackA));

        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackX),
            StackA->name, StackX->name);
      } else if (stack_empty(StackA)) {
        stack_push(StackA, stack_pop(StackX));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackA),
            StackY->name, StackA->name);
      } else if (stack_peek(StackA) < stack_peek(StackX)) {
        stack_push(StackX, stack_pop(StackA));

        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackX),
            StackA->name, StackX->name);
      } else if (stack_peek(StackX) < stack_peek(StackA)) {
        stack_push(StackA, stack_pop(StackX));

        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackA),
            StackX->name, StackA->name);
      }
    }
    if (i % 3 == 2) {
      if (stack_empty(StackY)) {

        stack_push(StackY, stack_pop(StackA));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackY),
            StackA->name, StackY->name);
      } else if (stack_empty(StackA)) {
        stack_push(StackA, stack_pop(StackY));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackA),
            StackY->name, StackA->name);

      } else if (stack_peek(StackA) < stack_peek(StackY)) {
        stack_push(StackY, stack_pop(StackA));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackY),
            StackA->name, StackY->name);
      }

      else if (stack_peek(StackY) < stack_peek(StackA)) {

        stack_push(StackA, stack_pop(StackY));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackA),
            StackY->name, StackA->name);
      }
    }
    if (i % 3 == 0) {

      if ((stack_peek(StackX) != 0)
          && (stack_peek(StackX) < stack_peek(StackY))) {
        stack_push(StackY, stack_pop(StackX));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackY),
            StackX->name, StackY->name);
      } else if (stack_empty(StackA)) {
        stack_push(StackA, stack_pop(StackY));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackA),
            StackA->name, StackY->name);
      } else {
        stack_push(StackX, stack_pop(StackY));
        printf("Move disk %d from peg %c to peg %c\n", stack_peek(StackX),
            StackY->name, StackX->name);
      }
    }
  }
}
