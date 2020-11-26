#include "hs.h"
#include <stdlib.h>
#include <string.h>

HatterSpeak *hs_create(char* oldspeak, char* hatterspeak) {
  HatterSpeak *gs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  strcpy(gs->oldspeak, oldspeak);
   strcpy(gs->hatterspeak, hatterspeak);

//gs->oldspeak = oldspeak;
  //gs->hatterspeak = hatterspeak;
  return gs;
}

void hs_delete(HatterSpeak *gs)
{
  free(gs);
}
