/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/21/17
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
  RISKY_NULL_COUNTRY, RISKY_NULL_TROOPS, RISKY_NIL, RISKY_NULL_GAME,
  RISKY_OUT_OF_MEMORY, RISKY_INVALID_HPS, RISKY_INVALID_CPS, 
  RISKY_INVALID_COMPUTERS, RISKY_NULL_COMPUTERS,
  RISKY_NULL_DIR, RISKY_NULL_CARD_TYPES, RISKY_NULL_TRADEINS,
  RISKY_NULL_AIS, RISKY_NULL_NAMES, RISKY_NULL_CONTINENTS,
  RISKY_NULL_COUNTRY_BONUSES, RISKY_NULL_COUNTRIES, RISKY_NULL_BOARD,
  RISKY_BOARD_SIZE_ZERO, RISKY_COUNTRIES_SIZE_ZERO, RISKY_INVALID_RAND,
  RISKY_INVALID_LOGGING,
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

// Configure the number of human players for the game.
errRISKY_t setHumans(game_t *game, unsigned char players);

// Configure the AIs which will be playing this game.
errRISKY_t setComputers(game_t *game, unsigned char players, char **names);

// Turn logging on/off. Must specify a logging directory if turned on.
errRISKY_t setLogging(game_t *game, unsigned char on, char *dir);

// Configure the number of games used to train the AIs.
errRISKY_t setTraining(game_t *game, unsigned short games);

// Configure how troops will be handled throughout the game.
errRISKY_t setTroops(game_t *game, unsigned char beginning, unsigned char min, unsigned char bonus, unsigned char rand);

// Configure the deck/cards used for trading.
errRISKY_t setDeck(game_t *game, unsigned char wilds, char **types, unsigned char n);

// Configure how card trades are handled.
errRISKY_t setTrades(game_t *game, unsigned char *trades, unsigned char n, unsigned char incr);

// Configure the DNA used for the AIs.
errRISKY_t setCps(game_t *game, unsigned char **ais, char **names, unsigned char chromosomes, unsigned char traits);

// Configure the continents which make up the map.
errRISKY_t setContinents(game_t *game, char **continents, unsigned char *bonuses, unsigned char n);

// Configure the contries which make up the map.
errRISKY_t setCountries(game_t *game, char **countries, unsigned char n, unsigned char rand);

// Configure reachability between countries.
errRISKY_t setAdjacencies(game_t *game, unsigned char **board, unsigned char n);

// Determine whether or not any chromosomes changed.
errRISKY_t isEvolved(game_t *game, unsigned char *changed);

// Kick off a command line version of a Risk like game.
errRISKY_t risky(game_t *game);

/***********************************PLAYERS************************************/

errRISKY_t getPlayers(game_t *game, unsigned char *players); //
errRISKY_t troops(game_t *game, player_t);                   //
errRISKY_t owned(game_t *game, player_t);                    // list of countries owned by player as array

/**********************************COUNTRIES***********************************/

errRISKY_t countriesSize(game_t *game, unsigned char *size);     // return the size of countries()
errRISKY_t countries(game_t *game, char **all);                  // get all countries as an array with countrySize()
errRISKY_t boardersSize(game_t *game, country_t country);        // return the size of boarders()
errRISKY_t boarders(game_t *game, country_t country);            // return all boarding countries as an array with boardersSize()
errRISKY_t name(game_t *game, country_t countr);                 // get the name of the country
errRISKY_t owner(game_t *game, country_t country);               // player who owns country
errRISKY_t armies(game_t *game, country_t country);              // # armies on country
errRISKY_t place(game_t *game, unsigned char troops, country_t); // place armies on a country
errRISKY_t randomizeBoard(game_t *game, unsigned char rand);     // randomly assign countries to players
errRISKY_t randomizeArmies(game_t *game, unsigned char rand);    // randomly assign armies to players countries

/**********************************CONTINENTS**********************************/

errRISKY_t continents(game_t *game, unsigned char foo); // return ptr to array of all continents
errRISKY_t bonus(game_t *game, continent_t continent);  // troop bonus for the given continent

/************************************CARDS*************************************/

errRISKY_t cards(game_t *game, unsigned char foo);      // get all cards as array
errRISKY_t getcards(game_t *game, unsigned char foo );  // get number of cards
errRISKY_t draw(game_t *game, unsigned char foo );      // the next card to draw, takes care to shuffle cards and track cards still out
errRISKY_t next(game_t *game, unsigned char foo );      // number of troops recieved for next trade
errRISKY_t trade(game_t *game, card_t *trade[]);        // number of troops recieved for trade

/***********************************GAMEPLAY***********************************/

errRISKY_t attack(game_t *game, country_t src, country_t dest, unsigned char men);   // attack a given continent
errRISKY_t defend(game_t *game, unsigned char soilders);                             // defend against attackers
errRISKY_t maneuver(game_t *game, country_t src, country_t dest, unsigned char men); // move troops from any src continent to any reachable dest continent
errRISKY_t claimRegions(game_t *game, country_t country, player_t player);           //
errRISKY_t setDefenses(game_t *game);                                                //
errRISKY_t printBoard(game_t *game);                                                 // print out board as a str rep graph??

#endif
