#include "ll.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int seek = 0;  // make these extern later
static int numlinks = 0;
bool move_to_front;
static bool firstnode = 1;

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
 while(head->next != NIL)
 {
     ll_node_delete(head->next);
      head->next = (head->next)->next;
      
  }
 ll_node_delete(head);
}




ListNode *ll_insert(ListNode **head, HatterSpeak *gs)
{

//if(ll_lookup(head, gs->oldspeak) == NIL)
//{

//firstnode = 0;
//printf("checking nodde %s", checknode->gs->oldspeak);}
//if(strcmp(checknode->gs->oldspeak, gs->oldspeak) != 0)
//{
ListNode *node = ll_node_create(gs);

node->next = *head;

*head = node;
printf("bool val %d", firstnode);

//}
return *head;  // move the head to point to the new node made, return it


}


ListNode* ll_lookup(ListNode **head, char *key)
{
  ++seek;
  printf("     %s   ", (*head)->gs->oldspeak);
 ListNode * storehead = *head; 
  while((*head)->next != NIL)
  {
    ++numlinks;
    *head = (*head)->next;
      printf("the next val     %s   ", (*head)->gs->oldspeak);
      printf(" the key %s",key);
    if ((*head)->gs->oldspeak == key && move_to_front == 0)
    {
       return *head;
    }
   
  else if ((*head)->gs->oldspeak == key && move_to_front == 1)
    {
      HatterSpeak *keydataswap = (*head)->gs;
      (*head)->gs =  storehead->gs;
      (storehead)->gs = keydataswap;
     return storehead;
}

}

return NIL;
}
