#include "hs.h"
#include <stdlib.h>

HatterSpeak *hs_create() {
  HatterSpeak *gs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  gs->oldspeak = "NULL";
  gs->hatterspeak = "NULL";
  return gs;
}
