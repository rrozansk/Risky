/******************************************************************************
 * FILE:    risk.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  9/9/17                                                            *
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
  char **players;                 /* array of player names */
  char playersN;
  /* TROOPS */
  int starting;                   /* troops at game start */
  int minimum;                    /* minimum troop/turn */
  int bonus;                      /* countries/troop bonus */
  char randomTroops;              /* randomly distribute player troops at game start */
  /* CARDS */
  char **types;                   /* array of card types */
  int typesN;                     /* number of types and the required number of cards per trade in */
  int wilds;
  int *tradeRewards;              /* array of trade in bonuses */
  int tradeRewardsN;               
  int tradeIncrReward;            /* constant trade increment */
  /* MAP */
  char **continents;              /* array of continents */
  int continentsN;
  int *continentBonuses;          /* array of contnent bonuses */
  int continentBonusesN;          
  char **countries;               /* array of countries */
  int countriesN;
  char randomCountries;           /* randomly assign countries to players at game start */
  char validated;                 /* track if user validated game so we dont have to at start */
  char playing;                   /* locks game settings during gameplay */
};

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrRISK(errRISK_t errRISK) {
  switch(errRISK) {
    // MISC ERRORS
    case RISK_OUT_OF_MEMORY: return "out of memory";
    case RISK_GAMEPLAY_MUTATION: return "mutation of game setting during gameplay is prohibited";
    // INVALID ERRORS
    case RISK_INVALID_PLAYER_COUNT: return "players must be between 2-8";
    case RISK_INVALID_INDEX: return "invalid index";
    case RISK_INVALID_STARTING_TROOPS: return "starting troop count must be >= 0";
    case RISK_INVALID_TROOP_BONUS: return "troop bonus must be >=0";
    case RISK_INVALID_TROOP_MINIMUM: return "troop minimum must be >=0";
    case RISK_INVALID_TROOP_RANDOM: return "troop random must be 0 or 1";
    case RISK_INVALID_DECK_WILDS: return "deck wilds must be >= 0";
    case RISK_INVALID_CARD_TYPES_COUNT: return "deck card types must be between >= 0";
    case RISK_INVALID_REWARDS_COUNT: return "rewards length must be >= 0";
    case RISK_INVALID_LENGTH: return "n must be >= 0 and < length of the array";
    case RISK_INVALID_INCREMENT: return "increment must be >= 0";
    case RISK_INVALID_COUNTRIES_COUNT: return "countries must be >= 0";
    case RISK_INVALID_RANDOM: return "random must be 1 or 0";
    // NIL ERRORS
    case RISK_NIL_GAME: return "nil game";
    case RISK_NIL_ARR_PLAYERS: return "player names array is nil";
    case RISK_NIL_ARR_PLAYER: return "player names array contains a nil name";
    case RISK_NIL_PLAYERS: return "players must be non nil";
    case RISK_NIL_PLAYER: return "player must be non nil";
    case RISK_NIL_LENGTH: return "n must be non nil";
    case RISK_NIL_STARTING_TROOPS: return "starting troop count must be non nil";
    case RISK_NIL_TROOP_BONUS: return "troop bonus must be non nil";
    case RISK_NIL_TROOP_MINIMUM: return "troop minimum must be non nil";
    case RISK_NIL_TROOP_RANDOM: return "troop random must be non nil";
    case RISK_NIL_DECK_WILDS: return "deck wilds must be non nil";
    case RISK_NIL_CARD_TYPES: return "deck card types must be non nil";
    case RISK_NIL_TYPES: return "deck card types must be non nil";
    case RISK_NIL_TYPE: return "deck card type must be non nil";
    case RISK_NIL_ARR_REWARDS: return "rewards must be non nil";
    case RISK_NIL_REWARDS: return "rewards must be non nil";
    case RISK_NIL_INCREMENT: return "increment must be non nil";
    case RISK_NIL_ARR_CONTINENTS: return "continents array must be non nil";
    case RISK_NIL_ARR_CONTINENT: return "continents array contains a nil element";
    case RISK_NIL_CONTINENTS: return "continents must be non nil";
    case RISK_NIL_CONTINENT: return "continent must be non nil";
    case RISK_NIL_ARR_BONUSES: return "bonuses array must be non nil";
    case RISK_NIL_BONUSES: return "bonuses must be non nil";
    case RISK_NIL_ARR_COUNTRIES: return "countries must be non nil";
    case RISK_NIL_ARR_COUNTRY: return "country in countries array must be non nil";
    case RISK_NIL_COUNTRIES: return "countries must be non nil";
    case RISK_NIL_COUNTRY: return "country must be non nil";
    case RISK_NIL_RANDOM: return "random must be non nil";
    case RISK_NIL: return "";
    default: return "unrecognized errRISK_t";
  }
}

