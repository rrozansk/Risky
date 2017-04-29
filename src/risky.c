/******************************************************************************
 * FILE:    risky.c                                                           *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  4/29/17                                                           *
 * INFO:    Implementation of the interface located in risky.h.               *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <ini.h>
#include <risky.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
struct game {
  /* PLAYERS */
  int hps;             /* number of human players */
  char **computers;    /* ptr to array of cps i.e. isStr(arr[i]) */
  int cps;             /* size of computers */
  /* TRAINING */
  int log;             /* turn on/off logging during training exercises */
  char *dir;           /* directory to put taining logs */
  int trains;          /* numer of training exercises to perform */
  /* TROOPS */
  int beginning;       /* number of troops recieved at game start */
  int minimum;         /* minimum troop bonus per turn */
  int bonus;           /*  */
  int random;          /*  */
  /* CARDS */
  char **cardTypes;    /* ptr to array of card types */
  int numTypes;        /* size of cardTypes */
  int wilds;           /* number of wilds in the deck */
  int *tradeIns;       /* ptr to array of trade in bonuses */
  int numTrades;       /* size of tradeIns */
  int tradeIncr;       /* constant trade increment once  */
  /* CHROMOSOMES */
  int chromosomes;     /* number of chromosomes */
  int traits;          /* number of traits in each strand on DNA */
  int **ais;           /* ais[numChromosomes][numTraits] */
  char **names;        /* names[numChromosomes] */
  /* MAP */
  char **continents;   /* ptr to array of continents */
  int *contBonuses;    /* ptr to array of contnent bonuses */
  int numConts;        /* size of continents array and contBonuses */
  char **countries;    /* ptr to array of countries */
  int numCountries;    /* size of countries array */
  int randomCountries; /* to split up map randomly or not */
  int **board;         /* adjacency matrix --> board[numCountries][numCountries]; */
  int dimension;       /* numCountries */
  /* PRIVATE (NOT SETTABLE THROUGH API) */
  int evolved;         /* if any DNA changed */
  FILE *fp;            /* file to log to */
  int playing;         /* bool for starting gameplay to lock down the conf */
};

typedef struct card { } card_t;
typedef struct deck { } deck_t;
typedef struct player { } player_t;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/
const char *strErrRISKY(errRISKY_t errRISKY) {
  switch(errRISKY) {
    case RISKY_NIL_COUNTRY: return "nil country";
    case RISKY_NIL_TROOPS: return "nil troops";
    case RISKY_NIL_GAME: return "nil game";
    case RISKY_NIL_COMPUTERS: return "nil computers";
    case RISKY_NIL_DIR: return "nil logging directory";
    case RISKY_NIL_CARD_TYPES: return "nil card types";
    case RISKY_NIL_TRADEINS: return "nil trade in values";
    case RISKY_NIL_AIS: return "nil AIs";
    case RISKY_NIL_NAMES: return "nil names";
    case RISKY_NIL_CONTINENTS: return "nil continents";
    case RISKY_NIL_COUNTRY_BONUSES: return "nil country bonuses";
    case RISKY_NIL_COUNTRIES: return "nil countries";
    case RISKY_NIL_BOARD: return "nil board";
    case RISKY_NIL_CHOICE: return "nil choice";
    case RISKY_NIL_ELEMS: return "nil list";
    case RISKY_NIL_PLAYER: return "nil player";
    case RISKY_INVALID_HPS: return "number of human players must be 0-8";
    case RISKY_INVALID_CPS: return "number of computer players must be 0-8";
    case RISKY_INVALID_COMPUTERS: return "nil computers";
    case RISKY_INVALID_RAND: return "rand must be 1 or 0";
    case RISKY_INVALID_LOGGING: return "log on must be 1 or 0";
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
    case RISKY_INVALID_PROMPT: return "prompt must be 1 or 0";
    case RISKY_INVALID_ADJACENCIES: return "adjacency matrix must have the same dimensions as countries";
    case RISKY_INVALID_RANGE: return "invalid choice range";
    case RISKY_INVALID_INDEX_SIZE: return "array size must be >= 0";
    case RISKY_PLAYER_MANY: return "to many players";
    case RISKY_PLAYERS_LITTLE: return "not enough players";
    case RISKY_DIR_CREATION_FAILURE: return "logging directory creation failed";
    case RISKY_FILE_CREATION_FAILURE: return "logging file creation failed";
    case RISKY_READ_ERROR: return "error reading input";
    case RISKY_UNKNOWN_ERROR: return "congratulations! you broke the game in a way unknown way!";
    case RISKY_CPS_NOT_SUPPORTED: return "computer players/AIs are not yet a supported feature";
    case RISKY_OUT_OF_MEMORY: return "out of memory";
    case RISKY_GAME_PLAY_MUTATION: return "you cannot change game setting while in play";
    case RISKY_NOT_SUPPORTED: return "feature not yet implemented (still in dev)";
    case RISKY_NIL: return "";
    default: return "unrecognized errRISKY_t";
  }
}

