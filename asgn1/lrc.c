#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define POT 0;
typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
};

uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
};

int rand_num(int seed);
void play_game(int player, int seed, int arr[], const char *arr2[], faces die[]);
void die_rules(int play, int times, int seed, const char *arr2[], faces die[]);
const char* die_choice(int die_roll);

int main(void)
{
  
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

  
  play_game(player, seed, money_players, names, die);  
  
   

  return 0;
}

int rand_num(int seed)
{
  int rand_val;
  srand(seed);
  rand_val = (rand() % 6);
  return rand_val;
}

void play_game(int player, int seed, int money_players[], const char *names[], faces die[])
{
  int play_pos = 0;
  if (money_players[play_pos] >= 3)
  {
    die_rules(play_pos, 3, seed, names, die);
  }    
}

void die_rules(int play, int times, int seed, const char *names[], faces die[])
{
  printf("%s" " rolls... " , names[play] );
 
  for (int i = 0; i < times; i++)
 {

   int dice_num = rand_num(seed);
   int  die_value = die[dice_num];
   const char *die_play = die_choice(die_value);
   printf("%s"  "gets a " , die_play );
 }
 
}

const char *die_choice(int die_roll)
{
  switch(die_roll)
  {
    case 0:
      return "left";
      break;
   
    case 1:
      return "right";
      break;
    
    case 2:
      return "center";
      break;
    
    default:
       return "pass";
       break;
  }
}
