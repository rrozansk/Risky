/******************************************************************************
 * FILE:    testRISK.c                                                        *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/17/17                                                           *
 * INFO:    Test file for implementation of the interface located in risk.h.  *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<risk.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 69

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

testResultRISK_t testStrErrRISK_GAME_PLAY_MUTATION() {
  return (strcmp(strErrRISK(RISK_GAME_PLAY_MUTATION), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_COUNTRIES_MISMATCH() {
  return (strcmp(strErrRISK(RISK_COUNTRIES_MISMATCH), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_PLAYERS() {
  return (strcmp(strErrRISK(RISK_INVALID_PLAYERS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_RAND() {
  return (strcmp(strErrRISK(RISK_INVALID_RAND), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_BEGINNING() {
  return (strcmp(strErrRISK(RISK_INVALID_BEGINNING), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_MINIMUM() {
  return (strcmp(strErrRISK(RISK_INVALID_MINIMUM), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_BONUS() {
  return (strcmp(strErrRISK(RISK_INVALID_BONUS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_WILDS() {
  return (strcmp(strErrRISK(RISK_INVALID_WILDS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_INCR() {
  return (strcmp(strErrRISK(RISK_INVALID_INCR), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_DECK() {
  return (strcmp(strErrRISK(RISK_INVALID_DECK), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_TRADES_SET() {
  return (strcmp(strErrRISK(RISK_INVALID_TRADES_SET), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_COUNTRIES_SIZE() {
  return (strcmp(strErrRISK(RISK_INVALID_COUNTRIES_SIZE), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_CONTINENTS_SIZE() {
  return (strcmp(strErrRISK(RISK_INVALID_CONTINENTS_SIZE), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_BOARD_SIZE() {
  return (strcmp(strErrRISK(RISK_INVALID_BOARD_SIZE), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_COUNTRY_CONTINENT() {
  return (strcmp(strErrRISK(RISK_INVALID_COUNTRY_CONTINENT), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_DEFENCE() {
  return (strcmp(strErrRISK(RISK_INVALID_DEFENCE), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_INVALID_ATTACK() {
  return (strcmp(strErrRISK(RISK_INVALID_ATTACK), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_DEST() {
  return (strcmp(strErrRISK(RISK_NIL_DEST), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_SRC() {
  return (strcmp(strErrRISK(RISK_NIL_SRC), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_RESULT() {
  return (strcmp(strErrRISK(RISK_NIL_RESULT), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_CARD() {
  return (strcmp(strErrRISK(RISK_NIL_CARD), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_TROOPS() {
  return (strcmp(strErrRISK(RISK_NIL_TROOPS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_PLAYER() {
  return (strcmp(strErrRISK(RISK_NIL_PLAYER), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_GAME() {
  return (strcmp(strErrRISK(RISK_NIL_GAME), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_CARD_TYPES() {
  return (strcmp(strErrRISK(RISK_NIL_CARD_TYPES), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_TRADEINS() {
  return (strcmp(strErrRISK(RISK_NIL_TRADEINS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_NAMES() {
  return (strcmp(strErrRISK(RISK_NIL_NAMES), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_COUNTRY_BONUSES() {
  return (strcmp(strErrRISK(RISK_NIL_COUNTRY_BONUSES), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_BOARD() {
  return (strcmp(strErrRISK(RISK_NIL_BOARD), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_COUNTRY() {
  return (strcmp(strErrRISK(RISK_NIL_COUNTRY), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_CONFLICTS() {
  return (strcmp(strErrRISK(RISK_NIL_CONFLICTS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_COUNTRIES() {
  return (strcmp(strErrRISK(RISK_NIL_COUNTRIES), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_TRADES() {
  return (strcmp(strErrRISK(RISK_NIL_TRADES), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_INCR() {
  return (strcmp(strErrRISK(RISK_NIL_INCR), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_START() {
  return (strcmp(strErrRISK(RISK_NIL_START), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_MIN() {
  return (strcmp(strErrRISK(RISK_NIL_MIN), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_BONUS() {
  return (strcmp(strErrRISK(RISK_NIL_BONUS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_PLAYERS() {
  return (strcmp(strErrRISK(RISK_NIL_PLAYERS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_WILDS() {
  return (strcmp(strErrRISK(RISK_NIL_WILDS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_TYPES() {
  return (strcmp(strErrRISK(RISK_NIL_TYPES), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_SIZE() {
  return (strcmp(strErrRISK(RISK_NIL_SIZE), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_CONTINENTS() {
  return (strcmp(strErrRISK(RISK_NIL_CONTINENTS), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_CONTINENT() {
  return (strcmp(strErrRISK(RISK_NIL_CONTINENT), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL_BONUSES() {
  return (strcmp(strErrRISK(RISK_NIL_BONUSES), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testStrErrRISK_NIL() {
  return (!strcmp(strErrRISK(RISK_NIL), "")) ? RISK_PASS : RISK_FAIL;
}

testResultRISK_t testMakeRISK() {
  //makeRISK(risk_t **game)
  return RISK_FAIL;
}

testResultRISK_t testFreeRISK() {
  //freeRISK(risk_t *game)
  return RISK_FAIL;
}

testResultRISK_t testPlayers() {
  //setPlayers(risk_t *game, int n, char **names)
  //getPlayers(risk_t *game, char ***names, int *players)
  return RISK_FAIL;
}

testResultRISK_t testTroops() {
  //setTroops(risk_t *game, int beginning, int min, int bonus, int rand)
  //getTroops(risk_t *game, int *start, int *min, int *bonus)
  return RISK_FAIL;
}

testResultRISK_t testDeck() {
  //setDeck(risk_t *game, int wilds, char **types, int n)
  //getDeck(risk_t *game, int *wilds, char ***types, int *size)
  return RISK_FAIL;
}

testResultRISK_t testTrades() {
  //setTrades(risk_t *game, int *trades, int n, int incr)
  //getTrades(risk_t *game, int **trades, int *n, int *incr)
  return RISK_FAIL;
}

testResultRISK_t testContinents() {
  //setContinents(risk_t *game, char **continents, int n)
  //getContinents(risk_t *game, char ***continents, int *size)
  return RISK_FAIL;
}

testResultRISK_t testContinentBonus() {
  //getContinentBonus(risk_t *game, char *continent, int *bonus)
  return RISK_FAIL;
}

testResultRISK_t testContinentBonuses() {
  //setContinentBonuses(risk_t *game, int *bonuses, int n)
  //getContinentBonuses(risk_t *game, int **bonuses, int *size)
  return RISK_FAIL;
}

testResultRISK_t testCountries() {
  //setCountries(risk_t *game, char **countries, int n, int rand)
  //getCountries(risk_t *game, char ***countries, int *size)
  return RISK_FAIL;
}

testResultRISK_t testAdjacencies() {
  //setAdjacencies(risk_t *game, char *country, char **countries, int conflicts)
  //getNeighbors(risk_t *game, char *country, char ***neighbors, int *size)
  return RISK_FAIL;
}

testResultRISK_t testIsValid() {
  //isValid(risk_t *game)
  return RISK_FAIL;
}

testResultRISK_t testOwner() {
  //setOwner(risk_t *game, char *country, char *player)
  //getOwner(risk_t *game, char *country, char **player)
  return RISK_FAIL;
}

testResultRISK_t testArmies() {
  //setArmies(risk_t *game, char *country, int troops)
  //getArmies(risk_t *game, char *country, int *troops)
  return RISK_FAIL;
}

testResultRISK_t testSetRandomCountries() {
  //setRandomCountries(risk_t *game, int rand)
  return RISK_FAIL;
}

testResultRISK_t testSetRandomArmies() {
  //setRandomArmies(risk_t *game, int rand)
  return RISK_FAIL;
}

testResultRISK_t testGetNextTradeValue() {
  //getNextTradeValue(risk_t *game, int *troops)
  return RISK_FAIL;
}

testResultRISK_t testDrawCard() {
  //drawCard(risk_t *game, char **card)
  return RISK_FAIL;
}

testResultRISK_t testTradeCards() {
  //tradeCards(risk_t *game, char **cards, int *troops)
  return RISK_FAIL;
}

testResultRISK_t testAttack() {
  //attack(risk_t *game, char *src, int attack, char *dest, int defence, int *result)
  return RISK_FAIL;
}

testResultRISK_t testInitDeck() {
  //initDeck(risk_t *game)
  return RISK_FAIL;
}

testResultRISK_t testInitCountries() {
  //initCountries(risk_t *game)
  return RISK_FAIL;
}

testResultRISK_t testInitArmies() {
  //initArmies(risk_t *game)
  return RISK_FAIL;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testStrErrRISK_OUT_OF_MEMORY,             "testStrErrRISK_OUT_OF_MEMORY"             },
  { testStrErrRISK_GAME_PLAY_MUTATION,        "testStrErrRISK_GAME_PLAY_MUTATION"        },
  { testStrErrRISK_COUNTRIES_MISMATCH,        "testStrErrRISK_COUNTRIES_MISMATCH"        },
  { testStrErrRISK_INVALID_PLAYERS,           "testStrErrRISK_INVALID_PLAYERS"           },
  { testStrErrRISK_INVALID_RAND,              "testStrErrRISK_INVALID_RAND"              },
  { testStrErrRISK_INVALID_BEGINNING,         "testStrErrRISK_INVALID_BEGINNING"         },
  { testStrErrRISK_INVALID_MINIMUM,           "testStrErrRISK_INVALID_MINIMUM"           },
  { testStrErrRISK_INVALID_BONUS,             "testStrErrRISK_INVALID_BONUS"             },
  { testStrErrRISK_INVALID_WILDS,             "testStrErrRISK_INVALID_WILDS"             },
  { testStrErrRISK_INVALID_INCR,              "testStrErrRISK_INVALID_INCR"              },
  { testStrErrRISK_INVALID_DECK,              "testStrErrRISK_INVALID_DECK"              },
  { testStrErrRISK_INVALID_TRADES_SET,        "testStrErrRISK_INVALID_TRADES_SET"        },
  { testStrErrRISK_INVALID_COUNTRIES_SIZE,    "testStrErrRISK_INVALID_COUNTRIES_SIZE"    },
  { testStrErrRISK_INVALID_CONTINENTS_SIZE,   "testStrErrRISK_INVALID_CONTINENTS_SIZE"   },
  { testStrErrRISK_INVALID_BOARD_SIZE,        "testStrErrRISK_INVALID_BOARD_SIZE"        },
  { testStrErrRISK_INVALID_COUNTRY_CONTINENT, "testStrErrRISK_INVALID_COUNTRY_CONTINENT" },
  { testStrErrRISK_INVALID_DEFENCE,           "testStrErrRISK_INVALID_DEFENCE"           },
  { testStrErrRISK_INVALID_ATTACK,            "testStrErrRISK_INVALID_ATTACK"            },
  { testStrErrRISK_NIL_DEST,                  "testStrErrRISK_NIL_DEST"                  },
  { testStrErrRISK_NIL_SRC,                   "testStrErrRISK_NIL_SRC"                   },
  { testStrErrRISK_NIL_RESULT,                "testStrErrRISK_NIL_RESULT"                },
  { testStrErrRISK_NIL_CARD,                  "testStrErrRISK_NIL_CARD"                  },
  { testStrErrRISK_NIL_TROOPS,                "testStrErrRISK_NIL_TROOPS"                },
  { testStrErrRISK_NIL_PLAYER,                "testStrErrRISK_NIL_PLAYER"                },
  { testStrErrRISK_NIL_GAME,                  "testStrErrRISK_NIL_GAME"                  },
  { testStrErrRISK_NIL_CARD_TYPES,            "testStrErrRISK_NIL_CARD_TYPES"            },
  { testStrErrRISK_NIL_TRADEINS,              "testStrErrRISK_NIL_TRADEINS"              },
  { testStrErrRISK_NIL_NAMES,                 "testStrErrRISK_NIL_NAMES"                 },
  { testStrErrRISK_NIL_COUNTRY_BONUSES,       "testStrErrRISK_NIL_COUNTRY_BONUSES"       },
  { testStrErrRISK_NIL_BOARD,                 "testStrErrRISK_NIL_BOARD"                 },
  { testStrErrRISK_NIL_COUNTRY,               "testStrErrRISK_NIL_COUNTRY"               },
  { testStrErrRISK_NIL_CONFLICTS,             "testStrErrRISK_NIL_CONFLICTS"             },
  { testStrErrRISK_NIL_COUNTRIES,             "testStrErrRISK_NIL_COUNTRIES"             },
  { testStrErrRISK_NIL_TRADES,                "testStrErrRISK_NIL_TRADES"                },
  { testStrErrRISK_NIL_INCR,                  "testStrErrRISK_NIL_INCR"                  },
  { testStrErrRISK_NIL_START,                 "testStrErrRISK_NIL_START"                 },
  { testStrErrRISK_NIL_MIN,                   "testStrErrRISK_NIL_MIN"                   },
  { testStrErrRISK_NIL_BONUS,                 "testStrErrRISK_NIL_BONUS"                 },
  { testStrErrRISK_NIL_PLAYERS,               "testStrErrRISK_NIL_PLAYERS"               },
  { testStrErrRISK_NIL_WILDS,                 "testStrErrRISK_NIL_WILDS"                 },
  { testStrErrRISK_NIL_TYPES,                 "testStrErrRISK_NIL_TYPES"                 },
  { testStrErrRISK_NIL_SIZE,                  "testStrErrRISK_NIL_SIZE"                  },
  { testStrErrRISK_NIL_CONTINENTS,            "testStrErrRISK_NIL_CONTINENTS"            },
  { testStrErrRISK_NIL_CONTINENT,             "testStrErrRISK_NIL_CONTINENT"             },
  { testStrErrRISK_NIL_BONUSES,               "testStrErrRISK_NIL_BONUSES"               },
  { testStrErrRISK_NIL,                       "testStrErrRISK_NIL"                       },
  { testMakeRISK,                             "testMakeRISK"                             },
  { testFreeRISK,                             "testFreeRISK"                             },
  { testPlayers,                              "testPlayers"                              },
  { testTroops,                               "testTroops"                               },
  { testDeck,                                 "testDeck"                                 },
  { testTrades,                               "testTrades"                               },
  { testContinents,                           "testContinents"                           },
  { testContinentBonus,                       "testContinentBonus"                       },
  { testContinentBonuses,                     "testContinentBonuses"                     },
  { testCountries,                            "testCountries"                            },
  { testAdjacencies,                          "testAdjacencies"                          },
  { testIsValid,                              "testIsValid"                              },
  { testOwner,                                "testOwner"                                },
  { testArmies,                               "testArmies"                               },
  { testSetRandomCountries,                   "testSetRandomCountries"                   },
  { testSetRandomArmies,                      "testSetRandomArmies"                      },
  { testGetNextTradeValue,                    "testGetNextTradeValue"                    },
  { testDrawCard,                             "testDrawCard"                             },
  { testTradeCards,                           "testTradeCards"                           },
  { testAttack,                               "testAttack"                               },
  { testInitDeck,                             "testInitDeck"                             },
  { testInitCountries,                        "testInitCountries"                        },
  { testInitArmies,                           "testInitArmies"                           },
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
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
