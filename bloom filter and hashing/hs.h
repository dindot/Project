#ifndef __HATTER_H__
#define __HATTER_H__

typedef struct HatterSpeak {
  char *oldspeak;
  char *hatterspeak;
} HatterSpeak;

HatterSpeak *hs_create(char *oldspeak, char *hatterspeak);
void hs_delete(HatterSpeak *gs);

#endif
