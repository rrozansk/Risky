/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/26/17
 Edited:  4/1/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
//#include <board.h>
#include <deck.h>
#include <ini.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/

/*
typedef struct conf {      // conf file headers
  char hp;                 // [Players]
  char cp;                 // [Players]
  char randRegion;         // [Random]
  char randArmies;         // [Random]
  char chromosomes[8][10]; // [Chromosomes] 
  char sets;               // tracks # sets traded in
  char err[160];           // error msg if parse failure
} conf_t;


// [over]write a conf file reflecting the current games configuration
void writeINI(ini_t *conf, char *fname) {
  FILE *fp = fopen(fname, "w+"); // w+ overwrite files
  if(!fp) { 
    sprintf(conf->err, "error! failure to open conf file: %s, exiting...\n", fname); 
    return;
  }

  fprintf(fp,
   "; type := int (0-8)\n"
   "; keys:\n"
   ";   - human:    [number of human players]\n"
   ";   - computer: [number of computer players]\n"
   "[Players]\n"
   "human=%d\n"
   "computer=%d\n\n"
   
   "; type := bool (0/1)\n"
   "; keys:\n"
   ";   - regions: [randomly distribute the regions among the players]\n"
   ";   - armies:  [randomly distribute armies among the players regions]\n"
   "[Random]\n"
   "regions=%d\n"
   "armies=%d\n\n"
   
   "; type := char[10]\n"
   "; keys:\n"
   ";   - offense:     [world domination speed]\n"
   ";   - defence:     [building up troops]\n"
   ";   - armies:      [higher number of troops]\n"
   ";   - continents:  [continent bonuses]\n"
   ";   - card_b:      [card bonus]\n"
   ";   - troop_b:     [troop bonus]\n"
   ";   - claim:       [region placement at game start]\n"
   ";   - troops:      [troop placement at game start]\n"
   ";   - takeover:    [overtaking opponents for cards]\n"
   ";   - borders:     [fority borders]\n"
   "[Chromosomes]\n",
    conf->hp, conf->cp, conf->randRegion, conf->randArmies);

  char c, i;
  for(c = 0; c < 8; c++) { // FIXME: const @CHROMOSOMES?
    fprintf(fp, "c%d={", c);
    for(i = 0; i < 10; i++) { // FIXME: const @ATTRIBUTES?
      fprintf(fp, "%d", conf->chromosomes[c][i]);
      if(i < 9) { fprintf(fp, ","); }
    }
    fprintf(fp, "}\n");
  }

  if(fclose(fp)) {
    sprintf(conf->err, "error! failure to close conf file: %s, exiting...\n", fname);
    return;
  }

  return;
}

// read in and error check a conf file to configure the current game
// FIXME: parse into hash of hashes? hash section to key tbl which has key/vals
int parseConf(conf_t *conf, char *fname) {
  FILE *fp = fopen(fname, "r"); // r reads files
  if(!fp) { 
    sprintf(conf->err, "error! failure to open conf file: %s, exiting...\n", fname); 
    return 1;
  }

  //   ::INI config file BNF::
  // <comment>   := ; <char>*<newline>
  // <char>      := a-z | A-Z | 0-9
  // <newline>   := \n
  // <header>    := [<char>+]<newline>
  // <key/val>   := <char>+=<char>+<newline>
  // NOTE: ignore all white space except newlines
  char input;
  while(0) { //input = getchar()) { // read until EOF
    switch(input) {
      case ';': while(input != '\n') { getchar(); } break;               // comment
  //    case '[': for(i = 0; input != ']'; i++) { header[i] = getchar(); } break; // section header
      default:                                                           // key,val pr
        // leading white space and key value pr parseing

        break;
    }
  }

  if(fclose(fp)) {
    sprintf(conf->err, "failure to close conf file: %s, exiting...\n", fname);
    return 1;
  }
    
  // error checking conf
  if(conf->hp < 0) {
    sprintf(conf->err, "invalid input [humans], expected 0-8, given: %d\n", conf->hp);
    return 1;
  }

  if(conf->cp < 0) {
    sprintf(conf->err, "invalid input [computers], expected 0-8, given: %d\n", conf->cp);
    return 1;
  }

  if(!conf->hp && !conf->cp) {
    sprintf(conf->err, "you cannot play a game with no players\n");
    return 1;
  }

  if(conf->hp + conf->cp > 8) {
    sprintf(conf->err, "you cannot have more than 8 players in a single game\n");
    return 1;
  }

  if(!(conf->randRegion == 0 || conf->randRegion == 1)) {
    sprintf(conf->err, "invalid input [regions], expected 0-1, given: %d\n", conf->randRegion);
    return 1;
  }

  if(!(conf->randArmies == 0 || conf->randArmies== 1)) {
    sprintf(conf->err, "invalid input [armies], expected 0-1, given: %d\n", conf->randArmies);
    return 1;
  }

  return 0;
}

*/


// attack a given territory
char attack(region_t attacker, region_t defender, unsigned char soilders);

// defend against attackers
void defend(int soilders) { }

// move troops from any src territory to any reachable dest territory
void maneuver(region_t src, region_t dest, unsigned short soilders) {
  // check reachability
  // manipulate map
}

//void claimRegions() {  }
//void setDefenses() {  }

// the main game. set up regions and armies then take turns until 1 person left
void risk(ini_t *conf) {
  // error check config is valid or not
  //claimRegions(hp, cp, randomRegions);
  //setDefenses(hp, cp, randomArmies);
  //while ((cp + hp) > 1) {
  // 1) calculate troop bonus
  // 2) trade in cards if applicable (>= 5 must trade)
  // 3) place troops
  // 4) attack(s)
  //   a) move troops
  //   b) overtaking opponent
  // 5) manuver
  //}
}

// print out version information, attempt to parse conf and play risk.
// rewrite conf after game in case computers dna/chromosomes changed
int main(int argc, char *argv[]) {
  printf("Risky\nv1.0\nRyan Rozanski\n\n");

  if(argc != 2) {
    printf("error! must specify a conf file, exiting...\n");
    exit(EXIT_FAILURE);  
  }
  
  ini_t *ini = parseINI(argv[1]);
  if(!ini) {
    printf("error! failure to parse cond file: %s, exiting...\n", argv[1]);
    free(ini);
    exit(EXIT_FAILURE);  
  }

  risk(ini);

  writeINI(ini, argv[1]);

  exit(EXIT_SUCCESS);
}
