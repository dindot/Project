#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPTIONS "spn:"

// takes in num as integer, computes and ouputs the fibonacci up to num
// uses recursion, implemented from class slides
int fib(int num);

// takes in num as integer, computes and outputs the lucas numbers up to num
// uses recursion to step through like fibonacci, but starts at 2
int lucas(int num);

// takes in num as integer, computes and displays mersenne numbers up to num
// using form 2^n -1 , where n starts from 2 then is all odds
int mersenne(int num);

// takes in current as integer, to check if it is a mersenne prime, returning
// true if it is, else false
bool is_mersenne(int current);
// takes in current as integer, to check if it is a lucas prime, returning
// true if it is, else false
bool is_lucas(int current);
// takes in current as integer, to check if it is a fibonacci prime, returning
// true if it is, else false
bool is_fib(int current);

// takes in bv as pointer to BitVector Struct, to go through each bit with 1
// representing a prime, then printing all primes through given size of the bv
// vector along with if they are mersenne, lucas, or fibonacci primes
void prime_printer(BitVector *bv);

// takes in num and base as integers to convert the given decimal base number
// to base of choice, storing the remainders of num/base as
// the conversion and outputting as string in correct order
char *decimal_to_basex(int num, int base);

// takes in string and compares the last character to first to check if they are
// same, going towards middle of the string, returning true if the passed string is
// a palindrome, else false
bool isPalindrome(char *s);

// uses the value from isPalidrome to then take in bv as pointer to BitVector struct
// and b as the current base, printing out from the bv the primes with their corresponding
// converted base equivalents if palindromes
void palindrome_primeprint(BitVector *bv, int b);

int main(int argc, char **argv) {
  bool s, p, n;
  int default_prime = 0;
  s = p = n = false;
  char *next_input = NULL; // to obtain user input of desired primes
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
      next_input = optarg; // when supplied with number argument of total primes
      default_prime = atoi(
          next_input); // convert string to integer to be set as default_prime
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
    if (n == false) { // check if user entered a value for total primes
      default_prime = 1000; // if not set the default
    }

    BitVector *bv = bv_create(
        default_prime); // creates a bitvector of size default_primes
    sieve(
        bv); // use the sieve to store the prime numbers 0-default_primes inclusive
    prime_printer(
        bv); // print out all the primes found and if they are mersenne, lucas, fib
    bv_delete(bv); // free dynamically allocated bitvector
  }

  if (p == true) {
    if (n == false) {
      default_prime = 1000;
    }

    BitVector *bv2 = bv_create(default_prime);
    sieve(bv2);
    palindrome_primeprint(
        bv2, 2); // formatting of tabular report with the given bases 2,9,10,
    printf("\n"); // and 12 = first letter of last name (b/so 2nd alphabet) + 10
    palindrome_primeprint(bv2, 9);
    printf("\n");
    palindrome_primeprint(bv2, 10);
    printf("\n");
    palindrome_primeprint(bv2, 12);
    bv_delete(bv2);
  }
  return 0;
}

void prime_printer(BitVector *bv) {
  for (uint32_t i = 2; i < bv->length;
       i++) { // 2 is prime so start checking sieved numbers there
    bool isfib = is_fib(i); // go through each prime to check special numbers
    bool islucas = is_lucas(i);
    bool ismers = is_mersenne(i);
    if (bv_get_bit(bv, i)
        == 1) { // format tabular ouput of each case of the special numbers
      if (ismers == 1 && islucas == 1 && isfib == 1) {
        printf("%d: prime, mersenne, lucas, fibonacci\n", i);
      }
      if (islucas == 1 && isfib == 0 && ismers == 0) {
        printf("%d: prime, lucas\n", i);
      }
      if (islucas == 0 && isfib == 1 && ismers == 0) {
        printf("%d: prime, fibonacci\n", i);
      }
      if (islucas == 0 && isfib == 0 && ismers == 1) {
        printf("%d: prime, mersenne\n", i);
      }
      if (islucas == 0 && isfib == 1 && ismers == 1) {
        printf("%d: prime, mersenne, fibonacci\n", i);
      }
      if (islucas == 1 && isfib == 0 && ismers == 1) {
        printf("%d: prime, mersenne, lucas\n", i);
      }
      if (islucas == 1 && isfib == 1 && ismers == 0) {
        printf("%d: prime, lucas, fibonacci\n", i);
      }
      if (islucas == 0 && isfib == 0 && ismers == 0) {
        printf("%d: prime\n", i);
      }
    }
  }
}

