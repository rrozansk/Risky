/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/15/17
 Info:    Below is an API for building Risk like games. In addition to the API
          a command line version of a Risk like game is also exposed. The game
          allows total customization of gameplay through the use of a game_t
          type defined below. It also allows for the training and competing of
          custom configured AIs, and optional logging to files for all game types.
*/

#ifndef RISKY_DEFS
#define RISKY_DEFS

/*******************************************************************************

    T Y P E S

*******************************************************************************/
typedef struct game_conf {
  // PLAYERS
  int hps;             // number of human players  FIXME: int 0-8 -> put for all
  char *computers;     // ptr to array of cps, i.e {cp0,cp1}
  int cps;             // size of computers
  // TRAINING
  int log;             // turn on/off logging during training exercises
  char *dir;           // directory to put taining logs
  int trains;          // numer of training exercises to perform
  // TROOPS
  int beginning;       // number of troops recieved at game start
  int minimum;         // minimum troop bonus per turn
  int bonus;           // 
  int random;          // 
  // CARDS
  char *cardTypes;     // ptr to array of card types
  int numTypes;        // size of cardTypes
  int wilds;           // number of wilds in the deck
  int *tradeIns;       // ptr to array of trade in bonuses
  int numTrades;       // size of tradeIns
  int tradeIncr;       // constant trade increment once 
  // CHROMOSOMES
  int numChromosomes;  // number of chromosomes in each strand on DNA
  int *cp0;            // ai 0
  int *cp1;            // ai 1
  int *cp2;            // ai 2
  int *cp3;            // ai 3
  int *cp4;            // ai 4
  int *cp5;            // ai 5
  int *cp6;            // ai 6
  int *cp7;            // ai 7
  // MAP
  char *continents;    // ptr to array of continents
  int *contBonuses;    // ptr to array of contnent bonuses
  int numConts;        // size of continents array and contBonuses
  char *countries;     // ptr to array of countries
  int numCountries;    // size of countries array
  int randomCountries; // to split up map randomly or not
  int *board;          // adjacency matrix (2d array) 
} game_conf_t;

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/


/***********************************PLAYERS************************************/
typedef struct player player_t;
int troops(player_t);              // calculate troop bonus
typedef struct country country_t;
country_t *owned(player_t);        // list of countries owned by player as array

/**********************************COUNTRIES***********************************/
int countriesSize();                    // return the size of countries()
country_t *countries();                 // get all countries as an array with countrySize()
int boardersSize(country_t country);    // return the size of boarders()
country_t *boarders(country_t country); // return all boarding countries as an array with boardersSize()
char *name(country_t countr);           // get the name of the country
player_t owner(country_t country);      // player who owns country
int armies(country_t country);          // # armies on country
int place(int troops, country_t);       // place armies on a country
void randomizeBoard();                  // randomly assign countries to players
void randomizeArmies();                 // randomly assign armies to players countries

/**********************************CONTINENTS**********************************/
typedef struct continent continent_t;
continent_t *continents();              // return ptr to array of all continents
int bonus(continent_t continent);  // troop bonus for the given continent

/************************************CARDS*************************************/
typedef struct card card_t;
card_t *cards();                   // get all cards as array
int getcards();                    // get number of cards
card_t *draw();                    // the next card to draw, takes care to shuffle cards and track cards still out
int next();                        // number of troops recieved for next trade
int trade(card_t *thesecards[], int size);   // number of troops recieved for trade

/***********************************GAMEPLAY***********************************/
char attack(country_t src, country_t dest, int men);   // attack a given continent
void defend(int soilders);                             // defend against attackers
void maneuver(country_t src, country_t dest, int men); // move troops from any src continent to any reachable dest continent
void claimRegions();                                   //
void setDefenses();                                    //
char *printBoard();                                    // print out board as a str rep graph??

/************************************RISKY*************************************/
char *risk(game_conf_t *game); // play an approximation of Risk board game

#endif
