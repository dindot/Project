#include "binary.h"
#include "bubble.h"
#include "counters.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// options input by user to be parsed, where A is to perform all sorts,
// b is bubble sort, s is shell sort, q is quicksort, and i is binary
// insertion sort, while p is the # elements to print, r is the random set,
// and n is the number of elements to put in array.
#define OPTIONS "Absqip:r:n:"
enum opts {
  A,
  b,
  s,
  q,
  i
}; // make a set to allow options to be not mutually exclusive

// cited, used from piazza post
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

// takes in default_arraysize as integer which is the array size provided by user
// else 100 default, the default_seed which is seed provided by user, else 8222022,
// option as pointer to enum opts, the set of all possible options that user can choose,
// and default_print which user can specify amount of elements to print, else 100.
// The function checks the options that have been selected by user and then operates
// performing the appropriate sorts.
void choices(int default_arraysize, int default_seed, enum opts *option,
    int default_print);

// takes in default_size as integer which is the array size provided by user
// else 100 default, the default_seed which is seed provided by user, else 8222022.
// It returns a pointer to uint32_t which is the array of random values that
// gets created based on user inputs, and we will be used on sorts
uint32_t *array_maker(int default_size, int default_seed);

// takes in arr pointer to uint32_t, which is the array that has been made,
// to be sorted and its size and # of elements to print accordingly. Outputs with
// tabular format for each array and sort used.
void print_array(uint32_t *arr, int default_size, int default_print);

// These functions all take in the array to be operated on and peform
// binary insertion sort, quicksort, shell short, and bubble sort, one by one
// respectively on the array with its passed in size, # elements to print
// and seed. Each must be freed in memeory after printed.
void i_sort_operate(int default_arraysize, int default_seed, int default_print);
void q_sort_operate(int default_arraysize, int default_seed, int default_print);
void s_sort_operate(int default_arraysize, int default_seed, int default_print);
void b_sort_operate(int default_arraysize, int default_seed, int default_print);

static uint32_t max_num
    = (1 << 30)
      - 1; // The max number for rand() generator 2^30 -1, ensures numbers to be 30 bits

int main(int argc, char **argv) {

  // set the default values
  enum opts option = 0;
  int default_arraysize = 100;
  int default_print = 100;
  int default_seed = 8222022;
  char *input_num = NULL;
  char c; // used to obtain the user input of choices

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'A':
      setopt(&option,
          0); // in the set, set which ones the user has entered to be accessed later
      break;
    case 'b':
      setopt(&option, 1);
      break;
    case 's':
      setopt(&option, 2);
      break;
    case 'q':
      setopt(&option, 3);
      break;
    case 'i':
      setopt(&option, 4);
      break;
    case 'p':
      setopt(&option, 5);
      input_num = optarg;
      default_print
          = atoi(input_num); // when user specified, convert to a int to be used
      break;
    case 'r':
      input_num = optarg;
      default_seed = atoi(input_num);
      break;
    case 'n':
      input_num = optarg;
      default_arraysize = atoi(input_num);
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

  choices(default_arraysize, default_seed, &option, default_print);
}

void choices(int default_arraysize, int default_seed, enum opts *option,
    int default_print) {

  for (
      enum opts x = A; x <= i;
      x++) { // traverse the enum set to find which ones have been entered and thus set by the use, cited from piazza used on sets for lab from TA Eugene Chou
    if (checkopt(option, x)) {
      switch (x) {
      case A: // perform the respective sorts based on the user option inputs
        i_sort_operate(default_arraysize, default_seed, default_print);
        swaps
            = 0; // since every sort, must reset the extern values to keep track of new sort
        compares = 0;
        q_sort_operate(default_arraysize, default_seed, default_print);
        swaps = 0;
        compares = 0;
        s_sort_operate(default_arraysize, default_seed, default_print);
        swaps = 0;
        compares = 0;
        b_sort_operate(default_arraysize, default_seed, default_print);
        break;
      case b:
        b_sort_operate(default_arraysize, default_seed, default_print);

        break;
      case s:
        s_sort_operate(default_arraysize, default_seed, default_print);

        break;
      case q:
        q_sort_operate(default_arraysize, default_seed, default_print);

        break;
      case i:
        i_sort_operate(default_arraysize, default_seed, default_print);

        break;
      default:
        break;
      }
    }
  }
}

void print_array(uint32_t *arr, int default_size, int default_print) {
  // print the header with stats for each sort
  printf("%d elements, %d moves, %d compares\n", default_size, swaps, compares);
  int i = 0;
  while (i < default_print) {
    for (int j = 1; j < 8;
         j++) { // formatting to make 7 columns in table output
      printf("%13u", arr[i]);
      ++i;

      if (i == default_print) {
        break;
      }
    }
    printf("\n");
  }
}

uint32_t *array_maker(int default_size, int default_seed) {
  srand(default_seed);
  uint32_t *arr
      = (uint32_t *)calloc(default_size, sizeof(uint32_t) * default_size);

  for (
      int i = 0; i < default_size;
      i++) { // using the seed and calloc'd new array on the default_size of array provided, initialize the array with random values
    if (arr != (NULL)) {
      arr[i] = rand() % max_num;
    }
  }

  return arr;
}

void i_sort_operate(
    int default_arraysize, int default_seed, int default_print) {
  printf("Binary Insertion Sort\n"); // the header of the sort performed
  uint32_t *arr = array_maker(
      default_arraysize, default_seed); // create an array to be sorted
  binary_insertion_sort(arr, default_arraysize); // perform respective sort
  print_array(arr, default_arraysize, default_print);
  free(arr); // after printing, clear up dynamic memory
}

void q_sort_operate(
    int default_arraysize, int default_seed, int default_print) {

  printf("Quick Sort\n");
  uint32_t *arr = array_maker(default_arraysize, default_seed);
  quick_sort(arr, 0,
      default_arraysize
          - 1); // start quick sort at left index 0, right index at size of array -1
  print_array(arr, default_arraysize, default_print);
  free(arr); // after printing, clear up dynamic memory
}

void s_sort_operate(
    int default_arraysize, int default_seed, int default_print) {

  printf("Shell Sort\n");
  uint32_t *arr = array_maker(default_arraysize, default_seed);
  int *arr2 = gap(default_arraysize); // holds the gap intervals
  shell_sort(arr, default_arraysize, arr2);
  print_array(arr, default_arraysize, default_print);
  free(arr);
}

void b_sort_operate(
    int default_arraysize, int default_seed, int default_print) {

  printf("Bubble Sort\n");
  uint32_t *arr = array_maker(default_arraysize, default_seed);
  bubble_sort(arr, default_arraysize);
  print_array(arr, default_arraysize, default_print);
  free(arr);
}
