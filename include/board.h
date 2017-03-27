/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/26/17
 Edited:  3/26/17
*/

#ifndef RISKY_BOARD_DEFS
#define RISKY_BOARD_DEFS

#include <stdbool.h>

// a region represents a given space on the board
typedef enum region {
  ALASKA = 0, NORTHWEST_TERRITORY, GREENLAND, ALBERTA, ONTARIO, QUEBEC, WESTERN_UNITED_STATES, EASTERN_UNITED_STATES, CENTRAL_AMERICA, // NORTH AMERICA (9)
  ICELAND, SCANDINAVIA, UKRAINE, GREAT_BRITAIN, NORTHERN_EUROPE, WESTERN_EUROPE, SOUTHERN_EUROPE, // EUROPE (7)
  URAL, SIBERIA, YAKUTSK, KAMCHATKA, IRKUTSK, MONGOLIA, JAPAN, AFGHANISTAN, CHINA, MIDDLE_EAST, INDIA, SIAM, // ASIA (12)
  VENEZUELA, PERU, BRAZIL, ARGENTINA, // SOUTH AMERICA (4)
  NORTH_AFRICA, EGYPT, CONGO, EAST_AFRICA, SOUTH_AFRICA, MADAGASCAR, // AFRICA (6)
  INDONESIA, NEW_GUINEA, WESTERN_AUSTRALIA, EASTERN_AUSTRALIA // OCEANA (4)
} region_t;

typedef enum territory {
  ASIA, NORTH_AMERICA, EUROPE, AFRICA, SOUTH_AMERICA, OCEANA,
} territory_t;

// an array of continent bonuses
unsigned char BONUS[6] = { 7, 5, 3, 2, 2 }; // ASIA, NORTH_AMERICA, EUROPE, AFRICA, SOUTH_AMERICA, OCEANA

// a flat array which hold pertinent dynamic gameplay information including:
//  1) which player controls the territory    [3 bits: 1-3]  (8 players max)
//  2) number of armies on the territory      [9 bits: 4-16] (512 max)
unsigned short TERRITORIES[42] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

// bit masks to retreive gameplay information from TERRITORIES array
#define REACH_MASK  0b0000000000000001
#define BONUS_MASK  0b0000000000001110
#define PLAYER_MASK 0b0000000001110000
#define ARMIES_MASK 0b1111111110000000

// adjacency graph of bools (1 bit) to record static reachability between regions


/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/
int reachable(region_t r1, region_t r2);
int armies(region_t region);
int player(region_t region);
short troops(char player);
void printBoard();

#endif
