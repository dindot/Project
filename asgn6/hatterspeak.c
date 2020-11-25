#include "bf.h"
#include "hash.h"
#include "hs.h"
#include "ll.h"
#include "parser.h"
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "mbh:f:s"

void choices(int default_hash, int default_bloom);

bool hashval = 0, bloomval = 0, tofront = 0, nofront = 0, stats = 0;

int main(int argc, char **argv) {

  char *input_num = (char *)NULL; // to get user changed values
  int default_hashtable = 10000;
  int default_bloom = 1048576;
  char c; // to obtain user input of choices

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'm':
      ///setopt(&option, 1);
      tofront = 1;
      move_to_front = 1;
      break;
    case 'b':
      //setopt(&option, 2);
      nofront = 1;
      move_to_front = 0;
      break;
    case 'h':
      // setopt(&option, 3);
      hashval = 1;
      input_num = optarg;
      default_hashtable
          = atoi(input_num); // when user specified, convert to a int to be used
      break;
    case 'f':
      // setopt(&option, 4);
      hashval = 1;
      input_num = optarg;
      default_bloom = atoi(input_num);
      break;
    case 's':
      puts("display stats");
      stats = 1;
      break;
    default:
      printf(
          "Character not found in string"); // if options other than ones supported entered
      return -1;
    }
  }
  if (argc == 1) { // user must supply arguments to run
    printf("No arguments supplied!");
    return -1;
  }

  choices(default_hashtable, default_bloom);
  return 0;
}

void choices(int default_hash, int default_bloom) {

  if (stats == 1) {
    puts("stats are\n");
  }

  if (tofront == 1 && nofront == 1) {
    puts("this combination is not supported!\n");
    return;
  }

  if (bloomval == 1 || bloomval == 0) {
    bf_create(default_bloom);
    printf("%d\n", default_bloom);
  }
  if (hashval == 1 || hashval == 0) {
    ht_create(default_hash);
    printf("%d\n", default_hash);
  }
  printf("%d", move_to_front);
}
