#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int seek = 0; // make these extern later
static int numlinks = 0;
bool move_to_front;
//static bool firstnode = 1;

ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->gs = malloc(sizeof(HatterSpeak));

  if (node == NIL) {
    return (ListNode *)NIL;
  }
  node->gs->oldspeak = malloc(100);
if (gs->oldspeak !=(char*) (NULL))
  strcpy(node->gs->oldspeak, gs->oldspeak);
else
   gs->oldspeak = (char*)NULL;

  node->gs->hatterspeak = malloc(100);
  if (gs->hatterspeak != (char*)(NULL)) {
    strcpy(node->gs->hatterspeak, gs->hatterspeak);

  } else
    gs->hatterspeak = (char*)NULL;

  node->next = NIL;

  return node;
}

void ll_node_delete(ListNode *n) {

  free(n->gs);
  free(n);
}

void ll_delete(ListNode *head) {
  while (head->next != NIL) {
    ll_node_delete(head->next);
    head->next = (head->next)->next;
  }
  ll_node_delete(head);
}

ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  ListNode *node = ll_node_create(gs);

  node->next = *head;

  *head = node;

  return *head; // move the head to point to the new node made, return it
}

ListNode *ll_lookup(ListNode **head, char *key) {
  ++seek;

  ListNode *headswap = *head;
  ListNode *storehead = *head;

  if(strcmp(storehead->gs->oldspeak, key) == 0)
  {
    return storehead;
   }

storehead = storehead->next;
  while (storehead != NIL) {
    if(strcmp(key, storehead->gs->oldspeak) == 0 && move_to_front == 0)
    {
    return storehead;
   }
   else if (strcmp(key, storehead->gs->oldspeak) == 0 && move_to_front == 1)
   {
     HatterSpeak *keydataswap = storehead->gs;
      storehead->gs = headswap->gs;
      headswap->gs = keydataswap;
      return headswap;
    }
    ++numlinks;

    storehead = storehead->next;
    
  }

  return NIL;
}
