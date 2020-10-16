#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int POT = 0;
static int PLAYERSIN = 0;
typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;

// return unsigned 32 bit int of position of
// player to left of current player
// input the current player pos, as unsigned
// 32 bit int, total players, as unsigned 32 bit int
//
uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

// return unsigned 32 bit int of position of
// player to right of current player
// input the current player pos, as unsigned
// 32 bit int, total players, as unsigned 32 bit int
//
uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
}

// returns as int a random number from 0-5
//
int rand_num();

// void function, allows to play game after initial seed and total players input by user
// money_players[]: array of type int, holds the current cash of all players playing
// names[]: array of pointers to constant char, allows for retrieval of player names
// die[]: array of the enum type faces, stored the values of the die (L, R, C, P, P, P)
// play_pos: stores as int position of the player currently playing
// player: stores as int the total number of players playing the game
//
void play_game(int money_players[], const char *names[], faces die[],
               int play_pos, int player);
// void function to implement the rules of the game, by giving each player rolls based on money
// times: the number of rolls that the player gets based on current money
//
void die_rules(int play, int times, const char *names[], faces die[],
               int money_players[], int player);

// void function to check how many players are still in the game based on add/removed cash
// playercash: total amount of cash player currently has as int
//
void player_in_checker(int playercash);

// die_choice returns pointer to constant char which is acutal c string value of value on die
// die_roll: stores as int  the number 0-5
const char *die_choice(int die_roll);

int main(void) {
  faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS }; // array die of enum type faces
  const char *names[] = { "Happy", "Sleepy", "Sneezy", "Dopey", // names of the max 10 players
                          "Bashful", "Grumpy", "Doc", "Mirror", "Snow White", "Wicked Queen" };
  int player, seed, play_pos = 0;

  // take in user input of seed, players to be able to start game
  printf("Random seed: ");
  scanf("%d", &seed); // random seed value, user input allow same pseudorandom sequence
  srand(seed);

  printf("How many players? ");
  scanf("%d", &player);
  while (player <= 1 || player > 10) { // user input validation to meet game specs
    printf("Enter valid number of players, must be at least 2 players, max 10 ");
    scanf("%d", &player);
  }

  PLAYERSIN = player;
  int money_players[player];
  for (int i = 0; i < player; i++) {
    money_players[i] = 3; // initialize array with 3 dollars for each player
  }

  play_game(money_players, names, die, play_pos, player); // starts the game

  return 0;
}

// must mod by 6 in order to get a random value in proper range to match die sides
//
int rand_num() {
  int rand_val;
  rand_val = (rand() % (6));
  return rand_val;
}

// game is an infinite loop until condition of only one player with money
void play_game(int money_players[], const char *names[], faces die[],
               int play_pos, int player) {

  int record_spot = 0; // keep track of only player left in game with cash

  while (1) {
    if (money_players[play_pos] >= 3) { // player has $3 or more in bank

      die_rules(play_pos, 3, names, die, money_players, player); // allow to roll 3 times
      play_pos = right(play_pos, player); // move on to the next player, right of current
    } else if (money_players[play_pos] == 2) { // player has $2 in bank
   
      die_rules(play_pos, 2, names, die, money_players,
          player); // allow to roll 2 times
      play_pos = right(play_pos, player);
    } else if (money_players[play_pos] == 1) { // player only has $1 in bank
   
      ++PLAYERSIN; // account for players being at $0 then coming back to $1
      die_rules(play_pos, 1, names, die, money_players, player); // allow to roll once
      play_pos = right(play_pos, player);
    } else if (money_players[play_pos] == 0) { // player has no money left
 
      --PLAYERSIN; // this player is "out"
      play_pos = right(play_pos, player);
    }

    for (int i = 0; i < player; i++) { // checks to see what player is the only one w money left
      if (money_players[i] > 0) {
        record_spot = i; // store index of the player
      }
    }

    if (PLAYERSIN == 0) { // check if only 1 player left, comparing to 0 because of double counting
      printf("%s wins the $%d pot with $%d left in the bank!", names[record_spot],
              POT, money_players[record_spot]); // displays winner, using index to get correct name
      break;
    }
  }
}

// checks all c string values on die matching the random roll each player gets
//
void die_rules(int play, int times, const char *names[], faces die[],
               int money_players[], int player) {
  // c string checkers for comparison of die values
  const char *check_string = "left";
  const char *check_string2 = "right";
  const char *check_string3 = "center";

  printf("%s rolls... ", names[play]); // current player rolling the dice

  for (int i = 0; i < times; i++) { // number of rolls depends on cash

    int dice_num = rand_num(); // get a random number each roll and map to array
    int die_value = die[dice_num];
    const char *die_play = die_choice(die_value); // get the value rolled on dice

    if (die_play == check_string) { // checking for value of left
    
      int left_pos = left(play, player); // get position of player to left of current player
      money_players[left_pos] += 1; // increment left player money by 1
      money_players[play] -= 1; // decrement current player money by 1
      player_in_checker(money_players[left_pos]); // check if players join back
      printf("gives $1 to %s ", names[left_pos]); // display the ammount given to left player
    } else if (die_play == check_string2) { // checking for value of right

      int right_pos = right(play, player); // get position of player to right of current player
      money_players[right_pos] += 1; // increment right player money by 1
      money_players[play] -= 1; // decrement current player money by 1
      player_in_checker(money_players[right_pos]);
      printf("gives $1 to %s ", names[right_pos]); // display amount given to right player
    } else if (die_play == check_string3) { // checking for value of center
    
      POT++; // money gets placed into the center pot
      money_players[play] -= 1;
      if (money_players[play] == 0) { // check if the players goes "out"
      
        --PLAYERSIN;
      }
      printf("puts $1 in the pot ");
    } else { // if the roll is a pass
   
      printf("gets a %s ", die_play);
    }
  }
}

// maps int value of random roll to return c strings, to be compared to proper die rule
//
const char *die_choice(int die_roll) {
  switch (die_roll) {
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

// for checking if player who might have been at $0 got an increment, so they are back in
void player_in_checker(int playercash) {
  if (playercash == 1) {
    ++PLAYERSIN;
  }
}
