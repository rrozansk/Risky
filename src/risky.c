/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/22/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <ini.h>
#include <risky.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
 
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
  int chromosomes;     // number of chromosomes
  int traits;          // number of traits in each strand on DNA
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
  int dimension;       // numCountries
  // PRIVATE (NOT SETTABLE THROUGH API)
  int evolved;         // if any DNA changed
  FILE *fp;            // file to log to
};

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
    case RISKY_INVALID_RAND: return "rand must be 1 or 0";
    case RISKY_INVALID_LOGGING: return "log on must be 1 or 0";
    case RISKY_PLAYER_MANY: return "to many players";
    case RISKY_PLAYERS_LITTLE: return "not enough players";
    case RISKY_INVALID_ADJACENCIES: return "adjacency matrix must have the same dimensions as countries";
    case RISKY_DIR_CREATION_FAILURE: return "logging directory creation failed";
    case RISKY_FILE_CREATION_FAILURE: return "logging file creation failed";
    case RISKY_INVALID_GAMES: return "training games must be between 0-2^16";
    case RISKY_INVALID_BEGINNING: return "troop beginning must be between 0-2^8";
    case RISKY_INVALID_MINIMUM: return "troop minimum must be between 0-2^8";
    case RISKY_INVALID_BONUS: return "troop bonus must be between 0-2^8";
    case RISKY_INVALID_WILDS: return "wild card must be between 0-2^8";
    case RISKY_INVALID_INCR: return "trade increment must be between 0-2^8";
    case RISKY_INVALID_CHROMOSOMES: return "number of chromosomes must be between 0-2^8";
    case RISKY_INVALID_TRAITS: return "number of traits must be between 0-2^8";
    case RISKY_INVALID_DECK: return "types of wilds must be between 0-2^8";
    case RISKY_INVALID_TRADES_SET: return "number of defined trades must be between 0-2^8";
    case RISKY_INVALID_COUNTRIES_SIZE: return "number of defined countries must be between 0-2^8";
    case RISKY_INVALID_CONTINENTS_SIZE: return "number of defined continents must be between 0-2^8";
    case RISKY_INVALID_BOARD_SIZE: return "number of adjacencies must be between 0-2^8";
    case RISKY_INVALID_COUNTRY_CONTINENT: return "number of defined countries must be greater than or equal to number of defined continents";
    case RISKY_NIL: return "";
    default: return "unrecognized RISKY error code";
  }
}

errRISKY_t makeRISKY(game_t **game) {
  if(!game) { return RISKY_NULL_GAME; }

  if(!(*game = malloc(sizeof(game_t)))) { return RISKY_OUT_OF_MEMORY; }

  return RISKY_NIL;
}

// check every addr before freeing??
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

errRISKY_t setHumans(game_t *game, int hps) {
  if(!game) { return RISKY_NULL_GAME; }
  if(hps > 8) { return RISKY_INVALID_HPS; }

  game->hps = hps;

  return RISKY_NIL;
}

errRISKY_t setComputers(game_t *game, int cps, char **computers) {
  if(!game) { return RISKY_NULL_GAME; }
  if(cps > 8) { return RISKY_INVALID_CPS; }
  if(!computers) { return RISKY_INVALID_COMPUTERS; }

  game->cps = cps;
  game->computers = computers;

  return RISKY_NIL;
}

errRISKY_t setLogging(game_t *game, int on, char *dir) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!(on == 1 || on == 0)) { return RISKY_INVALID_LOGGING; }
  if(on == 1 && (!dir || strlen(dir) > 255)) { return RISKY_NULL_DIR; }

  game->log = on;
  game->dir = dir;

  return RISKY_NIL;
}
errRISKY_t setTraining(game_t *game, int games) {
  if(!game) { return RISKY_NULL_GAME; }
  if(games < 0 || games > 65536) { return RISKY_INVALID_GAMES; }

  game->trains = games;

  return RISKY_NIL;
}

errRISKY_t setTroops(game_t *game, int beginning, int min, int bonus, int rand) {
  if(!game) { return RISKY_NULL_GAME; }
  if(beginning < 0 || beginning > 256) { return RISKY_INVALID_BEGINNING; }
  if(min < 0 || min > 256) { return RISKY_INVALID_MINIMUM; }
  if(bonus < 0 || bonus > 256) { return RISKY_INVALID_BONUS; }
  if(!(rand == 0 || rand == 1)) { return RISKY_INVALID_RAND; }

  game->beginning = beginning;
  game->minimum = min;
  game->bonus = bonus;
  game->random = rand;

  return RISKY_NIL;
}

errRISKY_t setDeck(game_t *game, int wilds, char **types, int n) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!types) { return RISKY_NULL_CARD_TYPES; }
  if(wilds < 0 || wilds > 256) { return RISKY_INVALID_WILDS; }
  if(n < 0 || n > 256) { return RISKY_INVALID_DECK; }

  game->wilds = wilds;
  game->cardTypes = types;
  game->numTypes = n;

  return RISKY_NIL;
}

