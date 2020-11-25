#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "bf.h"
#include "ll.h"
#include "hs.h"
#include "hash.h"
#include "parser.h"

#define CONTRACTIONS "[a-zA-Z0-9]*[-_']*[a-zA-Z0-9]"


void linked_helper(ListNode **nodes, HashTable *ht);



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


// insert and printing from hashtable

//if(ht_insert(ht,ds) != NULL){

/*ht_insert(ht,ds);
printf("hashed %s", ht->heads[1]->gs->oldspeak);
ht_insert(ht,ds);
printf("hashed %s", ht->heads[1]->gs->oldspeak);


ht_insert(ht,fs);
printf("hashed %s", ht->heads[1]->gs->oldspeak);

ht_insert(ht,ss);
printf("hashed %s\n", ht->heads[0]->gs->oldspeak);

linked_helper(ht->heads, ht);
//printf("hashed %s", ht->heads[1]->gs->oldspeak);

*/



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
//
//
//
//
//
//
//
//
//
FILE* file = fopen("oldspeak.txt", "r");
if (file == NULL)
{
puts("could not open file!\n");
return -1;
}


//size_t size = 1024;
//char *buffer = (char*)malloc(sizeof(char) * size);
// put each of the lines from file into buffer and print them, use this to put into
// hatter struct
//
/*while(!feof(file))
{

fscanf(file, "%s", buffer);
printf("%s\n", buffer);
printf("%zu\n", sizeof(buffer));
}*/


int returncode;
regex_t regex;
returncode = regcomp(&regex, CONTRACTIONS, 0);
if(returncode)
{
puts("compilation unsuccessful\n");
return -1;
}




// allows for i/o redirection by first letting user type in desired words,
// prints them to stdout, so that when program ./hatter > checker.txt, will
// enter those words into the file for use in the parser using regex

while(!feof(stdin)) // source cited used from lecture 2 notes from Prof Dunne echo program
{
int c = getchar();
putchar(c);
  // keep getting user input until they press ctrl+d to finish, then pass to parser
}
FILE *input_stream = fopen("checker.txt", "r");

if(input_stream == NULL)
{
puts("file was not created");
return -1;
}

//char* matchedword = next_word(input_stream, &regex);
//printf("%s",matchedword);


return 0;
}





void linked_helper(ListNode **nodes, HashTable *ht)
{

for(uint32_t i = 0; i< ht->length; i++)
{

if(nodes[i] != NULL)
{

if(nodes[i]->next == NULL)
{
return;
}
if(nodes[i]->gs->oldspeak == nodes[i]->next->gs->oldspeak)
{
ListNode* repairlink = nodes[i]->next->next;
ll_node_delete(nodes[i]->next);
nodes[i]->next = repairlink;
}
}
}
}

