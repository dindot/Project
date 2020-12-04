#include "trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define EMPTY_CODE 1

TrieNode *trie_node_create(uint16_t code)
{

TrieNode *treenode = (TrieNode*)malloc(sizeof(TrieNode));
if(treenode == NULL)
{
  return (TrieNode*) NULL;
}
for(int i = 0; i < ALPHABET; i++)
{
treenode->children[i] = NULL;
}

treenode->code = code;
return treenode;
}

void trie_node_delete(TrieNode *n)
{
free(n);
n = NULL;
}

TrieNode *trie_create(void)
{
TrieNode *root_node = trie_node_create(EMPTY_CODE);
return root_node;
}

void trie_reset(TrieNode *root)
{

TrieNode *next = root;

uint16_t checkcode = 0;

for(int i = 0; i < ALPHABET; i++){
TrieNode *curr = root->children[i];
if(curr->children[i] == (TrieNode*)NULL)
{
curr->code = (uint16_t)NULL;
}

while(curr->code != (uint16_t)NULL)
{
if( curr->children[i]->code!= (uint16_t)NULL)
{
next = curr->children[i];

curr->code = (uint16_t)NULL;

curr = next;
}
if(curr->children[i] == (TrieNode*)NULL)
{
curr->code = (uint16_t)NULL;
}
}
}
}


void trie_delete(TrieNode *n)
{


TrieNode *next = n;

uint16_t checkcode = 0;

for(int i = 0; i < ALPHABET; i++){
TrieNode *curr = n;
TrieNode *temp = curr;
/*if(curr->children[i] == (TrieNode*)NULL)
{
curr->code = (uint16_t)NULL;

if(curr!= NULL)
trie_node_delete(curr);
}*/

while(curr->children[i]->code != (uint16_t)NULL)
{
if( curr->children[i]->code!= (uint16_t)NULL)
{
next = curr->children[i];

curr->code = (uint16_t)NULL;
temp = curr;
if(curr != NULL){
trie_node_delete(curr);
}
temp = next;
}
if(temp->children[i]->children[i] == (TrieNode*)NULL)
{
temp->code = (uint16_t)NULL;
if(temp != NULL)
trie_node_delete(temp);
}
}
}
}
