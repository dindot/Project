#include "sieve.h"
#include "bv.c"
#include <stdio.h>
#include <stdbool.h>

int main(void)
{

BitVector *bv = bv_create(100);
sieve(bv);


return 0;
}
