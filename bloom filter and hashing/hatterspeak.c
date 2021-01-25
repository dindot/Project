#include "bf.h"
#include "hash.h"
#include "hs.h"
#include "ll.h"
#include "parser.h"
#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "mbh:f:s" // supported options
#define CONTRACTIONS                                                           \
  "[a-zA-Z0-9]*[-_']?[a-zA-Z0-9]*[a-zA-Z0-9]" // regex expression

// reads in hatterspeak.txt and oldspeak.txt files taking each word separated by space
// to put into hash table. Takes in ht pointer to HashTable struct, the hashtable and
// takes in bf pointer to BloomFilter struct the bloomfilter to first use bf and insert
// all oldspeak words, then insert into ht with NULL hatterspeak values, and then places
// into bf the extracted hatterspeak.txt words and places them into ht.
void file_readin(BloomFilter *bf, HashTable *ht);

// uses regex and calls parser to parse user input and then search that word
// within the bf, if found, proceeds to look it up in the ht, then based on if it
// was found with translation or not, places each word into separate created linked list
// to be used for output at end.
void redir_input(BloomFilter *bf, HashTable *ht);

// takes in the stored found words from each of the separate linkedlist and displays
// if only oldspeak or oldspeak with translations, or a mix of both the appropriate
// message to user and punishment if any. Take in node as pointer to ListNode struct
// to be traversed in list.
void printer(ListNode *node);

// If the words stored in the linkedlist do not have any translations, then this will print
// out the appropriate message of punishment.
void oldspeakprint(ListNode *node);

// access the variables from other files to keep track of stats
extern int avg_seek;
extern int seek;
extern int nodes;
extern int slots;

bool tofront = 0, nofront = 0, stats = 0, transwords = 0, notrans = 0;

int main(int argc, char **argv) {

  char *input_num = (char *)NULL; // to get user changed values
  uint32_t default_hashtable = 10000;
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

  if (tofront == 1 && nofront == 1) {
    puts("this combination is not supported!\n");
    return -1;
  }

  BloomFilter *bf = bf_create(default_bloom); // create all data structs needed
  HashTable *ht = ht_create(default_hashtable);

  HatterSpeak *hs = hs_create((char *)NULL, (char *)NULL);
  ListNode *node = ll_node_create(hs);
  for (uint32_t i = 0; i < ht->length;
       i++) { // initialize ht with null nodes to allow linkage
    ht->heads[i] = node;
  }

  file_readin(bf, ht);
  redir_input(bf, ht);
  uint32_t htcount = ht_count(ht);
  // the # nonNULL nodes / hashtable size
  double hashload = ((double)htcount / default_hashtable) * 100;

  if (stats == 1) // display of stats
  {
    printf("Seeks: %d\n", seek);
    printf("Average seek length: %f\n", (double)avg_seek / seek);
    printf(
        "Average Linked List Length: %f\n", (double)nodes / default_hashtable);
    printf("Hash table load: %f%%\n", hashload);
    printf("Bloom filter load: %f%%\n", ((double)slots / default_bloom) * 100);
  }
  ht_delete(ht);
  bf_delete(bf);
  return 0;
}

void file_readin(BloomFilter *bf, HashTable *ht) {

  FILE *file = fopen("oldspeak.txt", "r");
  if (file == NULL) {
    puts("could not open file!\n");
    return;
  }

  FILE *hatter = fopen("hatterspeak.txt", "r");
  if (hatter == NULL) {
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
    HatterSpeak *gs = hs_create(buffer, (char *)NULL);
    ListNode *checker = ht_lookup(ht, buffer);
    if (checker == NULL) {

      ht_insert(ht, gs);
    }
  }

  fclose(file);

  while (!feof(hatter)) {
    fscanf(hatter, "%s\n%s", buffer, buffer2);

    bf_insert(bf, buffer);
    HatterSpeak *gs = hs_create(buffer, buffer2);
    ListNode *checker = ht_lookup(ht, buffer);
    if (checker == NULL) {

      ht_insert(ht, gs);
    }
  }

  fclose(hatter);
  free(buffer2);
  free(buffer);
}

