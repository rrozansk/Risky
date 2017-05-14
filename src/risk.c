/******************************************************************************
 * FILE:    risk.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  5/13/17                                                           *
 * INFO:    Implementation of the interface located in risk.h.                *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <risk.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
struct risk {
  /* PLAYERS */
  char **names;        /* array of player names */
  int size;            /* # human */
  /* TROOPS */
  int beginning;       /* # troops at game start */
  int minimum;         /* minimum troop/turn */
  int bonus;           /* #countries/troop bonus */
  int random;          /* randomly assign troops to countries */
  /* CARDS */
  char **cardTypes;    /* array of card types */
  int numTypes;        /* # card types */
  int wilds;           /* # wilds */
  int *tradeIns;       /* array of trade in bonuses */
  int numTrades;       /* # trade ins */
  int tradeIncr;       /* constant trade increment */
  /* MAP */
  char **continents;   /* array of continents */
  int *contBonuses;    /* array of contnent bonuses */
  int numConts;        /* # continents and continent bonuses */
  char **countries;    /* array of countries */
  int numCountries;    /* # countries */
  int randomCountries; /* random countries at game start */
  int **board;         /* adjacency matrix */
  // TODO: use board to track player ownage and army count?
  // TODO: holding deck information?
  int playing;
};

typedef struct card { 
  char *country;
  char *type;
  char *owner;
} card_t;

typedef struct deck { 
  int size;
  int currCard;
  card_t *cards;
} deck_t;

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrRISK(errRISK_t errRISK) {
  switch(errRISK) {
    case RISK_OUT_OF_MEMORY: return "out of memory";
    case RISK_GAME_PLAY_MUTATION: return "you cannot change game setting while in play";
    case RISK_COUNTRIES_MISMATCH: return "countries size does not match game board dimensions";
    case RISK_INVALID_PLAYERS: return "number of players must be 0-8";
    case RISK_INVALID_RAND: return "rand must be 1 or 0";
    case RISK_INVALID_BEGINNING: return "troop beginning must be between 0-2^8";
    case RISK_INVALID_MINIMUM: return "troop minimum must be between 0-2^8";
    case RISK_INVALID_BONUS: return "troop bonus must be between 0-2^8";
    case RISK_INVALID_WILDS: return "wild card must be between 0-2^8";
    case RISK_INVALID_INCR: return "trade increment must be between 0-2^8";
    case RISK_INVALID_DECK: return "types of wilds must be between 0-2^8";
    case RISK_INVALID_TRADES_SET: return "number of defined trades must be between 0-2^8";
    case RISK_INVALID_COUNTRIES_SIZE: return "number of defined countries must be between 0-2^8";
    case RISK_INVALID_CONTINENTS_SIZE: return "number of defined continents must be between 0-2^8";
    case RISK_INVALID_BOARD_SIZE: return "number of adjacencies must be between 0-2^8";
    case RISK_INVALID_COUNTRY_CONTINENT: return "number of defined countries must be greater than or equal to number of defined continents";
    case RISK_INVALID_DEFENCE: return "invalid defence";
    case RISK_INVALID_ATTACK: return "invalid attack";
    case RISK_NIL_DEST: return "nil dest";
    case RISK_NIL_SRC: return "nil src";
    case RISK_NIL_RESULT: return "nil result";
    case RISK_NIL_CARD: return "nil card";
    case RISK_NIL_TROOPS: return "nil troops";
    case RISK_NIL_PLAYER: return "nil players";
    case RISK_NIL_GAME: return "nil game";
    case RISK_NIL_CARD_TYPES: return "nil card types";
    case RISK_NIL_TRADEINS: return "nil trade in values";
    case RISK_NIL_NAMES: return "nil names";
    case RISK_NIL_COUNTRY_BONUSES: return "nil country bonuses";
    case RISK_NIL_BOARD: return "nil board";
    case RISK_NIL_COUNTRY: return "nil country";
    case RISK_NIL_CONFLICTS: return "nil conflicts";
    case RISK_NIL_COUNTRIES: return "nil countries";
    case RISK_NIL_TRADES: return "nil trades";
    case RISK_NIL_INCR: return "nil incr";
    case RISK_NIL_START: return "nil start";
    case RISK_NIL_MIN: return "nil minimum";
    case RISK_NIL_BONUS: return "nil bonus";
    case RISK_NIL_PLAYERS: return "nil players";
    case RISK_NIL_WILDS: return "nil wilds";
    case RISK_NIL_TYPES: return "nil types";
    case RISK_NIL_SIZE: return "nil size";
    case RISK_NIL_CONTINENTS: return "nil continents";
    case RISK_NIL_CONTINENT: return "nil continent";
    case RISK_NIL_BONUSES: return "nil bonuses";
    case RISK_NIL: return "";
    default: return "unrecognized errRISK_t";
  }
}

