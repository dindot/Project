#include "trie.h"
#include "code.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {

  TrieNode *treenode = (TrieNode *)malloc(sizeof(TrieNode));
  if (treenode == (TrieNode *)NULL) {
    return (TrieNode *)NULL;
  }
  for (int i = 0; i < ALPHABET; i++) {
    treenode->children[i] = (TrieNode *)NULL;
  }

  treenode->code = code;
  return treenode;
}

void trie_node_delete(TrieNode *n) {
  free(n);
  n = (TrieNode *)NULL;
}

TrieNode *trie_create(void) {
  TrieNode *root_node = trie_node_create(EMPTY_CODE);
  return root_node;
}

void trie_reset(TrieNode *root) {

  TrieNode *next = root;

  for (int i = 0; i < ALPHABET; i++) {
    TrieNode *curr = root->children[i];
    if (curr->children[i] == (TrieNode *)NULL) {
      curr->code = (uint16_t)NULL;
    }

    while (curr->code != (uint16_t)NULL) {
      if (curr->children[i]->code != (uint16_t)NULL) {
        next = curr->children[i];

        curr->code = (uint16_t)NULL;

        curr = next;
      }
      if (curr->children[i] == (TrieNode *)NULL) {
        curr->code = (uint16_t)NULL;
      }
    }
  }
}

void trie_delete(TrieNode *n) {

  TrieNode *next = n;
  for (int i = 0; i < ALPHABET; i++) {
    TrieNode *curr = n->children[i];
    if (curr->children[i] == (TrieNode *)NULL) {
      curr->code = (uint16_t)NULL;
      trie_node_delete(curr);
    }

    while (curr != (TrieNode *)NULL) {
      next = curr->children[i];

      curr->code = (uint16_t)NULL;
      trie_node_delete(curr);
      curr = next;
      if (curr == (TrieNode *)NULL) {
        trie_node_delete(curr);
      }
    }
  }
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  TrieNode *curr = n->children[sym];
  if (curr == (TrieNode *)NULL) {
    return (TrieNode *)NULL;
  }

  if (curr != (TrieNode *)NULL) {

    return curr;
  }
  return n;
}
