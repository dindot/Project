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
//if(n->code != (uint16_t)NULL)
//{
free(n);
n = NULL;
//}
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
while(curr->code != (uint16_t)NULL)
{
if( curr->children[i]->code!= (uint16_t)NULL)
{
next = curr->children[i];

curr->code = (uint16_t)NULL;

curr = next;

//if(curr->code != (uint16_t) NULL)
//printf("%hu", curr->code);

}

//for(int i =0; i < ALPHABET; i++){

if(curr->children[i] == (TrieNode*)NULL)
{
curr->code = (uint16_t)NULL;
}

//else
//{
//curr->code = (uint16_t)NULL;
//}
}
}

}





void trie_delete(TrieNode *n)
{
TrieNode *root = n;
TrieNode *prev = n;
int i = 0;
while(n->children[i] != NULL)
{
n = n->children[i];
if(n->children[i] != NULL)
{
 prev = n;
}
}
while(n->children[i] == NULL)
{
trie_node_delete(n->children[i]);
trie_node_delete(prev);
}
trie_node_delete(root);
}
