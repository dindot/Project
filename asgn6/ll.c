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
  strcpy(node->gs->oldspeak, gs->oldspeak);

  node->gs->hatterspeak = malloc(100);
  if (gs->hatterspeak != NULL) {
    strcpy(node->gs->hatterspeak, gs->hatterspeak);

  } else
    gs->hatterspeak = NULL;

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

  ListNode *storehead = *head;
  if ((*head)->next == NIL && key == (*head)->gs->oldspeak) {
    return *head;
  }
  while ((*head)->next != NIL) {
    ++numlinks;
    *head = (*head)->next;

    if ((*head)->gs->oldspeak == key && move_to_front == 0) {
      return *head;
    }

    else if ((*head)->gs->oldspeak == key && move_to_front == 1) {
      HatterSpeak *keydataswap = (*head)->gs;
      (*head)->gs = storehead->gs;
      (storehead)->gs = keydataswap;
      return storehead;
    }
  }

  return NIL;
}
