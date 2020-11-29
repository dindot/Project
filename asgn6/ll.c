#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int avg_seek = 0;  // vars for display stats
int seek = 0; 
int nodes = 0;
bool move_to_front;

ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->gs = malloc(sizeof(HatterSpeak));

  if (node == NIL) {
    return (ListNode *)NIL;
  }
  node->gs->oldspeak = malloc(100);  // to allow to copy new string into it
if (gs->oldspeak !=(char*) (NULL))
  strcpy(node->gs->oldspeak, gs->oldspeak);
else
   gs->oldspeak = (char*)NULL;

  node->gs->hatterspeak = malloc(100);  // to allow to copy new string into it
  if (gs->hatterspeak != (char*)(NULL)) {
    strcpy(node->gs->hatterspeak, gs->hatterspeak);

  } else
    gs->hatterspeak = (char*)NULL;

  node->next = NIL;

  return node;
}

void ll_node_delete(ListNode *n) { 
  hs_delete(n->gs);
  free(n);
}

void ll_delete(ListNode *head) {
  while (head->next != NIL) {  // loop thru deleting each node
    ll_node_delete(head->next);
    head->next = (head->next)->next;
  }
  ll_node_delete(head);
}

ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  ++nodes;
  ListNode *node = ll_node_create(gs);
  
  node->next = *head;

  *head = node;

  return *head; // move the head to point to the new node made, return it
}

ListNode *ll_lookup(ListNode **head, char *key) {
 ++seek;
 
  ListNode *headswap = *head;  // store head for later swaps
  ListNode *storehead = *head;  // use this one to traverse

  if(strcmp(storehead->gs->oldspeak, key) == 0)  // if at first node
  {
    return storehead;
   }

storehead = storehead->next;

  while (storehead != NIL) {  // keep traversing nodes until key found or not
    if(strcmp(key, storehead->gs->oldspeak) == 0 && move_to_front == 0)
    {
    return storehead;
   }
   else if (strcmp(key, storehead->gs->oldspeak) == 0 && move_to_front == 1)
   {
     HatterSpeak *keydataswap = storehead->gs; // when key found swap it to the front of list
      storehead->gs = headswap->gs;
      headswap->gs = keydataswap;
      return headswap;
    }
    

    storehead = storehead->next;
    ++avg_seek; 
  }
  return NIL;  // the node was not found in list

}
