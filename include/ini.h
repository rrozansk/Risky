/******************************************************************************
 * FILE:    ini.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  6/27/17                                                           *
 * INFO:    A ini configuration file library. Allows the static reading from  *
 *          and dynamic output to a file, as well as dynamic CRUD operations. *
 *          The exposed library API's follow a uniform interface where only   *
 *          errors are returned from functions, if any, and all getters take  *
 *          ptr's to destinations in which to set the requested information.  * 
 *          Below is the grammar accepted and output by the library.          *
 *                                                                            *
 *                ::BNF GRAMMAR::                                             *
 *                                                                            *
 *         <ini>     ::= <section>*                                           *
 *         <section> ::= <header><setting>+                                   *
 *         <header>  ::= [<term>]                                             *
 *         <setting> ::= <term><dividor><value><space>+                       *
 *         <term>    ::= <elem>+                                              *
 *         <value>   ::= <int> | <float> | <bool> | <char> | <str> | <array>  *
 *         <array>   ::= <iArr> | <fArr> | <bArr> | <cArr> | <sArr>           *
 *         <iArr>    ::= {<int><ints>*}                                       *
 *         <fArr>    ::= {<float><floats>*}                                   *
 *         <bArr>    ::= {<bool><bools>*}                                     *
 *         <cArr>    ::= {<char><chars>*}                                     *
 *         <sArr>    ::= {<string><strings>*}                                 *
 *         <ints>    ::= ,<int>                                               *
 *         <floats>  ::= ,<float>                                             *
 *         <bools>   ::= ,<bool>                                              *
 *         <chars>   ::= ,<char>                                              *
 *         <strings> ::= ,<string>                                            *
 *         <int>     ::= <digit>+                                             *
 *         <float>   ::= <digit>*.<digit>+                                    *
 *         <bool>    ::= true | false                                         *
 *         <char>    ::= '<elem>'                                             *
 *         <string>  ::= "<elem>*"                                            *
 *         <dividor> ::= : | =                                                *
 *         <space>   ::= \t | \v | \f | \n | \r | ' '                         *
 *         <elem>    ::= <lower> | <upper> | <digit> | <special>              *
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

typedef enum errINI { /* All the possible errors produced by this library. */
  INI_UNKNOWN_TYPE, INI_OPEN_FAILURE, INI_CLOSE_FAILURE, INI_OUT_OF_MEMORY,
  INI_NOT_FOUND, INI_TYPE_MISMATCH, INI_INVALID_CONF, INI_INVALID_KEY,
  INI_INVALID_VAL, INI_INVALID_SECTION, INI_INVALID_LEN, INI_NIL_FNAME,
  INI_NIL_INI, INI_NIL_KEY, INI_NIL_VAL, INI_NIL_LEN, INI_NIL_SECTION, INI_NIL,
} errINI_t;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: Returns a string representation of any possible error returned by *
 *          the library.                                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * errDNA   the error to stringify                                            *
 *                                                                            *
 * RETURNS: A string representation of the error                              *
 *                                                                            *
 ******************************************************************************/
const char *strErrINI(errINI_t errINI);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempts to create an new ini configuration object. If any        *
 *          problem is encounted during initialization all memory will be     *
 *          freed, an error will be returned, and the value stored at ini     *
 *          will be NULL.                                                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      an address to a ptr in which to set the newly created object      *
 *                                                                            *
 * RETURNS: INI_NULL_INI if ini is NULL                                       *
 *          INI_OUT_OF_MEMORY if allocation of the ini configuration fails    *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t makeINI(ini_t **ini);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To free any ini object created through the ini constructor.       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ptr to the ini construct in which to free                     *
 *                                                                            *
 * RETURNS: INI_NIL                                                           *
 *                                                                            *
 ******************************************************************************/
errINI_t freeINI(ini_t *ini);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read in and create an ini configuration given a file name which   *
 *          corresponds to a specified ini configuration in a file adhereing  *
 *          to the library grammar.
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      a pointer which to set with the address of the conf read in       *
 * fname    the name of the file to read from                                 *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t readINI(ini_t **ini, char *fname); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Output the ini configuration to a file with the specified name.   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration to output                                   *
 * fname    the name of the file to [over]write                               *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_NIL_FNAME if fname is NULL                                    *
 *          INI_OPEN_FAILURE if creating/opening the file failed              *
 *          INI_CLOSE_FAILURE if closing the file failed                      *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t writeINI(ini_t *ini, char *fname);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section under which the key is located                        *
 * key      the key of the setting to remove                                  *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setIntINI(ini_t *ini, char *section, char *key, int val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getIntINI(ini_t *ini, char *section, char *key, int *val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setFloatINI(ini_t *ini, char *section, char *key, double val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getFloatINI(ini_t *ini, char *section, char *key, double *val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setBoolINI(ini_t *ini, char *section, char *key, int val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getBoolINI(ini_t *ini, char *section, char *key, int *val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setCharINI(ini_t *ini, char *section, char *key, char val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getCharINI(ini_t *ini, char *section, char *key, char *val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setStrINI(ini_t *ini, char *section, char *key, char *val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getStrINI(ini_t *ini, char *section, char *key, char **val); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setIntArrINI(ini_t *ini, char *section, char *key, int *val, int n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getIntArrINI(ini_t *ini, char *section, char *key, int **val, int *n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setFloatArrINI(ini_t *ini, char *section, char *key, double *val, int n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getFloatArrINI(ini_t *ini, char *section, char *key, double **val, int *n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setBoolArrINI(ini_t *ini, char *section, char *key, int *val, int n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getBoolArrINI(ini_t *ini, char *section, char *key, int **val, int *n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setCharArrINI(ini_t *ini, char *section, char *key, char *val, int n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
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
errINI_t getCharArrINI(ini_t *ini, char *section, char *key, char **val, int *n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create/Update a new key value setting under the specified section.*
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section to make a new setting under                           *
 * key      the key of the new setting                                        *
 * val      the val of the new setting                                        *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t setStrArrINI(ini_t *ini, char *section, char *key, char **val, int n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: Read a value from the conf given by section and key.              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to use                               *
 * section  the section under which the key is located                        *
 * key      the key of the setting to get                                     *
 * val      a pointer which to set with the val of the setting found, if any  *
 * n        the size of the array of the var val                              *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errINI_t getStrArrINI(ini_t *ini, char *section, char *key, char ***val, int *n); // TODO

/******************************************************************************
 *                                                                            *
 * PURPOSE: To delete the key/value association located under the specified   *
 *          section if it exists. Requests to remove non-present keys will be * 
 *          ignored. If the deleted association was the last in the given     *
 *          section then the section will also be removed.                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section under which the key is located                        *
 * key      the key of the setting to remove                                  *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_NIL_SECTION if section is NULL                                *
 *          INI_NIL_KEY if key is NULL                                        *
 *          INI_INVALID_SECTION if section does not adhere to library grammar *
 *          INI_INVALID_KEY if key does not adhere to library grammar         *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t deleteINI(ini_t *ini, char *section, char *key);

#endif
