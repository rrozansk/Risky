/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/20/17
 Info:    TODO
*/

#ifndef RISKY_DEFS
#define RISKY_DEFS

/*******************************************************************************

    T Y P E S

*******************************************************************************/
typedef struct game game_t;
typedef struct card card_t;
typedef struct player player_t;
typedef struct country country_t;
typedef struct continent continent_t;

// All the possible errors returned from the library.
typedef enum errRISKY { // 
  RISKY_NULL_COUNTRY, RISKY_NULL_TROOPS, RISKY_NIL, RISKY_NULL_GAME,
} errRISKY_t;

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/

/***********************************ERRORS*************************************/
// Return a string representation of any possible error returned by the library.
const char *strErrRISKY(errRISKY_t errRISKY);

/************************************SETUP*************************************/
errRISKY_t makeRISKY(game_t **game);
errRISKY_t freeRISKY(game_t *game);
errRISKY_t setHumans(game_t *game, char hps);
errRISKY_t setComputers(game_t *game, unsigned char cps, char **computers);
errRISKY_t setLogging(game_t *game, unsigned char on, char *dir);
errRISKY_t setTraining(game_t *game, unsigned short games);
errRISKY_t setTroops(game_t *game, int beginning, int min, int bonus, int rand);
errRISKY_t setDeck(game_t *game, int wilds, char **types, int n);
errRISKY_t setTrades(game_t *game, int *trades, int n, int incr);
errRISKY_t setCps(game_t *game, int **ais, unsigned short chromosomes, unsigned char traits);
errRISKY_t setContinents(game_t *game, char **continents, int *bonuses, int n);
errRISKY_t setCountries(game_t *game, char **countries, int n, int rand);
errRISKY_t setAdjacencies(game_t *game, int **board, int n);
errRISKY_t isEvolved(game_t *game, char *changed);
errRISKY_t risk(game_t *game);

/***********************************PLAYERS************************************/
errRISKY_t getPlayers(game_t *game, int *players);
errRISKY_t troops(game_t *game, player_t);
errRISKY_t owned(game_t *game, player_t);                    // list of countries owned by player as array

/**********************************COUNTRIES***********************************/
errRISKY_t countriesSize(game_t *game, int *size);           // return the size of countries()
errRISKY_t countries(game_t *game, char **all);              // get all countries as an array with countrySize()
errRISKY_t boardersSize(game_t *game, country_t country);    // return the size of boarders()
errRISKY_t boarders(game_t *game, country_t country);        // return all boarding countries as an array with boardersSize()
errRISKY_t name(game_t *game, country_t countr);             // get the name of the country
errRISKY_t owner(game_t *game, country_t country);           // player who owns country
errRISKY_t armies(game_t *game, country_t country);          // # armies on country
errRISKY_t place(game_t *game, int troops, country_t);       // place armies on a country
errRISKY_t randomizeBoard(game_t *game, int rand);           // randomly assign countries to players
errRISKY_t randomizeArmies(game_t *game, int rand);          // randomly assign armies to players countries

/**********************************CONTINENTS**********************************/
errRISKY_t continents(game_t *game, int foo);                       // return ptr to array of all continents
errRISKY_t bonus(game_t *game, continent_t continent);       // troop bonus for the given continent

/************************************CARDS*************************************/
errRISKY_t cards(game_t *game, int foo);                            // get all cards as array
errRISKY_t getcards(game_t *game, int foo );                         // get number of cards
errRISKY_t draw(game_t *game, int foo );                             // the next card to draw, takes care to shuffle cards and track cards still out
errRISKY_t next(game_t *game, int foo );                             // number of troops recieved for next trade
errRISKY_t trade(game_t *game, card_t *trade[]);             // number of troops recieved for trade

/***********************************GAMEPLAY***********************************/
errRISKY_t attack(game_t *game, country_t src, country_t dest, int men);   // attack a given continent
errRISKY_t defend(game_t *game, int soilders);                             // defend against attackers
errRISKY_t maneuver(game_t *game, country_t src, country_t dest, int men); // move troops from any src continent to any reachable dest continent
errRISKY_t claimRegions(game_t *game, country_t country, player_t player); //
errRISKY_t setDefenses(game_t *game);                        //
errRISKY_t printBoard(game_t *game);                         // print out board as a str rep graph??

#endif
