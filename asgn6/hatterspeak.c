#include "bf.h"
#include "hash.h"
#include "hs.h"
#include "ll.h"
#include "parser.h"
#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "mbh:f:s"
#define CONTRACTIONS "[a-zA-Z0-9]*[-_']*[a-zA-Z0-9]"

void file_readin(BloomFilter *bf, HashTable *ht);
void redir_input(BloomFilter *bf, HashTable *ht);
void printer(ListNode *node);
void oldspeakprint(ListNode *node);

bool tofront = 0, nofront = 0, stats = 0, transwords = 0, notrans = 0;

int main(int argc, char **argv) {

  char *input_num = (char *)NULL; // to get user changed values
  int default_hashtable = 10000;
  int default_bloom = 1048576;
  char c; // to obtain user input of choices

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'm':
      tofront = 1;
      move_to_front = 1;
      break;
    case 'b':
      nofront = 1;
      move_to_front = 0;
      break;
    case 'h':
      input_num = optarg;
      default_hashtable
          = atoi(input_num); // when user specified, convert to a int to be used
      break;
    case 'f':
      input_num = optarg;
      default_bloom = atoi(input_num);
      break;
    case 's':
      puts("display stats");
      stats = 1;
      break;
    default:
      printf(
          "Character not found in string"); // if options other than ones supported entered
      return -1;
    }
  }
  if (argc == 1) { // user must supply arguments to run
    printf("No arguments supplied!");
    return -1;
  }

  if (stats == 1) {
    puts("stats are\n");
  }

  if (tofront == 1 && nofront == 1) {
    puts("this combination is not supported!\n");
    return -1;
  }

  BloomFilter *bf = bf_create(default_bloom);
  HashTable *ht = ht_create(default_hashtable);

 HatterSpeak *hs = hs_create((char*)NULL,(char*)NULL);
 ListNode *node = ll_node_create(hs);
  for (uint32_t i = 0; i < ht->length; i++) {
    ht->heads[i] = node;
  }

  file_readin(bf, ht);
  redir_input(bf, ht);
  return 0;
}

void file_readin(BloomFilter *bf, HashTable *ht) {


   FILE *file = fopen("oldspeak.txt", "r");
  if (file == NULL) {
    puts("could not open file!\n");
    return;
  }

  FILE *hatter = fopen("hatterspeak.txt", "r");
  if (hatter == NULL) {
    puts("could not open file!\n");
    return;
  }

  size_t size = 1024;
  char *buffer = (char *)malloc(sizeof(char) * size);
  char *buffer2 = (char *)malloc(sizeof(char) * size);
  // put each of the lines from file into buffer and print them, use this to put into
  // hatter struct

  while (!feof(file)) {

    fscanf(file, "%s", buffer);
    bf_insert(bf, buffer);
   HatterSpeak *gs = hs_create(buffer, (char*)NULL);
   ht_insert(ht, gs);

    //  hs_delete(gs);           // later  might need to delete to put in rest
    //  gs = NULL;
  }

  fclose(file);

  while (!feof(hatter)) {
    fscanf(hatter, "%s\n%s", buffer, buffer2);

    bf_insert(bf, buffer);
    HatterSpeak *gs = hs_create(buffer, buffer2);
    ht_insert(ht, gs);
}
     
  fclose(hatter);
}


void redir_input(BloomFilter *bf, HashTable *ht) {
   HatterSpeak *hs = hs_create((char*)NULL,(char*)NULL);
ListNode *stored_notranswords = ll_node_create(hs); 
ListNode *stored_transwords = ll_node_create(hs);


  int returncode;
  regex_t regex;
  returncode = regcomp(&regex, CONTRACTIONS, REG_EXTENDED);
  if (returncode) {
    puts("compilation unsuccessful\n");
    return;
  }

  while(!feof(stdin))
{
   char *matchedword = next_word(stdin, &regex);
  if(matchedword !=NULL){
  
   for(unsigned long i = 0; i < strlen(matchedword); i++)
  {
   matchedword[i] = tolower(matchedword[i]);
   
   }
   bool passbf = bf_probe(bf, matchedword);
    if(passbf == 1)
    {
    ListNode *node =  ht_lookup(ht, matchedword);

   if(node != NULL && isalpha(node->gs->hatterspeak[0]) != 0)
     {
        transwords = 1;
        ll_insert(&stored_transwords, node->gs);
     }
     else if (node != NULL && isalpha(node->gs->hatterspeak[0]) == 0)
     {
       notrans = 1;
       ll_insert(&stored_notranswords, node->gs);
      }
     else if (node != NULL && (isalpha(node->gs->hatterspeak[0]) == 0 || isalpha(node->gs->hatterspeak[0]) !=0))
     {
       transwords = notrans = 1;
      }
  
     }    

    }  
}
clear_words();

if(transwords == 1 && notrans == 1)
{
printer(stored_notranswords);
printer(stored_transwords);
}
else if (transwords == 1 && notrans == 0)
{
printer(stored_transwords);
}
else if (transwords == 0 && notrans == 1)
{
printer(stored_notranswords);

}

}

void printer(ListNode *node)
{
if((transwords == 1 && notrans == 1) && isalpha(node->gs->hatterspeak[0]) == 0)
{
puts("Dear Comrade,\n");
puts("You have chosen to use words that the queen has decreed oldspeak.");
puts("Due to your infraction you will be sent to the dungeon where you will");
puts("   be taught hatterspeak.\n");
puts("Your errors:\n");

while(node->next != NULL)
{
 printf("%s\n", node->gs->oldspeak);
  node = node->next;
}
}
else if((transwords == 1 && notrans == 1) && isalpha(node->gs->hatterspeak[0]) != 0)
{

puts("\nAppropriate hatterspeak translations.\n");
while(node->next != NULL)
{
 printf("%s -> %s\n", node->gs->oldspeak, node->gs->hatterspeak);
  node = node->next;
}

}

else if(transwords == 1)
{
printf("Dear Wonderlander,\n");
printf("\nThe decree for hatterspeak finds your message lacking. Some of the\n");
printf("   words that you used are not hatterspeak.\n");
puts("The list shows how to turn the oldspeak words into hatterspeak.\n");

while(node->next != NULL)
{
  printf("%s -> %s\n", node->gs->oldspeak, node->gs->hatterspeak);
  node = node->next;
}
}
else if(notrans == 1)
{
oldspeakprint(node);
}
}

void oldspeakprint(ListNode *node)
{

printf("Dear Wonderlander,\n");
printf("\nYou have chosen to use words that the queen has decreed oldspeak.\n");
printf("Due to your infraction you will be sent to the dungeon where you will\n");
printf("   be taught hatterspeak.\n");
puts("\nYour errors:\n");

while(node->next != NULL)
{
        printf("%s\n", node->gs->oldspeak);
             node = node->next;
 }
       }
