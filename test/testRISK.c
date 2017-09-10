/******************************************************************************
 * FILE:    testRISK.c                                                        *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  9/9/17                                                            *
 * INFO:    Test file for implementation of the interface located in risk.h.  *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <risk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 224

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultRISK { RISK_PASS, RISK_FAIL } testResultRISK_t;

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/
testResultRISK_t testStrErrRISK_OUT_OF_MEMORY() {
  return (strcmp(strErrRISK(RISK_OUT_OF_MEMORY), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t  testStrErrRISK_GAMEPLAY_MUTATION() {
  return (strcmp(strErrRISK(RISK_GAMEPLAY_MUTATION), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_PLAYER_COUNT() {
  return (strcmp(strErrRISK(RISK_INVALID_PLAYER_COUNT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_INDEX() {
  return (strcmp(strErrRISK(RISK_INVALID_INDEX), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_STARTING_TROOPS() {
  return (strcmp(strErrRISK(RISK_INVALID_STARTING_TROOPS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_TROOP_BONUS() {
  return (strcmp(strErrRISK(RISK_INVALID_TROOP_BONUS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_TROOP_MINIMUM() {
  return (strcmp(strErrRISK(RISK_INVALID_TROOP_MINIMUM), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_TROOP_RANDOM() {
  return (strcmp(strErrRISK(RISK_INVALID_TROOP_RANDOM), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_DECK_WILDS() {
  return (strcmp(strErrRISK(RISK_INVALID_DECK_WILDS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_CARD_TYPES_COUNT() {
  return (strcmp(strErrRISK(RISK_INVALID_CARD_TYPES_COUNT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_REWARDS_COUNT() {
  return (strcmp(strErrRISK(RISK_INVALID_REWARDS_COUNT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_LENGTH() {
  return (strcmp(strErrRISK(RISK_INVALID_LENGTH), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_INCREMENT() {
  return (strcmp(strErrRISK(RISK_INVALID_INCREMENT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_COUNTRIES_COUNT() {
  return (strcmp(strErrRISK(RISK_INVALID_COUNTRIES_COUNT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_INVALID_RANDOM() {
  return (strcmp(strErrRISK(RISK_INVALID_RANDOM), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_GAME() {
  return (strcmp(strErrRISK(RISK_NIL_GAME), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_PLAYERS() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_PLAYERS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_PLAYER() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_PLAYER), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_PLAYERS() {
  return (strcmp(strErrRISK(RISK_NIL_PLAYERS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_PLAYER() {
  return (strcmp(strErrRISK(RISK_NIL_PLAYER), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_LENGTH() {
  return (strcmp(strErrRISK(RISK_NIL_LENGTH), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_STARTING_TROOPS() {
  return (strcmp(strErrRISK(RISK_NIL_STARTING_TROOPS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_TROOP_BONUS() {
  return (strcmp(strErrRISK(RISK_NIL_TROOP_BONUS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_TROOP_MINIMUM() {
  return (strcmp(strErrRISK(RISK_NIL_TROOP_MINIMUM), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_TROOP_RANDOM() {
  return (strcmp(strErrRISK(RISK_NIL_TROOP_RANDOM), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_DECK_WILDS() {
  return (strcmp(strErrRISK(RISK_NIL_DECK_WILDS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_CARD_TYPES() {
  return (strcmp(strErrRISK(RISK_NIL_CARD_TYPES), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_TYPES() {
  return (strcmp(strErrRISK(RISK_NIL_TYPES), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_TYPE() {
  return (strcmp(strErrRISK(RISK_NIL_TYPE), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_REWARDS() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_REWARDS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_REWARDS() {
  return (strcmp(strErrRISK(RISK_NIL_REWARDS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_INCREMENT() {
  return (strcmp(strErrRISK(RISK_NIL_INCREMENT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_CONTINENTS() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_CONTINENTS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_CONTINENT() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_CONTINENT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_CONTINENTS() {
  return (strcmp(strErrRISK(RISK_NIL_CONTINENTS), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_CONTINENT() {
  return (strcmp(strErrRISK(RISK_NIL_CONTINENT), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_BONUSES() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_BONUSES), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_BONUSES() {
  return (strcmp(strErrRISK(RISK_NIL_BONUSES), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_COUNTRIES() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_COUNTRIES), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_ARR_COUNTRY() {
  return (strcmp(strErrRISK(RISK_NIL_ARR_COUNTRY), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_COUNTRIES() {
  return (strcmp(strErrRISK(RISK_NIL_COUNTRIES), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_COUNTRY() {
  return (strcmp(strErrRISK(RISK_NIL_COUNTRY), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL_RANDOM() {
  return (strcmp(strErrRISK(RISK_NIL_RANDOM), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testStrErrRISK_NIL() {
  return (!strcmp(strErrRISK(RISK_NIL), "")) ? RISK_PASS : RISK_FAIL; 
}

testResultRISK_t testMakeRISKNilGame() {
  return (makeRISK(NULL) != RISK_NIL_GAME) ? RISK_FAIL : RISK_PASS;
}

//testResultRISK_t testMakeRISKOutOfMemory() {} // RISK_OUT_OF_MEMORY

testResultRISK_t testMakeRISKValid() {
  risk_t *game;
  return (makeRISK(&game) != RISK_NIL) ? RISK_FAIL : RISK_PASS;
}

testResultRISK_t testFreeRISKNilGame() {
  return (freeRISK(NULL) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testFreeRISKValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (freeRISK(game) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetPlayersNilGame() {
  char *players[5];

  return (setPlayers(NULL, 5, players) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetPlayersInvalidPlayerCount() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[5];

  return (setPlayers(game, 1, players) == RISK_INVALID_PLAYER_COUNT) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetPlayersNilPlayers() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setPlayers(game, 5, NULL) == RISK_NIL_ARR_PLAYERS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetPlayersNilPlayer() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[5] = { "FOO", "BAR", "BAZ", NULL, "GARY" };

  return (setPlayers(game, 5, players) == RISK_NIL_ARR_PLAYER) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetPlayersGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[3] = { "FOO", "BAR", "BAZ" };

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setPlayers(game, 3, players) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

//testResultRISK_t testSetPlayersOutOfMemory() {} // RISK_OUT_OF_MEMORY;

testResultRISK_t testSetPlayersValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[3] = { "FOO", "BAR", "BAZ" };

  return (setPlayers(game, 3, players) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthPlayersNilGame() {
  int players;
  return (getLengthPlayers(NULL, &players) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthPlayersNilPlayers() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthPlayers(game, NULL) == RISK_NIL_PLAYERS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthPlayersValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int players = 1;

  return (getLengthPlayers(game, &players) == RISK_NIL && !players) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthPlayersElemNilGame() {
  int n;
  return (getLengthPlayersElem(NULL, 0, &n) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthPlayersElemInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthPlayersElem(game, -1, &n) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthPlayersElemNilLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[2] = { "FOO", "BAR" };
  if(setPlayers(game, 2, players) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthPlayersElem(game, 0, NULL) == RISK_NIL_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthPlayersElemValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[2] = { "FOO", "BAR" };
  if(setPlayers(game, 2, players) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthPlayersElem(game, 0, &n) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetPlayerNilGame() {
  char player[10];
  return (getPlayer(NULL, 0, player) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetPlayerInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char player[10];
  return (getPlayer(game, -1, player) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetPlayerNilPlayer() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[2] = { "FOO", "BAR" };
  if(setPlayers(game, 2, players) != RISK_NIL) { return RISK_FAIL; }

  return (getPlayer(game, 0, NULL) == RISK_NIL_PLAYER) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetPlayerValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *players[2] = { "FOO", "BAR" };
  if(setPlayers(game, 2, players) != RISK_NIL) { return RISK_FAIL; }

  char player[5];
  return (getPlayer(game, 0, player) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetStartingTroopCountNilGame() {
  return (setStartingTroopCount(NULL, 10) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetStartingTroopCountInvalidStart() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setStartingTroopCount(game, -1) == RISK_INVALID_STARTING_TROOPS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetStartingTroopCountGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setStartingTroopCount(game, 1) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetStartingTroopCountValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setStartingTroopCount(game, 1) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetStartingTroopCountNilGame() {
  int start;
  return (getStartingTroopCount(NULL, &start) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetStartingTroopCountNilStart() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getStartingTroopCount(game, NULL) == RISK_NIL_STARTING_TROOPS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetStartingTroopCountValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int start;
  return (getStartingTroopCount(game, &start) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTroopTerritoryBonusNilGame() {
  return (setTroopTerritoryBonus(NULL, 10) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTroopTerritoryBonusInvalidBonus() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setTroopTerritoryBonus(game, -1) == RISK_INVALID_TROOP_BONUS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTroopTerritoryBonusGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setTroopTerritoryBonus(game, 10) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTroopTerritoryBonusValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setTroopTerritoryBonus(game, 10) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}
  
testResultRISK_t testGetTroopTerritoryBonusNilGame() {
  int bonus;
  return (getTroopTerritoryBonus(NULL, &bonus) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTroopTerritoryBonusNilBonus() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getTroopTerritoryBonus(game, NULL) == RISK_NIL_TROOP_BONUS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTroopTerritoryBonusValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int bonus;
  return (getTroopTerritoryBonus(game, &bonus) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}
  
testResultRISK_t testSetMinimumTroopHandoutNilGame() {
  return (setMinimumTroopHandout(NULL, 5) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetMinimumTroopHandoutInvalidMinimum() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setMinimumTroopHandout(game, -1) == RISK_INVALID_TROOP_MINIMUM) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetMinimumTroopHandoutGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setMinimumTroopHandout(game, 0) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetMinimumTroopHandoutValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setMinimumTroopHandout(game, 0) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetMinimumTroopHandoutNilGame() {
  int minimum;
  return (getMinimumTroopHandout(NULL, &minimum) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetMinimumTroopHandoutNilMinimum() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getMinimumTroopHandout(game, NULL) == RISK_NIL_TROOP_MINIMUM) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetMinimumTroopHandoutValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int minimum;
  return (getMinimumTroopHandout(game, &minimum) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomTroopsNilGame() {
  return (setRandomTroops(NULL, 1) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomTroopsInvalidRandom() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setRandomTroops(game, 45) == RISK_INVALID_TROOP_RANDOM) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomTroopsGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setRandomTroops(game, 0) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomTroopsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setRandomTroops(game, 0) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetRandomTroopsNilGame() {
  int random;
  return (getRandomTroops(NULL, &random) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetRandomTroopsNilRandom() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getRandomTroops(game, NULL) == RISK_NIL_TROOP_RANDOM) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetRandomTroopsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int random;
  return (getRandomTroops(game, &random) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckWildsNilGame() {
  return (setDeckWilds(NULL, 10) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckWildsInvalidWilds() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setDeckWilds(game, -1) == RISK_INVALID_DECK_WILDS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckWildsGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setDeckWilds(game, 1) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckWildsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setDeckWilds(game, 1) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetDeckWildsNilGame() {
  int wilds;
  return (getDeckWilds(NULL, &wilds) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetDeckWildsNilWilds() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getDeckWilds(game, NULL) == RISK_NIL_DECK_WILDS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetDeckWildsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int wilds;
  return (getDeckWilds(game, &wilds) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckTypesNilGame() {
  char *types[3] = { "SOILDER", "CANNON", "CALVARY" };
  return (setDeckTypes(NULL, 3, types) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckTypesInvalidCardCount() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *types[3] = { "SOILDER", "CANNON", "CALVARY" };
  return (setDeckTypes(game, -1, types) == RISK_INVALID_CARD_TYPES_COUNT) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckTypesNilTypes() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setDeckTypes(game, 1, NULL) == RISK_NIL_CARD_TYPES) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckTypesGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  char *types[3] = { "SOILDER", "CANNON", "CALVARY" };
  return (setDeckTypes(game, 3, types) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetDeckTypesNilType() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *types[3] = { "SOILDER", NULL, "CALVARY" };
  return (setDeckTypes(game, 3, types) == RISK_NIL_TYPE) ? RISK_PASS : RISK_FAIL;
}

//testResultRISK_t testSetDeckTypesOutOfMemory() {} // OUT_OF_MEMORY

testResultRISK_t testSetDeckTypesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *types[3] = { "SOILDER", "CANNON", "CALVARY" };
  return (setDeckTypes(game, 3, types) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthDeckTypesNilGame() {
  int types;
  return (getLengthDeckTypes(NULL, &types) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthDeckTypesNilTypes() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthDeckTypes(game, NULL) == RISK_NIL_TYPES) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthDeckTypesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int types;
  return (getLengthDeckTypes(game, &types) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthDeckTypesElemNilGame() {
  int n;
  return (getLengthDeckTypesElem(NULL, 0, &n) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthDeckTypesElemInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthDeckTypesElem(game, -1, &n) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthDeckTypesElemNilLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *types[1] = { "SOILDER" };
  if(setDeckTypes(game, 1, types) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthDeckTypesElem(game, 0, NULL) == RISK_NIL_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthDeckTypesElemValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *types[1] = { "SOILDER" };
  if(setDeckTypes(game, 1, types) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthDeckTypesElem(game, 0, &n) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetDeckTypesElemNilGame() {
  char type[10];
  return (getDeckTypesElem(NULL, 0, type) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetDeckTypesElemInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char type[10];
  return (getDeckTypesElem(game, -1, type) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetDeckTypesElemNilType() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getDeckTypesElem(game, 0, NULL) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetDeckTypesElemValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *types[1] = { "SOILDER" };
  if(setDeckTypes(game, 1, types) != RISK_NIL) { return RISK_FAIL; }

  char type[10];
  return (getDeckTypesElem(game, 0, type) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeRewardsNilGame() {
  int rewards[5] = { 0, 1, 2, 3, 4 };
  return (setTradeRewards(NULL, 5, rewards) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeRewardsInvalidRewardsCount() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int rewards[5] = { 0, 1, 2, 3, 4 };
  return (setTradeRewards(game, -1, rewards) == RISK_INVALID_REWARDS_COUNT) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeRewardsNilRewards() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setTradeRewards(game, 0, NULL) == RISK_NIL_ARR_REWARDS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeRewardsGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  int rewards[5] = { 0, 1, 2, 3, 4 };
  return (setTradeRewards(game, 5, rewards) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

//testResultRISK_t testSetTradeRewardsOutOfMemory() {} // RISK_OUT_OF_MEMORY

testResultRISK_t testSetTradeRewardsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int rewards[5] = { 0, 1, 2, 3, 4 };
  return (setTradeRewards(game, 5, rewards) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthTradeRewardsNilGame() {
  int rewards;
  return (getLengthTradeRewards(NULL, &rewards) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthTradeRewardsNilRewards() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthTradeRewards(game, NULL) == RISK_NIL_REWARDS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthTradeRewardsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int rewards;
  return (getLengthTradeRewards(game, &rewards) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTradeRewardsNilGame() {
  int rewards[5];
  return (getTradeRewards(NULL, 0, rewards) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTradeRewardsInvalidLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int rewards[5];
  return (getTradeRewards(game, -1, rewards) == RISK_INVALID_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTradeRewardsNilRewards() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getTradeRewards(game, 0, NULL) == RISK_NIL_REWARDS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTradeRewardsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int rewards[5];
  return (getTradeRewards(game, 0, rewards) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeIncrRewardNilGame() {
  return (setTradeIncrReward(NULL, 20) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeIncrRewardInvalidIncrement() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setTradeIncrReward(game, -1) == RISK_INVALID_INCREMENT) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeIncrRewardGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setTradeIncrReward(game, 1) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetTradeIncrRewardValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setTradeIncrReward(game, 1) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTradeIncrRewardNilGame() {
  int increment;
  return (getTradeIncrReward(NULL, &increment) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTradeIncrRewardNilIncrement() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getTradeIncrReward(game, NULL) == RISK_NIL_INCREMENT) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetTradeIncrRewardValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int increment;
  return (getTradeIncrReward(game, &increment) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentsNilGame() {
  char *continents[3] = { "SOME", "TIME", "NEW" };
  return (setContinents(NULL, 0, continents) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentsInvalidLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", "TIME", "NEW" };
  return (setContinents(game, -1, continents) == RISK_INVALID_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentsNilContinents() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setContinents(game, 0, NULL) == RISK_NIL_ARR_CONTINENTS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentsGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", "TIME", "NEW" };
  return (setContinents(game, 3, continents) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentsNilContinent() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", NULL, "NEW" };
  return (setContinents(game, 3, continents) == RISK_NIL_ARR_CONTINENT) ? RISK_PASS : RISK_FAIL;
}

//testResultRISK_t testSetContinentsOutOfMemory() {} // RISK_OUT_OF_MEMORY

testResultRISK_t testSetContinentsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", "TIME", "NEW" };
  return (setContinents(game, 3, continents) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentsNilGame() {
  int continents;
  return (getLengthContinents(NULL, &continents) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentsNilContinents() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthContinents(game, NULL) == RISK_NIL_CONTINENTS) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentsValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int continents;
  return (getLengthContinents(game, &continents) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentsElemNilGame() {
  int n;
  return (getLengthContinentsElem(NULL, 0, &n) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentsElemInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthContinentsElem(game, -1, &n) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentsElemNilLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", "TIME", "NEW" };
  if(setContinents(game, 3, continents) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthContinentsElem(game, 0, NULL) == RISK_NIL_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentsElemValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", "TIME", "NEW" };
  if(setContinents(game, 3, continents) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthContinentsElem(game, 0, &n) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentElemNilGame() {
  char continent[10];
  return (getContinentElem(NULL, 0, continent) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentElemInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char continent[10];
  return (getContinentElem(game, -1, continent) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentElemNilContinent() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", "TIME", "NEW" };
  if(setContinents(game, 3, continents) != RISK_NIL) { return RISK_FAIL; }

  return (getContinentElem(game, 0, NULL) == RISK_NIL_CONTINENT) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentElemValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *continents[3] = { "SOME", "TIME", "NEW" };
  if(setContinents(game, 3, continents) != RISK_NIL) { return RISK_FAIL; }

  char continent[10];
  return (getContinentElem(game, 0, continent) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentBonusesNilGame() {
  int bonuses[5] = { 0, 1, 2, 3, 4 };
  return (setContinentBonuses(NULL, 5, bonuses) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentBonusesInvalidLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int bonuses[5] = { 0, 1, 2, 3, 4 };
  return (setContinentBonuses(game, -1, bonuses) == RISK_INVALID_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentBonusesNilBonuses() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setContinentBonuses(game, 0, NULL) == RISK_NIL_ARR_BONUSES) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetContinentBonusesGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  int bonuses[5] = { 0, 1, 2, 3, 4 };
  return (setContinentBonuses(game, 5, bonuses) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

//testResultRISK_t testSetContinentBonusesOutOfMemory() {} // RISK_OUT_OF_MEMORY

testResultRISK_t testSetContinentBonusesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int bonuses[5] = { 0, 1, 2, 3, 4 };
  return (setContinentBonuses(game, 5, bonuses) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentBonusesNilGame() {
  int bonuses;
  return (getLengthContinentBonuses(NULL, &bonuses) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentBonusesNilBonuses() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthContinentBonuses(game, NULL) == RISK_NIL_BONUSES) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthContinentBonusesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int bonuses;
  return (getLengthContinentBonuses(game, &bonuses) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentBonusesNilGame() {
  int bonuses[5];
  return (getContinentBonuses(NULL, 5, bonuses) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentBonusesInvalidLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int bonuses[5];
  return (getContinentBonuses(game, -1, bonuses) == RISK_INVALID_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentBonusesNilBonuses() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int bonuses[5] = { 0, 1, 2, 3, 4 };
  if(setContinentBonuses(game, 5, bonuses) != RISK_NIL) { return RISK_FAIL; }

  return (getContinentBonuses(game, 0, NULL) == RISK_NIL_ARR_BONUSES) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentBonusesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int bonuses[5] = { 0, 1, 2, 3, 4 };
  if(setContinentBonuses(game, 5, bonuses) != RISK_NIL) { return RISK_FAIL; }

  int _bonuses[5];
  return (getContinentBonuses(game, 5, _bonuses) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetCountriesNilGame() {
  char *countries[3] = { "FOO", "BAR", "BAZ" };
  return (setCountries(NULL, 3, countries) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetCountriesInvalidCountryCount() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", "BAR", "BAZ" };
  return (setCountries(game, -1, countries) == RISK_INVALID_COUNTRIES_COUNT) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetCountriesNilCountries() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setCountries(game, 1, NULL) == RISK_NIL_ARR_COUNTRIES) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetCountriesGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", "BAR", "BAZ" };
  return (setCountries(game, 3, countries) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetCountriesNilCountry() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", NULL, "BAZ" };
  return (setCountries(game, 3, countries) == RISK_NIL_ARR_COUNTRY) ? RISK_PASS : RISK_FAIL;
}

//testResultRISK_t testSetCountriesOutOfMemory() {} // RISK_OUT_OF_MEMORY

testResultRISK_t testSetCountriesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", "BAR", "BAZ" };
  return (setCountries(game, 3, countries) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthCountriesNilGame() {
  int countries;
  return (getLengthCountries(NULL, &countries) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthCountriesNilCountries() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthCountries(game, NULL) == RISK_NIL_COUNTRIES) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthCountriesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int countries;
  return (getLengthCountries(game, &countries) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthCountriesElemNilGame() {
  int n;
  return (getLengthCountriesElem(NULL, 0, &n) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthCountriesElemInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthCountriesElem(game, -1, &n) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthCountriesElemNilLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", "BAR", "BAZ" };
  if(setCountries(game, 3, countries) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthCountriesElem(game, 0, NULL) == RISK_NIL_LENGTH) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthCountriesElemValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", "BAR", "BAZ" };
  if(setCountries(game, 3, countries) != RISK_NIL) { return RISK_FAIL; }

  int n;
  return (getLengthCountriesElem(game, 0, &n) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetCountryElemNilGame() {
  char country[10];
  return (getCountryElem(NULL, 0, country) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetCountryElemInvalidIndex() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char country[10];
  return (getCountryElem(game, -1, country) == RISK_INVALID_INDEX) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetCountryElemNilCountry() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", "BAR", "BAZ" };
  if(setCountries(game, 3, countries) != RISK_NIL) { return RISK_FAIL; }

  return (getCountryElem(game, 0, NULL) == RISK_NIL_COUNTRY) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetCountryElemValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  char *countries[3] = { "FOO", "BAR", "BAZ" };
  if(setCountries(game, 3, countries) != RISK_NIL) { return RISK_FAIL; }

  char country[10];
  return (getCountryElem(game, 0, country) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomCountriesNilGame() {
  return (setRandomCountries(NULL, 0) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomCountriesInvalidRandom() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setRandomCountries(game, 10) == RISK_INVALID_RANDOM) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomCountriesGameplayMutation() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  if(start(game) != RISK_NIL) { return RISK_FAIL; }

  return (setRandomCountries(game, 0) == RISK_GAMEPLAY_MUTATION) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetRandomCountriesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (setRandomCountries(game, 0) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetRandomCountriesNilGame() {
  int random;
  return (getRandomCountries(NULL, &random) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetRandomCountriesNilRandom() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getRandomCountries(game, NULL) == RISK_NIL_RANDOM) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetRandomCountriesValid() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  int random;
  return (getRandomCountries(game, &random) == RISK_NIL) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testSetBordersNilGame() {
  char *countries[3] = { "foo", "bar", "baz" };
  return (setBorders(NULL, "country", 3, countries) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t setBorders(risk_t *game, char *country, int n, char *countries[]) {}
testResultRISK_t testSetBordersValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetLengthBordersNilGame() {
  int countries;
  return (getLengthBorders(NULL, "country", &countries) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getLengthBorders(risk_t *game, char *country, int *countries) {}
testResultRISK_t testGetLengthBordersValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetLengthBordersElemNilGame() {
  int n;
  return (getLengthBordersElem(NULL, "country", 0, &n) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetLengthBordersElemNilLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getLengthBordersElem(game, "country", 0, NULL) == RISK_NIL_LENGTH) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getLengthBordersElem(risk_t *game, char *country, int idx, int *n) {}
testResultRISK_t testGetLengthBordersElemValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetBordersElemNilGame() {
  char neighbor[10];
  return (getBordersElem(NULL, "country", 0, neighbor) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getBordersElem(risk_t *game, char *country, int idx, char *neighbor) {}
testResultRISK_t testGetBordersElemValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testSetContinentSetNilGame() {
  char *countries[3] = { "foo" , "bar", "baz" };
  return (setContinentSet(NULL, "continent", 3, countries) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t setContinentSet(risk_t *game, char *continent, int n, char *countries[]) {}
testResultRISK_t testSetContinentSetValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetContinentSetLengthNilGame() {
  int countries;
  return (getContinentSetLength(NULL, "continent", &countries) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getContinentSetLength(risk_t *game, char *continent, int *countries) {}
testResultRISK_t testGetContinentSetLengthValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetContinentSetLengthElemNilGame() {
  int n;
  return (getContinentSetLengthElem(NULL, "continent", 0, &n) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetContinentSetLengthElemNilLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getContinentSetLengthElem(game, "continent", 0, NULL) == RISK_NIL_LENGTH) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getContinentSetLengthElem(risk_t *game, char *continent, int idx, char *n) {}
testResultRISK_t testGetContinentSetLengthElemValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetContinentSetElemNilGame() {
  char country[10];
  return (getContinentSetElem(NULL, "continent", 0, country) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getContinentSetElem(risk_t *game, char *continent, int idx, char *country) {}
testResultRISK_t testGetContinentSetElemValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testSetOwnerNilGame() {
  return (setOwner(NULL, "country", "player") == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t setOwner(risk_t *game, char *country, char *player) {}
testResultRISK_t testSetOwnerValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetOwnerLengthNilGame() {
  int n;
  return (getOwnerLength(NULL, "country", &n) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testGetOwnerLengthNilLength() {
  risk_t *game;
  if(makeRISK(&game) != RISK_NIL) { return RISK_FAIL; }

  return (getOwnerLength(game, "country", NULL) == RISK_NIL_LENGTH) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getOwnerLength(risk_t *game, char *country, int *n) {}
testResultRISK_t testGetOwnerLengthValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetOwnerNilGame() {
  char player[10];
  return (getOwner(NULL, "country", player) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getOwner(risk_t *game, char *country, char *player) {}
testResultRISK_t testGetOwnerValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testReinforceNilGame() {
  return (reinforce(NULL, "country", 10) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t reinforce(risk_t *game, char *country, int troops) {}
testResultRISK_t testReinforceValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testGetTroopsNilGame() {
  int troops;
  return (getTroops(NULL, "country", &troops) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t getTroops(risk_t *game, char *country, int *troops) {}
testResultRISK_t testGetTroopsValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testValidNilGame() {
  return (valid(NULL) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t valid(risk_t *game) {}
testResultRISK_t testValidValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testStartNilGame() {
  return (start(NULL) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t start(risk_t *game) {}
testResultRISK_t testStartValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

testResultRISK_t testEndNilGame() {
  return (end(NULL) == RISK_NIL_GAME) ? RISK_PASS : RISK_FAIL;
}

//errRISK_t end(risk_t *game) {}
testResultRISK_t testEndValid() {
  return RISK_FAIL; //return RISK_NIL;  
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testStrErrRISK_OUT_OF_MEMORY,               "testStrErrRISK_OUT_OF_MEMORY"                },
  { testStrErrRISK_GAMEPLAY_MUTATION,           "testStrErrRISK_GAMEPLAY_MUTATION"            },
  { testStrErrRISK_INVALID_PLAYER_COUNT,        "testStrErrRISK_INVALID_PLAYER_COUNT"         },
  { testStrErrRISK_INVALID_INDEX,               "testStrErrRISK_INVALID_INDEX"                },
  { testStrErrRISK_INVALID_STARTING_TROOPS,     "testStrErrRISK_INVALID_STARTING_TROOPS"      },
  { testStrErrRISK_INVALID_TROOP_BONUS,         "testStrErrRISK_INVALID_TROOP_BONUS"          },
  { testStrErrRISK_INVALID_TROOP_MINIMUM,       "testStrErrRISK_INVALID_TROOP_MINIMUM"        },
  { testStrErrRISK_INVALID_TROOP_RANDOM,        "testStrErrRISK_INVALID_TROOP_RANDOM"         },
  { testStrErrRISK_INVALID_DECK_WILDS,          "testStrErrRISK_INVALID_DECK_WILDS"           },
  { testStrErrRISK_INVALID_CARD_TYPES_COUNT,    "testStrErrRISK_INVALID_CARD_TYPES_COUNT"     },
  { testStrErrRISK_INVALID_REWARDS_COUNT,       "testStrErrRISK_INVALID_REWARDS_COUNT"        },
  { testStrErrRISK_INVALID_LENGTH,              "testStrErrRISK_INVALID_LENGTH"               },
  { testStrErrRISK_INVALID_INCREMENT,           "testStrErrRISK_INVALID_INCREMENT"            },
  { testStrErrRISK_INVALID_COUNTRIES_COUNT,     "testStrErrRISK_INVALID_COUNTRIES_COUNT"      },
  { testStrErrRISK_INVALID_RANDOM,              "testStrErrRISK_INVALID_RANDOM"               },
  { testStrErrRISK_NIL_GAME,                    "testStrErrRISK_NIL_GAME"                     },
  { testStrErrRISK_NIL_ARR_PLAYERS,             "testStrErrRISK_NIL_ARR_PLAYERS"              },
  { testStrErrRISK_NIL_ARR_PLAYER,              "testStrErrRISK_NIL_ARR_PLAYER"               },
  { testStrErrRISK_NIL_PLAYERS,                 "testStrErrRISK_NIL_PLAYERS"                  },
  { testStrErrRISK_NIL_PLAYER,                  "testStrErrRISK_NIL_PLAYER"                   },
  { testStrErrRISK_NIL_LENGTH,                  "testStrErrRISK_NIL_LENGTH"                   },
  { testStrErrRISK_NIL_STARTING_TROOPS,         "testStrErrRISK_NIL_STARTING_TROOPS"          },
  { testStrErrRISK_NIL_TROOP_BONUS,             "testStrErrRISK_NIL_TROOP_BONUS"              },
  { testStrErrRISK_NIL_TROOP_MINIMUM,           "testStrErrRISK_NIL_TROOP_MINIMUM"            },
  { testStrErrRISK_NIL_TROOP_RANDOM,            "testStrErrRISK_NIL_TROOP_RANDOM"             },
  { testStrErrRISK_NIL_DECK_WILDS,              "testStrErrRISK_NIL_DECK_WILDS"               },
  { testStrErrRISK_NIL_CARD_TYPES,              "testStrErrRISK_NIL_CARD_TYPES"               },
  { testStrErrRISK_NIL_TYPES,                   "testStrErrRISK_NIL_TYPES"                    },
  { testStrErrRISK_NIL_TYPE,                    "testStrErrRISK_NIL_TYPE"                     },
  { testStrErrRISK_NIL_ARR_REWARDS,             "testStrErrRISK_NIL_ARR_REWARDS"              },
  { testStrErrRISK_NIL_REWARDS,                 "testStrErrRISK_NIL_REWARDS"                  },
  { testStrErrRISK_NIL_INCREMENT,               "testStrErrRISK_NIL_INCREMENT"                },
  { testStrErrRISK_NIL_ARR_CONTINENTS,          "testStrErrRISK_NIL_ARR_CONTINENTS"           },
  { testStrErrRISK_NIL_ARR_CONTINENT,           "testStrErrRISK_NIL_ARR_CONTINENT"            },
  { testStrErrRISK_NIL_CONTINENTS,              "testStrErrRISK_NIL_CONTINENTS"               },
  { testStrErrRISK_NIL_CONTINENT,               "testStrErrRISK_NIL_CONTINENT"                },
  { testStrErrRISK_NIL_ARR_BONUSES,             "testStrErrRISK_NIL_ARR_BONUSES"              },
  { testStrErrRISK_NIL_BONUSES,                 "testStrErrRISK_NIL_BONUSES"                  },
  { testStrErrRISK_NIL_ARR_COUNTRIES,           "testStrErrRISK_NIL_ARR_COUNTRIES"            },
  { testStrErrRISK_NIL_ARR_COUNTRY,             "testStrErrRISK_NIL_ARR_COUNTRY"              },
  { testStrErrRISK_NIL_COUNTRIES,               "testStrErrRISK_NIL_COUNTRIES"                },
  { testStrErrRISK_NIL_COUNTRY,                 "testStrErrRISK_NIL_COUNTRY"                  },
  { testStrErrRISK_NIL_RANDOM,                  "testStrErrRISK_NIL_RANDOM"                   },
  { testStrErrRISK_NIL,                         "testStrErrRISK_NIL"                          },
  { testMakeRISKNilGame,                        "testMakeRISKNilGame"                         },
  //{ testMakeRISKOutOfMemory,                    "testMakeRISKOutOfMemory"                     },
  { testMakeRISKValid,                          "testMakeRISKValid"                           },
  { testFreeRISKNilGame,                        "testFreeRISKNilGame"                         },
  { testFreeRISKValid,                          "testFreeRISKValid"                           },
  { testSetPlayersNilGame,                      "testSetPlayersNilGame"                       },
  { testSetPlayersInvalidPlayerCount,           "testSetPlayersInvalidPlayerCount"            },
  { testSetPlayersNilPlayers,                   "testSetPlayersNilPlayers"                    },
  { testSetPlayersNilPlayer,                    "testSetPlayersNilPlayer"                     },
  { testSetPlayersGameplayMutation,             "testSetPlayersGameplayMutation"              },
  //{ testSetPlayersOutOfMemory,                  "testSetPlayersOutOfMemory"                   },
  { testSetPlayersValid,                        "testSetPlayersValid"                         },
  { testGetLengthPlayersNilGame,                "testGetLengthPlayersNilGame"                 },
  { testGetLengthPlayersNilPlayers,             "testGetLengthPlayersNilPlayers"              },
  { testGetLengthPlayersValid,                  "testGetLengthPlayersValid"                   },
  { testGetLengthPlayersElemNilGame,            "testGetLengthPlayersElemNilGame"             },
  { testGetLengthPlayersElemInvalidIndex,       "testGetLengthPlayersElemInvalidIndex"        },
  { testGetLengthPlayersElemNilLength,          "testGetLengthPlayersElemNilLength"           },
  { testGetLengthPlayersElemValid,              "testGetLengthPlayersElemValid"               },
  { testGetPlayerNilGame,                       "testGetPlayerNilGame"                        },
  { testGetPlayerInvalidIndex,                  "testGetPlayerInvalidIndex"                   },
  { testGetPlayerNilPlayer,                     "testGetPlayerNilPlayer"                      },
  { testGetPlayerValid,                         "testGetPlayerValid"                          },
  { testSetStartingTroopCountNilGame,           "testSetStartingTroopCountNilGame"            },
  { testSetStartingTroopCountInvalidStart,      "testSetStartingTroopCountInvalidStart"       },
  { testSetStartingTroopCountGameplayMutation,  "testSetStartingTroopCountGameplayMutation"   },
  { testSetStartingTroopCountValid,             "testSetStartingTroopCountValid"              },
  { testGetStartingTroopCountNilGame,           "testGetStartingTroopCountNilGame"            },
  { testGetStartingTroopCountNilStart,          "testGetStartingTroopCountNilStart"           },
  { testGetStartingTroopCountValid,             "testGetStartingTroopCountValid"              },
  { testSetTroopTerritoryBonusNilGame,          "testSetTroopTerritoryBonusNilGame"           },
  { testSetTroopTerritoryBonusInvalidBonus,     "testSetTroopTerritoryBonusInvalidBonus"      },
  { testSetTroopTerritoryBonusGameplayMutation, "testSetTroopTerritoryBonusGameplayMutation"  },
  { testSetTroopTerritoryBonusValid,            "testSetTroopTerritoryBonusValid"             },
  { testGetTroopTerritoryBonusNilGame,          "testGetTroopTerritoryBonusNilGame"           },
  { testGetTroopTerritoryBonusNilBonus,         "testGetTroopTerritoryBonusNilBonus"          },
  { testGetTroopTerritoryBonusValid,            "testGetTroopTerritoryBonusValid"             },
  { testSetMinimumTroopHandoutNilGame,          "testSetMinimumTroopHandoutNilGame"           },
  { testSetMinimumTroopHandoutInvalidMinimum,   "testSetMinimumTroopHandoutInvalidMinimum"    },
  { testSetMinimumTroopHandoutGameplayMutation, "testSetMinimumTroopHandoutGameplayMutation"  },
  { testSetMinimumTroopHandoutValid,            "testSetMinimumTroopHandoutValid"             },
  { testGetMinimumTroopHandoutNilGame,          "testGetMinimumTroopHandoutNilGame"           },
  { testGetMinimumTroopHandoutNilMinimum,       "testGetMinimumTroopHandoutNilMinimum"        },
  { testGetMinimumTroopHandoutValid,            "testGetMinimumTroopHandoutValid"             },
  { testSetRandomTroopsNilGame,                 "testSetRandomTroopsNilGame"                  },
  { testSetRandomTroopsInvalidRandom,           "testSetRandomTroopsInvalidRandom"            },
  { testSetRandomTroopsGameplayMutation,        "testSetRandomTroopsGameplayMutation"         },
  { testSetRandomTroopsValid,                   "testSetRandomTroopsValid"                    },
  { testGetRandomTroopsNilGame,                 "testGetRandomTroopsNilGame"                  },
  { testGetRandomTroopsNilRandom,               "testGetRandomTroopsNilRandom"                },
  { testGetRandomTroopsValid,                   "testGetRandomTroopsValid"                    },
  { testSetDeckWildsNilGame,                    "testSetDeckWildsNilGame"                     },
  { testSetDeckWildsInvalidWilds,               "testSetDeckWildsInvalidWilds"                },
  { testSetDeckWildsGameplayMutation,           "testSetDeckWildsGameplayMutation"            },
  { testSetDeckWildsValid,                      "testSetDeckWildsValid"                       },
  { testGetDeckWildsNilGame,                    "testGetDeckWildsNilGame"                     },
  { testGetDeckWildsNilWilds,                   "testGetDeckWildsNilWilds"                    },
  { testGetDeckWildsValid,                      "testGetDeckWildsValid"                       },
  { testSetDeckTypesNilGame,                    "testSetDeckTypesNilGame"                     },
  { testSetDeckTypesInvalidCardCount,           "testSetDeckTypesInvalidCardCount"            },
  { testSetDeckTypesNilTypes,                   "testSetDeckTypesNilTypes"                    },
  { testSetDeckTypesGameplayMutation,           "testSetDeckTypesGameplayMutation"            },
  { testSetDeckTypesNilType,                    "testSetDeckTypesNilType"                     },
  //{ testSetDeckTypesOutOfMemory,                "testSetDeckTypesOutOfMemory"                 },
  { testSetDeckTypesValid,                      "testSetDeckTypesValid"                       },
  { testGetLengthDeckTypesNilGame,              "testGetLengthDeckTypesNilGame"               },
  { testGetLengthDeckTypesNilTypes,             "testGetLengthDeckTypesNilTypes"              },
  { testGetLengthDeckTypesValid,                "testGetLengthDeckTypesValid"                 },
  { testGetLengthDeckTypesElemNilGame,          "testGetLengthDeckTypesElemNilGame"           },
  { testGetLengthDeckTypesElemInvalidIndex,     "testGetLengthDeckTypesElemInvalidIndex"      },
  { testGetLengthDeckTypesElemNilLength,        "testGetLengthDeckTypesElemNilLength"         },
  { testGetLengthDeckTypesElemValid,            "testGetLengthDeckTypesElemValid"             },
  { testGetDeckTypesElemNilGame,                "testGetDeckTypesElemNilGame"                 },
  { testGetDeckTypesElemInvalidIndex,           "testGetDeckTypesElemInvalidIndex"            },
  { testGetDeckTypesElemNilType,                "testGetDeckTypesElemNilType"                 },
  { testGetDeckTypesElemValid,                  "testGetDeckTypesElemValid"                   },
  { testSetTradeRewardsNilGame,                 "testSetTradeRewardsNilGame"                  },
  { testSetTradeRewardsInvalidRewardsCount,     "testSetTradeRewardsInvalidRewardsCount"      },
  { testSetTradeRewardsNilRewards,              "testSetTradeRewardsNilRewards"               },
  { testSetTradeRewardsGameplayMutation,        "testSetTradeRewardsGameplayMutation"         },
  //{ testSetTradeRewardsOutOfMemory,             "testSetTradeRewardsOutOfMemory"              },
  { testSetTradeRewardsValid,                   "testSetTradeRewardsValid"                    },
  { testGetLengthTradeRewardsNilGame,           "testGetLengthTradeRewardsNilGame"            },
  { testGetLengthTradeRewardsNilRewards,        "testGetLengthTradeRewardsNilRewards"         },
  { testGetLengthTradeRewardsValid,             "testGetLengthTradeRewardsValid"              },
  { testGetTradeRewardsNilGame,                 "testGetTradeRewardsNilGame"                  },
  { testGetTradeRewardsInvalidLength,           "testGetTradeRewardsInvalidLength"            },
  { testGetTradeRewardsNilRewards,              "testGetTradeRewardsNilRewards"               },
  { testGetTradeRewardsValid,                   "testGetTradeRewardsValid"                    },
  { testSetTradeIncrRewardNilGame,              "testSetTradeIncrRewardNilGame"               },
  { testSetTradeIncrRewardInvalidIncrement,     "testSetTradeIncrRewardInvalidIncrement"      },
  { testSetTradeIncrRewardGameplayMutation,     "testSetTradeIncrRewardGameplayMutation"      },
  { testSetTradeIncrRewardValid,                "testSetTradeIncrRewardValid"                 },
  { testGetTradeIncrRewardNilGame,              "testGetTradeIncrRewardNilGame"               },
  { testGetTradeIncrRewardNilIncrement,         "testGetTradeIncrRewardNilIncrement"          },
  { testGetTradeIncrRewardValid,                "testGetTradeIncrRewardValid"                 },
  { testSetContinentsNilGame,                   "testSetContinentsNilGame"                    },
  { testSetContinentsInvalidLength,             "testSetContinentsInvalidLength"              },
  { testSetContinentsNilContinents,             "testSetContinentsNilContinents"              },
  { testSetContinentsGameplayMutation,          "testSetContinentsGameplayMutation"           },
  { testSetContinentsNilContinent,              "testSetContinentsNilContinent"               },
  //{ testSetContinentsOutOfMemory,               "testSetContinentsOutOfMemory"                },
  { testSetContinentsValid,                     "testSetContinentsValid"                      },
  { testGetLengthContinentsNilGame,             "testGetLengthContinentsNilGame"              },
  { testGetLengthContinentsNilContinents,       "testGetLengthContinentsNilContinents"        },
  { testGetLengthContinentsValid,               "testGetLengthContinentsValid"                },
  { testGetLengthContinentsElemNilGame,         "testGetLengthContinentsElemNilGame"          },
  { testGetLengthContinentsElemInvalidIndex,    "testGetLengthContinentsElemInvalidIndex"     },
  { testGetLengthContinentsElemNilLength,       "testGetLengthContinentsElemNilLength"        },
  { testGetLengthContinentsElemValid,           "testGetLengthContinentsElemValid"            },
  { testGetContinentElemNilGame,                "testGetContinentElemNilGame"                 },
  { testGetContinentElemInvalidIndex,           "testGetContinentElemInvalidIndex"            },
  { testGetContinentElemNilContinent,           "testGetContinentElemNilContinent"            },
  { testGetContinentElemValid,                  "testGetContinentElemValid"                   },
  { testSetContinentBonusesNilGame,             "testSetContinentBonusesNilGame"              },
  { testSetContinentBonusesInvalidLength,       "testSetContinentBonusesInvalidLength"        },
  { testSetContinentBonusesNilBonuses,          "testSetContinentBonusesNilBonuses"           },
  { testSetContinentBonusesGameplayMutation,    "testSetContinentBonusesGameplayMutation"     },
  //{ testSetContinentBonusesOutOfMemory,         "testSetContinentBonusesOutOfMemory"          },
  { testSetContinentBonusesValid,               "testSetContinentBonusesValid"                },
  { testGetLengthContinentBonusesNilGame,       "testGetLengthContinentBonusesNilGame"        },
  { testGetLengthContinentBonusesNilBonuses,    "testGetLengthContinentBonusesNilBonuses"     },
  { testGetLengthContinentBonusesValid,         "testGetLengthContinentBonusesValid"          },
  { testGetContinentBonusesNilGame,             "testGetContinentBonusesNilGame"              },
  { testGetContinentBonusesInvalidLength,       "testGetContinentBonusesInvalidLength"        },
  { testGetContinentBonusesNilBonuses,          "testGetContinentBonusesNilBonuses"           },
  { testGetContinentBonusesValid,               "testGetContinentBonusesValid"                },
  { testSetCountriesNilGame,                    "testSetCountriesNilGame"                     },
  { testSetCountriesInvalidCountryCount,        "testSetCountriesInvalidCountryCount"         },
  { testSetCountriesNilCountries,               "testSetCountriesNilCountries"                },
  { testSetCountriesGameplayMutation,           "testSetCountriesGameplayMutation"            },
  { testSetCountriesNilCountry,                 "testSetCountriesNilCountry"                  },
  //{ testSetCountriesOutOfMemory,                "testSetCountriesOutOfMemory"                 },
  { testSetCountriesValid,                      "testSetCountriesValid"                       },
  { testGetLengthCountriesNilGame,              "testGetLengthCountriesNilGame"               },
  { testGetLengthCountriesNilCountries,         "testGetLengthCountriesNilCountries"          },
  { testGetLengthCountriesValid,                "testGetLengthCountriesValid"                 },
  { testGetLengthCountriesElemNilGame,          "testGetLengthCountriesElemNilGame"           },
  { testGetLengthCountriesElemInvalidIndex,     "testGetLengthCountriesElemInvalidIndex"      },
  { testGetLengthCountriesElemNilLength,        "testGetLengthCountriesElemNilLength"         },
  { testGetLengthCountriesElemValid,            "testGetLengthCountriesElemValid"             },
  { testGetCountryElemNilGame,                  "testGetCountryElemNilGame"                   },
  { testGetCountryElemInvalidIndex,             "testGetCountryElemInvalidIndex"              },
  { testGetCountryElemNilCountry,               "testGetCountryElemNilCountry"                },
  { testGetCountryElemValid,                    "testGetCountryElemValid"                     },
  { testSetRandomCountriesNilGame,              "testSetRandomCountriesNilGame"               },
  { testSetRandomCountriesInvalidRandom,        "testSetRandomCountriesInvalidRandom"         },
  { testSetRandomCountriesGameplayMutation,     "testSetRandomCountriesGameplayMutation"      },
  { testSetRandomCountriesValid,                "testSetRandomCountriesValid"                 },
  { testGetRandomCountriesNilGame,              "testGetRandomCountriesNilGame"               },
  { testGetRandomCountriesNilRandom,            "testGetRandomCountriesNilRandom"             },
  { testGetRandomCountriesValid,                "testGetRandomCountriesValid"                 },
  { testSetBordersNilGame,                      "testSetBordersNilGame"                       },
  { testSetBordersValid,                        "testSetBordersValid"                         },
  { testGetLengthBordersNilGame,                "testGetLengthBordersNilGame"                 },
  { testGetLengthBordersValid,                  "testGetLengthBordersValid"                   },
  { testGetLengthBordersElemNilGame,            "testGetLengthBordersElemNilGame"             },
  { testGetLengthBordersElemNilLength,          "testGetLengthBordersElemNilLength"           },
  { testGetLengthBordersElemValid,              "testGetLengthBordersElemValid"               },
  { testGetBordersElemNilGame,                  "testGetBordersElemNilGame"                   },
  { testGetBordersElemValid,                    "testGetBordersElemValid"                     },
  { testSetContinentSetNilGame,                 "testSetContinentSetNilGame"                  },
  { testSetContinentSetValid,                   "testSetContinentSetValid"                    },
  { testGetContinentSetLengthNilGame,           "testGetContinentSetLengthNilGame"            },
  { testGetContinentSetLengthValid,             "testGetContinentSetLengthValid"              },
  { testGetContinentSetLengthElemNilGame,       "testGetContinentSetLengthElemNilGame"        },
  { testGetContinentSetLengthElemNilLength,     "testGetContinentSetLengthElemNilLength"      },
  { testGetContinentSetLengthElemValid,         "testGetContinentSetLengthElemValid"          },
  { testGetContinentSetElemNilGame,             "testGetContinentSetElemNilGame"              },
  { testGetContinentSetElemValid,               "testGetContinentSetElemValid"                },
  { testSetOwnerNilGame,                        "testSetOwnerNilGame"                         },
  { testSetOwnerValid,                          "testSetOwnerValid"                           },
  { testGetOwnerLengthNilGame,                  "testGetOwnerLengthNilGame"                   },
  { testGetOwnerLengthNilLength,                "testGetOwnerLengthNilLength"                 },
  { testGetOwnerLengthValid,                    "testGetOwnerLengthValid"                     },
  { testGetOwnerNilGame,                        "testGetOwnerNilGame"                         },
  { testGetOwnerValid,                          "testGetOwnerValid"                           },
  { testReinforceNilGame,                       "testReinforceNilGame"                        },
  { testReinforceValid,                         "testReinforceValid"                          },
  { testGetTroopsNilGame,                       "testGetTroopsNilGame"                        },
  { testGetTroopsValid,                         "testGetTroopsValid"                          },
  { testValidNilGame,                           "testValidNilGame"                            },
  { testValidValid,                             "testValidValid"                              },
  { testStartNilGame,                           "testStartNilGame"                            },
  { testStartValid,                             "testStartValid"                              },
  { testEndNilGame,                             "testEndNilGame"                              },
  { testEndValid,                               "testEndValid"                                },
};

int main() {

  testResultRISK_t result;
  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    result = ((testResultRISK_t (*)(void))(TESTS[test][0]))();
    if(result == RISK_PASS) {
      passes++;
      fprintf(stdout, "PASS: %s\n", (char *)TESTS[test][1]);
    } else {
      fprintf(stdout, "FAIL: %s\n", (char *)TESTS[test][1]);
      fails++;
    }
    fflush(stdout); // so if segfault/crash we know last successful test
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
