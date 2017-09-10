/******************************************************************************
 * FILE:    risk.h                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  9/9/17                                                            *
 * INFO:    A library to easily implement Risk like games. The API allows for *
 *          setting up custom games by allowing the user to define all        *
 *          aspects of the game including: the board, cards types, trade in   *
 *          values, troop bonuses for continents and territories, and initial *
 *          game values. It also attempts to make manipulation of the game    *
 *          state easy, while also guarding against changing game parameteres *
 *          during gameplay. This allows the user to easily implement higher  *
 *          level game logic (i.e. rules) without having to deal with the     *
 *          lower level details of the implementation. In addition to this the*
 *          library also handles errors for invalid parameters as well as for *
 *          checking the overall game configuration before gameplay to        *
 *          verify/validate it.                                               *
 *                                                                            *
 ******************************************************************************/

#ifndef RISK_DEFS
#define RISK_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct risk risk_t; /* A representation of the game */

typedef enum errRISK { /* All the possible errors returned from the library. */
  RISK_OUT_OF_MEMORY, RISK_GAMEPLAY_MUTATION, RISK_INVALID_PLAYER_COUNT,
  RISK_INVALID_INDEX, RISK_INVALID_STARTING_TROOPS, RISK_INVALID_TROOP_BONUS,
  RISK_INVALID_TROOP_MINIMUM, RISK_INVALID_TROOP_RANDOM,
  RISK_INVALID_DECK_WILDS, RISK_INVALID_CARD_TYPES_COUNT,
  RISK_INVALID_REWARDS_COUNT, RISK_INVALID_LENGTH, RISK_INVALID_INCREMENT,
  RISK_INVALID_COUNTRIES_COUNT, RISK_INVALID_RANDOM, RISK_NIL_GAME,
  RISK_NIL_ARR_PLAYERS, RISK_NIL_ARR_PLAYER, RISK_NIL_PLAYERS, RISK_NIL_PLAYER,
  RISK_NIL_LENGTH, RISK_NIL_STARTING_TROOPS, RISK_NIL_TROOP_BONUS,
  RISK_NIL_TROOP_MINIMUM, RISK_NIL_TROOP_RANDOM, RISK_NIL_DECK_WILDS,
  RISK_NIL_CARD_TYPES, RISK_NIL_TYPES, RISK_NIL_TYPE, RISK_NIL_ARR_REWARDS,
  RISK_NIL_REWARDS, RISK_NIL_INCREMENT, RISK_NIL_ARR_CONTINENTS,
  RISK_NIL_ARR_CONTINENT, RISK_NIL_CONTINENTS, RISK_NIL_CONTINENT,
  RISK_NIL_ARR_BONUSES, RISK_NIL_BONUSES, RISK_NIL_ARR_COUNTRIES,
  RISK_NIL_ARR_COUNTRY, RISK_NIL_COUNTRIES, RISK_NIL_COUNTRY, RISK_NIL_RANDOM,
  RISK_NIL,
} errRISK_t;

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
 * errRISK The error in question                                              *
 *                                                                            *
 * RETURNS: A string representing the given error.                            *
 *                                                                            *
 ******************************************************************************/
