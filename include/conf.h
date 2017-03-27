/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  3/27/17
*/

#ifndef RISKY_CONF_DEFS
#define RISKY_CONF_DEFS

char *LABEL_NAMES[5] = {
  "[Human Players]",
  "[Computer Players]",
  "[Random Regions]",
  "[Random Armies]",
  "[Chromosomes]",
};

typedef enum label {
  HUMAN_PLAYER = 0, COMPUTER_PLAYER, RANDOM_REGIONS, RANDOM_ARMIES, CHROMOSOMES,
} label_t;

typedef struct conf {      // conf file headers
  char hp;                 // [Human Players]
  char cp;                 // [Computer Players]
  char randRegion;         // [Random Regions]
  char randArmies;         // [Random Armies]
  char sets;               // tracks # sets traded in
  // deck_t deck = newDeck();
  char chromosomes[8][10]; // [Chromosomes] 
  char err[320];           // error msg if parse failure
} conf_t;

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/
char parseConf(conf_t *conf, char *fname);
void writeConf(conf_t *conf, char *fname);

#endif