errRISKY_t makeRISKY(game_t **game) {
  if(!game) { return RISKY_NIL_GAME; }

  if(!(*game = calloc(1, sizeof(game_t)))) { return RISKY_OUT_OF_MEMORY; }

  return RISKY_NIL;
}

errRISKY_t freeRISKY(game_t *game) {
  if(!game) { return RISKY_NIL_GAME; }

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
  if(game->contBonuses) { free(game->contBonuses); }
  if(game->continents) {
    for(; game->numConts; game->numConts--) { free(game->continents[game->numConts-1]); }
    free(game->continents);
  }
  if(game->countries) {
    for(; game->numCountries; game->numCountries--) { free(game->countries[game->numCountries-1]); }
    free(game->countries);
  }
  if(game->board) {
    for(; game->dimension; game->dimension--) { free(game->board[game->dimension-1]); }
    free(game->board);
  }
  free(game);

  return RISKY_NIL;
}

errRISKY_t setHumans(game_t *game, int hps) {
  if(!game) { return RISKY_NIL_GAME; }
  if(hps > 8) { return RISKY_INVALID_HPS; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->hps = hps;

  return RISKY_NIL;
}

errRISKY_t setComputers(game_t *game, int cps, char **computers) {
  if(!game) { return RISKY_NIL_GAME; }
  if(cps > 8) { return RISKY_INVALID_CPS; }
  if(!computers) { return RISKY_INVALID_COMPUTERS; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->cps = cps;
  game->computers = computers; // TODO: malloc and copy (reset/free)

  return RISKY_NIL;
}

errRISKY_t setLogging(game_t *game, int on, char *dir) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!(on == 1 || on == 0)) { return RISKY_INVALID_LOGGING; }
  if(on == 1 && (!dir || strlen(dir) > 255)) { return RISKY_NIL_DIR; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->log = on;
  game->dir = dir;  // TODO: malloc and copy (reset/free)

  return RISKY_NIL;
}
errRISKY_t setTraining(game_t *game, int games) {
  if(!game) { return RISKY_NIL_GAME; }
  if(games < 0 || games > 65536) { return RISKY_INVALID_GAMES; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->trains = games;

  return RISKY_NIL;
}

errRISKY_t setTroops(game_t *game, int beginning, int min, int bonus, int rand) {
  if(!game) { return RISKY_NIL_GAME; }
  if(beginning < 0 || beginning > 256) { return RISKY_INVALID_BEGINNING; }
  if(min < 0 || min > 256) { return RISKY_INVALID_MINIMUM; }
  if(bonus < 0 || bonus > 256) { return RISKY_INVALID_BONUS; }
  if(!(rand == 0 || rand == 1)) { return RISKY_INVALID_RAND; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->beginning = beginning;
  game->minimum = min;
  game->bonus = bonus;
  game->random = rand;

  return RISKY_NIL;
}

errRISKY_t setDeck(game_t *game, int wilds, char **types, int n) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!types) { return RISKY_NIL_CARD_TYPES; }
  if(wilds < 0 || wilds > 256) { return RISKY_INVALID_WILDS; }
  if(n < 0 || n > 256) { return RISKY_INVALID_DECK; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->wilds = wilds;
  game->cardTypes = types;
  game->numTypes = n;

  return RISKY_NIL;
}

errRISKY_t setTrades(game_t *game, int *trades, int n, int incr) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!trades) { return RISKY_NIL_TRADEINS; }
  if(incr < 0 || incr > 256) { return RISKY_INVALID_INCR; }
  if(n < 0 || n > 256) { return RISKY_INVALID_TRADES_SET; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->tradeIns = trades;  // TODO: malloc and copy (reset/free)
  game->numTrades = n;
  game->tradeIncr = incr;

  return RISKY_NIL;
}

errRISKY_t setCps(game_t *game, int **ais, char **names, int chromosomes, int traits) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!names) { return RISKY_NIL_NAMES; }
  if(chromosomes < 0 || chromosomes > 256) { return RISKY_INVALID_CHROMOSOMES; }
  if(traits < 0 || traits > 256) { return RISKY_INVALID_TRAITS; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->ais = ais;  // TODO: malloc and copy (reset/free)
  game->names = names;  // TODO: malloc and copy (reset/free)
  game->chromosomes = chromosomes;
  game->traits = traits;

  return RISKY_NIL;
}

