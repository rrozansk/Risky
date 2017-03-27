/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/26/17
 Edited:  3/26/17
*/

#ifndef RISKY_CARD_DEFS
#define RISKY_CARD_DEFS

typedef enum card {
  CANNON, SOILDER, CALVARY, WILD
} card_t;

int CARDS[44][2] = {
  { NULL,                  WILD    },
  { NULL,                  WILD    },
  { GREENLAND,             CALVARY },
  { ALBERTA,               CALVARY },
  { ONTARIO,               CALVARY },
  { QUEBEC,                CALVARY },
  { SCANDINAVIA,           CALVARY },
  { UKRAINE,               CALVARY },
  { URAL,                  CALVARY },
  { SIBERIA,               CALVARY },
  { YAKUTSK,               CALVARY },
  { IRKUTSK,               CALVARY },
  { AFGHANISTAN,           CALVARY },
  { INDIA,                 CALVARY },
  { NORTH_AFRICA           CALVARY },
  { MADAGASCAR,            CALVARY },
  { NORTHWEST_TERRITORY,   CANNON  },
  { WESTERN_UNITED_STATES, CANNON  },
  { EASTERN_UNITED_STATES, CANNON  },
  { CENTRAL_AMERICA,       CANNON  },
  { GREAT_BRITAIN,         CANNON  },
  { NORTHERN_EUROPE,       CANNON  },
  { WESTERN_EUROPE,        CANNON  },
  { SOUTHERN_EUROPE,       CANNON  },
  { JAPAN,                 CANNON  },
  { BRAZIL,                CANNON  },
  { SOUTH_AFRICA,          CANNON  },
  { INDONESIA              CANNON  },
  { WESTERN_AUSTRALIA,     CANNON  },
  { EASTERN_AUSTRALIA,     CANNON  },
  { CONGO,                 SOILDER },
  { ALASKA,                SOILDER },
  { ICELAND,               SOILDER },
  { KAMCHATKA,             SOLIDER },
  { MONGOLIA,              SOILDER },
  { CHINA,                 SOILDER },
  { MIDDLE_EAST,           SOILDER },
  { SIAM,                  SOILDER },
  { VENEZUELA,             SOILDER },
  { PERU,                  SOILDER },
  { ARGENTINA,             SOILDER },
  { EGYPT,                 SOILDER },
  { EAST_AFRICA,           SOILDER },
  { NEW_GUINEA,            SOILDER },
};

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/
//deck newDeck(); // for game structs in the case of multiple games/threaded execution
void shuffle();
card_t draw(char player); // short CURRENT_CARD = 0;
int trade(card_t c1, card_t c2, card_t c3);

#endif
