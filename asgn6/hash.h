#ifndef __HASH_H__
#define __HASH_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "ll.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include "speck.h"

//
// Struct definition for a HashTable.
//
// salt: the salt of the HashTable (used for hashing)
// length: The maximum number of entries in the HashTable
// heads: An array of linked list heads.
//
typedef struct HashTable{
  uint64_t salt[2];
  uint32_t length;
  ListNode **heads;
} HashTable;

//
// Constructor for a HashTable.
//
// length: Length of the HashTable
// salt: Salt for the Hashtable
//
HashTable *ht_create(uint32_t length);

//
// Destructor for a HashTable.
//
// ht: The HashTable
//
void ht_delete(HashTable *ht);

//
// Returns number of entries in hash table
//
// h: the hashtable
//
uint32_t ht_count(HashTable *h);

//
// Searches a HashTable for a key.
// Returns the ListNode if found and returns NULL otherwise.
// This should call the ll_lookup() function.
//
// ht: the HashTable
// key: the key to search for
//
ListNode *ht_lookup(HashTable *ht, char *key);

//
// First creates a new ListNode from HatterSpeak.
// The created ListNode is then inserted into a HashTable.
// This should call the ll_insert() function.
//
// ht: the hashtable
// gs: the hatterspeak to add to the hashtable
//
void ht_insert(HashTable *ht, HatterSpeak *gs);

#endif