errRISKY_t setContinents(game_t *game, char **continents, int n) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!continents) { return RISKY_NIL_CONTINENTS; }
  if(n < 0 || n > 256) { return RISKY_INVALID_CONTINENTS_SIZE; }
  if(game->contBonuses && game->numConts != n) { return RISKY_INVALID_CONTINENTS_SIZE; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->continents = continents;  // TODO: malloc and copy (reset/free)
  game->numConts = n;

  return RISKY_NIL;
}

errRISKY_t setContinentBonuses(game_t *game, int *bonuses, int n) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!bonuses) { return RISKY_NIL_COUNTRY_BONUSES; }
  if(n < 0 || n > 256) { return RISKY_INVALID_CONTINENTS_SIZE; }
  if(game->continents && game->numConts != n) { return RISKY_INVALID_CONTINENTS_SIZE; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->contBonuses = bonuses;  // TODO: malloc and copy (reset/free)
  game->numConts = n;

  return RISKY_NIL;
}

errRISKY_t setCountries(game_t *game, char **countries, int n, int rand) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!countries) { return RISKY_NIL_COUNTRIES; }
  if(!(rand == 1 || rand == 0)) { return RISKY_INVALID_RAND; }
  if(n < 0 || n > 256) { return RISKY_INVALID_COUNTRIES_SIZE; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->countries = countries;  // TODO: malloc and copy (reset/free)
  game->numCountries = n;
  game->randomCountries = rand;

  return RISKY_NIL;
}

errRISKY_t setAdjacencies(game_t *game, int **board, int n) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!board) { return RISKY_NIL_BOARD; }
  if(n < 0 || n > 256) { return RISKY_INVALID_BOARD_SIZE; }
  if(game->playing) { return RISKY_GAME_PLAY_MUTATION; }

  game->board = board;  // TODO: malloc and copy (reset/free)
  game->dimension = n;

  return RISKY_NIL;
}

errRISKY_t isEvolved(game_t *game, int *changed) {
  if(!game) { return RISKY_NIL_GAME; }

  *changed = game->evolved;
  
  return RISKY_NIL;
}

