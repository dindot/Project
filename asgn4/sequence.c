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
int fib(int num);
int lucas(int num);
int mersenne(int num);
bool is_mersenne(int current);
bool is_lucas(int current);
bool is_fib(int current);
void prime_printer(BitVector *bv);
char *decimal_to_basex(int num, int base);
bool isPalindrome(char *s);
void palindrome_primeprint(BitVector *bv, int b);

int main(int argc, char **argv) {
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

  if (s == true) {
    if (n == false) {
      default_prime = 1000;
    }

    BitVector *bv = bv_create(default_prime);
    sieve(bv);
    prime_printer(bv);
    bv_delete(bv);
  }

  if (p == true) {
    if (n == false) {
      default_prime = 1000;
    }

    BitVector *bv2 = bv_create(default_prime);
    sieve(bv2);
    palindrome_primeprint(bv2, 2);
    printf("\n");
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
  for (uint32_t i = 2; i < bv->length; i++) {
    bool isfib = is_fib(i);
    bool islucas = is_lucas(i);
    bool ismers = is_mersenne(i);
    if (bv_get_bit(bv, i) == 1) {
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

int fib(int num) {
  if (num == 0 || num == 1) {
    return num;
  } else {
    return fib(num - 1) + fib(num - 2);
  }
}

bool is_fib(int current) {
  bool found_fib = false;
  for (int i = 0; i < 20; i++) {
    int fibnum = fib(i);
    if (fibnum == current) {
      found_fib = true;
    }
  }

  return found_fib;
}

int lucas(int num) {
  if (num == 0) {
    return 2;
  } else if (num == 1) {
    return num;
  } else {
    return lucas(num - 1) + lucas(num - 2);
  }
}

bool is_lucas(int current) {
  bool found_lucas = false;
  for (int i = 0; i < 20; i++) {
    int lucasnum = lucas(i);
    if (lucasnum == current) {
      found_lucas = true;
    }
  }

  return found_lucas;
}

int mersenne(int num) {
  int val = 0;
  if (num == 2) {
    return 3;
  }
  if (num % 2 != 0) {

    val = (pow(2, num) - 1);
  }
  return val;
}

bool is_mersenne(int current) {
  bool found_mersenne = false;
  for (int i = 0; i < 20; i++) {
    int mersennenum = mersenne(i);
    if (mersennenum == current) {
      found_mersenne = true;
    }
  }
  return found_mersenne;
}

char *decimal_to_basex(int num, int base) {
  char *base_string = NULL;
  char c;
  char *thestring = NULL;
  char string[8];
  char newstring[8];
  int counter = 0;
  if (num / base == 0) {
    if (num % base == 10) {
      return "A";
    } else if (num % base == 11) {
      return "B";
    } else if (num % base == 12) {
      return "C";
    } else if (num % base == 13) {
      return "D";
    } else if (num % base == 14) {
      return "E";
    } else if (num % base == 15) {
      return "F";
    }
  }
  if (num == 2 && base == 2) {
    return "1";
  } else if (num == 2 && base != 2) {
    return "2";
  }
  while (num > 0) {
    int x = num;
    num = (num / base);
    int remainder = x % base;
    c = remainder + '0';
    string[counter] = c;
    // printf("string is: %s", string);

    counter++;
  }
  string[counter] = '\0';
  thestring = string;
  //     printf("string is: %s", thestring);
  counter--;
  for (int i = counter, k = 0; i >= 0; i--, k++) {
    newstring[k] = string[i];
    if (i == 0) {
      newstring[k + 1] = '\0';
    }
  }

  base_string = newstring;
  return base_string;
}

bool isPalindrome(char *s) {

  bool f = true;
  int length = strlen(s);

  for (int i = 0; i < length; i++) {

    if (s[i] != s[length - (i + 1)]) {
      f = false;
      break;
    }
  }
  return f;
}

void palindrome_primeprint(BitVector *bv, int b) {
  int base = b;
  printf("Base  %d\n", base);
  puts("---- --");
  for (uint32_t i = 2; i < bv->length; i++) {

    if (bv_get_bit(bv, i) == 1) {
      char *newbase = decimal_to_basex(i, base);
      // printf("the new base is%s\n", newbase);
      bool palindrome = isPalindrome(newbase);

      if (palindrome == 1) {
        printf("%d = %s\n", i, newbase);
      }
    }
  }
}
