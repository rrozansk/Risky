/******************************************************************************
 * FILE:    risk.h                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  5/2/17                                                            *
 * INFO:    A game library to easily implement Risk like games.               *
 *                                                                            *
 ******************************************************************************/

#ifndef RISK_DEFS
#define RISK_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct game game_t; /* A representation of the game */

typedef enum errRISK { /* All the possible errors returned from the library. */
  RISK_NIL_COUNTRY, RISK_NIL_TROOPS, RISK_NIL_GAME, RISK_NIL_CARD_TYPES,
  RISK_OUT_OF_MEMORY, RISK_NIL_BOARD, RISK_INVALID_INCR, RISK_NIL,
  RISK_NIL_TRADEINS, RISK_INVALID_DECK, RISK_INVALID_WILDS, RISK_NIL_NAMES, 
  RISK_NIL_COUNTRY_BONUSES, RISK_NIL_COUNTRIES, RISK_INVALID_COUNTRY_CONTINENT,
  RISK_COUNTRIES_MISMATCH, RISK_GAME_PLAY_MUTATION, RISK_NIL_CONTINENTS, 
  RISK_INVALID_BEGINNING, RISK_INVALID_MINIMUM, RISK_INVALID_BOARD_SIZE,
  RISK_INVALID_TRADES_SET, RISK_INVALID_COUNTRIES_SIZE, RISK_INVALID_PLAYERS,
  RISK_INVALID_CONTINENTS_SIZE, RISK_INVALID_RAND, RISK_INVALID_BONUS,
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
errRISK_t makeRISK(game_t **game);

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
errRISK_t freeRISK(game_t *game);

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
errRISK_t setPlayers(game_t *game, int players, char **names);

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
errRISK_t setTroops(game_t *game, int start, int min, int bonus, int random);

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
errRISK_t setDeck(game_t *game, int wilds, char **types, int n);

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
errRISK_t setTrades(game_t *game, int *trades, int n, int incr);

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
errRISK_t setContinents(game_t *game, char **continents, int n);

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
errRISK_t setContinentBonuses(game_t *game, int *bonuses, int n);

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
errRISK_t setCountries(game_t *game, char **countries, int n, int random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure reachability between countries using 2D array of 1's    *
 *          and 0's.                                                          *
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
errRISK_t setAdjacencies(game_t *game, int **board, int n);

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
errRISK_t isValid(game_t *game);




typedef struct card card_t; // A representation of a card

/***********************************PLAYERS************************************/
errRISK_t getPlayers(game_t *game, int *players); // names
errRISK_t troops(game_t *game, char *);           //
errRISK_t owned(game_t *game, char *);            // list of countries owned by player as array

/**********************************COUNTRIES***********************************/
errRISK_t countriesSize(game_t *game, int *size);         // return the size of countries()
errRISK_t countries(game_t *game, char **all);            // get all countries as an array with countrySize()
errRISK_t boardersSize(game_t *game, char *country);      // return the size of boarders()
errRISK_t boarders(game_t *game, char *country);          // return all boarding countries as an array with boardersSize()
errRISK_t name(game_t *game, char *country);              // get the name of the country
errRISK_t owner(game_t *game, char *country);             // player who owns country
errRISK_t armies(game_t *game, char *country);            // # armies on country
errRISK_t place(game_t *game, int troops, char *country); // place armies on a country
errRISK_t randomizeBoard(game_t *game, int rand);         // randomly assign countries to players
errRISK_t randomizeArmies(game_t *game, int rand);        // randomly assign armies to players countries

/**********************************CONTINENTS**********************************/
errRISK_t continents(game_t *game, int foo);    // return ptr to array of all continents
errRISK_t bonus(game_t *game, char *continent); // troop bonus for the given continent

/************************************CARDS*************************************/
errRISK_t cards(game_t *game, int foo);         // get all cards as array
errRISK_t getcards(game_t *game, int foo );     // get number of cards
errRISK_t draw(game_t *game, char *card);       // the next card to draw, takes care to shuffle cards and track cards still out
errRISK_t next(game_t *game, int foo );         // number of troops recieved for next trade
errRISK_t trade(game_t *game, card_t *trade[]); // number of troops recieved for trade

/***********************************GAMEPLAY***********************************/
errRISK_t attack(game_t *game, char *src, char *dest, int men);    // attack a given continent TODO result
errRISK_t setDefence(game_t *game, char *country, int soilders);   // defend against attackers
errRISK_t maneuver(game_t *game, char *src, char *dest, int men);  // move troops from any src continent to any reachable dest continent
errRISK_t claimRegions(game_t *game, char *country, char *player); //
errRISK_t setDefenses(game_t *game);                               //

#endif