const char *strErrRISK(errRISK_t errRISK);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempt to malloc the space for a new game.                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     where to store the address of the instantiated game               *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_OUT_OF_MEMORY is allocation of game fails                    *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t makeRISK(risk_t **game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Free all alloc'ed memory, including any configured dynamic arrays.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to free                                         *
 *                                                                            *
 * RETURNS: RISK_NIL                                                          *
 *                                                                            *
 ******************************************************************************/
errRISK_t freeRISK(risk_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of human players (0-8) for the game.         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * n        the number of players in players array                            *
 * players  an array of strings containing the names of each player           *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_PLAYER_COUNT if n > 8 or n < 2                       *
 *          RISK_NIL_ARR_PLAYERS if players is NULL                           *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL_ARR_PLAYER if any reference into players is NULL         *
 *          RISK_OUT_OF_MEMORY is allocation of game fails                    *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setPlayers(risk_t *game, int n, char *players[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Retrieve the number of players in the given game.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * players  the address of an int in which to with the number of players      *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_PLAYERS is players is NULL                               *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthPlayers(risk_t *game, int *players);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Retrieve the string length of a player in the given game.         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * idx      the index of the player in question                               *
 * n        the address of an int in which to store the length of the player  *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 or idx >= number of players         *
 *          RISK_NIL_LENGTH if n is NULL                                      *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthPlayersElem(risk_t *game, int idx, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Retrieve the name of a player in the given game.                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * idx      the index of the player in question                               *
 * player   the address of a string capable of holding the players name       *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 idx >= number of players            *
 *          RISK_NIL_PLAYER if player is NULL                                 *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getPlayer(risk_t *game, int idx, char *player);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Arrange how many troops each player will start off the game with. *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * start    the starting troop count per player at the game start             *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_STARTING_TROOPS if start < 0                         *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setStartingTroopCount(risk_t *game, int start);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Gather the number of troops each player started the game with.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * start    the address of an int in which to store the initial troop count   *
 *          that each player started off with                                 *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_STARTING_TROOPS if start is NULL                         *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getStartingTroopCount(risk_t *game, int *start);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Setup the ratio of countries owned to bonus troops received at    *
 *          the beginning of a given players turn.                            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * bonus    how many countries constitue an extra troop on turn start         *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_TROOP_BONUS if bonus < 0                             *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setTroopTerritoryBonus(risk_t *game, int bonus);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To inquire about the ratio of countries which must be owned per   *
 *          extra troop earned at trun start.                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * bonus    how many countries constitue an extra troop on turn start         *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_TROOP_BONUS if bonus is NULL                             *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getTroopTerritoryBonus(risk_t *game, int *bonus);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the minimum number of troops for a player to recieve at *
 *          the beginning of their turn.                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * minimum  the lowest possible troop bonus per turn                          *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_TROOP_MINIMUM if minimum < 0                         *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setMinimumTroopHandout(risk_t *game, int minimum);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To gather the minimum number of troops which are handed out at the*
 *          start of a plyers turn.                                           *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * minimum  the address where to store the int value inquired about           *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_TROOP_MINIMUM if minimum is NULL                         *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getMinimumTroopHandout(risk_t *game, int *minimum);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To turn on/off random troops distribution at game start.          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * random   whether or not to turn on/off (1/0) random troop placement        * 
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_TROOP_RANDOM if random is not 1 or 0                 *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setRandomTroops(risk_t *game, int random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To inquire if troops will be or if they have already been randomly*
 *          distributed at game start.                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * random   an address of an int where to store if random troop placement is  *
 *          turned on/off (1/0)                                               *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_TROOP_RANDOM if random is NULL                           *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getRandomTroops(risk_t *game, int *random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the number of wilds to place/set in the deck.           *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * wilds    the number of wilds to set in the deck                            *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_DECK_WILDS if wilds < 0                              *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setDeckWilds(risk_t *game, int wilds);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To gather the number of wild cards contained in the game deck.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * wilds    the number of wilds contained in the deck                         *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_DECK_WILDS if wilds is NULL                              *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getDeckWilds(risk_t *game, int *wilds);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To setup the different types of cards contained in the deck.      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * n        the number of string names in the types array                     *
 * types    an array containing the names of all the different card types     *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_CARD_TYPES_COUNT if n < 0                            *
 *          RISK_NIL_CARD_TYPES if types is NULL                              *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL_TYPE if any reference into types is NULL                 *
 *          RISK_OUT_OF_MEMORY if allocation fails                            *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setDeckTypes(risk_t *game, int n, char *types[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Get the number of different types contained in the deck.          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * types    an address to an int where to store the number of card types      *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_TYPES if types is NULL                                   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthDeckTypes(risk_t *game, int *types);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Get the string length of a given card type contained in the deck. *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * idx      the index of the card type in question                            *
 * n        an address where to store the string length of the card type      *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 or idx >= number of game types      *
 *          RISK_NIL_LENGTH if n is NULL                                      *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthDeckTypesElem(risk_t *game, int idx, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To retrieve the string representation of a given card type        *
 *          contained in the deck.                                            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * idx      the index of the card type in question                            *
 * type     a pointer to a character array big enough to hold the type        *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 or idx >= number of game types      *
 *          RISK_NIL_TYPE if type is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getDeckTypesElem(risk_t *game, int idx, char *type);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To define the troop bonuses up to some fixed number of trades.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * n        the number of trades defined in rewards array                     *
 * rewards  an array of integer values defining trade in bonuses at the game  *
 *          level, not the player level                                       *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_REWARDS_COUNT if n < 0                               *
 *          RISK_NIL_ARR_REWARDS if rewards is NULL                           *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_OUT_OF_MEMORY if allocation fails                            *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setTradeRewards(risk_t *game, int n, int rewards[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To inquire for the number of card trade in's defined.             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * rewards  where to store the number of defined awards                       *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_REWARDS if rewards is NULL                               *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthTradeRewards(risk_t *game, int *rewards);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To gather the first n rewards defined in the game.                *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * n        the number of rewards to gather                                   *
 * rewards  an array to store the values wanted                               *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_LENGTH if n < 0 or n > number of trade rewards       *
 *          RISK_NIL_REWARDS if rewards is NULL                               *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getTradeRewards(risk_t *game, int n, int rewards[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To set the constant bonus increment in which to raise the bonus   *
 *          for card trades after the defined rewards are exhausted.          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * incr     the constant increment to increase the troop bonus per trade in   *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INCREMENT if increment < 0                           *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setTradeIncrReward(risk_t *game, int incr);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To gather the constant troop bonus increment used to define the   *
 *          value of card trade in's after all the defined values are         *
 *          exhausted.                                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * incr     where to store the constant increment                             *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_INCREMENT if increment is NULL                           *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getTradeIncrReward(risk_t *game, int *increment);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Set the continents which will make up the game map.               *
 *                                                                            *
 * ARGUMENT   DESCRIPTION                                                     *
 * --------   -----------                                                     *
 * game       the game instance to manipulate                                 *
 * n          the number of continents in the continents array                *
 * continents the continents to use for the games map                         *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_LENGTH if n < 0                                      *
 *          RISK_NIL_ARR_CONTINENTS if continents is NULL                     *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL_ARR_CONTINENT if any reference into continents is NULL   *
 *          RISK_OUT_OF_MEMORY if allocation fails                            *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setContinents(risk_t *game, int n, char *continents[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Retrieve the number of continents which make up the game map.     *
 *                                                                            *
 * ARGUMENT   DESCRIPTION                                                     *
 * --------   -----------                                                     *
 * game       the game instance to query                                      *
 * continents where to store the resulting value requested                    *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_CONTINENTS if continents is NULL                         *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthContinents(risk_t *game, int *continents);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To gather the string length of a given continent.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * idx      the index of the continent in question                            *
 * n        where to store the resulting length of the continent              *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 or idx >= number of continents      *
 *          RISK_NIL_LENGTH if n is NULL                                      *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthContinentsElem(risk_t *game, int idx, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Gather the continent indexed by idx.                              *
 *                                                                            *
 * ARGUMENT   DESCRIPTION                                                     *
 * --------   -----------                                                     *
 * game       the game instance to query                                      *
 * idx        the index of the continent in question                          *
 * continent  where to store the resulting continent on question              *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 or idx >= number of continents      *
 *          RISK_NIL_CONTINENT if contient is NULL                            *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinentElem(risk_t *game, int idx, char *continent);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the troop bonuses associated with controlling an entire *
 *          continent. The bonuses should correspond 1:1 with the array given *
 *          when setting continents in the game.                              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * n        the number of bonuses in the bonuses array                        *
 * bonuses  an array of the bonsues for controlling the corresponding         *
 *          continent                                                         *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_LENGTH if n < 0                                      *
 *          RISK_NIL_ARR_BONUSES if bonuses is NULL                           *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_OUT_OF_MEMORY if allocation fails                            *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setContinentBonuses(risk_t *game, int n, int bonuses[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To gather the number of defined bonuses for controlling countries.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * bonuses  where to store the resultign value requested                      *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_BONUSES if bonuses is NULL                               *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthContinentBonuses(risk_t *game, int *bonuses);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Gather the first n bonuses defined for controlling the            *
 *          corresponding continents.                                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * n        the number of bonuses to gather                                   *
 * bonuses  an array to store the resulting values requested                  *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_LENGTH if n < 0 or n >= number of continent bonuses  *
 *          RISK_NIL_ARR_BONUSES if bonuses is NULL                           *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinentBonuses(risk_t *game, int n, int bonuses[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Configure the countries used to make up the game map.             *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * game      the game instance to manipulate                                  *
 * n         the number of countries in the array                             *
 * countries the countries hich make up the game map                          *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_COUNTRIES_COUNT if n < 0                             *
 *          RISK_NIL_ARR_COUNTRIES if countries is NULL                       *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL_ARR_COUNTRY if any refence in countries is NULL          *
 *          RISK_OUT_OF_MEMORY if allocation fails                            *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setCountries(risk_t *game, int n, char *countries[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To gather the number of countries which make up the games map.    *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * game      the game instance to query                                       *
 * countries where to store the resulting value requested                     *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_COUNTRIES if countries is NULL                           *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthCountries(risk_t *game, int *countries);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Gather the string length of a given country.                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * idx      the index of the country to query                                 *
 * n        where to store the resulting string length of the country         *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 or idx >= number of countries       *
 *          RISK_NIL_LENGTH if n is NULL                                      *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthCountriesElem(risk_t *game, int idx, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Get the country indexed by idx.                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * idx      the index in the countries array                                  *
 * country  where to store the resulting country queried                      *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_INDEX if idx < 0 or idx >= number of countries       *
 *          RISK_NIL_COUNTRY if country is NULL                               *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getCountryElem(risk_t *game, int idx, char *country);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To set if all the game countries should be randomly distributed   *
 *          among the players at game start.                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * random   1 to randomly distribute countries, 0 to choose manually          *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_INVALID_RANDOM if random is not 1 or 0                       *
 *          RISK_GAMEPLAY_MUTATION if attempting to change game during play   *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setRandomCountries(risk_t *game, int random);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To determine whether or not countries were or are to be randomly  *
 *          distributed at the game start.                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * random   where to store the resulting value in question                    *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_RANDOM if random is NULL                                 *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getRandomCountries(risk_t *game, int *random);

// TODO: the following API's are still a work in progress

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * country
 * n
 * countries
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setBorders(risk_t *game, char *country, int n, char *countries[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * country
 * countries
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthBorders(risk_t *game, char *country, int *countries);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * country
 * idx
 * n
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_LENGTH if n is NULL                                      *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getLengthBordersElem(risk_t *game, char *country, int idx, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * country
 * idx
 * neighbor
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getBordersElem(risk_t *game, char *country, int idx, char *neighbor);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * continent
 * n
 * countries
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setContinentSet(risk_t *game, char *continent, int n, char *countries[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * continent
 * countries
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinentSetLength(risk_t *game, char *continent, int *countries);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * continent
 * idx
 * n
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_LENGTH if n is NULL                                      *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinentSetLengthElem(risk_t *game, char *continent, int idx, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * continent
 * idx
 * country
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getContinentSetElem(risk_t *game, char *continent, int idx, char *country);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * country
 * player
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t setOwner(risk_t *game, char *country, char *player);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * country
 * n
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL_LENGTH if n is NULL                                      *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getOwnerLength(risk_t *game, char *country, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * country
 * player
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getOwner(risk_t *game, char *country, char *player);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 * country
 * troops
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t reinforce(risk_t *game, char *country, int troops);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 * country
 * troops
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t getTroops(risk_t *game, char *country, int *troops);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to query                                        *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t valid(risk_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t start(risk_t *game);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * game     the game instance to manipulate                                   *
 *                                                                            *
 * RETURNS: RISK_NIL_GAME if game is NULL                                     *
 *          RISK_NIL if no error                                              *
 *                                                                            *
 ******************************************************************************/
errRISK_t end(risk_t *game);

#endif
