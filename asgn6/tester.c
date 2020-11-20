#include <stdlib.h>
#include <stdio.h>
#include "bf.h"
#include "ll.h"
#include "hs.h"

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
HatterSpeak *gs = (HatterSpeak*)malloc(sizeof(HatterSpeak));
gs->oldspeak = "hrmy";
gs->hatterspeak = "benny";
ListNode* node = ll_node_create(gs);
printf("node %s", node->gs->oldspeak);

HatterSpeak *ss = (HatterSpeak*)malloc(sizeof(HatterSpeak));
ss->oldspeak = "redd";
ss->hatterspeak = "defef";
ListNode *head = ll_insert(&node, ss);
printf("head is %s", head->gs->oldspeak);

ListNode* foundnode =  ll_lookup(&head, "redd");
printf("found %s", foundnode->gs->oldspeak);

//free(node->gs);
ll_delete(node);
if(node->gs->oldspeak == NIL)
{
node = NIL;
printf("\nthe entire list has been deleted"); 
}
return 0;
}
