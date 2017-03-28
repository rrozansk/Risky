/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  3/27/17
*/

#ifndef RISKY_CONF_DEFS
#define RISKY_CONF_DEFS

/*******************************************************************************

    S T R U C T S

*******************************************************************************/
typedef struct conf {      // conf file headers
  char hp;                 // [Players]
  char cp;                 // [Players]
  char randRegion;         // [Random]
  char randArmies;         // [Random]
  char chromosomes[8][10]; // [Chromosomes] 
  char sets;               // tracks # sets traded in
  char err[160];           // error msg if parse failure
} conf_t;

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/
int parseConf(conf_t *conf, char *fname);
int writeConf(conf_t *conf, char *fname);

#endif