errRISKY_t setTrades(game_t *game, int *trades, int n, int incr) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!trades) { return RISKY_NULL_TRADEINS; }
  if(incr < 0 || incr > 256) { return RISKY_INVALID_INCR; }
  if(n < 0 || n > 256) { return RISKY_INVALID_TRADES_SET; }

  game->tradeIns = trades;
  game->numTrades = n;
  game->tradeIncr = incr;

  return RISKY_NIL;
}

errRISKY_t setCps(game_t *game, int **ais, char **names, int chromosomes, int traits) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!names) { return RISKY_NULL_NAMES; }
  if(chromosomes < 0 || chromosomes > 256) { return RISKY_INVALID_CHROMOSOMES; }
  if(traits < 0 || traits > 256) { return RISKY_INVALID_TRAITS; }

  game->ais = ais;
  game->names = names;
  game->chromosomes = chromosomes;
  game->traits = traits;

  return RISKY_NIL;
}

errRISKY_t setContinents(game_t *game, char **continents, int *bonuses, int n) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!continents) { return RISKY_NULL_CONTINENTS; }
  if(!bonuses) { return RISKY_NULL_COUNTRY_BONUSES; }
  if(n < 0 || n > 256) { return RISKY_INVALID_CONTINENTS_SIZE; }

  game->continents = continents;
  game->contBonuses = bonuses;
  game->numConts = n;

  return RISKY_NIL;
}

errRISKY_t setCountries(game_t *game, char **countries, int n, int rand) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!countries) { return RISKY_NULL_COUNTRIES; }
  if(!(rand == 1 || rand == 0)) { return RISKY_INVALID_RAND; }
  if(n < 0 || n > 256) { return RISKY_INVALID_COUNTRIES_SIZE; }

  game->countries = countries;
  game->numCountries = n;
  game->randomCountries = rand;

  return RISKY_NIL;
}

errRISKY_t setAdjacencies(game_t *game, int **board, int n) {
  if(!game) { return RISKY_NULL_GAME; }
  if(!board) { return RISKY_NULL_BOARD; }
  if(n < 0 || n > 256) { return RISKY_INVALID_BOARD_SIZE; }

  game->board = board;
  game->dimension = n;

  return RISKY_NIL;
}

errRISKY_t isEvolved(game_t *game, int *changed) {
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
  if(game->hps + game->cps > 8) { return RISKY_PLAYER_MANY; }
  if(game->hps + game->cps < 2) { return RISKY_PLAYERS_LITTLE; }
  if(!(game->random == 0 || game->random == 1)) { return RISKY_INVALID_RAND; }
  if(!(game->randomCountries == 1 || game->randomCountries == 0)) { return RISKY_INVALID_RAND; }
  if(game->dimension < 0 || game->dimension > 256) { return RISKY_INVALID_BOARD_SIZE; }
  if(game->numCountries != game->dimension) { return RISKY_INVALID_ADJACENCIES; }
  if(game->chromosomes < 0 || game->chromosomes > 256) { return RISKY_INVALID_CHROMOSOMES; }
  if(game->traits < 0 || game->traits > 256) { return RISKY_INVALID_TRAITS; }
  if(game->tradeIncr < 0 || game->tradeIncr > 256) { return RISKY_INVALID_INCR; }
  if(game->trains < 0 || game->trains > 65536) { return RISKY_INVALID_GAMES; }
  if(game->beginning < 0 || game->beginning > 256) { return RISKY_INVALID_BEGINNING; }
  if(game->minimum < 0 || game->minimum > 256) { return RISKY_INVALID_MINIMUM; }
  if(game->bonus < 0 || game->bonus > 256) { return RISKY_INVALID_BONUS; }
  if(game->wilds < 0 || game->wilds > 256) { return RISKY_INVALID_WILDS; }
  if(game->numTrades < 0 || game->numTrades > 256) { return RISKY_INVALID_DECK; }
  if(game->numTypes < 0 || game->numTypes > 256) { return RISKY_INVALID_TRADES_SET; }
  if(game->numConts < 0 || game->numConts > 256) { return RISKY_INVALID_CONTINENTS_SIZE; }
  if(game->numCountries < 0 || game->numCountries > 256) { return RISKY_INVALID_COUNTRIES_SIZE; }
  if(game->numCountries < game->numConts) { return RISKY_INVALID_COUNTRY_CONTINENT; }

  return RISKY_NIL;  
}

void fprintIntArr(FILE *fp, int *arr, int size) {
  fprintf(fp, "{");
  int i;
  for(i = 0; i < size; i++) {
    (i < size -1) ? fprintf(fp, "%i, ", arr[i]) : fprintf(fp, "%i", arr[i]);  
  }
  fprintf(fp, "}\n");
}