errRISKY_t isValid(game_t *game) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!game->computers) { return RISKY_NIL_COMPUTERS; }
  if(!game->dir) { return RISKY_NIL_DIR; }
  if(!game->cardTypes) { return RISKY_NIL_CARD_TYPES; }
  if(!game->tradeIns) { return RISKY_NIL_TRADEINS; }
  if(!game->ais) { return RISKY_NIL_AIS; }
  if(!game->names) { return RISKY_NIL_NAMES; }
  if(!game->continents) { return RISKY_NIL_CONTINENTS; }
  if(!game->contBonuses) { return RISKY_NIL_COUNTRY_BONUSES; }
  if(!game->countries) { return RISKY_NIL_COUNTRIES; }
  if(!game->board) { return RISKY_NIL_BOARD; }
  if(!(game->log == 1 || game->log == 0)) { return RISKY_INVALID_LOGGING; }
  if(game->log == 1 && (!game->dir || strlen(game->dir) > 255)) { return RISKY_NIL_DIR; }
  if(game->cps > 8) { return RISKY_INVALID_CPS; }
  if(game->hps > 8) { return RISKY_INVALID_HPS; }
  if(game->hps + game->cps > 8) { return RISKY_PLAYER_MANY; }
  if(game->hps + game->cps < 2) { return RISKY_PLAYERS_LITTLE; }
  if(!(game->random == 0 || game->random == 1)) { return RISKY_INVALID_RAND; }
  if(!(game->randomCountries == 1 || game->randomCountries == 0)) { return RISKY_INVALID_RAND; }
  if(game->dimension < 0 || game->dimension > 256) { return RISKY_INVALID_BOARD_SIZE; }
  if(game->numCountries != game->dimension) { return RISKY_INVALID_ADJACENCIES; }
  if(game->chromosomes < 0 || game->chromosomes > 256) { return RISKY_INVALID_CHROMOSOMES; }
  if(game->traits < 0 || game->traits > 256) { return RISKY_INVALID_TRAITS; } // FIXME enfore all between 0-256
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

/* PRIVATE HELPERS */
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

errRISKY_t logSetup(game_t *game) {
  if(!game) { return RISKY_NIL_GAME; }

  struct stat st;
  if(mkdir(game->dir, 0700) && stat(game->dir, &st)) { return RISKY_DIR_CREATION_FAILURE; }

  time_t t = time(NULL);
  struct tm *date = localtime(&t);
  char *fname = calloc(80, sizeof(char));
  strftime(fname, 80, "%Y_%B_%d_%A_%X", date); // unique to the second.

  char *path = calloc(80, sizeof(char));
  sprintf(path, "%s/%s.txt", game->dir, fname);

  if(!(game->fp = fopen(path, "w"))) { 
    free(fname);
    free(path);
    return RISKY_FILE_CREATION_FAILURE;
  }
  fprintf(game->fp, "\t\t\t\t**GAME SESSION: %s**\n\n", fname);

  free(fname);
  free(path);

  fprintf(game->fp, "***********************************SETTINGS*************************************\n");

  fprintf(game->fp, "\n\t**PLAYER**\n");
  fprintf(game->fp, "Human players: %i\n", game->hps);
  fprintf(game->fp, "Computer players: %i\n", game->cps);
  fprintf(game->fp, "Computer names: "); 
  fprintStrArr(game->fp, game->computers, game->cps);

  fprintf(game->fp, "\n\t**TRAINING**\n");
  fprintf(game->fp, "Training sessions: %i\n", game->trains);

  fprintf(game->fp, "\n\t**TROOP**\n");
  fprintf(game->fp, "Beginning game troop count: %i\n", game->beginning);
  fprintf(game->fp, "Minimum troops per turn: %i\n", game->minimum);
  fprintf(game->fp, "Extra troop bonus ratio per countries: %i\n", game->bonus);
  fprintf(game->fp, "Randomized troops: %i\n", game->random);

  fprintf(game->fp, "\n\t**CARD**\n");
  fprintf(game->fp, "Number of wilds: %i\n", game->wilds);
  fprintf(game->fp, "Number of card types: %i\n", game->numTypes);
  fprintf(game->fp, "Card types: "); 
  fprintStrArr(game->fp, game->cardTypes, game->numTypes);
  fprintf(game->fp, "Number of trade ins: %i\n", game->numTrades);
  fprintf(game->fp, "Trade Ins: "); 
  fprintf(game->fp, "Trade increment: %i\n", game->tradeIncr);
  fprintIntArr(game->fp, game->tradeIns, game->numTrades);

  fprintf(game->fp, "\n\t**DNA**\n");
  fprintf(game->fp, "Number of chromosomes: %i\n", game->chromosomes);
  fprintf(game->fp, "Number of traits: %i\n", game->traits);
  fprintf(game->fp, "AI names: "); 
  fprintStrArr(game->fp, game->names, game->chromosomes);
  fprintf(game->fp, "Chromosomes:\n"); 
  fprintIntArr2D(game->fp, game->ais, game->chromosomes, game->traits);

  fprintf(game->fp, "\n\t**MAP SETTINGS**\n");
  fprintf(game->fp, "Number of continents: %i\n", game->numConts);
  fprintf(game->fp, "Continents: "); 
  fprintStrArr(game->fp, game->continents, game->numConts);
  fprintf(game->fp, "Continent bonuses: "); 
  fprintIntArr(game->fp, game->contBonuses, game->numConts);
  fprintf(game->fp, "Randomized countries: %i\n", game->randomCountries);
  fprintf(game->fp, "Number of countries: %i\n", game->numCountries);
  fprintf(game->fp, "Countries: "); 
  fprintStrArr(game->fp, game->countries, game->numCountries);
  fprintf(game->fp, "Adjacency dimensions: %i\n", game->dimension);
  fprintf(game->fp, "Adjacency Matrix:\n");
  fprintIntArr2D(game->fp, game->board, game->dimension, game->dimension);
  fflush(game->fp);

  return RISKY_NIL;
}

