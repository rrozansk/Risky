/******************************************************************************
 * FILE:    risk.h                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  5/13/17                                                           *
 * INFO:    A game library to easily implement Risk like games, by making     *
 *          and manipulation of the game state easy.                          *  
 *                                                                            *
 ******************************************************************************/

#ifndef RISK_DEFS
#define RISK_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct risk risk_t; /* A representation of the game */

typedef enum errRISK { /* All the possible errors returned from the library. */
  RISK_NIL_GAME, RISK_NIL_CARD_TYPES, RISK_NIL_CARD, RISK_NIL_TROOPS,
  RISK_OUT_OF_MEMORY, RISK_NIL_BOARD, RISK_INVALID_INCR, RISK_NIL,
  RISK_NIL_TRADEINS, RISK_INVALID_DECK, RISK_INVALID_WILDS, RISK_NIL_NAMES, 
  RISK_NIL_COUNTRY_BONUSES, RISK_NIL_COUNTRIES, RISK_INVALID_COUNTRY_CONTINENT,
  RISK_COUNTRIES_MISMATCH, RISK_GAME_PLAY_MUTATION, RISK_NIL_CONTINENTS, 
  RISK_INVALID_BEGINNING, RISK_INVALID_MINIMUM, RISK_INVALID_BOARD_SIZE,
  RISK_INVALID_TRADES_SET, RISK_INVALID_COUNTRIES_SIZE, RISK_INVALID_PLAYERS,
  RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_RAND, RISK_INVALID_BONUS,
  RISK_NIL_CONFLICTS, RISK_NIL_SIZE, RISK_NIL_TRADES, RISK_NIL_BONUSES,
  RISK_NIL_INCR, RISK_NIL_START, RISK_NIL_MIN, RISK_NIL_BONUS, RISK_NIL_PLAYERS,
  RISK_NIL_COUNTRY, RISK_NIL_CONTINENT, RISK_INVALID_DEFENCE, RISK_NIL_SRC,
  RISK_INVALID_ATTACK, RISK_NIL_DEST, RISK_NIL_RESULT, RISK_NIL_PLAYER,
  RISK_NIL_WILDS, RISK_NIL_TYPES, 
} errRISK_t;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: Return a string representation of any possible error returned by  *
 *          the library.                                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * errRISK The error in question                                              *
 *                                                                            *
 * RETURNS: A string representing the given error.                            *
 *                                                                            *
 ******************************************************************************/
const char *strErrRISK(errRISK_t errRISK);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempt to malloc the space for a new game.                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     where to store the address of the intiated game                   *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_OUT_OF_MEMORY, or RISK_NIL if no error.       *
 *                                                                            *
 ******************************************************************************/