errRISK_t makeRISK(risk_t **game) {
  if(!game) { return RISK_NIL_GAME; }

  if(!(*game = calloc(1, sizeof(risk_t)))) { return RISK_OUT_OF_MEMORY; }

  return RISK_NIL;
}

errRISK_t freeRISK(risk_t *game) {
  if(!game) { return RISK_NIL; }

  for(; game->playersN; game->playersN--) { free(game->players[game->playersN-1]); }
  free(game->players);

  for(; game->typesN; game->typesN--) { free(game->types[game->typesN-1]); }
  free(game->types);

  free(game->tradeRewards);

  for(; game->continentsN; game->continentsN--) { free(game->continents[game->continentsN-1]); }
  free(game->continents);
  
  free(game->continentBonuses);

  for(; game->countriesN; game->countriesN--) { free(game->countries[game->countriesN-1]); }
  free(game->countries);

  free(game);

  return RISK_NIL;
}

errRISK_t setPlayers(risk_t *game, int n, char *players[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n > 8 || n < 2) { return RISK_INVALID_PLAYER_COUNT; }
  if(!players) { return RISK_NIL_ARR_PLAYERS; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }
 
  game->validated = 0;

  for(; game->playersN; game->playersN--) { free(game->players[game->playersN-1]); }
  free(game->players);

  game->playersN = n;

  for(; n; n--) { if(!players[n-1]) { return RISK_NIL_ARR_PLAYER; } }

  if(!(game->players = malloc(sizeof(char *) * game->playersN))) {
    game->players = NULL;
    game->playersN = 0;
    return RISK_OUT_OF_MEMORY;
  }

  for(n = 0; n < game->playersN; n++) {
    if(!(game->players[n] = calloc(strlen(players[n])+1, sizeof(char)))) {
      for(; n; n--) { free(game->players[n-1]); }
      free(game->players);
      game->players = NULL;
      game->playersN = 0;
      return RISK_OUT_OF_MEMORY;
    }

    strcpy(game->players[n], players[n]);
  }

  return RISK_NIL;
}

errRISK_t getLengthPlayers(risk_t *game, int *players) {
  if(!game) { return RISK_NIL_GAME; }
  if(!players) { return RISK_NIL_PLAYERS; }

  *players = game->playersN;

  return RISK_NIL;
}

errRISK_t getLengthPlayersElem(risk_t *game, int idx, int *n) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->playersN) { return RISK_INVALID_INDEX; }
  if(!n) { return RISK_NIL_LENGTH; }

  *n = strlen(game->players[idx]);

  return RISK_NIL;
}

errRISK_t getPlayer(risk_t *game, int idx, char *player) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->playersN) { return RISK_INVALID_INDEX; }
  if(!player) { return RISK_NIL_PLAYER; }

  strcpy(player, game->players[idx]);

  return RISK_NIL;  
}

