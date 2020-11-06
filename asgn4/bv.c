#include "bv.h"
#include <stdlib.h>
#include <stdint.h>
#define NULL (void*)0

BitVector *bv_create(uint32_t bit_len)
{
  BitVector *v = (struct BitVector*)malloc(sizeof(BitVector));
  if(v == NULL)
  {
    return 0;
  }
  if (bit_len < 1)
  {
    bit_len = 1;
  }	
  v->length = bit_len;
  v->vector = (uint8_t*)malloc(sizeof(uint32_t) * v->length);
  if(v->vector == NULL)
  {
      return 0; 
  }
  return v;
}

void bv_delete(BitVector *v)
{
   free(v->vector);
   free(v);
   return;
}

uint32_t bv_get_len(BitVector *v)
{
  return v->length;
}

void bv_set_bit(BitVector *v, uint32_t i)
{
  int bucket = i /8;
  int thebit = bv_get_bit(v,i);
  printf("the bit: %d\n", thebit);

  uint8_t thebyte = v->vector[bucket];
  printf("the bucket/byte: %d\n", thebyte);

  uint8_t shiftbyte =  (00000001<<thebit);
  printf("the byte to OR original byte: %d\n", shiftbyte);

  uint8_t newresult = thebyte | shiftbyte;
  printf("the new byte with value: %d\n", newresult); 

  v->vector[bucket] = newresult;
}

void bv_clr_bit(BitVector *v, uint32_t i)
{
  int bucket = i /8;
  int thebit = bv_get_bit(v,i);
  printf("the bit: %d\n", thebit);

  uint8_t thebyte = v->vector[bucket];
  printf("the bucket/byte: %d\n", thebyte);

  uint8_t shiftbyte =  ~(00000001<<thebit);
  printf("the byte to OR original byte: %d\n", shiftbyte);
 
  uint8_t newresult = (thebyte & shiftbyte);
  printf("the new byte with value: %d\n", newresult); 

  v->vector[bucket] = newresult;

}

uint8_t bv_get_bit(BitVector *v, uint32_t i)
{
  return i%8;
}

void bv_set_all_bits(BitVector *v)
{
  for(int i = 0; i < v->length; i++)
  {
    bv_set_bit(v,i);
  }

}
