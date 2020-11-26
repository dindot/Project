#include "hs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

HatterSpeak *hs_create(char* oldspeak, char* hatterspeak) {
  HatterSpeak *gs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  gs->oldspeak = malloc(100);
  gs->hatterspeak = malloc(100);
  strcpy(gs->oldspeak, oldspeak);
  if(hatterspeak != NULL)
  strcpy(gs->hatterspeak, hatterspeak);
  else
  gs->hatterspeak = NULL;
  return gs;


}

void hs_delete(HatterSpeak *gs)
{
  free(gs->oldspeak);
  free(gs->hatterspeak);
  free(gs);
}