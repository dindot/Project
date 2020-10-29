#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#define NULL ((void*)0)
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
   if (s->items == NULL)
    {
       return 0;
     }

   return s;
}



void stack_delete(Stack *s)
{
  free(s->items);
  free(s);
  return;
}


int stack_pop(Stack *s)
{
  if(s == NULL)
  {
   puts("The stack not in memory");
   return -1;
  }
  if(s->top >0)
  {
    s->top -= 1;
   return s->items[s->top];

     }

   else
    {
     // puts("Empty stack, nothing to be popped");
     return -1;    
}

}

void stack_push(Stack *s, int item)
{
  if (s == NULL)
   {

    return;
   }


   if (s->top == s->capacity)
   {
    s->capacity *= 2;
    s->items = (int*)realloc(s->items, s->capacity * sizeof(int));
   }
   if (s->items)
   {
     s->items[s->top] = item;
     s->top += 1;
   }
     return;
 }



bool stack_empty(Stack *s)
{
   return s->top == 0;
}

int stack_peek(Stack *s)
{

return s->items[s->top-1];

}

