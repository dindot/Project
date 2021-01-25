#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

Word *word_create(uint8_t *syms, uint64_t len) {

  Word *wrd = (Word *)calloc(sizeof(Word), 1);
  if (wrd == NULL)
    return (Word *)NULL;

  wrd->len = len;
  wrd->syms = (uint8_t *)malloc(sizeof(syms) * len);
  if (wrd->syms == NULL)
    return (Word *)NULL;

  return wrd;
}

Word *word_append_sym(Word *w, uint8_t sym) {

  Word *rw = NULL;

  if (w != (Word *)NULL) {
    w->syms = (uint8_t *)realloc(w->syms, w->len + 1);
    if (w->syms != (uint8_t *)NULL)
      w->syms[w->len] = sym;

    rw = word_create(w->syms, w->len);
  }

  if (w != (Word *)NULL) {
    if (w->len == 0) {
      rw->syms = (uint8_t *)malloc(sizeof(w->syms) * 1);
      if (rw->syms != (uint8_t *)NULL)
        rw->syms[0] = sym;
    }
  }
  return rw;
}

void word_delete(Word *w) {
  free(w);
  w = (Word *)NULL;
}

WordTable *wt_create(void) {

  WordTable *wt = (WordTable *)calloc(MAX_CODE - 1, sizeof(Word));
  Word *word = word_create(0, 0);
  if (wt != (WordTable *)NULL)
    wt[EMPTY_CODE] = word;
  return wt;
}

void wt_reset(WordTable *wt) {
  for (uint16_t i = 2; i < MAX_CODE - 1; i++) {
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
