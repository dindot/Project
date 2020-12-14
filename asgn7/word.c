#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

Word *word_create(uint8_t *syms, uint64_t len) {

  Word *wrd = (Word *)malloc(sizeof(Word));
  if (wrd == NULL)
    return (Word *)NULL;

  wrd->len = len;
  wrd->syms = (uint8_t*)malloc(sizeof(syms) * len);
  if(wrd->syms == NULL)
  return (Word *)NULL;

  return wrd;
}

Word *word_append_sym(Word *w, uint8_t sym) {

/*if(w != (Word*) NULL){
w->syms = (uint8_t*)realloc(w->syms, w->len+1);
w->syms[w->len] = sym;	 
return w;
}
if(sym == 0){
w->syms[0] = sym;

*for(uint32_t i = 0; i < w->len; i++){
 if (w->syms[i] == (uint8_t)NULL) {

    w->syms[i] = sym;
    w->len = 1;
    return w;
  }
}*/
  //printf("len %u\n", w->len);
 // w->syms[(w->len)] = sym;
 // w->len = ++(w->len);
  //printf("len %u\n", w->len);
//  return w;}
printf("syms %d", sym);
if(w == (Word*) NULL)
{
printf("hallo");//Word* y = word_create(w->syms, 1);
}return 0;


//return w;
}

void word_delete(Word *w) {
  free(w);
  w = (Word *)NULL;
}

WordTable *wt_create(void) {

  WordTable *wt = (WordTable *)calloc(MAX_CODE - 1, sizeof(Word));
  Word *word = word_create(0, 0);
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
