/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  4/4/17
 Info:    A ini conf file interface. Allows static reading a from file as well as
          dynamic creation, mutation, and output to a file. Below is the grammar
          accepted/output by read/write.

                 ::BNF GRAMMAR::

          <ini>     ::= <blank>*<section>+<blank>*
          <section> ::= <header><setting>+<whitespace>
          <header>  ::= '['<term>']'<blank>*<newline>
          <setting> ::= <term><blank>*<dividor><blank>*<term><blank>*<newline>
          <blank>   ::= \t | \r | \space | <newline>
          <newline> ::= \n
          <dividor> ::= : | = 
          <term>    ::= [a-z][A-Z][0-9][{/?<>.}`]
          <comment> ::= # | ; <any characters up to \n> 
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
// read in and create an ini conf given a file name. return NULL on success and
// a descriptive error message on failure
const char *readINI(ini_t **ini, char *fname);

// output the ini conf to a file with the specified name. 0 on success, 1 on fail
int writeINI(ini_t *ini, char *fname);

// attempt to create an new ini conf. return NULL upon failure.
ini_t *makeINI();

// free the ini conf
void freeINI(ini_t *ini);

// retrieve a value from the conf given by section and key.
// return NULL if any of: ini, section, or key are NULL, or if not found
char *getINI(ini_t *ini, char *section, char *key);

// create a new setting in the conf under the specified section with the given 
// key and value. return 0 if successful, 1 on failure.
// failure occurs if ini, section, key, or val is NULL or cannot alloc space
int setINI(ini_t *ini, char *section, char *key, char *val);

#endif