errRISK_t makeRISK(risk_t **game) {
  if(!game) { return RISK_NIL_GAME; }

  if(!(*game = calloc(1, sizeof(risk_t)))) { return RISK_OUT_OF_MEMORY; }

  return RISK_NIL;
}

errRISK_t freeRISK(risk_t *game) { // TODO: redo with free API above
  if(!game) { return RISK_NIL_GAME; }

  if(game->names) { 
    for(; game->size; game->size--) { free(game->names[game->size-1]); }
    free(game->names);
  }
  if(game->cardTypes) {
    for(; game->numTypes; game->numTypes--) { free(game->cardTypes[game->numTypes-1]); }
    free(game->cardTypes);
  }
  if(game->tradeIns) { free(game->tradeIns); }
  if(game->contBonuses) { free(game->contBonuses); }
  if(game->continents) {
    for(; game->numConts; game->numConts--) { free(game->continents[game->numConts-1]); }
    free(game->continents);
  }
  int tmp = game->numCountries;
  if(game->countries) {
    for(; tmp; tmp--) { free(game->countries[tmp-1]); }
    free(game->countries);
  }
  if(game->board) {
    for(; game->numCountries; game->numCountries--) { free(game->board[game->numCountries-1]); }
    free(game->board);
  }
  free(game);
  //*game = NULL; // TODO make it risk_t **game??

  return RISK_NIL;
}

errRISK_t setPlayers(risk_t *game, int n, char **names) {
  if(!game) { return RISK_NIL_GAME; }
  if(n > 8 || n < 2) { return RISK_INVALID_PLAYERS; }
  if(!names) { return RISK_NIL_NAMES; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }

  //freeArr2D(&game->humans, game->hps);
  game->size = n;
  game->names = names; // TODO: copy

  return RISK_NIL;
}

errRISK_t getPlayers(risk_t *game, char ***names, int *players) {
  if(!game) { return RISK_NIL_GAME; }
  if(!names) { return RISK_NIL_NAMES; }
  if(!players) { return RISK_NIL_PLAYERS; }

  return RISK_NIL;
}

errRISK_t setTroops(risk_t *game, int beginning, int min, int bonus, int rand) {
  if(!game) { return RISK_NIL_GAME; }
  if(beginning < 0 || beginning > 256) { return RISK_INVALID_BEGINNING; }
  if(min < 0 || min > 256) { return RISK_INVALID_MINIMUM; }
  if(bonus < 0 || bonus > 256) { return RISK_INVALID_BONUS; }
  if(!(rand == 0 || rand == 1)) { return RISK_INVALID_RAND; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }

  game->beginning = beginning;
  game->minimum = min;
  game->bonus = bonus;
  game->random = rand;

  return RISK_NIL;
}

errRISK_t getTroops(risk_t *game, int *start, int *min, int *bonus) {
  if(!game) { return RISK_NIL_GAME; }
  if(!start) { return RISK_NIL_START; }
  if(!min) { return RISK_NIL_MIN; }
  if(!bonus) { return RISK_NIL_BONUS; }

  return RISK_NIL;
}

errRISK_t setDeck(risk_t *game, int wilds, char **types, int n) {
  if(!game) { return RISK_NIL_GAME; }
  if(!types) { return RISK_NIL_CARD_TYPES; }
  if(wilds < 0 || wilds > 256) { return RISK_INVALID_WILDS; }
  if(n < 0 || n > 256) { return RISK_INVALID_DECK; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }

  //freeArr2D(game->cardTypes, game->numTypes);
  game->wilds = wilds;
  game->cardTypes = types;  // TODO: malloc and copy
  game->numTypes = n;

  return RISK_NIL;
}

errRISK_t getDeck(risk_t *game, int *wilds, char ***types, int *size) {
  if(!game) { return RISK_NIL_GAME; }
  if(!wilds) { return RISK_NIL_WILDS; }
  if(!types) { return RISK_NIL_TYPES; }
  if(!size) { return RISK_NIL_SIZE; }

  return RISK_NIL;
}

errRISK_t setTrades(risk_t *game, int *trades, int n, int incr) {
  if(!game) { return RISK_NIL_GAME; }
  if(!trades) { return RISK_NIL_TRADEINS; }
  if(incr < 0 || incr > 256) { return RISK_INVALID_INCR; }
  if(n < 0 || n > 256) { return RISK_INVALID_TRADES_SET; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }

  //freeArr(&game->trades, game->numTrades);
  game->tradeIns = trades;  // TODO: copy
  game->numTrades = n;
  game->tradeIncr = incr;

  return RISK_NIL;
}

errRISK_t getTrades(risk_t *game, int **trades, int *n, int *incr) {
  if(!game) { return RISK_NIL_GAME; }
  if(!trades) { return RISK_NIL_TRADES; }
  if(!n) { return RISK_NIL_SIZE; }
  if(!incr) { return RISK_NIL_INCR; }

  return RISK_NIL;
}

