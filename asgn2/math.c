#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define EPSILON 1e-10  // use for limiting Exp() to produce restricted  decimals
#define OPTIONS "sctea"                                                     
#define SC_MIN -2 * M_PI // most accurate rep. of pi, use to bound the functions
#define SC_MAX 2 * M_PI
#define SCT_STEP M_PI / 16
#define TAN_MIN -M_PI / 3
#define TAN_MAX M_PI / 3
#define EXP_MIN 0
#define EXP_MAX 9
#define EXP_STEP 0.1

// void function for determining the sin of numbers [-2/pi, 2/pi] incrementing by pi/16
// Implemented by use of horner normal form pade approximations using 14 terms taylor series
// center at 0, loop to display sin printed as table in comparision with the actual lib sin function
void Sin();

// void function for determining the cos of numbers [-2/pi, 2/pi] incrementing by pi/16
// Implemented by use of horner normal form pade approximations using 14 terms taylor series
// center at 0, loop to display cos printed as table in comparision with the actual lib cos function
void Cos();

// void function for determining the tan of numbers [-pi/3, pi/3] incrementing by pi/16
// Implemented by use of horner normal form pade approximations using 14 terms taylor series
// center at 0, loop to display tan printed as table in comparision with the actual lib tan function
void Tan();

// void function for determining the exponentials e^x where x [0,9], incrementing by 0.1
// Implemented as under the hood taylor series centered at 0, by use of looping
// to get a fixed decimal as the value converges towards 0 stopping when reaches EPSILON
// Displays each exp in table with comparision of actual exp lib function
void Exp();

int main(int argc, char **argv) {
  bool s, c, t, e,
      a
      = false; // -s -c -t -e user option to individually perform and display sin,
  int ch = 0; //  cos, tin, exp, respectively, -a will perform them all
  if ((ch = getopt(argc, argv, OPTIONS))
      != -1) // parse user input for options provided
  {
    if (ch == 's') // if user enters -s call Sin()
    {
      s = true;
      if (s) {
        Sin();
      }
    } else if (ch == 'c') // if user enters -c call Cos()
    {
      c = true;
      if (c) {
        Cos();
      }
    } else if (ch == 't') // if user enters -t call Tan()
    {
      t = true;
      if (t) {
        Tan();
      }
    } else if (ch == 'e') // if user enters -e call Exp()
    {
      e = true;
      if (e) {
        Exp();
      }
    } else if (ch == 'a') // if user enters -a call Sin(), Cos(), Tan(), Exp()
    {
      a = true;
      if (a) {
        Sin();
        Cos();
        Tan();
        Exp();
      }
    } else if (ch == '?') // check if user enters other characters as options
    {
      printf("Character not defined in the string");
      return -1;
    }
  }

  if (argc == 1) // check if user entered in no options
  {
    printf("Error: no arguments supplied!");
    return -1;
  }

  return 0;
}

// Perform the calculation of sin Pade approximation for each value, print out formatted table
void Sin() {
  double Sin_x = 0.0;
  double sin_lib = 0.0;

  printf("x \t Sin  \t\t Library         Difference\n"); // table headers
  printf("- \t ---  \t\t -------         ----------\n");

  for (double i = SC_MIN; i <= (SC_MAX + SCT_STEP); i += SCT_STEP) {
    Sin_x = (i
                * ((i * i * (52785432 - 479249 * i * i) - 1640635920) * i * i
                      + 11511339840))
            / (((18361 * i * i + 3177720) * i * i + 277920720) * i * i
                  + 11511339840);
    sin_lib
        = sin(i); // the actual sin function from math.h lib, use as comparison
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Sin_x, sin_lib,
        (Sin_x - sin_lib));
  }
}

// Perform the calculation of cos Pade approximation for each value, print out formatted table
void Cos() {
  double Cos_x = 0.0;
  double cos_lib = 0.0;

  printf("x \t Cos  \t\t Library         Difference\n"); // table headers
  printf("- \t ---  \t\t -------         ----------\n");

  for (double i = SC_MIN; i <= (SC_MAX + SCT_STEP); i += SCT_STEP) {
    Cos_x = ((i * i * (1075032 - 14615 * i * i) - 18471600) * i * i + 39251520)
            / (((127 * i * i + 16632) * i * i + 1154160) * i * i + 39251520);
    cos_lib
        = cos(i); // the actual cos function from math.h lib, use as comparison
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Cos_x, cos_lib,
        (Cos_x - cos_lib));
  }
}

// Perform the calculation of tan Pade approximation for each value, print out formatted table
void Tan() {
  double Tan_x = 0.0;
  double tan_lib = 0.0;

  printf("x \t Tan  \t\t Library         Difference\n"); // table headers
  printf("- \t ---  \t\t -------         ----------\n");

  for (double i = TAN_MIN; i <= TAN_MAX; i += SCT_STEP) {
    Tan_x = (i
                * ((i * i * ((i * i - 990) * i * i + 135135) - 4729725) * i * i
                      + 34459425))
            / ((i * i * ((45 * i * i - 13860) * i * i + 945945) - 16216200) * i
                      * i
                  + 34459425);

    tan_lib
        = tan(i); // the actual tan function from math.h lib, use as comparison
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Tan_x, tan_lib,
        (Tan_x - tan_lib));
  }
}

// Performining Taylor series by multiplying the following ratio of (number inputted
// over term num) x/k by the previous term to get the current term,
// which is then added to running total sum
void Exp() {
  double total_num = 0;
  double exp_lib = 0.0;

  printf(
      "x \t Exp  \t\t Library         Difference\n"); // print the header for table
  printf("- \t ---  \t\t -------         ----------\n");

  while (
      total_num
      < 91) // there are total of 91 numbers between 0 and 9 if stepping by 0.1
  {
    double term = 1.0; // start off at 1 accounting for 0! in first term
    double sum = term;
    static double input_num = EXP_MIN; // number starting off from 0 to reach 9

    for (double k = 1.0; (fabs(term) > EPSILON);
         k += 1.0) // ensure a limited decimals result
    {
      term = (input_num / k) * term; // current term in series
      sum += term;
    }
    exp_lib = exp(
        input_num); // actual exp function from math.h lib, use as comparision
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", input_num, sum, exp_lib,
        (sum - exp_lib));
    input_num += EXP_STEP;
    total_num++; // account for ending at given range of inputs
  }
}
