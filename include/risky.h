/******************************************************************************
 * FILE:    risky.h                                                           *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  4/24/17                                                           *
 * INFO:    A game library to easily implement Risk like games. It also       *
 *          exposes a command line version of risk which is completely        *
 *          configurable and allows for the training and competing of AIs.    *
 *                                                                            *
 ******************************************************************************/

#ifndef RISKY_DEFS
#define RISKY_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct game game_t; /* A representation of the game */

typedef enum errRISKY { /* All the possible errors returned from the library. */
  RISKY_NIL_COUNTRY, RISKY_NIL_TROOPS, RISKY_NIL_GAME, RISKY_PLAYER_MANY,
  RISKY_OUT_OF_MEMORY, RISKY_INVALID_HPS, RISKY_INVALID_CPS, RISKY_NIL_BOARD,
  RISKY_INVALID_COMPUTERS, RISKY_NIL_COMPUTERS, RISKY_INVALID_INCR, RISKY_NIL,
  RISKY_NIL_DIR, RISKY_NIL_TRADEINS, RISKY_INVALID_DECK, RISKY_INVALID_WILDS,
  RISKY_NIL_COUNTRY_BONUSES, RISKY_NIL_COUNTRIES, RISKY_PLAYERS_LITTLE,
  RISKY_INVALID_LOGGING, RISKY_NIL_CARD_TYPES, RISKY_INVALID_COUNTRY_CONTINENT,
  RISKY_INVALID_ADJACENCIES, RISKY_DIR_CREATION_FAILURE, RISKY_INVALID_GAMES,
  RISKY_FILE_CREATION_FAILURE, RISKY_INVALID_CHROMOSOMES, RISKY_INVALID_BONUS,
  RISKY_INVALID_BEGINNING, RISKY_INVALID_MINIMUM, RISKY_INVALID_BOARD_SIZE,
  RISKY_INVALID_TRAITS, RISKY_INVALID_TRADES_SET, RISKY_INVALID_COUNTRIES_SIZE,
  RISKY_INVALID_CONTINENTS_SIZE, RISKY_INVALID_PROMPT, RISKY_NIL_CHOICE,
  RISKY_INVALID_INDEX_SIZE, RISKY_NIL_ELEMS, RISKY_READ_ERROR, RISKY_NIL_AIS,
  RISKY_INVALID_RANGE, RISKY_NIL_PLAYER, RISKY_UNKNOW_ERROR, RISKY_NIL_NAMES,
  RISKY_CPS_NOT_SUPPORTED, RISKY_NIL_CONTINENTS, RISKY_INVALID_RAND,
} errRISKY_t;

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
 * errRISKY ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
