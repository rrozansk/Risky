/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/20/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <ini.h>
#include <risky.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************

    T Y P E S

*******************************************************************************/
struct game {
  // PLAYERS
  int hps;             // number of human players
  char **computers;    // ptr to array of cps i.e. isStr(arr[i])
  int cps;             // size of computers
  // TRAINING
  int log;             // turn on/off logging during training exercises
  char *dir;           // directory to put taining logs
  int trains;          // numer of training exercises to perform
  // TROOPS
  int beginning;       // number of troops recieved at game start
  int minimum;         // minimum troop bonus per turn
  int bonus;           // 
  int random;          // 
  // CARDS
  char **cardTypes;    // ptr to array of card types
  int numTypes;        // size of cardTypes
  int wilds;           // number of wilds in the deck
  int *tradeIns;       // ptr to array of trade in bonuses
  int numTrades;       // size of tradeIns
  int tradeIncr;       // constant trade increment once 
  // CHROMOSOMES
  int numChromosomes;  // number of chromosomes in each strand on DNA
  int numTraits;
  int **ais;           // ais[numChromosomes][numTraits]
  char **names;        // names[numChromosomes]
  // MAP
  char **continents;   // ptr to array of continents
  int *contBonuses;    // ptr to array of contnent bonuses
  int numConts;        // size of continents array and contBonuses
  char **countries;    // ptr to array of countries
  int numCountries;    // size of countries array
  int randomCountries; // to split up map randomly or not
  int **board;         // adjacency matrix --> board[numCountries][numCountries];
};

/*******************************************************************************

    S T R U C T S

*******************************************************************************/
typedef struct country {
  int foo;
} country_t;

typedef struct continent {
  char *name;
  char bonus;
} continent_t;

typedef struct card { 
  char *type, *country;
} card_t;

typedef struct deck {
  int foo;
} deck_t;

typedef struct player { 
  char *name;
} player_t;

typedef struct list {
  void *head, *tail;
} list_t;

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
const char *strErrRISKY(errRISKY_t errRISKY) {
  switch(errRISKY) {
    case RISKY_NULL_COUNTRY: return "nil country";
    case RISKY_NULL_TROOPS: return "nil troops";
    case RISKY_NULL_GAME: return "nil game";
    case RISKY_NIL: return "";
    default: return "unrecognized RISKY error code";
  }
}

errRISKY_t makeRISKY(game_t **game) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t freeRISKY(game_t *game) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setHumans(game_t *game, char hps) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setComputers(game_t *game, unsigned char cps, char **computers) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setLogging(game_t *game, unsigned char on, char *dir) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setTraining(game_t *game, unsigned short games) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setTroops(game_t *game, int beginning, int min, int bonus, int rand) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setDeck(game_t *game, int wilds, char **types, int n) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setTrades(game_t *game, int *trades, int n, int incr) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setCps(game_t *game, int **ais, unsigned short chromosomes, unsigned char traits) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setContinents(game_t *game, char **continents, int *bonuses, int n) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setCountries(game_t *game, char **countries, int n, int rand) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t setAdjacencies(game_t *game, int **board, int n) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t isEvolved(game_t *game, char *changed) {
  if(!game) { return RISKY_NULL_GAME; }

  return RISKY_NIL;
}

errRISKY_t risk(game_t *game) {
  if(!game) { return RISKY_NULL_GAME; }

  //errRISKY_t errRISKY = isValid(game);
  //if(errRISKY != RISKY_NIL) { return errRISKY; }

  int i,j;
  printf("{\n");
  for(i = 0; i < game->numCountries; i++) {
    printf("{");
    for(j = 0; j < game->numCountries; j++) {
      printf("%i, ", (game->board)[i][j]);
    }
    printf("}\n");
  }
  printf("}\n");

  return RISKY_NIL;
}
