/******************************************************************************
 * FILE:    risky.h                                                           *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  4/29/17                                                           *
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
  RISKY_INVALID_RANGE, RISKY_NIL_PLAYER, RISKY_UNKNOWN_ERROR, RISKY_NIL_NAMES,
  RISKY_CPS_NOT_SUPPORTED, RISKY_NIL_CONTINENTS, RISKY_INVALID_RAND,
  RISKY_GAME_PLAY_MUTATION, RISKY_NOT_SUPPORTED, RISKY_INVALID_HUMANS,
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
 * errRISKY The error in question                                             *
 *                                                                            *
 * RETURNS: A string representing the given error.                            *
 *                                                                            *
 ******************************************************************************/
const char *strErrRISKY(errRISKY_t errRISKY);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempt to malloc the space for a new game.                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     where to store the address of the intiated game                   *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_OUT_OF_MEMORY, or RISKY_NIL if no error.    *
 *                                                                            *
 ******************************************************************************/
errRISKY_t makeRISKY(game_t **game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Free all alloc'ed memory, including any configured dynamic arrays.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game you wish to free                                         *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME or RISKY_NIL if no error.                          *
 *                                                                            *
 ******************************************************************************/
errRISKY_t freeRISKY(game_t *game);

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
 * RETURNS: RISKY_NIL_GAME, RISKY_INVALID_HPS, RISKY_GAME_PLAY_MUTATION,      *
 *          RISKY_INVALID_HUMANS, or RISKY_NIL if no error.                   *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setHumans(game_t *game, int players, char **names);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of AIs (0-8) playing by suppling an array of *
 *          strings corresponding to named chromosomes.                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * players  the number of computer players                                    *
 * name     a pointer to an array of names                                    *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_INVALID_CPS, RISKY_INVALID_COMPUTERS,       *
 *          RISKY_GAME_PLAY_MUTATION, or RISKY_NIL if no error.               *
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
 * game     the game instance which to set                                    *
 * on       whether or not to turn logging on                                 *
 * dir      the name of the directory to store game logs                      *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_INVALID_LOGGING, RISKY_NIL_DIR,             *
 *          RISKY_GAME_PLAY_MUTATION, or RISKY_NIL if no error.               *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setLogging(game_t *game, int on, char *dir);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of games (0-2^16) used to train the AIs.     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * games    the number of games to train for                                  *
 *                                                                            *
 * RETURNS: RISKY_GAME_PLAY_MUTATION, RISKY_INVALID_GAMES, RISKY_NIL_GAME, or *
 *          RISKY_NIL if no error.                                            *
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
 * game     the game instance which to set                                    *
 * start    the begginning number of troops to start the game with            *
 * min      the minimum number of troops possible to receive per turn         *
 * bonus    how many countries constitue an extra troop on turn start         *
 * random   whether or not to randomly distribute troops at the start of game *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_INVALID_BEGINNING, RISKY_INVALID_MINIMUM,   *
 *          RISKY_INVALID_BONUS, RISKY_INVALID_RAND, RISKY_GAME_PLAY_MUTATION,*
 *          or RISKY_NIL if no error.                                         *
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
 * game     the game instance which to set                                    *
 * wilds    the number of wilds contained in the deck                         *
 * types    a pointer to an array of card types                               *
 * n        the number of types                                               *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_CARD_TYPES, RISKY_INVALID_WILDS,        *
 *          RISKY_INVALID_DECK, RISKY_GAME_PLAY_MUTATION, or RISKY_NIL if no  *
 *          error.                                                            *
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
 * game     the game instance which to set                                    *
 * trades   a pointer to an array of integers definig the values of trades    *
 * n        the number of defined trades                                      *
 * incr     the constant increment to apply to trades after trades runs out   *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_TRADEINS, RISKY_INVALID_INCR,           *
 *          RISKY_INVALID_TRADES_SET, RISKY_GAME_PLAY_MUTATION, or RISKY_NIL  *
 *          if no error.                                                      *
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
 * game     the game instance which to set                                    *
 * ais      an array of chromosomes                                           *
 * names    a pointer the the names of the AIs                                *
 * strands  the number of chromosomes in ais                                  *
 * traits   the number of traits contained in each chromosome                 *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_NAMES, RISKY_INVALID_CHROMOSOMES,       *
 *          RISKY_INVALID_TRAITS, RISKY_GAME_PLAY_MUTATION, or RISKY_NIL if   *
 *          no error.                                                         *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setCps(game_t *game, int **ais, char **names, int strands, int traits);

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
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_CONTINENTS,                             *
 *          RISKY_INVALID_CONTINENTS_SIZE, RISKY_INVALID_CONTINENTS_SIZE,     *
 *          RISKY_GAME_PLAY_MUTATION, or RISKY_NIL if no error.               *
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
 * game     the game instance which to set                                    *
 * bonus    array of integers defining the troop bonus for owning a continent * 
 * n        the number of bonues                                              *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_COUNTRY_BONUSES,                        *
 *          RISKY_INVALID_CONTINENTS_SIZE, RISKY_INVALID_CONTINENTS_SIZE,     *
 *          RISKY_GAME_PLAY_MUTATION, or RISKY_NIL if no error.               *
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
 * game      the game instance which to set                                   *
 * countries an array of the names of all the countries                       *
 * n         the number of countries                                          *
 * random    whether or not to randomly distribute ownership at game start    *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_COUNTRIES, RISKY_INVALID_RAND,          *
 *          RISKY_INVALID_COUNTRIES_SIZE, RISKY_GAME_PLAY_MUTATION, or        *
 *          RISKY_NIL if no error.                                            *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setCountries(game_t *game, char **countries, int n, int random);

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
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_BOARD, RISKY_INVALID_BOARD_SIZE,        *
 *          RISKY_GAME_PLAY_MUTATION, or RISKY_NIL if no error.               *
 *                                                                            *
 ******************************************************************************/
errRISKY_t setAdjacencies(game_t *game, int **board, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Determine whether or not any chromosomes changed.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance which to set                                    *
 * changed  an int in which to set with whether or not dna changed            *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME or RISKY_NIL if no error.                          *
 *                                                                            *
 ******************************************************************************/
errRISKY_t isEvolved(game_t *game, int *changed);

/****************************************************************************** // FIXME: not a public function!?
 *                                                                            *
 * PURPOSE: Print an enumerated list of choices starting from 0.              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * elems    an array of choices                                               *
 * size     the number of choices                                             *
 *                                                                            *
 * RETURNS: RISKY_INVALID_INDEX_SIZE, RISKY_NIL_ELEMS, or RISKY_NIL if no     *
 *          error.                                                            *
 *                                                                            *
 ******************************************************************************/
errRISKY_t printChoices(char **elems, int size);

/****************************************************************************** // FIXME: not a public function!?
 *                                                                            *
 * PURPOSE: Read in an integer, only accepting input between the bounds.      *
 *           Optionally prompt user 'are you sure'. Handles all errors        *
 *           appropriately.                                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * lbound   the lower bound of acceptance                                     *
 * ubound   the upper bound of acceptance                                     *
 * pick     address to set with the resulting choice                          *
 * prompt   whether or not to prompt for sureness of choice                   *
 *                                                                            *
 * RETURNS: RISKY_INVALID_RANGE, RISKY_NIL_CHOICE, RISKY_INVALID_PROMPT,      *
 *          RISKY_READ_ERROR, or RISKY_NIL if no error.                       *
 *                                                                            *
 ******************************************************************************/
errRISKY_t readInt(int lbound, int ubound, int *pick, int prompt);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Kick off a command line version of a Risk like game.              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to use for the command line version of the game *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_NIL_GAME, RISKY_NIL_COMPUTERS,              *
 *          RISKY_NIL_DIR, RISKY_NIL_CARD_TYPES, RISKY_NIL_TRADEINS,          *
 *          RISKY_NIL_AIS, RISKY_NIL_NAMES, RISKY_NIL_CONTINENTS,             *
 *          RISKY_NIL_COUNTRY_BONUSES, RISKY_NIL_COUNTRIES, RISKY_NIL_BOARD,  *
 *          RISKY_INVALID_LOGGING, RISKY_NIL_DIR, RISKY_INVALID_CPS,          *
 *          RISKY_INVALID_HPS, RISKY_PLAYER_MANY, RISKY_PLAYERS_LITTLE,       *
 *          RISKY_INVALID_RAND, RISKY_INVALID_RAND, RISKY_INVALID_BOARD_SIZE, *
 *          RISKY_INVALID_ADJACENCIES, RISKY_INVALID_CHROMOSOMES,             *
 *          RISKY_INVALID_TRAITS, RISKY_INVALID_INCR, RISKY_INVALID_GAMES,    *
 *          RISKY_INVALID_BEGINNING, RISKY_INVALID_MINIMUM,                   *
 *          RISKY_INVALID_BONUS, RISKY_INVALID_WILDS, RISKY_INVALID_DECK,     *
 *          RISKY_INVALID_TRADES_SET, RISKY_INVALID_CONTINENTS_SIZE,          *
 *          RISKY_INVALID_COUNTRIES_SIZE, RISKY_INVALID_COUNTRY_CONTINENT,    *
 *          RISKY_DIR_CREATION_FAILURE, RISKY_FILE_CREATION_FAILURE, or       *
 *          RISKY_NIL if no error.                                            *
 *                                                                            *
 ******************************************************************************/
errRISKY_t risky(game_t *game);

/****************************************************************************** // FIXME: not a public function!?
 *                                                                            *
 * PURPOSE: Print out the game board.                                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to use.                                         *
 *                                                                            *
 * RETURNS: RISKY_NIL_GAME, RISKY_NOT_SUPPORTED, or RISKY_NIL if no error.    *
 *                                                                            *
 ******************************************************************************/
errRISKY_t printBoard(game_t *game);

errRISKY_t getCps(game_t *game, char ***strArr1, int *size);
errRISKY_t getChromosome(game_t *game, char *name, int **dna, int *size);





/***********************************PLAYERS************************************/
typedef struct card card_t; // A representation of a card    // FIXME: needed??

errRISKY_t getPlayers(game_t *game, int *players); // names
errRISKY_t troops(game_t *game, char *);
errRISKY_t owned(game_t *game, char *); // list of countries owned by player as array

/**********************************COUNTRIES***********************************/
errRISKY_t countriesSize(game_t *game, int *size);     // return the size of countries()
errRISKY_t countries(game_t *game, char **all);                  // get all countries as an array with countrySize()
errRISKY_t boardersSize(game_t *game, char *country);        // return the size of boarders()
errRISKY_t boarders(game_t *game, char *country);            // return all boarding countries as an array with boardersSize()
errRISKY_t name(game_t *game, char *country);                 // get the name of the country
errRISKY_t owner(game_t *game, char *country);               // player who owns country
errRISKY_t armies(game_t *game, char *country);              // # armies on country
errRISKY_t place(game_t *game, int troops, char *country); // place armies on a country
errRISKY_t randomizeBoard(game_t *game, int rand);     // randomly assign countries to players
errRISKY_t randomizeArmies(game_t *game, int rand);    // randomly assign armies to players countries

/**********************************CONTINENTS**********************************/
errRISKY_t continents(game_t *game, int foo); // return ptr to array of all continents
errRISKY_t bonus(game_t *game, char *continent);  // troop bonus for the given continent

/************************************CARDS*************************************/
errRISKY_t cards(game_t *game, int foo);      // get all cards as array
errRISKY_t getcards(game_t *game, int foo );  // get number of cards
errRISKY_t draw(game_t *game, int foo );      // the next card to draw, takes care to shuffle cards and track cards still out
errRISKY_t next(game_t *game, int foo );      // number of troops recieved for next trade
errRISKY_t trade(game_t *game, card_t *trade[]);        // number of troops recieved for trade

/***********************************GAMEPLAY***********************************/
errRISKY_t attack(game_t *game, char *src, char *dest, int men);   // attack a given continent
errRISKY_t defend(game_t *game, int soilders);                             // defend against attackers
errRISKY_t maneuver(game_t *game, char *src, char *dest, int men); // move troops from any src continent to any reachable dest continent
errRISKY_t claimRegions(game_t *game, char *country, char *player);           //
errRISKY_t setDefenses(game_t *game);                                                //

#endif
