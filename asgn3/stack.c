#include "stack.h"
#include <stdlib.h>


Stack *stack_create(int capacity, char name)
{
   Stack *s = (Stack*)malloc(sizeof(Stack));
   if (s == NULL)
   { 
    return 0;
   }
   
   if (capacity < 1)
   { 
     capacity = 1;

   }

   s->capacity = capacity;
   s->name = name;
   s->top = 0;
   
   s->items = (int*)malloc(sizeof(int) * capacity);
   if (items == NULL)
    {
       return 0;
     }

   return s;
}
