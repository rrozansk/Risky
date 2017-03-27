/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/26/17
 Edited:  3/26/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <board.h>
#include <deck.h>
#include <stdio.h>

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// attack a given territory
char attack(region_t attacker, region_t defender, unsigned char soilders);

// defend against attackers
void defend(int soilders) {
  
}

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

int main() {
  printf("\t\t\tRisky");

  //int hp;
  printf("Human players (1-5): ");
  // scanf(%d);

  //int cp;
  printf("Computer players (1-5): ");
  // scanf(%d);

  //int players = hp + cp;

  // divide all territories up (randomly/manual)
  // place all armies (varies depending on # players) (randomly/maual)
 
  //int input; // used to take all menu inputs??
  //while (players > 1) {
    // 1) print map
  //}
  
  return 0;  
}