int fib(int num) { // cited source, implemented from class slides on recursion
  if (num == 0 || num == 1) { // base case
    return num;
  } else {
    return fib(num - 1) + fib(num - 2);
  }
}

bool is_fib(int current) {
  bool found_fib = false;
  for (int i = 0; i < 20;
       i++) { // list out the first 20 numbers in fib sequence
    int fibnum = fib(i); // compare if the given bit is anyone of them
    if (fibnum == current) {
      found_fib = true;
    }
  }

  return found_fib;
}

int lucas(
    int num) { //recursive lucas with bases of 2 when num = 0, 1 when num = 1
  if (num == 0) {
    return 2;
  } else if (num == 1) {
    return num;
  } else {
    return lucas(num - 1) + lucas(num - 2); // step through like fib
  }
}

bool is_lucas(int current) {
  bool found_lucas = false;
  for (int i = 0; i < 20;
       i++) { // list out the first 20 numbers in lucas sequence
    int lucasnum = lucas(i); // compare if the given bit is any one of them
    if (lucasnum == current) {
      found_lucas = true;
    }
  }

  return found_lucas;
}

int mersenne(
    int num) { // mersenne number is 2^n -1, with base case of 3 when num == 2
  int val = 0;
  if (num == 2) {
    return 3;
  }
  if (num % 2 != 0) { // uses odd numbers as n

    val = (pow(2, num) - 1);
  }
  return val;
}

bool is_mersenne(int current) {
  bool found_mersenne = false;
  for (int i = 0; i < 20;
       i++) { // list out the first 20 numbers in mersenne sequence
    int mersennenum
        = mersenne(i); // compare if the given bit is any one of them
    if (mersennenum == current) {
      found_mersenne = true;
    }
  }
  return found_mersenne;
}

char *decimal_to_basex(int num, int base) {
  char *base_string
      = NULL; // will store final converted num into base: base as string
  char c;
  char *thestring
      = NULL; // stores the remainders of num/base. must be reversed then
  char string
      [8]; // initially used for storing the remainders as they are converted into string
  char newstring[8];
  int counter = 0;
  if (num / base
      == 0) { // check initially since for base > 10 must use more digits than 0-9
    if (num % base
        == 10) { // so if the quotient is 0, display the remainder as hex
      return "a";
    } else if (num % base == 11) {
      return "b";
    } else if (num % base == 12) {
      return "c";
    } else if (num % base == 13) {
      return "d";
    } else if (num % base == 14) {
      return "e";
    } else if (num % base == 15) {
      return "f";
    }
  }
 // if (num == 2
   //   && base == 2) { // there will be 0 as remainder in string, so this case
   // return "1"; // allows for correcting palindrome output of num as 2
 // } else if (num == 2 && base != 2) {
   // return "2";
  //}
  while (num > 0) {
    int x = num; // temp storing num
    num = (num / base); // find the quotient of num and keep going until its 0
    int remainder = x % base; // find the remainder of num and store it,
    c = remainder
        + '0'; // converts the int remainder into a char to store in the array
    string[counter] = c;
    counter++;
  }
  string[counter]
      = '\0'; // ends the char array to form string of accurate length
  thestring = string; // store as string
  counter--; // get rid of the null terminator so can loop through

  for (int i = counter, k = 0; i >= 0;
       i--, k++) { // reverses the string of remainders
    newstring[k] = thestring[i];
    if (i == 0) {
      newstring[k + 1]
          = '\0'; // once done terminate the string to desired length
    }
  }

  base_string
      = newstring; // this will be the correct order string of remainders in new base
  return base_string;
}

bool isPalindrome(
    char *s) { // sources cited, used from lab manual asgn4 pseudocode

  bool f = true;
  int length = strlen(
      s); // take the length of string passed and go through each character

  for (int i = 0; i < length; i++) {

    if (s[i]
        != s[length - (i + 1)]) { // palindrome if the firsts match the lasts
      f = false;
      break;
    }
  }
  return f;
}

void palindrome_primeprint(BitVector *bv, int b) {
  int base = b; // given the desired base print out tabular form headers of each
  printf("Base  %d\n",
      base); // with the bit prime and its equivalent form in the base
  puts("---- --");
  for (uint32_t i = 2; i < bv->length; i++) {

    if (bv_get_bit(bv, i) == 1) {
      char *newbase = decimal_to_basex(i, base);
      bool palindrome = isPalindrome(newbase);

      if (palindrome
          == 1) { // display if the base converted string is palindrome
        printf("%d = %s\n", i, newbase);
      }
    }
  }
}