errRISK_t setContinents(risk_t *game, char **continents, int n) {
  if(!game) { return RISK_NIL_GAME; }
  if(!continents) { return RISK_NIL_CONTINENTS; }
  if(n < 0 || n > 256) { return RISK_INVALID_CONTINENTS_SIZE; }
  if(game->contBonuses && game->numConts != n) { return RISK_INVALID_CONTINENTS_SIZE; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }

  //freeArr2D(&game->continents, game->numConts);
  game->continents = continents;  // TODO: copy
  game->numConts = n;

  return RISK_NIL;
}

errRISK_t getContinents(risk_t *game, char ***continents, int *size) {
  if(!game) { return RISK_NIL_GAME; }
  if(!continents) { return RISK_NIL_CONTINENTS; }
  if(!size) { return RISK_NIL_SIZE; }

  return RISK_NIL;
}

errRISK_t setContinentBonuses(risk_t *game, int *bonuses, int n) {
  if(!game) { return RISK_NIL_GAME; }
  if(!bonuses) { return RISK_NIL_COUNTRY_BONUSES; }
  if(n < 0 || n > 256) { return RISK_INVALID_CONTINENTS_SIZE; }
  if(game->continents && game->numConts != n) { return RISK_INVALID_CONTINENTS_SIZE; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }

  //freeArr2D(&game->contBonuses, game->contBonuses);
  game->contBonuses = bonuses;  // TODO: copy
  game->numConts = n;

  return RISK_NIL;
}

errRISK_t getContinentBonus(risk_t *game, char *continent, int *bonus) {
  if(!game) { return RISK_NIL_GAME; }
  if(!continent) { return RISK_NIL_CONTINENT; }
  if(!bonus) { return RISK_NIL_BONUS; }

  return RISK_NIL;
}

errRISK_t getContinentBonuses(risk_t *game, int **bonuses, int *size) {
  if(!game) { return RISK_NIL_GAME; }
  if(!bonuses) { return RISK_NIL_BONUSES; }
  if(!size) { return RISK_NIL_SIZE; }

  return RISK_NIL;
}

errRISK_t setCountries(risk_t *game, char **countries, int n, int rand) {
  if(!game) { return RISK_NIL_GAME; }
  if(!countries) { return RISK_NIL_COUNTRIES; }
  if(!(rand == 1 || rand == 0)) { return RISK_INVALID_RAND; }
  if(n < 0 || n > 256) { return RISK_INVALID_COUNTRIES_SIZE; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }
  if(game->board && game->numCountries != n) { return RISK_COUNTRIES_MISMATCH; }

  //freeArr2D(&game->countries, game->numCountries);
  game->countries = countries;  // TODO: copy
  game->numCountries = n;
  game->randomCountries = rand;

  return RISK_NIL;
}

errRISK_t getCountries(risk_t *game, char ***countries, int *size) {
  if(!game) { return RISK_NIL_GAME; }
  if(!countries) { return RISK_NIL_COUNTRIES; }
  if(!size) { return RISK_NIL_SIZE; }

  return RISK_NIL;
}

errRISK_t setAdjacencies(risk_t *game, char *country, char **countries, int conflicts) {
  if(!game) { return RISK_NIL_GAME; }
  //if(!board) { return RISK_NIL_BOARD; }
  //if(n < 0 || n > 256) { return RISK_INVALID_BOARD_SIZE; }
  if(game->playing) { return RISK_GAME_PLAY_MUTATION; }
  //if(game->countries && game->numCountries != n) { return RISK_COUNTRIES_MISMATCH; }

/*
    for(; j; j--) {
      for(k = n; k; k--) {
        if(!strcmp(sarr1[k-1], sarr2[j-1])) {
          matrix[i][k-1] = 1;
          break;
        }
      }
    }
 */

  // freeArr2D(game->board, game->numCountries);
  //game->board = board;  // TODO: copy
  //game->numCountries = n;

  return RISK_NIL;
}

errRISK_t getNeighbors(risk_t *game, char *country, char ***neighbors, int *size) {
  if(!game) { return RISK_NIL_GAME; }
  if(!country) { return RISK_NIL_COUNTRY; }
  if(!neighbors) { return RISK_NIL_CONFLICTS; }
  if(!size) { return RISK_NIL_SIZE; }

  return RISK_NIL;
}

