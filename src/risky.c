/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/26/17
 Edited:  3/26/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <board.h>
#include <deck.h>

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// attack a given territory
char attack(region_t attacker, region_t defender, unsigned char soilders);

// defend against attackers
void defend(int soilders) {
  
}

// move troops from any src territory to any reachable dest territory
void maneuver(region_t src, region_t dest, unsigned short soilders) {
  // check reachability
  // manipulate map
}
