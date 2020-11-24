#include "hash.h"

//
// Constructor for a HashTable
//
// length: length of the HashTable
// salt: Salt for the HashTable
//
HashTable *ht_create(uint32_t length){
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
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
free(ht->heads);
free(ht);

}

uint32_t ht_count(HashTable *ht)
{
uint32_t counter = 0;
for(uint32_t i = 0; i <ht->length; i++)
{
if(ht->heads[i] != NULL)
{
counter++;
}

}

return counter;
}



ListNode *ht_lookup(HashTable *ht, char *key)
{
for(uint32_t i = 0; i<ht->length; i++)
{
 ListNode* checknode = ll_lookup(&ht->heads[i], key);
 if(checknode != NIL)
 {
  return checknode;
  }
}

return NIL;
}

void ht_insert(HashTable *ht, HatterSpeak *gs)
{

//ListNode *savehead = (ListNode*)NULL;
ListNode* node = ll_node_create(gs);
uint32_t index = hash(ht->salt, gs->oldspeak) % ht->length;
printf("index: %d", index);
if(ht->heads[index] == NIL)
{
ht->heads[index] = node;
//savehead = node;
}
else
{
//printf("\nsaved head: %s\n", node->gs->oldspeak);
//printf("other one %s", gs->oldspeak);

//printf("node vale: %s",  node->gs->oldspeak);
//if(savehead->gs->oldspeak != node->gs->oldspeak)
//{


//if(ll_insert(&ht->heads[index], gs) != NIL)
//{
ListNode* chainednode = ll_insert(&ht->heads[index], gs);
if(chainednode == NIL)
{
puts("nodenot in");
}
//}


}

}

//if(chainednode == NIL)
//{
//puts("node not inserted");
//}




