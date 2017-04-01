/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  4/1/17
*/

#ifndef INI_CONF_DEFS
#define INI_CONF_DEFS

/*******************************************************************************

    T Y P E S

*******************************************************************************/
typedef struct ini ini_t; // INI conf files

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/
ini_t *parseINI(char *fname);
void  writeINI(ini_t *conf, char *fname);
char  *getINI(ini_t *conf, char *section, char *key);
void  setINI(ini_t *conf, char *section, char *key, char *val);
void  freeINI(ini_t *ini);

#endif
