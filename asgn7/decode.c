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

void decompress(int infile, int outfile);

bool input = 0, output = 0, stats = 0;

int bitlen(uint16_t code) {
  if (code == 0)
    return 1;
  int minbitscurrcode = (log2(code)) + 1;
  return minbitscurrcode;
}

void compress(int infile, int outfile);

int main(int argc, char **argv) {
  char inputfile[50] = { '0' };
  char outputfile[50] = { '0' };
  int defaultinput = STDIN_FILENO;
  int defaultoutput = STDOUT_FILENO;

  char *input_num = (char *)NULL;
  char c; // to obtain user input of choices
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'i':
      input = 1;
      input_num = optarg;
      strcpy(inputfile, input_num);
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
      printf("Character not found in string");
      return -1;
    }
  }
  if (argc == 1) {
    char text[4096] = { '0' };
    while (!feof(stdin)) {
      fgets(text, 4096, stdin);
    }

    decompress(defaultinput, defaultoutput);
  }

  if (input == 1 && output == 1) {
    int infile = open(inputfile, O_RDONLY, 0600);
    if (infile == -1) {
      puts("Unable to open file");
      return -1;
    }

    FileHeader h;

    struct stat dststats;
    struct stat srcstats;
    fstat(infile, &srcstats);

    read_header(infile, &h);

    int outfile = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (infile == -1) {
      puts("Unable to open file");
      return -1;
    }
    fstat(outfile, &dststats);
    fchmod(outfile, srcstats.st_mode);

    decompress(infile, outfile);
  }

  return 0;
}

void decompress(int infile, int outfile) {
  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;

  while (read_pair(infile, &curr_code, &curr_sym, bitlen(next_code)) == 1) {
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    next_code = next_code + 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);
}