errRISK_t makeRISK(risk_t **game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Free all alloc'ed memory, including any configured dynamic arrays.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game you wish to free                                         *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME or RISK_NIL if no error.                            *
 *                                                                            *
 ******************************************************************************/
errRISK_t freeRISK(risk_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of human players (0-8) for the game.         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * players  the number of humans players                                      *
 * name     a pointer to an array of names                                    *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_INVALID_HPS, RISK_GAME_PLAY_MUTATION,         *
 *          RISK_INVALID_HUMANS, or RISK_NIL if no error.                     *
 *                                                                            *
 ******************************************************************************/
errRISK_t setPlayers(risk_t *game, int players, char **names);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of human players (0-8) for the game.         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * players  the number of humans players                                      *
 * name     a pointer to an array of names                                    *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_INVALID_HPS, RISK_GAME_PLAY_MUTATION,         *
 *          RISK_INVALID_HUMANS, or RISK_NIL if no error.                     *
 *                                                                            *
 ******************************************************************************/
errRISK_t getPlayers(risk_t *game, char ***names, int *players);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure how troops are setup. How much you receive at the game  *
 *          start, the minimum per turn, and ratio of countries to troops to  *
 *          recieve for turn bonus all 0-2^8. Can also choose to randomly     *
 *          assign troops to countries yes(1)/no(0).                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * start    the begginning number of troops to start the game with            *
 * min      the minimum number of troops possible to receive per turn         *
 * bonus    how many countries constitue an extra troop on turn start         *
 * random   whether or not to randomly distribute troops at the start of game *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_INVALID_BEGINNING, RISK_INVALID_MINIMUM,      *
 *          RISK_INVALID_BONUS, RISK_INVALID_RAND, RISK_GAME_PLAY_MUTATION,   *
 *          or RISK_NIL if no error.                                          *
 *                                                                            *
 ******************************************************************************/
errRISK_t setTroops(risk_t *game, int start, int min, int bonus, int random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure how troops are setup. How much you receive at the game  *
 *          start, the minimum per turn, and ratio of countries to troops to  *
 *          recieve for turn bonus all 0-2^8. Can also choose to randomly     *
 *          assign troops to countries yes(1)/no(0).                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * start    the begginning number of troops to start the game with            *
 * min      the minimum number of troops possible to receive per turn         *
 * bonus    how many countries constitue an extra troop on turn start         *
 * random   whether or not to randomly distribute troops at the start of game *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_INVALID_BEGINNING, RISK_INVALID_MINIMUM,      *
 *          RISK_INVALID_BONUS, RISK_INVALID_RAND, RISK_GAME_PLAY_MUTATION,   *
 *          or RISK_NIL if no error.                                          *
 *                                                                            *
 ******************************************************************************/
errRISK_t getTroops(risk_t *game, int *start, int *min, int *bonus);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the deck/cards used for trading. The number of wild     *
 *          (0-2^8), and all possible card types besides wilds (len 2-2^8).   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * wilds    the number of wilds contained in the deck                         *
 * types    a pointer to an array of card types                               *
 * n        the number of types                                               *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_CARD_TYPES, RISK_INVALID_WILDS,           *
 *          RISK_INVALID_DECK, RISK_GAME_PLAY_MUTATION, or RISK_NIL if no     *
 *          error.                                                            *
 *                                                                            *
 ******************************************************************************/
errRISK_t setDeck(risk_t *game, int wilds, char **types, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the deck/cards used for trading. The number of wild     *
 *          (0-2^8), and all possible card types besides wilds (len 2-2^8).   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * wilds    the number of wilds contained in the deck                         *
 * types    a pointer to an array of card types                               *
 * n        the number of types                                               *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_CARD_TYPES, RISK_INVALID_WILDS,           *
 *          RISK_INVALID_DECK, RISK_GAME_PLAY_MUTATION, or RISK_NIL if no     *
 *          error.                                                            *
 *                                                                            *
 ******************************************************************************/
errRISK_t getDeck(risk_t *game, int *wilds, char ***types, int *size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure how card trades are handled. How much each is worth     *
 *          (0-2^8) and the contant incrment (0-2^8) after the predefined     *
 *          ones run out.                                                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * trades   a pointer to an array of integers definig the values of trades    *
 * n        the number of defined trades                                      *
 * incr     the constant increment to apply to trades after trades runs out   *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_TRADEINS, RISK_INVALID_INCR,              *
 *          RISK_INVALID_TRADES_SET, RISK_GAME_PLAY_MUTATION, or RISK_NIL     *
 *          if no error.                                                      *
 *                                                                            *
 ******************************************************************************/
errRISK_t setTrades(risk_t *game, int *trades, int n, int incr);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure how card trades are handled. How much each is worth     *
 *          (0-2^8) and the contant incrment (0-2^8) after the predefined     *
 *          ones run out.                                                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * trades   a pointer to an array of integers definig the values of trades    *
 * n        the number of defined trades                                      *
 * incr     the constant increment to apply to trades after trades runs out   *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_TRADEINS, RISK_INVALID_INCR,              *
 *          RISK_INVALID_TRADES_SET, RISK_GAME_PLAY_MUTATION, or RISK_NIL     *
 *          if no error.                                                      *
 *                                                                            *
 ******************************************************************************/
errRISK_t getTrades(risk_t *game, int **trades, int *n, int *incr);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the continents (1-2^8) which make up the map.           *
 *                                                                            *
 * ARGUMENT   DESCRIPTION                                                     *
 * --------   -----------                                                     *
 * game       the game instance which to set                                  *
 * continents an array of all the continents names                            *
 * n          the number of continents                                        *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_CONTINENTS,                               *
 *          RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_CONTINENTS_SIZE,       *
 *          RISK_GAME_PLAY_MUTATION, or RISK_NIL if no error.                 *
 *                                                                            *
 ******************************************************************************/
errRISK_t setContinents(risk_t *game, char **continents, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the continents (1-2^8) which make up the map.           *
 *                                                                            *
 * ARGUMENT   DESCRIPTION                                                     *
 * --------   -----------                                                     *
 * game       the game instance which to set                                  *
 * continents an array of all the continents names                            *
 * n          the number of continents                                        *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_CONTINENTS,                               *
 *          RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_CONTINENTS_SIZE,       *
 *          RISK_GAME_PLAY_MUTATION, or RISK_NIL if no error.                 *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinents(risk_t *game, char ***continents, int *size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the continent bonuses (val: 0-2^8, len: 0-2^8) which    *
 *          make up the map.                                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * bonus    array of integers defining the troop bonus for owning a continent * 
 * n        the number of bonues                                              *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_COUNTRY_BONUSES,                          *
 *          RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_CONTINENTS_SIZE,       *
 *          RISK_GAME_PLAY_MUTATION, or RISK_NIL if no error.                 *
 *                                                                            *
 ******************************************************************************/
errRISK_t setContinentBonuses(risk_t *game, int *bonuses, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the continent bonuses (val: 0-2^8, len: 0-2^8) which    *
 *          make up the map.                                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * bonus    array of integers defining the troop bonus for owning a continent * 
 * n        the number of bonues                                              *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_COUNTRY_BONUSES,                          *
 *          RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_CONTINENTS_SIZE,       *
 *          RISK_GAME_PLAY_MUTATION, or RISK_NIL if no error.                 *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinentBonus(risk_t *game, char *continent, int *bonus);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the continent bonuses (val: 0-2^8, len: 0-2^8) which    *
 *          make up the map.                                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * bonus    array of integers defining the troop bonus for owning a continent * 
 * n        the number of bonues                                              *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_COUNTRY_BONUSES,                          *
 *          RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_CONTINENTS_SIZE,       *
 *          RISK_GAME_PLAY_MUTATION, or RISK_NIL if no error.                 *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinentBonuses(risk_t *game, int **bonuses, int *size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the contries (0-2^8) which make up the map, and whether *
 *          or not to randomly yes(1)/no(0) distribute them at the beginning  *
 *          of the game.                                                      *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * game      the game instance which to set                                   *
 * countries an array of the names of all the countries                       *
 * n         the number of countries                                          *
 * random    whether or not to randomly distribute ownership at game start    *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_COUNTRIES, RISK_INVALID_RAND,             *
 *          RISK_INVALID_COUNTRIES_SIZE, RISK_GAME_PLAY_MUTATION, or          *
 *          RISK_NIL if no error.                                             *
 *                                                                            *
 ******************************************************************************/
errRISK_t setCountries(risk_t *game, char **countries, int n, int random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the contries (0-2^8) which make up the map, and whether *
 *          or not to randomly yes(1)/no(0) distribute them at the beginning  *
 *          of the game.                                                      *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * game      the game instance which to set                                   *
 * countries an array of the names of all the countries                       *
 * n         the number of countries                                          *
 * random    whether or not to randomly distribute ownership at game start    *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_COUNTRIES, RISK_INVALID_RAND,             *
 *          RISK_INVALID_COUNTRIES_SIZE, RISK_GAME_PLAY_MUTATION, or          *
 *          RISK_NIL if no error.                                             *
 *                                                                            *
 ******************************************************************************/
errRISK_t getCountries(risk_t *game, char ***countries, int *size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure reachability between countries using 2D array of 1's    *
 *          and 0's.                                                          *

 FIXME: update this shit
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * board    an adjacency matrix                                               *
 * n        the dimension of the adjacency matrix                             *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_BOARD, RISK_INVALID_BOARD_SIZE,           *
 *          RISK_GAME_PLAY_MUTATION, or RISK_NIL if no error.                 *
 *                                                                            *
 ******************************************************************************/
errRISK_t setAdjacencies(risk_t *game, char *country, char **countries, int conflicts);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT   DESCRIPTION                                                     *
 * --------   -----------                                                     *
 * game       the game instance which to set                                  *
 * country
 * neighbors
 * size
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t getNeighbors(risk_t *game, char *country, char ***neighbors, int *size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To test whether or not a give game configuration is valid.        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to test                                   *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME, RISK_NIL_CARD_TYPES, RISK_NIL_TRADEINS,            *
 *          RISK_NIL_NAMES, RISK_NIL_CONTINENTS, RISK_NIL_COUNTRY_BONUSES,    *
 *          RISK_NIL_COUNTRIES, RISK_NIL_BOARD, RISK_INVALID_PLAYERS,         *
 *          RISK_INVALID_RAND, RISK_INVALID_RAND, RISK_INVALID_INCR,          *
 *          RISK_INVALID_BEGINNING, RISK_INVALID_MINIMUM, RISK_INVALID_BONUS, *
 *          RISK_INVALID_WILDS, RISK_INVALID_DECK, RISK_INVALID_TRADES_SET,   *
 *          RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_COUNTRIES_SIZE,        *
 *          RISK_INVALID_COUNTRY_CONTINENT, or RISK_NIL if no error           *
 *                                                                            *
 ******************************************************************************/
errRISK_t isValid(risk_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * country
 * player
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t setOwner(risk_t *game, char *country, char *player);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * country
 * player
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t getOwner(risk_t *game, char *country, char **player);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * country
 * troops
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t setArmies(risk_t *game, char *country, int troops);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * country
 * troops
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t getArmies(risk_t *game, char *country, int *troops);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * rand
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t setRandomCountries(risk_t *game, int rand); // need I/O so this should be tracked else where??

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * rand
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t setRandomArmies(risk_t *game, int rand);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * troops
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t getNextTradeValue(risk_t *game, int *troops);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * card
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t drawCard(risk_t *game, char **card);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * cards
 * troops
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t tradeCards(risk_t *game, char **cards, int *troops);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 * src
 * attack
 * dest
 * defence
 * result
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t attack(risk_t *game, char *src, int attack, char *dest, int defence, int *result); // result is +/- # ??

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t initDeck(risk_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t initCountries(risk_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game       the game instance which to set                                  *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errRISK_t initArmies(risk_t *game);

#endif
