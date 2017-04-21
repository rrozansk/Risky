/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/21/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <ini.h>
#include <risky.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************

    T Y P E S

*******************************************************************************/
struct game {
  // PLAYERS
  unsigned char hps;             // number of human players
  char **computers;              // ptr to array of cps i.e. isStr(arr[i])
  unsigned char cps;             // size of computers
  // TRAINING
  unsigned char log;             // turn on/off logging during training exercises
  char *dir;                     // directory to put taining logs
  unsigned short trains;         // numer of training exercises to perform
  // TROOPS
  unsigned char beginning;       // number of troops recieved at game start
  unsigned char minimum;         // minimum troop bonus per turn
  unsigned char bonus;           // 
  unsigned char random;          // 
  // CARDS
  char **cardTypes;              // ptr to array of card types
  unsigned char numTypes;        // size of cardTypes
  unsigned char wilds;           // number of wilds in the deck
  unsigned char *tradeIns;       // ptr to array of trade in bonuses
  unsigned char numTrades;       // size of tradeIns
  unsigned char tradeIncr;       // constant trade increment once 
  // CHROMOSOMES
  unsigned char chromosomes;     // number of chromosomes in each strand on DNA
  unsigned char traits;
  unsigned char **ais;           // ais[numChromosomes][numTraits]
  char **names;                  // names[numChromosomes]
  // MAP
  char **continents;             // ptr to array of continents
  unsigned char *contBonuses;    // ptr to array of contnent bonuses
  unsigned char numConts;        // size of continents array and contBonuses
  char **countries;              // ptr to array of countries
  unsigned char numCountries;    // size of countries array
  unsigned char randomCountries; // to split up map randomly or not
  unsigned char **board;         // adjacency matrix --> board[numCountries][numCountries];
  // PRIVATE (NOT SETTABLE THROUGH API)
  unsigned char evolved;         //
};

/*******************************************************************************

    S T R U C T S

*******************************************************************************/
typedef struct country { } country_t;
typedef struct continent { } continent_t;
typedef struct card { } card_t;
typedef struct deck { } deck_t;
typedef struct player { } player_t;

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
const char *strErrRISKY(errRISKY_t errRISKY) {
  switch(errRISKY) {
    case RISKY_NULL_COUNTRY: return "nil country";
    case RISKY_NULL_TROOPS: return "nil troops";
    case RISKY_NULL_GAME: return "nil game";
    case RISKY_OUT_OF_MEMORY: return "out of memory";
    case RISKY_INVALID_HPS: return "number of human players must be 0-8";
    case RISKY_INVALID_CPS: return "number of computer players must be 0-8";
    case RISKY_INVALID_COMPUTERS: return "nil computers";
    case RISKY_NULL_COMPUTERS: return "nil computers";
    case RISKY_NULL_DIR: return "nil logging directory";
    case RISKY_NULL_CARD_TYPES: return "nil card types";
    case RISKY_NULL_TRADEINS: return "nil trade in values";
    case RISKY_NULL_AIS: return "nil AIs";
    case RISKY_NULL_NAMES: return "nil names";
    case RISKY_NULL_CONTINENTS: return "nil continents";
    case RISKY_NULL_COUNTRY_BONUSES: return "nil country bonuses";
    case RISKY_NULL_COUNTRIES: return "nil countries";
    case RISKY_NULL_BOARD: return "nil board";
    case RISKY_BOARD_SIZE_ZERO: return "board size cannot be zero";
    case RISKY_COUNTRIES_SIZE_ZERO: return "countries size cannot be zero";
    case RISKY_INVALID_RAND: return "rand must be 1 or 0";
    case RISKY_INVALID_LOGGING: return "log on must be 1 or 0";
    case RISKY_NIL: return "";
    default: return "unrecognized RISKY error code";
  }
}

errRISKY_t makeRISKY(game_t **game) {
  if(!game) { return RISKY_NULL_GAME; }

  if(!(*game = malloc(sizeof(game_t)))) { return RISKY_OUT_OF_MEMORY; }

  return RISKY_NIL;
}

errRISKY_t freeRISKY(game_t *game) {
  if(!game) { return RISKY_NULL_GAME; }

  if(game->computers) { 
    for(; game->cps; game->cps--) { free(game->computers[game->cps-1]); }
    free(game->computers);
  }
  if(game->dir) { free(game->dir); }
  if(game->cardTypes) {
    for(; game->numTypes; game->numTypes--) { free(game->cardTypes[game->numTypes-1]); }
    free(game->cardTypes);
  }
  if(game->tradeIns) { free(game->tradeIns); }
  if(game->ais && game->names) {
    for(; game->chromosomes; game->chromosomes--) { 
      free(game->ais[game->chromosomes-1]);
      free(game->names[game->chromosomes-1]);
    }
    free(game->ais);
    free(game->names);
  }
  if(game->continents && game->contBonuses) {
    for(; game->numConts; game->numConts--) { free(game->continents[game->numConts-1]); }
    free(game->continents);
    free(game->contBonuses);
  }
  game->cps = game->numCountries; // tmp storage
  if(game->countries) {
    for(; game->numCountries; game->numCountries--) { free(game->countries[game->numCountries-1]); }
    free(game->countries);
  }
  game->numCountries = game->cps;
  if(game->board) {
    for(; game->numCountries; game->numCountries--) { free(game->board[game->numCountries-1]); }
    free(game->board);
  }
  free(game);

  return RISKY_NIL;
}

errRISKY_t setHumans(game_t *game, unsigned char hps) {
  if(!game) { return RISKY_NULL_GAME; }
  if(hps > 8) { return RISKY_INVALID_HPS; }

  game->hps = hps;

  return RISKY_NIL;
}

