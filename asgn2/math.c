#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include <stdbool.h>

#define EPSILON 10e-9
#define OPTIONS "sctea"
#define SC_MIN -2 * M_PI
#define SC_MAX 2 * M_PI
#define SCT_STEP M_PI / 16
#define TAN_MIN -M_PI / 3
#define TAN_MAX M_PI / 3
#define EXP_MIN 0
#define EXP_MAX 9
#define EXP_STEP 0.1

void Sin();
void Cos();
void Tan();
void Exp();

int main(int argc, char **argv)
{
  bool s, c, t, e, a = false;
  int ch = 0;
  if((ch = getopt(argc, argv, OPTIONS)) != -1)
  { 
    if( ch == 's')
    {
      s = true;
      if(s)
      {
        Sin();  
      }
    }
    else if(ch == 'c')
   {
     c = true;
     if(c)
     {
       Cos();
     }
   }
  else  if(ch == 't')
   {
     t = true;
     if(t)
     {
       Tan();
     }
   }
  else  if (ch == 'e')
   {
    e = true;
    if(e)
    {
      Exp();
    }
   }
  else  if(ch == 'a')
   {
     a = true;
     if(a)
     {
       Sin();
       Cos();
       Tan();
       Exp();
     }
   }
  else  if(ch == '?')
   {
     printf("Character not defined in the string");
     return -1;  
   }
 }
  
  
  if(argc == 1)
  {
    printf("Error: no arguments supplied!");
    return -1;
   }
 


  return 0;
}

void Sin()
{
  double Sin_x = 0.0;
  double sin_lib = 0.0;
  
  printf("x \t Sin  \t\t Library         Difference\n");
  printf("- \t ---  \t\t -------         ----------\n");
  
  for(double i = SC_MIN; i <= (SC_MAX + SCT_STEP); i += SCT_STEP)
  {
    Sin_x = (i*((i*i*(52785432-479249*i*i)-1640635920)*i*i+11511339840)) /
            (((18361*i*i+3177720)*i*i+277920720)*i*i+11511339840);
    sin_lib = sin(i);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Sin_x, sin_lib, (sin_lib - Sin_x));
  }
}

void Cos()
{
  double Cos_x = 0.0;
  double cos_lib = 0.0;

  printf("x \t Cos  \t\t Library         Difference\n");
  printf("- \t ---  \t\t -------         ----------\n");
  
  for(double i = SC_MIN; i <= (SC_MAX + SCT_STEP); i += SCT_STEP)
  {
    Cos_x = ((i*i*(1075032-14615*i*i)-18471600)*i*i+39251520) /		 	 				(((127*i*i+16632)*i*i+1154160)*i*i+39251520);
    cos_lib = cos(i);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Cos_x, cos_lib, (cos_lib - Cos_x));
  }
}

void Tan()
{
  double Tan_x = 0.0;
  double tan_lib = 0.0;
  
  printf("x \t Tan  \t\t Library         Difference\n");
  printf("- \t ---  \t\t -------         ----------\n");
  
  for(double i = TAN_MIN; i <= TAN_MAX; i += SCT_STEP)
  {
    Tan_x = (i*((i*i*((i*i-990)*i*i+135135)-4729725)*i*i+34459425)) /			                        ((i*i*((45*i*i-13860)*i*i+945945)-16216200)*i*i+34459425);

    tan_lib = tan(i);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Tan_x, tan_lib, (tan_lib - Tan_x));
  }
}

void Exp()
{
  double total_num = 0;
  double exp_lib = 0.0;
  
  printf("x \t Exp  \t\t Library         Difference\n");
  printf("- \t ---  \t\t -------         ----------\n");
 
  while(total_num < 91)
  {
   double term = 1.0;
  double sum = term;
  static double input_num = EXP_MIN;
 
   for(double k = 1.0; (fabs(term) > EPSILON); k+= 1.0)
   {
    term = (input_num/k) * term;
    sum += term;
   }
   exp_lib = exp(input_num);
   printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", input_num, sum, exp_lib, (exp_lib - sum));
   input_num += EXP_STEP;
   total_num++;
  }
}

