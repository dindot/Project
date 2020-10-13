#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int POT =  0;
int PLAYERSIN = 0;
typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;

uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
};

uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
};

int rand_num();
void play_game(int seed, int arr[], const char *arr2[], faces die[], int play_pos, int player);
void die_rules(int play, int times, int seed, const char *arr2[], faces die[], int money_players[], int player);
void  player_in_checker(int playercash, int currentcash);
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
  srand(seed);

  printf("How many players? ");
  scanf("%d", &player);
  PLAYERSIN = player;
  int money_players[player];
  for (int i = 0; i < player; i++)
  {
    money_players[i] = 3;
  }

  
  play_game(seed, money_players, names, die, play_pos, player);  
  
   

  return 0;
}

int rand_num()
{
  int rand_val;
  rand_val = (rand() %(6));
  return rand_val;
}

void play_game( int seed, int money_players[], const char *names[], faces die[], int play_pos, int player)
{
  int counter = 0, record_spot = 0;
  while (1)
{
  if (money_players[play_pos] >= 3)
  {
    die_rules(play_pos, 3, seed, names, die,  money_players, player);
    play_pos = right(play_pos, player);
  }
  else if (money_players[play_pos] == 2)
  {
    die_rules(play_pos, 2, seed, names, die, money_players, player);
     play_pos = right(play_pos, player);
  }
  else if (money_players[play_pos] == 1)
  {
   ++PLAYERSIN;
    die_rules(play_pos, 1, seed, names, die, money_players, player);
    play_pos = right(play_pos, player); 
  }
  else if (money_players[play_pos] == 0)
  {
   --PLAYERSIN;
    play_pos = right(play_pos, player);
  }
  
  
   for (int i = 0; i < player; i++)  // or change to player
  { 
    if (money_players[i] >  0)
    { 
      record_spot = i;
    }
   
    }

 if (PLAYERSIN == 0 )
  {
  printf("%s wins the $%d pot with $%d left in the bank!", names[record_spot], POT, money_players[record_spot]);
  break;
  }  
  
 
}
 // printf("%s wins the $%d", names[record_spot], POT);
}

void die_rules(int play, int times, int seed, const char *names[], faces die[], int money_players[], int player)
{

 // printf("%d", PLAYERSIN);
   const char *check_string = "left";
   const char *check_string2 = "right";
   const char *check_string3 = "center";
  const char *check_string4 = "pass";
  printf("%s rolls... " , names[play] );
 
  for (int i = 0; i < times; i++)
 {
   int dice_num = rand_num();
  // printf("%d", dice_num);
   int  die_value = die[dice_num];
   const char *die_play = die_choice(die_value);
  

  // int checker = str_cmp(die_play, check_string);

  if (die_play  == check_string)
  {
   int left_pos =  left(play, player); 
   money_players[left_pos] += 1;
   money_players[play] -= 1;
   player_in_checker(money_players[left_pos], money_players[play]);

   printf("gives $1 to %s " , names[left_pos]); 
  }
  else if (die_play == check_string2)
  {
   int right_pos =  right(play, player);
   money_players[right_pos] += 1;
   money_players[play] -= 1;
 player_in_checker(money_players[right_pos], money_players[play]);
   printf("gives $1 to %s " , names[right_pos]);
  }
  else if (die_play == check_string3)
  {
   POT++;
   money_players[play] -= 1;
 if(money_players[play] == 0)
   { 
    --PLAYERSIN;
   }
   printf("puts $1 in the pot ");
  } 
  else
  {  
     printf( "gets a %s " , die_play);  
  }
}
printf("\n"); 
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


void player_in_checker(int playercash, int currentcash)
{
 if (playercash == 1)
   {
    ++PLAYERSIN;
   }
  // else if (currentcash == 0)
  // {
    // --PLAYERSIN;
  // }
} 
