Assignment 5 - Sorting

To use this program the user must enter options supported options of either -A, which will run all the sorts, -b which will just perform bubble sort on array, -s which will perform shell sort on array, -q which will perform quick sort on array, and -i which will perform binary insertion sort. These are the minimum flags to be entered to allow program to run, one or all can be used or any combination of them, as user desires due to them being a set where members (the options) are not mutually exclusive to each other. When these flags are entered then defauly values of array size 100, print elements size of 100, and random seed of 8222022 will be used. If user desires to change these then flags of -p n, which will print n # elements from array, or -r s, where the seed s will be used, or -n c, where c is size of array to create can be used, in same fashion or order as all other flags. When attempting to enter an option that supported the program will display error message and return with error message, as with no options being provided.

To build the program simply typing make or make all in terminal will do so, the program passes make infer cleanly and performing valgrind on it shows that all dynamically allocated memory and heap blocks have been freed.

Sources cited: the implementation of each sort was provided in lab manual for asgn5 as pseudocode, so that was used and converted into C code. For the set of enum types used from piazza provided by TA Eugene Chou, on post about sets on lab.

Built in UNIX timeshare terminal using Vim

Author: Din Bostandzic
