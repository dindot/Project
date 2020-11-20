#include "ll.h"
#include <stdlib.h>
#include <stdio.h>
static int seek = 0;
static int numlinks = 0;

ListNode *ll_node_create(HatterSpeak *gs)
{
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->gs = malloc(sizeof(HatterSpeak));
 
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
//  ListNode *prevnode = head->next;
 // ListNode *curr = head;
 // while(curr->next != NIL)
 // { 
  // curr = (head->next->next);
  // ll_node_delete(prevnode);
  // head->next = prevnode->next;
 // }
 // ll_node_delete(curr);
 //
 
 while(head->next != NIL)
 {
     ll_node_delete(head->next);
      head->next = (head->next)->next;
      
   
    
  }
 ll_node_delete(head);
}

ListNode *ll_insert(ListNode **head, HatterSpeak *gs)
{

ListNode *node = ll_node_create(gs);

//ListNode **prev = head;
(*head)->next = node;
//head = &node;
return *head;  // move the head to point to the new node made, return it
}

ListNode* ll_lookup(ListNode **head, char *key)
{
 ++seek;
 while( (*head)->next != NULL)
  {
   head = &((*head)->next);
   ++numlinks;
   if( (*head)->gs->oldspeak == key)
   {
     return *head;
   }

  }
return *head;

}
