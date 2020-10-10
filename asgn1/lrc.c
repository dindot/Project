#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define POT 0;
uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
};

uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
};

int rand_num(int seed);
void play_game(int player, int seed, int arr[], const char *arr2[]);
void die_rules(int play, int times, int seed, const char *arr2[]);


int main(void)
{
  typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
  faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
  const char *names[] = {"Happy", "Sleepy", "Sneezy", "Dopey",
                         "Bashful", "Grumpy", "Doc", "Mirror",
                         "Snow White", "Wicked Queen"};
  int player, seed;

  printf("Random seed: ");
  scanf("%d", &seed);
  
  printf("How many players? ");
  scanf("%d", &player);
  int money_players[player];
  for (int i = 0; i < player; i++)
  {
    money_players[i] = 3;
  }

  
  play_game(player, seed, money_players, names);  
  
   

  return 0;
}

int rand_num(int seed)
{
  int rand_val;
  srand(seed);
  rand_val = (rand() % 6);
  return rand_val;
}

void play_game(int player, int seed, int money_players[], const char *names[])
{
  int play_pos = 0;
  if (money_players[play_pos] >= 3)
  {
    die_rules(play_pos, 3, seed, names);
  }    
}

void die_rules(int play, int times, int seed, const char *names[])
{
 for (int i = 0; i < times; i++)
 {
   int dice_num = rand_num(seed);
   printf("%s", names[0] );
 }
 
}