errRISK_t isValid(risk_t *game) { // FIXME: make sure entire conf is sane
  if(!game) { return RISK_NIL_GAME; }
  if(!game->cardTypes) { return RISK_NIL_CARD_TYPES; }
  if(!game->tradeIns) { return RISK_NIL_TRADEINS; }
  if(!game->names) { return RISK_NIL_NAMES; }
  if(!game->continents) { return RISK_NIL_CONTINENTS; }
  if(!game->contBonuses) { return RISK_NIL_COUNTRY_BONUSES; }
  if(!game->countries) { return RISK_NIL_COUNTRIES; }
  if(!game->board) { return RISK_NIL_BOARD; }
  if(game->size > 8 || game->size < 2) { return RISK_INVALID_PLAYERS; }
  if(!(game->random == 0 || game->random == 1)) { return RISK_INVALID_RAND; }
  if(!(game->randomCountries == 1 || game->randomCountries == 0)) { return RISK_INVALID_RAND; }
  if(game->tradeIncr < 0 || game->tradeIncr > 256) { return RISK_INVALID_INCR; }
  if(game->beginning < 0 || game->beginning > 256) { return RISK_INVALID_BEGINNING; }
  if(game->minimum < 0 || game->minimum > 256) { return RISK_INVALID_MINIMUM; }
  if(game->bonus < 0 || game->bonus > 256) { return RISK_INVALID_BONUS; }
  if(game->wilds < 0 || game->wilds > 256) { return RISK_INVALID_WILDS; }
  if(game->numTrades < 0 || game->numTrades > 256) { return RISK_INVALID_DECK; }
  if(game->numTypes < 0 || game->numTypes > 256) { return RISK_INVALID_TRADES_SET; }
  if(game->numConts < 0 || game->numConts > 256) { return RISK_INVALID_CONTINENTS_SIZE; }
  if(game->numCountries < 0 || game->numCountries > 256) { return RISK_INVALID_COUNTRIES_SIZE; }
  if(game->numCountries < game->numConts) { return RISK_INVALID_COUNTRY_CONTINENT; }
  return RISK_NIL;  
}

errRISK_t setOwner(risk_t *game, char *country, char *player) {
  if(!game) { return RISK_NIL_GAME; }
  if(!country) { return RISK_NIL_COUNTRY; }
  if(!player) { return RISK_NIL_PLAYER; }

  return RISK_NIL;
}

errRISK_t getOwner(risk_t *game, char *country, char **player) {
  if(!game) { return RISK_NIL_GAME; }
  if(!country) { return RISK_NIL_COUNTRY; }
  if(!player) { return RISK_NIL_PLAYER; }

  return RISK_NIL;
}

errRISK_t setArmies(risk_t *game, char *country, int troops) {
  if(!game) { return RISK_NIL_GAME; }
  if(!country) { return RISK_NIL_COUNTRY; }
  if(!troops) { return RISK_NIL_TROOPS; }

  return RISK_NIL;
}

errRISK_t getArmies(risk_t *game, char *country, int *troops) {
  if(!game) { return RISK_NIL_GAME; }
  if(!country) { return RISK_NIL_COUNTRY; }
  if(!troops) { return RISK_NIL_TROOPS; }

  return RISK_NIL;
}

errRISK_t setRandomCountries(risk_t *game, int rand) {
  if(!game) { return RISK_NIL_GAME; }
  if(!(rand == 0 || rand == 1)) { return RISK_INVALID_RAND; }

  return RISK_NIL;
}

errRISK_t setRandomArmies(risk_t *game, int rand) {
  if(!game) { return RISK_NIL_GAME; }
  if(!(rand == 0 || rand == 1)) { return RISK_INVALID_RAND; }

  return RISK_NIL;
}

errRISK_t getNextTradeValue(risk_t *game, int *troops) {
  if(!game) { return RISK_NIL_GAME; }
  if(!troops) { return RISK_NIL_TROOPS; }

  return RISK_NIL;
}

errRISK_t drawCard(risk_t *game, char **card) {
  if(!game) { return RISK_NIL_GAME; }
  if(!card) { return RISK_NIL_CARD; }

  return RISK_NIL;
}

errRISK_t tradeCards(risk_t *game, char **cards, int *troops) {
  if(!game) { return RISK_NIL_GAME; }
  if(!cards) { return RISK_NIL_CARD; }
  if(!troops) { return RISK_NIL_TROOPS; }

  return RISK_NIL;
}

errRISK_t attack(risk_t *game, char *src, int attack, char *dest, int defence, int *result) {
  if(!game) { return RISK_NIL_GAME; }
  if(!src) { return RISK_NIL_SRC; }
  if(attack < 1 || attack > 3) { return RISK_INVALID_ATTACK; }
  if(!dest) { return RISK_NIL_DEST; }
  if(defence < 1 || defence > 2) { return RISK_INVALID_DEFENCE; }
  if(!result) { return RISK_NIL_RESULT; }

  return RISK_NIL;
}

errRISK_t initDeck(risk_t *game) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;
}

errRISK_t initCountries(risk_t *game) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;
}

errRISK_t initArmies(risk_t *game) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;
}
