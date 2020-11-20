#include "ll.h"
#include <stdlib.h>
#include <stdio.h>

static int seek = 0;  // make these extern later
static int numlinks = 0;
bool move_to_front;

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

ListNode *node = ll_node_create(gs);

node->next = *head;

*head = node;

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
      printf("dfd     %s   ", (*head)->gs->oldspeak);
      printf("%s",key);
    if ((*head)->gs->oldspeak == key && move_to_front == 0)
    {
       return *head;
    }
    
  else if ((*head)->gs->oldspeak == key && move_to_front == 1)
    {
      HatterSpeak *keydataswap = (*head)->gs;
    
     while((*head)->next != NIL)
     {
      ++numlinks;
         *head = (*head)->next;
    printf("   checking move to  %s   ", (*head)->gs->oldspeak);
	 }
        printf("   asdf  %s   ", (*head)->gs->oldspeak);
    

       if((*head)->next == NIL){
      HatterSpeak *tempkeydata = (*head)->gs;
       (*head)->gs = keydataswap;
       keydataswap = tempkeydata;
      //return *head; 	// this is the swapped node (moved it to front)
      return storehead;  // returning to be able to go thru entire list to check
      }
     }

    }
   return NIL;  
}
