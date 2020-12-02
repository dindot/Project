#include "trie.h"
#include <stdlib.h>
#include <stdio.h>

#define EMPTY_CODE 1

TrieNode *trie_node_create(uint16_t code)
{

TrieNode *treenode = (TrieNode*)calloc(1, sizeof(TrieNode));
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
if(n != NULL)
{
free(n);
}
}

TrieNode *trie_create(void)
{
TrieNode *root_node = trie_node_create(EMPTY_CODE);
return root_node;
}

void trie_reset(TrieNode *root)
{
for(int i = 0; i < ALPHABET; i++)
{

if(root->children[i]->code != (uint16_t)NULL)  // change to check is null nodes in array too
{
root->children[i]->code = (uint16_t)NULL;
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
