/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/26/17
 Edited:  3/26/17
*/

#include <board.h>

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// checks if r1 can attack r2
int reachable(region_t r1, region_t r2);

// get the territory bonus
int bonus(territory_t territory);

// get the current number of troops placed in the region
int getArmies(region_t region);
int setArmies(region_t region);

// get the current owner of the region
int getPlayer(region_t region);
int setPlayer(region_t region);

// Calculates the number of troops received based on territories owned
char troopBonus(char player) {
  char i, bonus;
  for(i = bonus = 0; i < 42; i++) { 
    //if(TERRITORIES[i] | PLAYER_MASK == player) { bonus++; }
  }
  return bonus / 3;
}

// Calculates the number of troops received based on territory bonuses
char regionBonus(char player) {
  return player;
  //   
}

// a array to map regions to a string representation for printing
char *NAME[42] = { 
  "Alaska", "Northwest Territory", "Greenland", "Alberta", "Ontario", "Quebec", "Western United States", "Eastern United States", "Central America",
  "Iceland", "Scandinavia", "Ukraine", "Great Britain", "Northern Europe", "Western Europe", "Southern Europe",
  "Ural", "Siberia", "Yakutsk", "Kamchatka", "Irkutsk", "Mongolia", "Japan", "Afghanistan", "China", "Middle East", "India", "Siam",
  "Venezuela", "Peru", "Brazil", "Argentina",
  "North Africa", "Egypt", "Congo", "East Africa", "South Africa", "Madagascar",
  "Indonesia", "New Guinea", "Western Australia", "Eastern Australia"
};

// print the game board
void printBoard(

);