void fprintIntArr2D(FILE *fp, int **arr, int x, int y) {
  int i, j;
  fprintf(fp, "{\n");
  for(i = 0; i < x; i++) {
    fprintf(fp, "\t{");
    for(j = 0; j < y; j++) {
      (j < y-1) ? fprintf(fp, "%i, ", arr[i][j]) : fprintf(fp, "%i", arr[i][j]);
    }
    (i < x-1) ? fprintf(fp, "},\n") : fprintf(fp, "}\n");
  }
  fprintf(fp, "}\n");
}

void fprintStrArr(FILE *fp, char **arr, int size) {
  fprintf(fp, "{");
  int i;
  for(i = 0; i < size; i++) {
    (i < size -1) ? fprintf(fp, "%s, ", arr[i]) : fprintf(fp, "%s", arr[i]);  
  }
  fprintf(fp, "}\n");
} 

errRISKY_t risky(game_t *game) {
  errRISKY_t errRISKY = isValid(game);
  if(errRISKY != RISKY_NIL) { return errRISKY; }

  if(game->log) {
    struct stat st;
    if(mkdir(game->dir, 0700) && stat(game->dir, &st)) { return RISKY_DIR_CREATION_FAILURE; }

    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    char *buffer = calloc(80, sizeof(char));
    strftime(buffer, 80, "%Y_%B_%d_%A_%X", date);

    char *buffer2 = calloc(80, sizeof(char));
    sprintf(buffer2, "%s/%s.txt", game->dir, buffer);

    if(!(game->fp = fopen(buffer2, "w"))) { return RISKY_FILE_CREATION_FAILURE; }
    fprintf(game->fp, "\t\t\t\t**GAME SESSION: %s**\n\n", buffer);

    free(buffer);
    free(buffer2);

    fprintf(game->fp, "***********************************SETTINGS*************************************\n");

    fprintf(game->fp, "\n\t**PLAYER**\n");
    fprintf(game->fp, "Human players: %i\n", game->hps);
    fprintf(game->fp, "Computer players: %i\n", game->cps);
    fprintf(game->fp, "Computer names: "); 
    fprintStrArr(game->fp, game->computers, game->cps);

    fprintf(game->fp, "\n\t**TRAINING**\n");
    fprintf(game->fp, "Training sessions: %i\n", game->trains);

    fprintf(game->fp, "\n\t**TROOP**\n");
    fprintf(game->fp, "Beginning troop count: %i\n", game->beginning);
    fprintf(game->fp, "Minimum troop per turn: %i\n", game->minimum);
    fprintf(game->fp, "Troop bonus: %i\n", game->bonus);
    fprintf(game->fp, "Randomize troops: %i\n", game->random);

    fprintf(game->fp, "\n\t**CARD**\n");
    fprintf(game->fp, "Number of wilds: %i\n", game->wilds);
    fprintf(game->fp, "Number of card types: %i\n", game->numTypes);
    fprintf(game->fp, "Card types: "); 
    fprintStrArr(game->fp, game->cardTypes, game->numTypes);
    fprintf(game->fp, "Trade increment: %i\n", game->tradeIncr);
    fprintf(game->fp, "Number of trade ins: %i\n", game->numTrades);
    fprintf(game->fp, "Trade Ins: "); 
    fprintIntArr(game->fp, game->tradeIns, game->numTrades);

    fprintf(game->fp, "\n\t**DNA**\n");
    fprintf(game->fp, "Number chromosomes: %i\n", game->chromosomes);
    fprintf(game->fp, "Number traits: %i\n", game->traits);
    fprintf(game->fp, "AI names: "); 
    fprintStrArr(game->fp, game->names, game->chromosomes);
    fprintf(game->fp, "Chromosomes:\n"); 
    fprintIntArr2D(game->fp, game->ais, game->chromosomes, game->traits);

    fprintf(game->fp, "\n\t**MAP SETTINGS**\n");
    fprintf(game->fp, "Number continents: %i\n", game->numConts);
    fprintf(game->fp, "Continents: "); 
    fprintStrArr(game->fp, game->continents, game->numConts);
    fprintf(game->fp, "Continent bonuses: "); 
    fprintIntArr(game->fp, game->contBonuses, game->numConts);
    fprintf(game->fp, "Randomize countries: %i\n", game->randomCountries);
    fprintf(game->fp, "Number countries: %i\n", game->numCountries);
    fprintf(game->fp, "Dimensions: %i\n", game->dimension);
    fprintf(game->fp, "Countries: "); 
    fprintStrArr(game->fp, game->countries, game->numCountries);
    fprintf(game->fp, "Adjacency Matrix:\n");
    fprintIntArr2D(game->fp, game->board, game->dimension, game->dimension);

    fprintf(game->fp, "\n\n*************************************GAMEPLAY***********************************\n\n");
  }

  fclose(game->fp);

  return RISKY_NIL;
}