errRISK_t setStartingTroopCount(risk_t *game, int start) {
  if(!game) { return RISK_NIL_GAME; }
  if(start < 0) { return RISK_INVALID_STARTING_TROOPS; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;
  game->starting = start;

  return RISK_NIL;  
}

errRISK_t getStartingTroopCount(risk_t *game, int *start) {
  if(!game) { return RISK_NIL_GAME; }
  if(!start) { return RISK_NIL_STARTING_TROOPS; }

  *start = game->starting;

  return RISK_NIL;  
}

errRISK_t setTroopTerritoryBonus(risk_t *game, int bonus) {
  if(!game) { return RISK_NIL_GAME; }
  if(bonus < 0) { return RISK_INVALID_TROOP_BONUS; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;
  game->bonus = bonus;

  return RISK_NIL;
}

errRISK_t getTroopTerritoryBonus(risk_t *game, int *bonus) {
  if(!game) { return RISK_NIL_GAME; }
  if(!bonus) { return RISK_NIL_TROOP_BONUS; }

  *bonus = game->bonus;

  return RISK_NIL;  
}

errRISK_t setMinimumTroopHandout(risk_t *game, int minimum) {
  if(!game) { return RISK_NIL_GAME; }
  if(minimum < 0) { return RISK_INVALID_TROOP_MINIMUM; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;
  game->minimum = minimum;

  return RISK_NIL;  
}

errRISK_t getMinimumTroopHandout(risk_t *game, int *minimum) {
  if(!game) { return RISK_NIL_GAME; }
  if(!minimum) { return RISK_NIL_TROOP_MINIMUM; }

  *minimum = game->minimum;

  return RISK_NIL;  
}

errRISK_t setRandomTroops(risk_t *game, int random) {
  if(!game) { return RISK_NIL_GAME; }
  if(!(random == 0 || random == 1)) { return RISK_INVALID_TROOP_RANDOM; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;
  game->randomTroops = random;

  return RISK_NIL;  
}

errRISK_t getRandomTroops(risk_t *game, int *random) {
  if(!game) { return RISK_NIL_GAME; }
  if(!random) { return RISK_NIL_TROOP_RANDOM; }

  *random = game->randomTroops;

  return RISK_NIL;  
}

errRISK_t setDeckWilds(risk_t *game, int wilds) {
  if(!game) { return RISK_NIL_GAME; }
  if(wilds < 0) { return RISK_INVALID_DECK_WILDS; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;
  game->wilds = wilds;

  return RISK_NIL;  
}

errRISK_t getDeckWilds(risk_t *game, int *wilds) {
  if(!game) { return RISK_NIL_GAME; }
  if(!wilds) { return RISK_NIL_DECK_WILDS; }

  *wilds = game->wilds;

  return RISK_NIL;  
}

errRISK_t setDeckTypes(risk_t *game, int n, char *types[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n < 0) { return RISK_INVALID_CARD_TYPES_COUNT; }
  if(!types) { return RISK_NIL_CARD_TYPES; }

  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;

  for(; game->typesN;) { free(game->types[game->typesN--]); }
  free(game->types);

  game->typesN = n;

  for(; n; n--) { if(!types[n-1]) { return RISK_NIL_TYPE; } }

  if(!(game->types = malloc(sizeof(char *) * game->typesN))) {
    game->types = NULL;
    game->typesN = 0;
    return RISK_OUT_OF_MEMORY;
  }

  for(n = 0; n < game->typesN; n++) {
    if(!(game->types[n] = calloc(strlen(types[n])+1, sizeof(char)))) {
      for(; n; n--) { free(game->types[n-1]); }
      free(game->types);
      game->types = NULL;
      game->typesN = 0;
      return RISK_OUT_OF_MEMORY;
    }

    strcpy(game->types[n], types[n]);
  }

  return RISK_NIL;  
}

errRISK_t getLengthDeckTypes(risk_t *game, int *types) {
  if(!game) { return RISK_NIL_GAME; }
  if(!types) { return RISK_NIL_TYPES; }

  *types = game->typesN;

  return RISK_NIL;  
}

errRISK_t getLengthDeckTypesElem(risk_t *game, int idx, int *n) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->typesN) { return RISK_INVALID_INDEX; }
  if(!n) { return RISK_NIL_LENGTH; }

  *n = strlen(game->types[idx]);

  return RISK_NIL;  
}

errRISK_t getDeckTypesElem(risk_t *game, int idx, char *type) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->typesN) { return RISK_INVALID_INDEX; }
  if(!type) { return RISK_NIL_TYPE; }

  strcpy(type, game->types[idx]);

  return RISK_NIL;  
}

errRISK_t setTradeRewards(risk_t *game, int n, int rewards[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n < 0) { return RISK_INVALID_REWARDS_COUNT; }
  if(!rewards) { return RISK_NIL_ARR_REWARDS; }

  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;

  free(game->tradeRewards);

  if(!(game->tradeRewards = calloc(n, sizeof(int)))) {
    game->tradeRewards = NULL;
    game->tradeRewardsN = 0;
    return RISK_OUT_OF_MEMORY;
  }

  game->tradeRewardsN = n;
  for(; n; n--) { game->tradeRewards[n-1] = rewards[n-1]; }

  return RISK_NIL;  
}

errRISK_t getLengthTradeRewards(risk_t *game, int *rewards) {
  if(!game) { return RISK_NIL_GAME; }
  if(!rewards) { return RISK_NIL_REWARDS; }

  *rewards = game->tradeRewardsN;

  return RISK_NIL;  
}

errRISK_t getTradeRewards(risk_t *game, int n, int rewards[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n < 0 || n > game->tradeRewardsN) { return RISK_INVALID_LENGTH; }
  if(!rewards) { return RISK_NIL_REWARDS; }

  for(; n; n--) { rewards[n-1] = game->tradeRewards[n-1]; }

  return RISK_NIL;  
}

errRISK_t setTradeIncrReward(risk_t *game, int incr) {
  if(!game) { return RISK_NIL_GAME; }
  if(incr< 0) { return RISK_INVALID_INCREMENT; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;
  game->tradeIncrReward = incr;

  return RISK_NIL;  
}

errRISK_t getTradeIncrReward(risk_t *game, int *incr) {
  if(!game) { return RISK_NIL_GAME; }
  if(!incr) { return RISK_NIL_INCREMENT; }

  *incr = game->tradeIncrReward;

  return RISK_NIL;  
}

errRISK_t setContinents(risk_t *game, int n, char *continents[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n < 0) { return RISK_INVALID_LENGTH; }
  if(!continents) { return RISK_NIL_ARR_CONTINENTS; }

  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;

  for(; game->continentsN;) { free(game->continents[game->continentsN--]); }
  free(game->continents);

  game->continentsN = n;

  for(; n; n--) { if(!continents[n-1]) { return RISK_NIL_ARR_CONTINENT; } }

  if(!(game->continents = malloc(sizeof(char *) * game->continentsN))) {
    game->continents = NULL;
    game->continentsN = 0;
    return RISK_OUT_OF_MEMORY;
  }

  for(n = 0; n < game->continentsN; n++) {
    if(!(game->continents[n] = calloc(strlen(continents[n])+1, sizeof(char)))) {
      for(; n; n--) { free(game->continents[n-1]); }
      free(game->continents);
      game->continents = NULL;
      game->continentsN = 0;
      return RISK_OUT_OF_MEMORY;
    }

    strcpy(game->continents[n], continents[n]);
  }

  return RISK_NIL;  
}

errRISK_t getLengthContinents(risk_t *game, int *continents) {
  if(!game) { return RISK_NIL_GAME; }
  if(!continents) { return RISK_NIL_CONTINENTS; }

  *continents = game->continentsN;

  return RISK_NIL;  
}

errRISK_t getLengthContinentsElem(risk_t *game, int idx, int *n) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->continentsN) { return RISK_INVALID_INDEX; }
  if(!n) { return RISK_NIL_LENGTH; }

  *n = strlen(game->continents[idx]);

  return RISK_NIL;
}

