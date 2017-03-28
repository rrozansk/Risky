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
#include <conf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

//void claimRegions() {  }
//void setDefenses() {  }

// the main game. set up regions and armies then take turns until 1 person left
void risk(conf_t *conf) {
   //claimRegions(hp, cp, randomRegions);
  //setDefenses(hp, cp, randomArmies);
  //while ((cp + hp) > 1) {
  //  takeTurn(player % 5);
  //}
}

// print out version information, attempt to parse conf and then play risk.
// rewrite conf after game is over in case computers dna/chromosomes changed
int main(int argc, char *argv[]) {
  printf("Risky\nv1.0\nRyan Rozanski\n\n");

  if(argc != 2) {
    printf("error! must specify a conf file, exiting...\n");
    exit(EXIT_FAILURE);  
  }

  conf_t *conf = malloc(sizeof(conf_t));
  if(!parseConf(conf, argv[1])) { 
    printf("error! %s, exiting...\n", conf->err);
    free(conf);
    exit(EXIT_FAILURE);  
  }

  risk(conf);
  
  if(!writeConf(conf, argv[1])) {
    printf("error! %s, exiting...\n", conf->err);
    free(conf);
    exit(EXIT_FAILURE);  
  }

  free(conf);
  exit(EXIT_SUCCESS);
}
