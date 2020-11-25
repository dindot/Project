#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include "bf.h"
#include "ll.h"
#include "hs.h"
#include "hash.h"
#include "parser.h"


// options input by user to be parsed, where A is to perform all sorts,
// // b is bubble sort, s is shell sort, q is quicksort, and i is binary
// // insertion sort, while p is the # elements to print, r is the random set,
// // and n is the number of elements to put in array.
#define OPTIONS "smbh:f:"
enum opts {
  s, m, b
};

//cited, used from piazza post
// on sets for this lab, by TA Eugene Chou. takes in option, a pointer
// to enum opts,  which acts as of options set, and enum_opt of type enum opts
// which is each individual value in the set. It then sets that bit to 1 if
// the user has entered it as an option.
static inline void setopt(enum opts *option, enum opts enum_opt) {
   *option |= (1 << enum_opt);
   }

// cited, used from piazza post
// on sets for this lab, by TA Eugene Chou. takes in option, a pointer
// to enum opts,  which acts as of options set, and enum_opt of type enum opts
// which is each individual value in the set. It then ands that bit to 1 to check
// if it has a 1 and has been set when the user has entered it as an option.
static inline bool checkopt(enum opts *option, enum opts enum_opt) {
     return *option & (1 << enum_opt);
     }

void choices(int default_hash, int default_bloom, enum opts *option);

int main(int argc, char** argv)
{

char* input_num = (char*) NULL;  // to get user changed values
enum opts option = 0;
int default_hashtable = 10000;
int default_bloom = 1048576;
char c; // to obtain user input of choices

while ((c = getopt(argc, argv, OPTIONS)) != -1){
  switch (c){
   case 's':
      setopt(&option, 0);
      break;
   case 'm':
      setopt(&option, 1);
      break;
   case 'b':
       setopt(&option, 2);
      break;
    case 'h':
       setopt(&option, 3);
       input_num = optarg;
       default_hashtable = atoi(input_num);  // when user specified, convert to a int to be used
      break;
    case 'f':
       setopt(&option, 4);
       input_num = optarg;
       default_bloom = atoi(input_num);
       break;
    default:
      printf(
          "Character not found in string"); // if options other than ones supported entered
      return -1;
}
}
if(argc == 1) {  // user must supply arguments to run
  printf("No arguments supplied!");
  return -1;
}

choices(default_hashtable, default_bloom, &option);
return 0;
}
