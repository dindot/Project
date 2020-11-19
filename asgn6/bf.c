#include "bf.h"
#include "speck.h"
#include <stdlib.h>

#define BFSIZE 1048576
//
// Constructor for a BloomFilter.
//
// size: The number of entries in the BloomFilter.
//
BloomFilter *bf_create(uint32_t size){
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
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
  uint32_t index = 0;
  index = hash(bf->primary, key) % BFSIZE;  // apply the 3 salts to the hash, set bit to 1 of index
  bv_set_bit(bf->filter, index);
  index = hash(bf->secondary, key) % BFSIZE;
  bv_set_bit(bf->filter, index);
  index = hash(bf->tertiary, key) % BFSIZE;
  bv_set_bit(bf->filter, index);
}

bool bf_probe(BloomFilter *bf, char *key)
{
 uint32_t index1 = hash(bf->primary, key) % BFSIZE;  // get indices when applied 3 salts to hash
 uint32_t index2 = hash(bf->secondary, key) % BFSIZE;
 uint32_t index3 = hash(bf->tertiary, key) % BFSIZE;
 
 // check to see if each bit is turned on, then its an oldspeak word
 if(bv_get_bit(bf->filter, index1) == 1 && bv_get_bit(bf->filter, index2) == 1 && bv_get_bit(bf->filter, index3) == 1)
  {
    return 1;
  }
 
return 0;

}

