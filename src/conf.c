/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  3/27/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <conf.h>
#include <stdio.h>

/*******************************************************************************

    S T R U C T S

*******************************************************************************/
char *LABEL_NAMES[5] = {
  "[Players]",     // keys: human, computer
  "[Random]",      // keys: region, armies
  "[Chromosomes]"  // keys: cp[chromosome#]
};

typedef enum label {
  HUMAN_PLAYER = 0, COMPUTER_PLAYER, RANDOM_REGIONS, RANDOM_ARMIES, CHROMOSOMES,
} label_t;

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// write out a new conf file with the given name (in case computers dna changed)
void writeConf(conf_t *conf, char *fname) {
  // open file 'conf.c'
  // print header then key:val prs with newline after each
  // final newline
  // etc...
}

// read in a game config with the given name (mostly for computers dna)
char parseConf(conf_t *conf, char *fname) {
  /*
  if(argc != 5) {
    sprintf(conf->err, "\n\nIncorrect number of arguments to %s\n%d given, %d expected:\n[int 0-8] Human Players\n[int 0-8] Computer Players\n[int 0-1] Randomly divide up territories\n[int 0-1] Randomly divide up armies\n", argv[0], argc-1, 4);
    return 1;
  }

  conf->hp = atoi(argv[1]);
  if(conf->hp < 0) {
    sprintf(conf->err, "error! invalid input (arg 1), expected 0-8, given: %d\n", conf->hp);
    return 1;
  }

  conf->cp = atoi(argv[2]);
  if(conf->cp < 0) {
    sprintf(conf->err, "error! invalid input (arg 2), expected 0-8, given: %d\n", conf->cp);
    return 1;
  }

  if(!conf->hp && !conf->cp) {
    sprintf(conf->err, "error! you cannot play a game with no players\n");
    return 1;
  }

  if(conf->hp + conf->cp > 8) {
    sprintf(conf->err, "error! you cannot have more than 8 players in a single game\n");
    return 1;
  }

  conf->randRegion = atoi(argv[3]);
  if(!(conf->randRegion == 0 || conf->randRegion == 1)) {
    sprintf(conf->err, "error! invalid input (arg 3), expected 0-1, given: %d\n", conf->randRegion);
    return 1;
  }

  conf->randArmies = atoi(argv[4]);
  if(!(conf->randArmies == 0 || conf->randArmies== 1)) {
    sprintf(conf->err, "error! invalid input (arg 4), expected 0-1, given: %d\n", conf->randArmies);
    return 1;
  }
  */
  return 0;
}
