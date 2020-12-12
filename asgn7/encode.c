#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "vi:o:"

bool input = 0, output = 0, stats = 0;

int bitlen(uint16_t code) {
  int minbitscurrcode = (log2(code)) + 1;
  return minbitscurrcode;
}

void compress(int infile, int outfile);

int main(int argc, char **argv) {
  char inputfile[50] = { '0' };
  char outputfile[50] = { '0' };
  int defaultinput = STDIN_FILENO;
  int defaultoutput = STDOUT_FILENO;

  char *input_num = (char *)NULL; // to get user changed values
  char c; // to obtain user input of choices

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'i':
      input = 1;
      input_num = optarg;
      strcpy(inputfile,
          input_num); // when user specified, convert to a int to be used
      break;
    case 'o':
      output = 1;
      input_num = optarg;
      strcpy(outputfile, input_num);
      break;
    case 'v':
      stats = 1;
      break;

    default:
      printf(
          "Character not found in string"); // if options other than ones supported entered
      return -1;
    }
  }
  if (argc == 1) { // user must supply arguments to run
    char text[4096]
        = { '0' }; // CHANGE THIS SO THAT IT TAKES INPUT TO BE PLACED INTO
    while (!feof(stdin)) {
      fgets(text, 4096, stdin);
    }

    compress(defaultinput, defaultoutput);
    //    printf("No arguments supplied!");
    //  return -1;
  }

  if (input == 1 && output == 1) {
    int infile = open(inputfile, O_RDONLY, 0600);
    if (infile == -1) {
      puts("Unable to open file");
      return -1;
    }

    struct stat srcstats;
    fstat(infile, &srcstats);
    FileHeader h;

    h.magic = MAGIC;
    h.protection = srcstats.st_mode;

    int outfile = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (infile == -1) {
      puts("Unable to open file");
      return -1;
    }

    write_header(outfile, &h);

    compress(infile, outfile);
  }
  //else
  //compress(defaultinput, defaultoutput);

  return 0;
}

void compress(int infile, int outfile) {

  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = (TrieNode *)NULL;

  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;

  while (read_sym(infile, &curr_sym) == 1) {
    TrieNode *next_node = trie_step(curr_node, curr_sym);
    if (next_node != (TrieNode *)NULL) {
      prev_node = curr_node;
      curr_node = next_node;
    } else {
      buffer_pair(outfile, curr_node->code, curr_sym, bitlen(next_code));
      curr_node->children[curr_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code = next_code + 1;
    }
    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    prev_sym = curr_sym;
  }
  if (curr_node != root) {
    buffer_pair(outfile, prev_node->code, prev_sym, bitlen(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0, bitlen(next_code));
  flush_pairs(outfile);
}