errRISKY_t setComputers(game_t *game, unsigned char cps, char **computers) {
  if(!game) { return RISKY_NULL_GAME; }
  if(cps > 8) { return RISKY_INVALID_CPS; }
  if(!computers) { return RISKY_INVALID_COMPUTERS; }

  game->cps = cps;
  game->computers = computers;

  return RISKY_NIL;
}

errRISKY_t setLogging(game_t *game, unsigned char on, char *dir) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!(on == 1 || on == 0)) { return RISKY_INVALID_LOGGING; }
  if(on == 1 && (!dir || strlen(dir) > 255)) { return RISKY_NULL_DIR; }

  game->log = on;
  game->dir = dir;

  return RISKY_NIL;
}

errRISKY_t setTraining(game_t *game, unsigned short games) {
  if(!game) { return RISKY_NULL_GAME; }

  game->trains = games;

  return RISKY_NIL;
}

errRISKY_t setTroops(game_t *game, unsigned char beginning, unsigned char min, unsigned char bonus, unsigned char rand) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!(rand == 0 || rand == 1)) { return RISKY_INVALID_RAND; }

  game->beginning = beginning;
  game->minimum = min;
  game->bonus = bonus;
  game->random = rand;

  return RISKY_NIL;
}

errRISKY_t setDeck(game_t *game, unsigned char wilds, char **types, unsigned char n) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!types) { return RISKY_NULL_CARD_TYPES; }

  game->wilds = wilds;
  game->cardTypes = types;
  game->numTypes = n;

  return RISKY_NIL;
}

errRISKY_t setTrades(game_t *game, unsigned char *trades, unsigned char n, unsigned char incr) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!trades) { return RISKY_NULL_TRADEINS; }

  game->tradeIns = trades;
  game->numTrades = n;
  game->tradeIncr = incr;

  return RISKY_NIL;
}

errRISKY_t setCps(game_t *game, unsigned char **ais, char **names, unsigned char chromosomes, unsigned char traits) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!names) { return RISKY_NULL_NAMES; }

  game->ais = ais;
  game->names = names;
  game->chromosomes = chromosomes;
  game->traits = traits;

  return RISKY_NIL;
}

errRISKY_t setContinents(game_t *game, char **continents, unsigned char *bonuses, unsigned char n) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!continents) { return RISKY_NULL_CONTINENTS; }
  if(!bonuses) { return RISKY_NULL_COUNTRY_BONUSES; }

  game->continents = continents;
  game->contBonuses = bonuses;
  game->numConts = n;

  return RISKY_NIL;
}

errRISKY_t setCountries(game_t *game, char **countries, unsigned char n, unsigned char rand) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!countries) { return RISKY_NULL_COUNTRIES; }
  if(!n) { return RISKY_COUNTRIES_SIZE_ZERO; }
  if(!(rand == 1 || rand == 0)) { return RISKY_INVALID_RAND; }

  game->countries = countries;
  game->numCountries = n;
  game->randomCountries = rand;

  return RISKY_NIL;
}

errRISKY_t setAdjacencies(game_t *game, unsigned char **board, unsigned char n) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!board) { return RISKY_NULL_BOARD; }
  if(!n) { return RISKY_BOARD_SIZE_ZERO; }

  game->board = board;
  game->numCountries = n;

  return RISKY_NIL;
}

errRISKY_t isEvolved(game_t *game, unsigned char *changed) {
  if(!game) { return RISKY_NULL_GAME; }

  *changed = game->evolved;
  
  return RISKY_NIL;
}

errRISKY_t isValid(game_t *game) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!game->computers) { return RISKY_NULL_COMPUTERS; }
  if(!game->dir) { return RISKY_NULL_DIR; }
  if(!game->cardTypes) { return RISKY_NULL_CARD_TYPES; }
  if(!game->tradeIns) { return RISKY_NULL_TRADEINS; }
  if(!game->ais) { return RISKY_NULL_AIS; }
  if(!game->names) { return RISKY_NULL_NAMES; }
  if(!game->continents) { return RISKY_NULL_CONTINENTS; }
  if(!game->contBonuses) { return RISKY_NULL_COUNTRY_BONUSES; }
  if(!game->countries) { return RISKY_NULL_COUNTRIES; }
  if(!game->board) { return RISKY_NULL_BOARD; }
  if(!(game->log == 1 || game->log == 0)) { return RISKY_INVALID_LOGGING; }
  if(game->log == 1 && (!game->dir || strlen(game->dir) > 255)) { return RISKY_NULL_DIR; }
  if(game->cps > 8) { return RISKY_INVALID_CPS; }
  if(game->hps > 8) { return RISKY_INVALID_HPS; }
  if(!(game->random == 0 || game->random == 1)) { return RISKY_INVALID_RAND; }
  if(!(game->randomCountries == 1 || game->randomCountries == 0)) { return RISKY_INVALID_RAND; }
  return RISKY_NIL;  
}

errRISKY_t risk(game_t *game) {
  errRISKY_t errRISKY = isValid(game);
  if(errRISKY != RISKY_NIL) { return errRISKY; }

  int i,j;
  printf("\t\t**GENERATED AJACENCY MATRIX**\n\n");
  printf("{\n");
  for(i = 0; i < game->numCountries; i++) {
    printf("\t{");
    for(j = 0; j < game->numCountries; j++) {
      printf("%i, ", (game->board)[i][j]);
    }
    printf("},\n");
  }
  printf("}\n");

  return RISKY_NIL;
}
