/******************************************************************************
 * FILE:    ini.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  5/13/17                                                           *
 * INFO:    A ini configuration file library. Allows the static reading from  *
 *          and output to a file, as well as dynamic CRUD operations. The     *
 *          library API is designed to return errors, which should be checked *
 *          and handled immediately. In the case of success INI_NIL error is  *
 *          returned. Below is the grammar accepted and output by the library.*
 *                                                                            *
 *                ::BNF GRAMMAR::                                             *
 *       FIXME                                                                     *
 *         <ini>     ::= <section>*                                           *
 *         <section> ::= <header><setting>+                                   *
 *         <header>  ::= [<term>]                                             *
 *         <setting> ::= <term><dividor><value><space>+                       *
 *         <term>    ::= <char>+                                              *
 *         <value>   ::= <int> | <float> | <char> | <bool> | <array>          *
 *         <array>   ::= <iArr> | <sArr> | <cArr>                             *
 *         <iArr>    ::= {<int><ints>*}                                       *
 *         <sArr>    ::= {<string><strings>*}                                 *
 *         <cArr>    ::= {<char><chars>*}                                     *
 *         <int>     ::= <int>+                                               *
 *         <float>   ::= <int>*.<int>+                                        *
 *         <ints>    ::= ,<int>                                               *
 *         <string>  ::= "<char>*"                                            *
 *         <strings> ::= ,<string>                                            *
 *         <chars>   ::= ,<char>                                              *
 *         <char>    ::= '<lower>' | '<upper>' | '<digit>' | '<special>'      *
 *         <bool>    ::= true | false                                         *
 *         <dividor> ::= : | =                                                *
 *         <space>   ::= \t | \v | \f | \n | \r | ' '                         *
 *         <lower>   ::= a | b | c | d | e | f | g | h | i | j | k | l | m |  *
 *                       n | o | p | q | r | s | t | u | v | w | x | y | z    *
 *         <upper>   ::= A | B | C | D | E | F | G | H | I | J | K | L | M |  *
 *                       N | O | P | Q | R | S | T | U | V | W | X | Y | Z    *
 *         <digit>   ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9                *
 *         <special> ::= ! | " | $ | % | & | ' | ( | ) | * | + | , | - | . |  *
 *                       / | < | > | ? | @ | [ | \ | ] | ^ | _ | ` | ~ | | |  *
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
  INI_INVALID_VAL, INI_OUT_OF_MEMORY, INI_NIL_KEY, INI_NIL_VAL, INI_NIL,
  INI_NIL_SECTION, INI_NIL_INI, INI_NIL_FNAME, INI_INVALID_CONF
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
 * PURPOSE: Create an new ini conf.                                           *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      a pointer which to set with the address of the conf read in       *
 *                                                                            *
 * RETURNS: INI_NULL_INI, INI_OUT_OF_MEMORY, or INI_NIL if no error.          *
 *                                                                            *
 ******************************************************************************/
errINI_t makeINI(ini_t **ini);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Free the ini conf.                                                *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to free                                              *
 *                                                                            *
 * RETURNS: INI_NULL_INI, or INI_NIL if no error.                             *
 *                                                                            *
 ******************************************************************************/
errINI_t freeINI(ini_t *ini);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read in and create an ini conf given a file name.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      a pointer which to set with the address of the conf read in       *
 * fname    the name of the file to read from                                 *
 *                                                                            *
 * RETURNS: INI_NULL_INI, INI_NULL_FNAME, INI_OPEN_FAILURE, INI_OUT_OF_MEMORY,*
 *          INI_CLOSE_FAILURE, INI_INVALID_CONF, INI_INVALID_SECTION,         *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *          INI_INVALID_KEY, INI_INVALID_VAL, INI_NULL_SECTION, INI_NULL_KEY, *
 *          INI_NULL_VAL, INI_NULL_VAL, or INI_NIL if no error.               *
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
 * fname    the name of the file to write out the conf to                     *
 *                                                                            *
 * RETURNS: INI_NULL_INI, INI_NULL_FNAME, INI_OPEN_FAILURE, INI_CLOSE_FAILURE,*
 *          or INI_NIL if no error.                                           *
 *                                                                            *
 ******************************************************************************/
errINI_t writeINI(ini_t *ini, char *fname);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: INI_NULL_INI, INI_NULL_SECTION, INI_NULL_KEY, INI_NULL_VAL,       * 
 *          INI_INVALID_SECTION, INI_INVALID_KEY, INI_INVALID_VAL,            *
 *          INI_NULL_VAL, or INI_NIL if no error.                             *
 *                                                                            *
 ******************************************************************************/
errINI_t setIntINI(ini_t *ini, char *section, char *key, int val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * sec      the section to look under                                         *
 * key      the key of the setting to get                                     *
 * v        a pointer which to set with the val of the setting found, if any  *
 *                                                                            *
 * RETURNS: INI_NULL_INI, INI_NULL_SECTION, INI_NULL_KEY, INI_NULL_VAL,       *
 *          INI_INVALID_SECTION, INI_INVALID_KEY, or INI_NIL if no error.     *
 *                                                                            *
 ******************************************************************************/
errINI_t getIntINI(ini_t *ini, char *section, char *key, int *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setFloatINI(ini_t *ini, char *section, char *key, double val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getFloatINI(ini_t *ini, char *section, char *key, double *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setBoolINI(ini_t *ini, char *section, char *key, int val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getBoolINI(ini_t *ini, char *section, char *key, int *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setCharINI(ini_t *ini, char *section, char *key, char val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getCharINI(ini_t *ini, char *section, char *key, char *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setStrINI(ini_t *ini, char *section, char *key, char *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getStrINI(ini_t *ini, char *section, char *key, char **val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setIntArrINI(ini_t *ini, char *section, char *key, int *val, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getIntArrINI(ini_t *ini, char *section, char *key, int **val, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setFloatArrINI(ini_t *ini, char *section, char *key, double *val, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getFloatArrINI(ini_t *ini, char *section, char *key, double **val, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setBoolArrINI(ini_t *ini, char *section, char *key, int *val, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getBoolArrINI(ini_t *ini, char *section, char *key, int **val, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setCharArrINI(ini_t *ini, char *section, char *key, char *val, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getCharArrINI(ini_t *ini, char *section, char *key, char **val, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setStrArrINI(ini_t *ini, char *section, char *key, char **val, int n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getStrArrINI(ini_t *ini, char *section, char *key, char ***val, int *n);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Delete the key value pair under the specified section.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini conf to use                                               *
 * section  the section to look under                                         *
 * key      the key of the setting to delete                                  *
 *                                                                            *
 * RETURNS: INI_NULL_INI, INI_NULL_SECTION, INI_NULL_KEY, INI_INVALID_SECTION,*
 *          INI_INVALID_KEY, or INI_NIL if no error.                          *
 *                                                                            *
 ******************************************************************************/
errINI_t deleteINI(ini_t *ini, char *section, char *key);

#endif
