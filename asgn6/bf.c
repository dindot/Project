#include "bf.h"
#include <stdlib.h>

//
// Constructor for a BloomFilter.
//
// size: The number of entries in the BloomFilter.
//
BloomFilter *bf_create(uint32_t size){
  Bloomfilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf){
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
}
 return (BloomFilter*)NIL;
}

void bf_delete(BloomFilter *bf)
{
  free(bf);
}

void bf_insert(BloomFilter *bf, char *key)
{
  hash();


}
