#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int POT =  0;
typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
};

uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
};

int rand_num(int seed);
void play_game(int player, int seed, int arr[], const char *arr2[], faces die[], int play_pos);
void die_rules(int play, int times, int seed, const char *arr2[], faces die[], int player, int money_players[]);

const char* die_choice(int die_roll);

int main(void)
{
  
  faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
  const char *names[] = {"Happy", "Sleepy", "Sneezy", "Dopey",
                         "Bashful", "Grumpy", "Doc", "Mirror",
                         "Snow White", "Wicked Queen"};
  int player, seed, play_pos = 0;

  printf("Random seed: ");
  scanf("%d", &seed);
  
  printf("How many players? ");
  scanf("%d", &player);
  int money_players[player];
  for (int i = 0; i < player; i++)
  {
    money_players[i] = 3;
  }

  
  play_game(player, seed, money_players, names, die, play_pos);  
  
   

  return 0;
}

int rand_num(int seed)
{
  int rand_val;
  srand(seed);
  rand_val = (rand() % 6);
  return rand_val;
}

void play_game(int player, int seed, int money_players[], const char *names[], faces die[], int play_pos)
{
  int counter = 0;
  while (1)
{
  if (money_players[play_pos] >= 3)
  {
    die_rules(play_pos, 3, seed, names, die, player, money_players);
  }
  else if (money_players[play_pos] == 2)
  {
    die_rules(play_pos, 2, seed, names, die, player, money_players);
  }
  else if (money_players[play_pos] == 1)
  {
    die_rules(play_pos, 1, seed, names, die, player, money_players);
  }
  
  play_pos = right(play_pos, player);
  for (int i = 0; i < player; i++)
  { 
    if (money_players[i] == 0)
    {
      counter++;
    }  
  }
  
  if (counter == (player - 1) )
  break;
 }
 
}

void die_rules(int play, int times, int seed, const char *names[], faces die[], int player, int money_players[])
{
  printf("%s" " rolls... " , names[play] );
 
  for (int i = 0; i < times; i++)
 {

   int dice_num = rand_num(seed);
   int  die_value = die[dice_num];
   const char *die_play = die_choice(die_value);
   printf("%s"  "gets a " , die_play );
   
   const char *check_string = "left";
   const char *check_string2 = "right";
   const char *check_string3 = "center";
  const char *check_string4 = "pass";
  // int checker = str_cmp(die_play, check_string);

  if (die_play  == check_string)
  {
   int left_pos =  left(play, player); 
   money_players[left_pos] += 1;
   money_players[play] -= 1; 
  }
  else if (die_play == check_string2)
  {
   int right_pos =  right(play, player);
   money_players[right_pos] += 1;
  }
  else if (die_play == check_string3)
  {
   POT++;
  } 
  
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
