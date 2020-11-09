#include "bv.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

BitVector *bv_create(uint32_t bit_len) {
  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  if (v == NULL) {
    return 0;
  }
  if (bit_len < 1) {
    bit_len = 1;
  }
  v->length = bit_len;
  v->vector = (uint8_t *)malloc(sizeof(uint32_t) * v->length);
  if (v->vector == NULL) {
    return 0;
  }
  return v;
}

void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
  return;
}

uint32_t bv_get_len(BitVector *v) {
  return v->length;
}

void bv_set_bit(
    BitVector *v, uint32_t i) { // cited sources used from class lecture on bits
  int bucket = i / 8;
  int thebit = i % 8;

  uint8_t thebyte = v->vector[bucket];

  uint8_t shiftbyte = (00000001 << thebit);

  uint8_t newresult = thebyte | shiftbyte;

  v->vector[bucket] = newresult;
}

void bv_clr_bit(BitVector *v,
    uint32_t i) { // cited sources, used from class lecture on bits
  int bucket = i / 8;
  int thebit = i % 8;

  uint8_t thebyte = v->vector[bucket];

  uint8_t shiftbyte = ~(00000001 << thebit);

  uint8_t newresult = (thebyte & shiftbyte);

  v->vector[bucket] = newresult;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {

  int bucket = i / 8;
  int thebit = i % 8;
  uint8_t thebyte = v->vector[bucket];

  uint8_t shiftbyte = (00000001 << thebit);
  uint8_t newresult = thebyte & shiftbyte;
  uint8_t valueinbit = newresult >> thebit;

  return valueinbit;
}

void bv_set_all_bits(BitVector *v) {
  for (uint32_t i = 0; i < v->length; i++) {
    bv_set_bit(v, i);
  }
}
