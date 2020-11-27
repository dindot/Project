#include "hs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HatterSpeak *hs_create(char *oldspeak, char *hatterspeak) {
  HatterSpeak *gs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  gs->oldspeak = malloc(100);
  gs->hatterspeak = malloc(100);
   if(oldspeak != (char*)(NULL))
  strcpy(gs->oldspeak, oldspeak);
   else
   gs->oldspeak = (char*)NULL;
  if (hatterspeak != (char*)(NULL))
    strcpy(gs->hatterspeak, hatterspeak);
  else
    gs->hatterspeak = (char*)NULL;
  return gs;

}

void hs_delete(HatterSpeak *gs) {
  free(gs->oldspeak);
  free(gs->hatterspeak);
  free(gs);
}
