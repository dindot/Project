#include "hs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HatterSpeak *hs_create(char *oldspeak, char *hatterspeak) {
  HatterSpeak *gs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  gs->oldspeak = malloc(100);
  gs->hatterspeak = malloc(100);
   if(oldspeak != NULL)
  strcpy(gs->oldspeak, oldspeak);
   else
   gs->oldspeak = NULL;
  if (hatterspeak != NULL)
    strcpy(gs->hatterspeak, hatterspeak);
  else
    gs->hatterspeak = NULL;
  return gs;

}

void hs_delete(HatterSpeak *gs) {
  free(gs->oldspeak);
  free(gs->hatterspeak);
  free(gs);
}