errRISK_t getContinentElem(risk_t *game, int idx, char *continent) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->continentsN) { return RISK_INVALID_INDEX; }
  if(!continent) { return RISK_NIL_CONTINENT; }

  strcpy(continent, game->continents[idx]);

  return RISK_NIL;  
}

errRISK_t setContinentBonuses(risk_t *game, int n, int bonuses[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n < 0) { return RISK_INVALID_LENGTH; }
  if(!bonuses) { return RISK_NIL_ARR_BONUSES; }

  if(game->continentBonuses) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;

  free(game->continentBonuses);

  if(!(game->continentBonuses = calloc(n, sizeof(int)))) {
    game->continentBonuses = NULL;
    game->continentBonusesN = 0;
    return RISK_OUT_OF_MEMORY;
  }

  game->continentBonusesN = n;
  for(; n; n--) { game->continentBonuses[n-1] = bonuses[n-1]; }

  return RISK_NIL;  
}

errRISK_t getLengthContinentBonuses(risk_t *game, int *bonuses) {
  if(!game) { return RISK_NIL_GAME; }
  if(!bonuses) { return RISK_NIL_BONUSES; }

  *bonuses = game->continentBonusesN;

  return RISK_NIL;  
}

errRISK_t getContinentBonuses(risk_t *game, int n, int bonuses[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n < 0 || n > game->continentBonusesN) { return RISK_INVALID_LENGTH; }
  if(!bonuses) { return RISK_NIL_ARR_BONUSES; }

  for(; n; n--) { bonuses[n-1] = game->continentBonuses[n-1]; }

  return RISK_NIL;  
}

