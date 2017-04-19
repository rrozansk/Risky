/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  4/16/17
 Info:    A ini configuration file library. Allows the static reading from and
          output to a file, as well as dynamic CRUD operations. The library API
          is designed to return errors, which should be checked and handled
          immediately. In the case of success INI_NIL error is returned. Below
          is the grammar accepted and output by the library.

                 ::BNF GRAMMAR::

          <ini>     ::= <section>*
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
// INI conf files.
typedef struct ini ini_t;

// All the possible errors returned from the library.
typedef enum errINI {
  INI_CLOSE_FAILURE, INI_OPEN_FAILURE, INI_INVALID_KEY, INI_INVALID_SECTION,
  INI_INVALID_VAL, INI_OUT_OF_MEMORY, INI_NULL_KEY, INI_NULL_VAL, INI_NIL,
  INI_NULL_SECTION, INI_FAILURE, INI_NULL_INI, INI_NULL_FILE_NAME,
  INI_INVALID_CONF
} errINI_t;

/*******************************************************************************

    F U N C T I O N   P R O T O T Y P E S

*******************************************************************************/
// Return a string representation of any possible error returned by the library.
const char *strErrINI(errINI_t errINI);

// Read in and create an ini conf given a file name.
errINI_t readINI(ini_t **ini, char *fname);

// Output the ini conf to a file with the specified name.
errINI_t writeINI(ini_t *ini, char *fname);

// Create an new ini conf.
errINI_t makeINI(ini_t **ini);

// Free the ini conf.
errINI_t freeINI(ini_t *ini);

// Read a value from the conf given by section and key.
errINI_t getINI(ini_t *ini, char *section, char *key, char **val);

// Create/Update a new key value setting under the specified section.
errINI_t setINI(ini_t *ini, char *section, char *key, char *val);

// Delete the key value pair under the specified section.
errINI_t deleteINI(ini_t *ini, char *section, char *key);

#endif
