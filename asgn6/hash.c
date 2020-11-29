#include "hash.h"

  ListNode **head = NULL;

//
// Constructor for a HashTable
//
// length: length of the HashTable
// salt: Salt for the HashTable
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  return (HashTable *)NIL;
}

void ht_delete(HashTable *ht) {
  free(ht->heads);
  free(ht);
}

uint32_t ht_count(HashTable *ht) {  // count nodes in the ht that are filled with other than NULL
  uint32_t counter = 0;
  for (uint32_t i = 0; i < ht->length; i++) {
    if (ht->heads[i]->next != NULL) {
      counter++;
    }
  }

  return counter;
}

ListNode *ht_lookup(HashTable *ht, char *key) {
 uint32_t index = hash(ht->salt, key) % ht->length; 
 
  ListNode *checknode = ll_lookup(&ht->heads[index], key);  // use index as inserted to search if node is there is table
  
    if (checknode != NIL) {
      return checknode;
    }
  

  return NIL;
}

void ht_insert(HashTable *ht, HatterSpeak *gs) {
 // create index using hash on key to place in given dayta
  uint32_t index = hash(ht->salt, gs->oldspeak) % ht->length;
    ListNode *node = ll_insert(&ht->heads[index], gs);
  
   if (node == NIL) {  // check to see if node was inserted
      puts("nodenot in");
    }
}
