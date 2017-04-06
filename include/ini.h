/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  4/6/17
 Info:    A ini conf file interface. Allows static reading a from file as well as
          dynamic creation, mutation, and output to a file. Below is the grammar
          accepted and output by the library.

                 ::BNF GRAMMAR::

          <ini>     ::= <section>+
          <section> ::= <header><setting>+
          <header>  ::= [<term>]
          <setting> ::= <term><dividor><term><space>+
          <term>    ::= <char>+
          <char>    ::= <lower> | <upper> | <number> | <special>
          <dividor> ::= : | = 
          <space>   ::= \t | \v | \f | \n | \r | ' '
          <lower>   ::= a | b | c | d | e | f | g | h | i | j | k | l | m |
                        n | o | p | q | r | s | t | u | v | w | x | y | z
          <upper>   ::= A | B | C | D | E | F | G | H | I | J | K | L | M |
                        N | O | P | Q | R | S | T | U | V | W | X | Y | Z
          <number>  ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
          <special> ::= ! | " | $ | % | & | ' | ( | ) | * | + | , | - | . | / |
                        < | > | ? | @ | [ | \ | ] | ^ | _ | ` | { | | | } | ~
          <comment> ::= #<any> | ;<any>
          <any>     ::= any characters, except \n, up to \n
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
// a descriptive error message on failure.
const char *readINI(ini_t **ini, char *fname);

// output the ini conf to a file with the specified name. 0 on success, 1 on fail.
int writeINI(ini_t *ini, char *fname);

// attempt to create an new ini conf. return NULL upon failure.
ini_t *makeINI();

// free the ini conf.
void freeINI(ini_t *ini);

// retrieve a value from the conf given by section and key.
// return NULL if any of: ini, section, or key are NULL, or if not found.
char *getINI(ini_t *ini, char *section, char *key);

// create a new setting in the conf under the specified section with the given 
// key and value. return 0 if successful, 1 on failure. failure occurs if ini,
// section, key, or val is NULL or cannot alloc space. failure can also occur if
// section, key, or val do not conform to the grammar given above.
int setINI(ini_t *ini, char *section, char *key, char *val);

#endif
