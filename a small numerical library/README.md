Assignment 2 - A Small Numerical Library

To successfully use the program, the user must input a desired flag (option) among the following: -s, -c, -t, -e, -a correspoding to sin, cos, tan, exponential, and all. This is typed in terminal when running program and the choices are exclusive meaning that even if user enters more of the options it will only perform and display the first option chosen, unless -a then all of Sin, Cos, Tan, Exp functions will be run. The option choice will result in the display of a table with all values entered, the values once the certain function is applied, and values of actual math functions from the math.h library, along with the difference between the two, in a tabular manner. Along with the choice flag, the -lm flag is required so the program will actually run, since the math.h library will be linked. Entering in no choices or options not among the ones listed will reslt in program termination.

To compile the program type in terminal make. The Makefile contains the -lm flag to ensure proper compilation.

Built in UNIX timeshare terminal using Vim

Author: Din Bostandzic
