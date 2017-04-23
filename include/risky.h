/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/22/17
 Info:    A game library to easily implement Risk like games. It also exposes a
          command line version of risk which is completely configurable and
          allows for the training and competing of AIs.
*/

#ifndef RISKY_DEFS
#define RISKY_DEFS

/*******************************************************************************

    T Y P E S

*******************************************************************************/
// A representation of the game
typedef struct game game_t;

// A representation of a card
typedef struct card card_t;

// A representation of a player
typedef struct player player_t;

// A representation of a country
typedef struct country country_t;

// A representation of a continent
typedef struct continent continent_t;

// All the possible errors returned from the library.
typedef enum errRISKY {
  RISKY_NULL_COUNTRY, RISKY_NULL_TROOPS, RISKY_NULL_GAME, RISKY_PLAYER_MANY,
  RISKY_OUT_OF_MEMORY, RISKY_INVALID_HPS, RISKY_INVALID_CPS, RISKY_NULL_BOARD,
  RISKY_INVALID_COMPUTERS, RISKY_NULL_COMPUTERS, RISKY_INVALID_INCR, RISKY_NIL,
  RISKY_NULL_DIR, RISKY_NULL_TRADEINS, RISKY_INVALID_DECK, RISKY_INVALID_WILDS,
  RISKY_NULL_AIS, RISKY_NULL_NAMES, RISKY_NULL_CONTINENTS, RISKY_INVALID_RAND,
  RISKY_NULL_COUNTRY_BONUSES, RISKY_NULL_COUNTRIES, RISKY_PLAYERS_LITTLE,
  RISKY_INVALID_LOGGING, RISKY_NULL_CARD_TYPES, RISKY_INVALID_COUNTRY_CONTINENT,
  RISKY_INVALID_ADJACENCIES, RISKY_DIR_CREATION_FAILURE, RISKY_INVALID_GAMES,
  RISKY_FILE_CREATION_FAILURE, RISKY_INVALID_CHROMOSOMES, RISKY_INVALID_BONUS,
  RISKY_INVALID_BEGINNING, RISKY_INVALID_MINIMUM, RISKY_INVALID_BOARD_SIZE,
  RISKY_INVALID_TRAITS, RISKY_INVALID_TRADES_SET, RISKY_INVALID_COUNTRIES_SIZE,
  RISKY_INVALID_CONTINENTS_SIZE,
} errRISKY_t;

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/

/***********************************ERRORS*************************************/

// Return a string representation of any possible error returned by the library.
const char *strErrRISKY(errRISKY_t errRISKY);

/************************************RISKY*************************************/

// Attempt to malloc the space for a new game.
errRISKY_t makeRISKY(game_t **game);

// Free all allocated memory for a game, including parameters which were set.
errRISKY_t freeRISKY(game_t *game);

// Configure the number of human players (0-8) for the game.
errRISKY_t setHumans(game_t *game, int players);

// Configure the number of AIs (0-8) playing by suppling an array of strings
// corresponding to named chromosomes.
errRISKY_t setComputers(game_t *game, int players, char **names);

// Turn logging on(1)/off(0). Must specify a logging directory if turned on,
// with length between 1-255 characters.
errRISKY_t setLogging(game_t *game, int on, char *dir);

// Configure the number of games (0-2^16) used to train the AIs.
errRISKY_t setTraining(game_t *game, int games);

// Configure how troops are setup. How much you receive at the game start, the
// minimum per turn, and ratio of countries to troops to recieve for turn bonus
// all 0-2^8. Can also choose to randomly assign troops to countries
// yes(1)/no(0).
errRISKY_t setTroops(game_t *game, int beginning, int min, int bonus, int rand);

// Configure the deck/cards used for trading. The number of wild (0-2^8), and
// all possible card types besides wilds (len 2-2^8).
errRISKY_t setDeck(game_t *game, int wilds, char **types, int n);

// Configure how card trades are handled. How much each is worth (0-2^8) and 
// the contant incrment (0-2^8) after the predefined ones run out.
errRISKY_t setTrades(game_t *game, int *trades, int n, int incr);

// Configure the DNA used for the AIs. a 2D array representing the chromosomes,
// the corresponding names for each AI, and the number of chromosomes and
// traits in the DNA. All values 0-2^8 and lengths of arrays 0-2^8.
errRISKY_t setCps(game_t *game, int **ais, char **names, int chromosomes, int traits);

// Configure the continents (1-2^8) which make up the map.
errRISKY_t setContinents(game_t *game, char **continents, int n);

// Configure the continent bonuses (val: 0-2^8, len: 0-2^8) which make up the map.
errRISKY_t setContinentBonuses(game_t *game, int *bonuses, int n);

// Configure the contries (0-2^8) which make up the map, and whether or not to
// randomly yes(1)/no(0) distribute them at the beginning of the game.
errRISKY_t setCountries(game_t *game, char **countries, int n, int rand);

// Configure reachability between countries using 2D array of 1's and 0's. 
errRISKY_t setAdjacencies(game_t *game, int **board, int n);

// Determine whether or not any chromosomes changed.
errRISKY_t isEvolved(game_t *game, int *changed);

// Kick off a command line version of a Risk like game.
errRISKY_t risky(game_t *game);

// TODO
/***********************************PLAYERS************************************/

errRISKY_t getPlayers(game_t *game, int *players);
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
