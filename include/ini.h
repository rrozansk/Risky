/******************************************************************************
 * FILE:    ini.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  4/24/17                                                           *
 * INFO:    A ini configuration file library. Allows the static reading from  *
 *          and output to a file, as well as dynamic CRUD operations. The     *
 *          library API is designed to return errors, which should be checked *
 *          and handled immediately. In the case of success INI_NIL error is  *
 *          returned. Below is the grammar accepted and output by the library.*
 *                                                                            *
 *                ::BNF GRAMMAR::                                             *
 *                                                                            *
 *         <ini>     ::= <section>*                                           *
 *         <section> ::= <header><setting>+                                   *
 *         <header>  ::= [<term>]                                             *
 *         <setting> ::= <term><dividor><term><space>+                        *
 *         <term>    ::= <char>+                                              *
 *         <char>    ::= <lower> | <upper> | <digit> | <special>              *
 *         <dividor> ::= : | =                                                *
 *         <space>   ::= \t | \v | \f | \n | \r | ' '                         *
 *         <lower>   ::= a | b | c | d | e | f | g | h | i | j | k | l | m |  *
 *                       n | o | p | q | r | s | t | u | v | w | x | y | z    *
 *         <upper>   ::= A | B | C | D | E | F | G | H | I | J | K | L | M |  *
 *                       N | O | P | Q | R | S | T | U | V | W | X | Y | Z    *
 *         <digit>   ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9                *
 *         <special> ::= ! | " | $ | % | & | ' | ( | ) | * | + | , | - | . |  *
 *                       / | < | > | ? | @ | [ | \ | ] | ^ | _ | ` | { | | |  *
 *                       } | ~                                                *
 *         <comment> ::= #<any> | ;<any>                                      *
 *         <any>     ::= any characters, except \n, up to \n                  *
 *                                                                            *
 ******************************************************************************/

#ifndef INI_CONF_DEFS
#define INI_CONF_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct ini ini_t; /* INI configuration files. */

typedef enum errINI { /* All the possible errors returned from the library. */
  INI_CLOSE_FAILURE, INI_OPEN_FAILURE, INI_INVALID_KEY, INI_INVALID_SECTION,
  INI_INVALID_VAL, INI_OUT_OF_MEMORY, INI_NULL_KEY, INI_NULL_VAL, INI_NIL,
  INI_NULL_SECTION, INI_NULL_INI, INI_NULL_FNAME, INI_INVALID_CONF
} errINI_t;

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
 * errINI   the error to strigify                                             *
 *                                                                            *
 * RETURNS: string rep                                                        *
 *                                                                            *
 ******************************************************************************/
const char *strErrINI(errINI_t errINI);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read in and create an ini conf given a file name.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the error to strigify                                             *
 * fname    ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errINI_t readINI(ini_t **ini, char *fname);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Output the ini conf to a file with the specified name.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the error to strigify                                             *
 * fname    ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errINI_t writeINI(ini_t *ini, char *fname);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create an new ini conf.                                           *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errINI_t makeINI(ini_t **ini);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Free the ini conf.                                                *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errINI_t freeINI(ini_t *ini);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      ...                                                               *
 * section  ...                                                               *
 * key      ...                                                               *
 * val      ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errINI_t getINI(ini_t *ini, char *section, char *key, char **val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      ...                                                               *
 * section  ...                                                               *
 * key      ...                                                               *
 * val      ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errINI_t setINI(ini_t *ini, char *section, char *key, char *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Delete the key value pair under the specified section.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      ...                                                               *
 * section  ...                                                               *
 * key      ...                                                               *
 *                                                                            *
 * RETURNS: error code: -,-,... or RISKY_NIL if no error                      *
 *                                                                            *
 ******************************************************************************/
errINI_t deleteINI(ini_t *ini, char *section, char *key);

#endif