errRISK_t setCountries(risk_t *game, int n, char *countries[]) {
  if(!game) { return RISK_NIL_GAME; }
  if(n < 0) { return RISK_INVALID_COUNTRIES_COUNT; }
  if(!countries) { return RISK_NIL_ARR_COUNTRIES; }

  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;

  for(; game->countriesN;) { free(game->countries[game->countriesN--]); }
  free(game->countries);

  game->countriesN = n;

  for(; n; n--) { if(!countries[n-1]) { return RISK_NIL_ARR_COUNTRY; } }

  if(!(game->countries = malloc(sizeof(char *) * game->countriesN))) {
    game->countries = NULL;
    game->countriesN = 0;
    return RISK_OUT_OF_MEMORY;
  }

  for(n = 0; n < game->countriesN; n++) {
    if(!(game->countries[n] = calloc(strlen(countries[n])+1, sizeof(char)))) {
      for(; n; n--) { free(game->countries[n-1]); }
      free(game->countries);
      game->countries = NULL;
      game->countriesN = 0;
      return RISK_OUT_OF_MEMORY;
    }

    strcpy(game->countries[n], countries[n]);
  }

  return RISK_NIL;  
}

errRISK_t getLengthCountries(risk_t *game, int *countries) {
  if(!game) { return RISK_NIL_GAME; }
  if(!countries) { return RISK_NIL_COUNTRIES; }

  *countries = game->countriesN;

  return RISK_NIL;  
}

errRISK_t getLengthCountriesElem(risk_t *game, int idx, int *n) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->countriesN) { return RISK_INVALID_INDEX; }
  if(!n) { return RISK_NIL_LENGTH; }

  *n = strlen(game->countries[idx]);

  return RISK_NIL;  
}

errRISK_t getCountryElem(risk_t *game, int idx, char *country) {
  if(!game) { return RISK_NIL_GAME; }
  if(idx < 0 || idx >= game->countriesN) { return RISK_INVALID_INDEX; }
  if(!country) { return RISK_NIL_COUNTRY; }

  strcpy(country, game->countries[idx]);

  return RISK_NIL;  
}

errRISK_t setRandomCountries(risk_t *game, int random) {
  if(!game) { return RISK_NIL_GAME; }
  if(!(random == 0 || random == 1)) { return RISK_INVALID_RANDOM; }
  if(game->playing) { return RISK_GAMEPLAY_MUTATION; }

  game->validated = 0;
  game->randomCountries = random;

  return RISK_NIL;  
}

errRISK_t getRandomCountries(risk_t *game, int *random) {
  if(!game) { return RISK_NIL_GAME; }
  if(!random) { return RISK_NIL_RANDOM; }

  *random = game->randomCountries;

  return RISK_NIL;  
}

// TODO: these APIs need an internal board representation to work.
// ... still need to work out the data structures for book keeping. 
errRISK_t setBorders(risk_t *game, char *country, int n, char *countries[]) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t getLengthBorders(risk_t *game, char *country, int *countries) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t getLengthBordersElem(risk_t *game, char *country, int idx, int *n) {
  if(!game) { return RISK_NIL_GAME; }

  if(!n) { return RISK_NIL_LENGTH; }

  return RISK_NIL;  
}

errRISK_t getBordersElem(risk_t *game, char *country, int idx, char *neighbor) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t setContinentSet(risk_t *game, char *continent, int n, char *countries[]) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t getContinentSetLength(risk_t *game, char *continent, int *countries) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t getContinentSetLengthElem(risk_t *game, char *continent, int idx, int *n) {
  if(!game) { return RISK_NIL_GAME; }

  if(!n) { return RISK_NIL_LENGTH; }

  return RISK_NIL;  
}

errRISK_t getContinentSetElem(risk_t *game, char *continent, int idx, char *country) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t setOwner(risk_t *game, char *country, char *player) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t getOwnerLength(risk_t *game, char *country, int *n) {
  if(!game) { return RISK_NIL_GAME; }

  if(!n) { return RISK_NIL_LENGTH; }

  return RISK_NIL;  
}

errRISK_t getOwner(risk_t *game, char *country, char *player) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t reinforce(risk_t *game, char *country, int troops) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t getTroops(risk_t *game, char *country, int *troops) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t valid(risk_t *game) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}

errRISK_t start(risk_t *game) {
  if(!game) { return RISK_NIL_GAME; }

  game->playing = 1;

  return RISK_NIL;  
}

errRISK_t end(risk_t *game) {
  if(!game) { return RISK_NIL_GAME; }

  return RISK_NIL;  
}
