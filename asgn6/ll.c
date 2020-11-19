#include "ll.h"
#include <stdlib.h>


ListNode *ll_node_create(HatterSpeak *gs)
{
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  if(node == NIL)
  {
   return (ListNode*)NIL;
 }
    node->gs->oldspeak = gs->oldspeak;
    node->gs->hatterspeak = gs->hatterspeak;
    node->next = NIL;
 return node; 
}

void ll_node_delete(ListNode *n)
{

free(n->gs);
free(n);

}

void ll_delete(ListNode *head)
{
  
  free(head->gs);
  free(head);

}

ListNode *ll_insert(ListNode **head, HatterSpeak *gs)
{

ListNode *node = ll_node_create(gs);

//ListNode **prev = head;
*(*head)->next = *node;
head = &node;
return *head;  // move the head to point to the new node made, return it
}
