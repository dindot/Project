Assignment 4 - Bit Vectors and Primes

To use this program the user must enter the option of -s or -p or both before running to program to specify if they want an computation and output in tabular format a list of all the primes from 0-1000 inclusive or a listing in bases of 2,9,10,12(first letter of last name + 10) of the primes that are palindromes in those according bases, respectively. To specify a total amount of primes the user can use -n x with x being the number they desire for the program to run on and sieve in all primes in that given range. The -s will print out if the primes are special prime numbers such as a fibonacci, mersenne, or lucas prime. If the user does not specify an option flag or uses another option flag not supported the program will terminate with error message.

When running make infer, there is one error generated of memory leak: "bv.c:20: error: MEMORY_LEAK memory dynamically allocated to `v` by call to `malloc()` at line 7, column 31 is not reachable after line 20, column 1." when in bv.c the bv is created dynamically. This is however usable during runtime and accessible as the bitvector is created in main. The error is not accurate because upon runtime all memory leaks are cleared due to running valgrind shows that all heap blocks have been freed.

Sources cited: for implementation of sieve.c and ispalindrome functions, used from the lab manual of assign 4. The set/clear bit functions in bv.c used ideas from lecture on bits and bitvectors. The fibonacci function was used from the class lecture on recursion.

Built in UNIX timeshare terminal using Vim

Author: Din Bostandzic