errRISKY_t printChoices(char **elems, int size) {
  if(!elems) { return RISKY_INVALID_INDEX_SIZE; }
  if(!size || size < 0) { return RISKY_NIL_ELEMS; }

  int i;
  for(i = 0; i < size; i++) { printf("\t%i) %s\n", i, elems[i]);  }
  printf("\n");
 
  return RISKY_NIL;
}

errRISKY_t readInt(int lbound, int ubound, int *pick, int prompt) {
  if(lbound >= ubound) { return RISKY_INVALID_RANGE; }
  if(!pick) { return RISKY_NIL_CHOICE; }
  if(!(prompt == 0 || prompt == 1)) { return RISKY_INVALID_PROMPT; }

  char c;
  char buffer[80];
  printf("Enter pick (%i-%i): ", lbound, ubound);
  while(fgets(buffer, 80, stdin)) {
    if(!sscanf(buffer, "%d\n", pick) || *pick < lbound || *pick > ubound) {
      printf("invalid, input must be a single integer between %i-%i\n", lbound, ubound);
      printf("Enter pick (%i-%i): ", lbound, ubound);
    } else if(prompt) {
      printf("Entered choice: %i, are you sure (y/n)? ", *pick);
      while(fgets(buffer, 80, stdin)) {
        if(!sscanf(buffer, "%c\n", &c) || !(c == 'y' || c == 'n')) {
          printf("invalid input, only enter 'y'/'n': ");
        }
        else if(c == 'y') { return RISKY_NIL; }
        else { break; } // c == 'n'
      }
      if(c != 'n') { return RISKY_READ_ERROR; }
      printf("Enter pick (%i-%i): ", lbound, ubound);
    } else { return RISKY_NIL; }
  }

  return RISKY_READ_ERROR;
}

errRISKY_t printBoard(game_t *game) {
  if(!game) { return RISKY_NIL_GAME; }

  return RISKY_NOT_SUPPORTED;

  return RISKY_NIL;
}

errRISKY_t humanTurn(game_t *game, player_t *player) {
  if(!game) { return RISKY_NIL_GAME; }
  //if(!player) { return RISKY_NIL_PLAYER; }

  int choice;
  int prompt = 1;

  int mainChoices = 6;
  char *mainMenu[] = {"Trade", "Attack", "Maneuver", "Query", "Board", "End"};

  int queryChoices = 5;
  char *queryMenu[] = {"Players", "Countries", "Continents", "Cards", "Main Menu"};

  int done = 0;
  errRISKY_t errRISKY;

  while(!done) {
    // printf("Player %s's turn\n", getName(game, player)); // TODO
    if((errRISKY = printChoices(mainMenu, mainChoices)) != RISKY_NIL) { return errRISKY; }
    if((errRISKY = readInt(0, mainChoices-1, &choice, prompt)) != RISKY_NIL) { return errRISKY; }
    switch(choice) {
      case 0: // TRADE
        // get which cards
        // place troops
        //    -- enfore trade rules, timeing(1/turn and beginning?)
        break;
      case 1: // ATTACK
        // src, dest (adjacency)
        // how many
        // ask defender how many (1 or 2)
        //  - draw card (if win), kill ememy (get card/enfore trade)
        break;
      case 2: // MANEUVER
        // src, dest (chain reachable)
        // how many
        done = 1;
        break;
      case 3: // QUERY
        if((errRISKY = printChoices(queryMenu, queryChoices)) != RISKY_NIL) { return errRISKY; }
        if((errRISKY = readInt(0, queryChoices-1, &choice, prompt)) != RISKY_NIL) { return errRISKY; }
        switch(choice) {
          case 0: // PLAYERS
            break;
          case 1: // COUNTRIES
            break;
          case 2: // CONTINENTS
            break;
          case 3: // CARDS
            break;
          case 4: // MAIN MENU
            break;
          default:
            return RISKY_UNKNOWN_ERROR;
        }
        break;
      case 4: // BOARD
        if((errRISKY = printBoard(game)) != RISKY_NIL) { return errRISKY; }
        break;
      case 5: // END
        done = 1;
        break;
      default:
        return RISKY_UNKNOWN_ERROR;
    }
  }

  return RISKY_NIL;
}

