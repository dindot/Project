#include <stdio.h>
#include "bf.h"
#include "ll.h"

int main(void)
{
 bool inbf = 0;
 BloomFilter *bf = bf_create(1048576);  // max size of 20^2
 bf_insert(bf, "potato");
 bf_insert(bf, "reddy");
 inbf = bf_probe(bf, "potato");
 printf("%d", inbf);
 inbf= bf_probe(bf, "adam");
printf("%d", inbf);
return 0;
}
