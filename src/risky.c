/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/26/17
 Edited:  3/27/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
//#include <board.h>
#include <deck.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// attack a given territory
char attack(region_t attacker, region_t defender, unsigned char soilders);

// defend against attackers
void defend(int soilders) { }

// move troops from any src territory to any reachable dest territory
void maneuver(region_t src, region_t dest, unsigned short soilders) {
  // check reachability
  // manipulate map
}

void takeTurn(int player) {
  // 1) calculate troop bonus
  // 2) trade in cards if applicable (>= 5 must trade)
  // 3) place troops
  // 4) attack(s)
  //   a) move troops
  //   b) overtaking opponent
  // 5) manuver
}

int main(int argc, char *argv[]) {
  printf("Risky\nv1.0\nRyan Rozanski\n\n");

  if(argc != 5) {
    printf("Incorrect nubmer of arguments to %s\n", argv[0]);
    printf("%d given, %d expected:\n", argc-1, 4);
    printf("[int 0-8] Human Players\n");
    printf("[int 0-8] Computer Players\n");
    printf("[int 0-1] Randomly divide up territories\n");
    printf("[int 0-1] Randomly divide up armies\n");
    printf("exiting...\n");
    exit(EXIT_FAILURE);
  }

  int hp = atoi(argv[1]);
  int cp = atoi(argv[2]);
  if(!hp && !cp) {
    printf("error! you cannot play a game with no players. exiting...\n");
    exit(EXIT_FAILURE);
  }

  if(hp + cp > 8) {
    printf("error! you cannot have more than 8 players in a single game. exiting...\n");
    exit(EXIT_FAILURE);
  }

  int randomRegions = atoi(argv[3]);
  if(!(randomRegions == 0 || randomRegions == 1)) {
    printf("error! invalid input, expected 0-1, given: %d. exiting...\n", randomRegions);
    exit(EXIT_FAILURE);  
  }

  int randomArmies = atoi(argv[4]);
  if(!(randomArmies == 0 || randomArmies== 1)) {
    printf("error! invalid input, expected 0-1, given: %d. exiting...\n", randomArmies);
    exit(EXIT_FAILURE);  
  }

  //claimRegions(hp, cp, randomRegions);
  //setDefenses(hp, cp, randomArmies);
  //while ((cp + hp) > 1) {
  //  takeTurn(player % 5);
  //}

  exit(EXIT_SUCCESS);
}