errRISKY_t computerTurn(game_t *game, player_t *player) { // TODO
  if(!game) { return RISKY_NIL_GAME; }
  if(!player) { return RISKY_NIL_PLAYER; }

  return RISKY_CPS_NOT_SUPPORTED;

  return RISKY_NIL;
}


errRISKY_t risky(game_t *game) {
  if(!game) { return RISKY_NIL_GAME; }

  errRISKY_t errRISKY;
  if((errRISKY = isValid(game)) != RISKY_NIL) { return errRISKY; }

  if(game->log && (errRISKY = logSetup(game)) != RISKY_NIL) { return errRISKY;  }

  // FIXME: game mode (hvh, hvc, cvc, train) train is just cvc in a loop

  game->playing = 1; // so people can not mutate the game conf with set---();

  int i,j;
  for(i = 0; i < game->chromosomes; i++) { // testing output of new chromosome
    for(j = 0; j < game->traits; j++) {
      game->ais[i][j] = 5;  
    }
  }
  game->evolved = 1; // to test output of new chromosomes

  // if((errRISKY = printRules(game)) != RISKY_NIL) { return errRISKY; }; // TODO print headers for each
  // if((errRISKY = initDeck(game)) != RISKY_NIL) { return errRISKY; }
  // if((errRISKY = initPlayers(game)) != RISKY_NIL) { return errRISKY; }
  // if((errRISKY = initCountries(game) != RISKY_NIL) { return errRISKY; }
  // if((errRISKY = initArmies(game)) != RISKY_NIL) { return errRISKY; }

  if(game->log) {
    fprintf(game->fp, "\n\n*************************************GAMEPLAY***********************************\n\n");
  }
  // while(NumberPlayer(game) > 1) {
  //   player_t player = getNextPlayer(game);
  //  dispatch on type
  //if((errRISKY = computerTurn(game, NULL)) != RISKY_NIL) { return errRISKY; }
  if((errRISKY = humanTurn(game, NULL)) != RISKY_NIL) { return errRISKY; }
  // }
  // printWinner(game);

  if(game->log) { fclose(game->fp); }

  return RISKY_NIL;
}

// FIXME: temp getters. should return copies of data since getters
errRISKY_t getCps(game_t *game, char ***strArr1, int *size) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!strArr1) { return RISKY_NIL_ELEMS; }
  if(!size) { return RISKY_INVALID_INDEX_SIZE; }

  *strArr1 = game->names;
  *size = game->chromosomes;
  
  return RISKY_NIL;
}

// FIXME: temp getters. should return copies of data since getters
errRISKY_t getChromosome(game_t *game, char *name, int **dna, int *size) {
  if(!game) { return RISKY_NIL_GAME; }
  if(!name) { return RISKY_NIL_NAMES; }
  if(!dna) { return RISKY_NIL_ELEMS; }

  int i;
  for(i = 0; i < game->chromosomes; i++) {
    if(!strcmp(name, game->names[i])) { break; }  
  }
  *dna = game->ais[i];
  *size = game->traits;
 
  return RISKY_NIL;
}
