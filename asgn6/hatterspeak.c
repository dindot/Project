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

void file_readin(BloomFilter *bf, HashTable *ht);

bool tofront = 0, nofront = 0, stats = 0;

int main(int argc, char **argv) {

  char *input_num = (char *)NULL; // to get user changed values
  int default_hashtable = 10000;
  int default_bloom = 1048576;
  char c; // to obtain user input of choices

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'm':
      tofront = 1;
      move_to_front = 1;
      break;
    case 'b':
      nofront = 1;
      move_to_front = 0;
      break;
    case 'h':
      input_num = optarg;
      default_hashtable
          = atoi(input_num); // when user specified, convert to a int to be used
      break;
    case 'f':
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

  if (stats == 1) {
    puts("stats are\n");
  }

  if (tofront == 1 && nofront == 1) {
    puts("this combination is not supported!\n");
    return -1;
  }

  BloomFilter *bf = bf_create(default_bloom);
  HashTable *ht = ht_create(default_hashtable);

  for (uint32_t i = 0; i < ht->length; i++) {
    ht->heads[i] = NIL;
  }

  file_readin(bf, ht);
  return 0;
}

void file_readin(BloomFilter *bf, HashTable *ht) {

  FILE *file = fopen("oldspeak.txt", "r");
  if (file == NULL) {
    puts("could not open file!\n");
    return;
  }

  FILE *hatter = fopen("hatterspeak.txt", "r");
  if (file == NULL) {
    puts("could not open file!\n");
    return;
  }

  size_t size = 1024;
  char *buffer = (char *)malloc(sizeof(char) * size);
  char *buffer2 = (char *)malloc(sizeof(char) * size);
  // put each of the lines from file into buffer and print them, use this to put into
  // hatter struct

  while (!feof(file)) {

    fscanf(file, "%s", buffer);
    bf_insert(bf, buffer);

    //  hs_delete(gs);           // later  might need to delete to put in rest
    //  gs = NULL;
  }

  fclose(file);

  while (!feof(hatter)) {
    fscanf(hatter, "%s\n%s", buffer, buffer2);

    if (bf_probe(bf, buffer) == 0) {
      HatterSpeak *gs = hs_create(buffer, NULL);
      ht_insert(ht, gs);
    }
  }

  rewind(hatter);
  while (!feof(hatter)) {
    fscanf(hatter, "%s\n%s", buffer, buffer2);
    bf_insert(bf, buffer);
    HatterSpeak *gs = hs_create(buffer, buffer2);
    ht_insert(ht, gs);

    //if(ht->heads[688] != NULL)
    //printf("%s", ht->heads[688]->gs->oldspeak);  // to test the values they appear to be printing!
  }

  fclose(hatter);
}