const char *strErrRISKY(errRISKY_t errRISKY);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempt to malloc the space for a new game.                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t makeRISKY(game_t **game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Free all alloc'ed memory, including any configured dynamic arrays.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t freeRISKY(game_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of human players (0-8) for the game.         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * players  ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setHumans(game_t *game, int players);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of AIs (0-8) playing by suppling an array of *
 *          strings corresponding to named chromosomes.                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * players  ...                                                               *
 * name     ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setComputers(game_t *game, int players, char **names);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Turn logging on(1)/off(0). Must specify a logging directory if    *
 *          turned on, with length between 1-255 characters.                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * on       ...                                                               *
 * dir      ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setLogging(game_t *game, int on, char *dir);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of games (0-2^16) used to train the AIs.     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * games    ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setTraining(game_t *game, int games);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure how troops are setup. How much you receive at the game  *
 *          start, the minimum per turn, and ratio of countries to troops to  *
 *          recieve for turn bonus all 0-2^8. Can also choose to randomly     *
 *          assign troops to countries yes(1)/no(0).                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * start    ...                                                               *
 * min      ...                                                               *
 * bonus    ...                                                               *
 * random   ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setTroops(game_t *game, int start, int min, int bonus, int random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the deck/cards used for trading. The number of wild     *
 *          (0-2^8), and all possible card types besides wilds (len 2-2^8).   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * wilds    ...                                                               *
 * types    ...                                                               *
 * n        ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setDeck(game_t *game, int wilds, char **types, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure how card trades are handled. How much each is worth     *
 *          (0-2^8) and the contant incrment (0-2^8) after the predefined     *
 *          ones run out.                                                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * trades   ...                                                               *
 * n        ...                                                               *
 * incr     ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setTrades(game_t *game, int *trades, int n, int incr);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the DNA used for the AIs. a 2D array representing the   *
 *          chromosomes, the corresponding names for each AI, and the number  *
 *          of chromosomes and traits in the DNA. All values 0-2^8 and        *
 *          lengths of arrays 0-2^8.                                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * ais      ...                                                               *
 * names    ...                                                               *
 * strands  ...                                                               *
 * traits   ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setCps(game_t *game, int **ais, char **names, int strands, int traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the continents (1-2^8) which make up the map.           *
 *                                                                            *
 * ARGUMENT   DESCRIPTION                                                     *
 * --------   -----------                                                     *
 * game       ...                                                             *
 * continents ...                                                             *
 * n          ...                                                             *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setContinents(game_t *game, char **continents, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the continent bonuses (val: 0-2^8, len: 0-2^8) which    *
 *          make up the map.                                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * bonus    ...                                                               *
 * n        ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setContinentBonuses(game_t *game, int *bonuses, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the contries (0-2^8) which make up the map, and whether *
 *          or not to randomly yes(1)/no(0) distribute them at the beginning  *
 *          of the game.                                                      *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * game      ...                                                              *
 * countries ...                                                              *
 * n         ...                                                              *
 * random    ...                                                              *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setCountries(game_t *game, char **countries, int n, int random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure reachability between countries using 2D array of 1's    *
 *           and 0's.                                                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * board    ...                                                               *
 * n        ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setAdjacencies(game_t *game, int **board, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Determine whether or not any chromosomes changed.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 * changed  ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t isEvolved(game_t *game, int *changed);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Print an enumerated list of choices starting from 0.              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * elems    ...                                                               *
 * size     ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t printChoices(char **elems, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read in an integer, only accepting input between the bounds.      *
 *           Optionally prompt user 'are you sure'. Handles all errors        *
 *           appropriately.                                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * lbound   ...                                                               *
 * ubound   ...                                                               *
 * pick     ...                                                               *
 * prompt   ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t readInt(int lbound, int ubound, int *pick, int prompt);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Kick off a command line version of a Risk like game.              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errRISKY_t risky(game_t *game);

/***********************************PLAYERS************************************/
typedef struct card card_t; // A representation of a card    // FIXME: are these needed??
typedef struct player player_t; // A representation of a player
typedef struct country country_t; // A representation of a country
typedef struct continent continent_t; // A representation of a continent

errRISKY_t getPlayers(game_t *game, int *players); // names
errRISKY_t troops(game_t *game, player_t);
errRISKY_t owned(game_t *game, player_t); // list of countries owned by player as array

/**********************************COUNTRIES***********************************/
errRISKY_t countriesSize(game_t *game, int *size);     // return the size of countries()
errRISKY_t countries(game_t *game, char **all);                  // get all countries as an array with countrySize()
errRISKY_t boardersSize(game_t *game, country_t country);        // return the size of boarders()
errRISKY_t boarders(game_t *game, country_t country);            // return all boarding countries as an array with boardersSize()
errRISKY_t name(game_t *game, country_t countr);                 // get the name of the country
errRISKY_t owner(game_t *game, country_t country);               // player who owns country
errRISKY_t armies(game_t *game, country_t country);              // # armies on country
errRISKY_t place(game_t *game, int troops, country_t); // place armies on a country
errRISKY_t randomizeBoard(game_t *game, int rand);     // randomly assign countries to players
errRISKY_t randomizeArmies(game_t *game, int rand);    // randomly assign armies to players countries

/**********************************CONTINENTS**********************************/
errRISKY_t continents(game_t *game, int foo); // return ptr to array of all continents
errRISKY_t bonus(game_t *game, continent_t continent);  // troop bonus for the given continent

/************************************CARDS*************************************/
errRISKY_t cards(game_t *game, int foo);      // get all cards as array
errRISKY_t getcards(game_t *game, int foo );  // get number of cards
errRISKY_t draw(game_t *game, int foo );      // the next card to draw, takes care to shuffle cards and track cards still out
errRISKY_t next(game_t *game, int foo );      // number of troops recieved for next trade
errRISKY_t trade(game_t *game, card_t *trade[]);        // number of troops recieved for trade

/***********************************GAMEPLAY***********************************/
errRISKY_t attack(game_t *game, country_t src, country_t dest, int men);   // attack a given continent
errRISKY_t defend(game_t *game, int soilders);                             // defend against attackers
errRISKY_t maneuver(game_t *game, country_t src, country_t dest, int men); // move troops from any src continent to any reachable dest continent
errRISKY_t claimRegions(game_t *game, country_t country, player_t player);           //
errRISKY_t setDefenses(game_t *game);                                                //
errRISKY_t printBoard(game_t *game);                                                 // print out board as a str rep graph??

#endif
