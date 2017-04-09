/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  4/7/17
 Info:    A ini conf file interface. Allows static reading from a file as well as
          dynamic creation, mutation, and output to a file. Below is the grammar
          accepted, and output by the library.

                 ::BNF GRAMMAR::

          <ini>     ::= <section>+
          <section> ::= <header><setting>+
          <header>  ::= [<term>]
          <setting> ::= <term><dividor><term><space>+
          <term>    ::= <char>+
          <char>    ::= <lower> | <upper> | <digit> | <special>
          <dividor> ::= : | = 
          <space>   ::= \t | \v | \f | \n | \r | ' '
          <lower>   ::= a | b | c | d | e | f | g | h | i | j | k | l | m |
                        n | o | p | q | r | s | t | u | v | w | x | y | z
          <upper>   ::= A | B | C | D | E | F | G | H | I | J | K | L | M |
                        N | O | P | Q | R | S | T | U | V | W | X | Y | Z
          <digit>   ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
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
// Read in and create an ini conf given a file name. Return NULL on success and
// a descriptive error message on failure.
char *readINI(ini_t **ini, char *fname);

// Output the ini conf to a file with the specified name. 0 on success, 1 on fail.
int writeINI(ini_t *ini, char *fname);

// Attempt to create an new ini conf. Return NULL upon failure.
ini_t *makeINI();

// Free the ini conf.
void freeINI(ini_t *ini);

// Retrieve a value from the conf given by section and key.
// Return NULL if ini, section, or key is NULL, or if not found.
char *getINI(ini_t *ini, char *section, char *key);

// Create a new setting in the conf under the specified section with the given 
// key and value. Return 0 if successful, 1 on failure. Failure occurs if ini,
// section, key, or val is NULL or cannot alloc space. Failure can also occur if
// section, key, or val do not conform to the grammar given above.
int setINI(ini_t *ini, char *section, char *key, char *val);

#endif
