#include <stdlib.h>
#include <stdio.h>
#include "bf.h"
#include "ll.h"
#include "hs.h"
#include "hash.h"

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
//bf_delete(bf);
HatterSpeak *ds = (HatterSpeak*)malloc(sizeof(HatterSpeak));
ds->oldspeak = "hrmy";
ds->hatterspeak = "benny";
//ListNode* node = ll_node_create(ds);
//printf("node %s", node->gs->oldspeak);

//ListNode *initial = ll_insert(&node, ds);     /// need these 2 lines to can print up to hrmy
//printf("head is %s\n", initial->gs->oldspeak);

HatterSpeak *ss = (HatterSpeak*)malloc(sizeof(HatterSpeak));
ss->oldspeak = "redd";
ss->hatterspeak = "defef";
/*HHHHEEEERRRRListNode *head = ll_insert(&node, ss);
printf("head is %s\n", head->gs->oldspeak);

HatterSpeak *bb = (HatterSpeak*)malloc(sizeof(HatterSpeak));
bb->oldspeak = "john";
bb->hatterspeak = "pierce";
ListNode *add = ll_insert(&node, bb);
printf("head is %s\n", add->gs->oldspeak);

HatterSpeak *ed = (HatterSpeak*)malloc(sizeof(HatterSpeak));
ed->oldspeak = "mart";
ed->hatterspeak = "aser";
ListNode *hety = ll_insert(&node, ed);
printf("head is %s\n", hety->gs->oldspeak);



while(node != NIL)
{
printf("\n nodes %s\n", node->gs->oldspeak);  //show list with searched found value moved to front of list
node = node->next;
} // print out nodes works


 move_to_front = 0;

// works for case 0, but need to change move to front whrn its activated at 1, to display proper node !!!!!!!!!
char* john = "john";
printf("\n passsing nodes %s\n", node->gs->oldspeak);
ListNode* foundnode =  ll_lookup(&node,john);

if (foundnode->gs->oldspeak == john)
{
printf("\nfound %s", foundnode->gs->oldspeak);
}
else
{
printf("\nNot in list");
}

if(move_to_front == 1) {
while(foundnode != NIL)
{
printf("\n nodes %s\n", foundnode->gs->oldspeak);  //show list with searched found value moved to front of list
foundnode = foundnode->next;
}
}


* toooohereree */


HatterSpeak *fs = (HatterSpeak*)malloc(sizeof(HatterSpeak));
fs->oldspeak = "qwe";
fs->hatterspeak = "defef";


uint32_t length = 3;
HashTable *ht = ht_create(length);
for(uint32_t i = 0; i<ht->length;i++)
{
ht->heads[i] = NIL;
}


//if(ht_insert(ht,ds) != NULL){

ht_insert(ht,ds);
printf("hashed %s", ht->heads[1]->gs->oldspeak);
ht_insert(ht,ds);
printf("hashed %s", ht->heads[1]->gs->oldspeak);


ht_insert(ht,fs);
printf("hashed %s", ht->heads[1]->gs->oldspeak);

ht_insert(ht,ss);
printf("hashed %s", ht->heads[0]->gs->oldspeak);


//}
//if(move_to_front == 1)
//{
 //  printf("moved to front of list: %s", foundnode->gs->oldspeak);
//}
//}


//printf("\n did i delete%s", head->gs->oldspeak);
///printf("\n did i delete%s", node->gs->oldspeak);
//free(node->gs);
//ll_delete(node);
///if(node->gs->oldspeak == NIL)
//{
//node = NIL;
///printf("\nthe entire list has been deleted"); 
//}*/
return 0;
}
