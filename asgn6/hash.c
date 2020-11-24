#include "hash.h"

//
// Constructor for a HashTable
//
// length: length of the HashTable
// salt: Salt for the HashTable
//
HashTable *ht_create(uint32_t length){
  Hashtable *ht = (HashTable *)malloc(sizeof(HashTable));
if(ht){
  ht->salt[0] = 0x85ae998311115ae3;
  ht->salt[1] = 0xb6fac2ae33a40089;
  ht->length = length;
  ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
  return ht;
}
return (HashTable*) NIL;
}

void ht_delete(HashTable *ht)
{


}