void redir_input(BloomFilter *bf, HashTable *ht) {
  HatterSpeak *hs = hs_create((char *)NULL, (char *)NULL);
  ListNode *stored_notranswords = ll_node_create(hs);
  ListNode *stored_transwords = ll_node_create(hs);

  int returncode;
  regex_t regex;
  returncode = regcomp(&regex, CONTRACTIONS, REG_EXTENDED);
  if (returncode) {
    puts("compilation unsuccessful\n");
    return;
  }

  while (!feof(stdin)) {
    char *matchedword = next_word(stdin, &regex);
    if (matchedword != NULL) {

      for (unsigned long i = 0; i < strlen(matchedword); i++) {
        matchedword[i] = tolower(matchedword[i]);
      }
      bool passbf = bf_probe(bf, matchedword);
      if (passbf == 1) {
        ListNode *node = ht_lookup(ht, matchedword);
        ++seek;
        if (node != NULL && isalpha(node->gs->hatterspeak[0]) != 0) {

          transwords = 1;
          ll_insert(&stored_transwords, node->gs);
        } else if (node != NULL && isalpha(node->gs->hatterspeak[0]) == 0) {

          notrans = 1;
          ll_insert(&stored_notranswords, node->gs);
        } else if (node != NULL
                   && (isalpha(node->gs->hatterspeak[0]) == 0
                          || isalpha(node->gs->hatterspeak[0]) != 0)) {

          transwords = notrans = 1;
        }
      }
    }
  }
  clear_words();

  if (transwords == 1 && notrans == 1) {
    printer(stored_notranswords);
    printer(stored_transwords);
  } else if (transwords == 1 && notrans == 0) {
    printer(stored_transwords);
  } else if (transwords == 0 && notrans == 1) {
    printer(stored_notranswords);
  }
}

void printer(ListNode *node) {

  if ((transwords == 1 && notrans == 1)
      && isalpha(node->gs->hatterspeak[0]) == 0) {
    puts("Dear Comrade,\n");
    puts("You have chosen to use words that the queen has decreed oldspeak.");
    puts("Due to your infraction you will be sent to the dungeon where you "
         "will");
    puts("   be taught hatterspeak.\n");
    puts("Your errors:\n");

    while (node->next != NULL) {
      printf("%s\n", node->gs->oldspeak);
      node = node->next;
    }
  } else if ((transwords == 1 && notrans == 1)
             && isalpha(node->gs->hatterspeak[0]) != 0) {

    puts("\nAppropriate hatterspeak translations.\n");
    while (node->next != NULL) {
      printf("%s -> %s\n", node->gs->oldspeak, node->gs->hatterspeak);
      node = node->next;
    }

  }

  else if (transwords == 1) {
    printf("Dear Wonderlander,\n");
    printf("\nThe decree for hatterspeak finds your message lacking. Some of "
           "the\n");
    printf("   words that you used are not hatterspeak.\n");
    puts("The list shows how to turn the oldspeak words into hatterspeak.\n");

    while (node->next != NULL) {
      printf("%s -> %s\n", node->gs->oldspeak, node->gs->hatterspeak);
      node = node->next;
    }
  } else if (notrans == 1 && stats == 0) {
    oldspeakprint(node);
  }
}

void oldspeakprint(ListNode *node) {

  printf("Dear Wonderlander,\n");
  printf(
      "\nYou have chosen to use words that the queen has decreed oldspeak.\n");
  printf("Due to your infraction you will be sent to the dungeon where you "
         "will\n");
  printf("   be taught hatterspeak.\n");
  puts("\nYour errors:\n");

  while (node->next != NULL) {
    printf("%s\n", node->gs->oldspeak);
    node = node->next;
  }
}
