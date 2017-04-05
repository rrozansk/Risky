/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/4/17
 Info:    Below is the API for Risk. It is general enough to allow user defined
          regions, territories, etc. through the conf file. These API's are also
          useful to help the ai's make decisions and track the game.
*/

#ifndef RISKY_DEFS
#define RISKY_DEFS

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <ini.h>

/*******************************************************************************

    T Y P E S

*******************************************************************************/
typedef struct region    region_t;
typedef struct territory territory_t;
typedef struct card      card_t;
typedef struct player    player_t;
typedef struct list      list_t;

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/
//  REGIONS:
list *regions();                  // get all regions
list *boarders(region_t region);  // boarding regions
player_t owner(region_t region);  // player who owns region
int armies(region_t region);      // # armies on region

//  TERRITORIES:
list *territories();              // return list of all territories
int bonus(territory_t territory); // troop bonus for the given territory

//  PLAYERS:
int troops(player_t);             // calculate troop bonus
list *owned(player_t);            // list of regions owned by player

//  CARDS:
list *cards();                    // get all cards
int getcards();                      // get # cards
card_t *draw();                   // the next card to draw, takes care to shuffle cards and track cards still out
int next();                       // number of troops recieved for next trade

//  GAMEPLAY:
int place(int troops, region_t);  // place armies on a region
int kill(int troops, region_t);   // # remaining on region
void defend(int soilders);        // defend against attackers
int trade(card_t thesecards[3]);       // number of troops recieved for trade
char attack(region_t attacker, region_t defender, unsigned char soilders); // attack a given territory
void maneuver(region_t src, region_t dest, unsigned short soilders);       // move troops from any src territory to any reachable dest territory
void claimRegions();
void setDefenses();
void printBoard(); // print the game board

// FIXME: really this should be risky.h?? and risk is just the API with no rules enforced??
void risk(ini_t *conf); // setup board, regions, bonuses, etc. (cards, territories, regions, bonuses, ... are dynamic and configuarble through conf)

#endif
