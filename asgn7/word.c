#include "word.h"
#include <stdio.h>
#include <stdlib.h>
#define EMPTY_CODE 1

Word *word_create(uint8_t *syms, uint64_t len) {

  Word *wrd = (Word *)malloc(sizeof(Word));
  if(wrd == NULL)
  return (Word*)NULL;
  
  wrd->len = len;
  wrd->syms = syms;
  return wrd;
}

Word *word_append_sym(Word *w, uint8_t sym) {

  if (w->syms[0] == (uint8_t)NULL) {

    w->syms[0] = sym;
    w->len = 1;
    return w;
  }
  //printf("len %u\n", w->len);
  w->syms[(w->len)] = sym;
  w->len = ++(w->len);
  //printf("len %u\n", w->len);
  return w;
}

void word_delete(Word *w) {
  free(w);
  w = (Word *)NULL;
}

WordTable *wt_create(void) {

  WordTable *wt = (WordTable *)calloc(UINT16_MAX - 1, sizeof(Word));
  Word *word = word_create(0, 0);
  wt[EMPTY_CODE] = word;
  return wt;
}

void wt_reset(WordTable *wt) {
  for (uint16_t i = 2; i < UINT16_MAX - 1; i++) {
    if (wt[i] != (Word *)NULL) {
      wt[i]->syms = 0;
      wt[i]->len = 0;
    }
  }
}

void wt_delete(WordTable *wt) {
  word_delete(wt[EMPTY_CODE]);

  for (uint16_t i = 2; i < UINT16_MAX - 1; i++) {
    if (wt[i] != (Word *)NULL) {
      word_delete(wt[i]);
    }
  }
  free(wt);

  wt = (WordTable *)NULL;
}
