/******************************************************************************
 * FILE:    ini.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  7/8/17                                                            *
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

typedef struct setting setting_t; /* INI configuration settings. */

typedef enum typeINI { /* INI setting value types */
  INT, FLOAT, BOOL, CHAR, STRING, INT_ARRAY, FLOAT_ARRAY, BOOL_ARRAY,
  CHAR_ARRAY, STRING_ARRAY, UNINITIALIZED
} typeINI_t;

typedef unsigned char option_t; /* INI configuration options */

typedef enum errINI { /* All the possible errors produced by this library. */
  INI_OPEN_FAILURE, INI_CLOSE_FAILURE, INI_OUT_OF_MEMORY, INI_TYPE_MISMATCH,
  INI_DUPLICATE_SETTING, INI_VALUE_UNINITIALIZED, INI_INVALID_CONF,
  INI_INVALID_KEY, INI_INVALID_VALUE, INI_INVALID_SECTION, INI_INVALID_INDEX,
  INI_INVALID_OPTIONS, INI_NIL_FNAME, INI_NIL_INI, INI_NIL_KEY, INI_NIL_VALUE,
  INI_NIL_SECTION, INI_NIL_OPTIONS, INI_NIL_SETTING, INI_NIL_TYPE,
  INI_NIL_LENGTH, INI_NIL
} errINI_t;

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/

// to output setting with and ':' if set, else '=' between the key and value
#define SETTING_SEPERATOR 0b00000001

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
 * RETURNS: INI_NIL_INI
 *          INI_NIL_FNAME
 *          INI_OPEN_FAILURE
 *          INI_OUT_OF_MEMORY
 *          INI_INVALID_SECTION
 *          INI_INVALID_KEY
 *          INI_INVALID_CONF
 *          INI_NIL if no error
 TODO: correct/fill in the rest when implemented
 *                                                                            *
 ******************************************************************************/
errINI_t readINI(ini_t **ini, char *filename);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Output the ini configuration to a file with the specified name    *
 *          using the set configuration options.                              *
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
errINI_t writeINI(ini_t *ini, char *filename);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration to query                                    *
 * options  a ptr to an allocated options type to store the gotten value      *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_NIL_OPTIONS if options is NULL                                *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t getConfigurationINI(ini_t *ini, option_t *options);

/******************************************************************************
 *                                                                            *
 * PURPOSE:  TODO
 *           | (bit or) wanted settings
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration to query                                    *
 * options  the settings for the configuration                                *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_INVALID_OPTIONS if options has conflicting bits set           *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t setConfigurationINI(ini_t *ini, option_t options);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO insert into ini, possibly creating a new section
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section under which tp place key under                        *
 * key      the key of the setting to create                                  *
 * setting  a ptr to an allocated ptr to store a ptr of the created setting   *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_NIL_SECTION if section is NULL                                *
 *          INI_NIL_KEY if key is NULL                                        *
 *          INI_NIL_SETTING if setting is NULL                                *
 *          INI_INVALID_SECTION if section does not adhere to library grammar *
 *          INI_INVALID_KEY if key does not adhere to library grammar         *
 *          INI_DUPLICATE_SETTING if key already appears under section        *
 *          INI_OUT_OF_MEMORY if allocation of the new setting fails          *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t createSetting(ini_t *ini, char *section, char *key, setting_t **setting);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to query                             *
 * section  the section under which the key is located                        *
 * key      the key of the setting to get                                     *
 * setting  a ptr to an allocated ptr to store a ptr of the gotten setting    *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_NIL_SECTION if section is NULL                                *
 *          INI_NIL_KEY if key is NULL                                        *
 *          INI_NIL_SETTING if setting is NULL                                *
 *          INI_INVALID_SECTION if section does not adhere to library grammar *
 *          INI_INVALID_KEY if key does not adhere to library grammar         *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t lookupSetting(ini_t *ini, char *section, char *key, setting_t **setting);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To delete the key/value association located under the specified   *
 *          section if it exists. Requests to remove non-present keys will be * 
 *          ignored. If the deleted association was the last in the given     *
 *          section then the section will also be removed... automatically    *
 *          takes 
 *          TODO care to delete unused sections...                            *
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
errINI_t deleteSetting(ini_t *ini, char *section, char *key);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * typeINI  a ptr to an allocated typeINI_t to store the gottne type at       *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_TYPE if typeINI is NULL                                   *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingType(setting_t *setting, typeINI_t *typeINI);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO immutable key
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * length   a ptr to an allocated into to store the length gotten at          *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_LENGTH if length is NULL                                  *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingKeyLength(setting_t *setting, int *length);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO immutable key
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * key      a ptr to an allocated char array to store the key at              *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_KEY if key is NULL                                        *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingKey(setting_t *setting, char *key); 

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO 0 for atoms, # for strings and arrays
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * length   a ptr to an allocated into to store the length gotten at          *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_LENGTH if length is NULL                                  *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingLength(setting_t *setting, int *length); 

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the list to get, from 0 to len(setting)-1*
 * length   a ptr to an allocated into to store the length gotten at          *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_LENGTH if length is NULL                                  *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_TYPE_MISMATCH if setting is a non array type                  *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingElemLength(setting_t *setting, int index, int *length);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated int to store the gotten value               *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetInt(setting_t *setting, int *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated float to store the gotten value             *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetFloat(setting_t *setting, float *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated int to store the gotten value               *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetBool(setting_t *setting, int *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated char to store the gotten value              *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetChar(setting_t *setting, char *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated char array to store the gotten value        *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetString(setting_t *setting, char *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the list to get, from 0 to len(setting)) *
 * elem     a ptr to an allocated int to store the gotten value               *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetIntElem(setting_t *setting, int index, int *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the list to get, from 0 to len(setting)) *
 * elem     a ptr to an allocated float to store the gotten value             *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetFloatElem(setting_t *setting, int index, float *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the list to get, from 0 to len(setting)) *
 * elem     a ptr to an allocated int to store the gotten value               *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetBoolElem(setting_t *setting, int index, int *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE:  TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the list to get, from 0 to len(setting)) *
 * elem     a ptr to an allocated char to store the gotten value              *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetCharElem(setting_t *setting, int index, char *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE:  TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the list to get, from 0 to len(setting)) *
 * elem     a ptr to an allocated char array to store the gotten value        *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetStringElem(setting_t *setting, int index, char *elem);
 
/******************************************************************************
 *                                                                            *
 * PURPOSE:  enables programatic creation of conf files TODO                  *
 *           will create/overwrite type/value appropriately                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * value    the int to store as the value of this setting                     *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetInt(setting_t *setting, int value); 

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * value    the float to store as the value of this setting                   *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetFloat(setting_t *setting, float value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * value    the bool to store as the value of this setting                    *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetBool(setting_t *setting, int value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * value    the char to store as the value of this setting                    *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetChar(setting_t *setting, char value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * value    the string to store as the value of this setting                  *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetString(setting_t *setting, char *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the list to set, from 0 to len(setting)) *
 * elem     the int to store as the elem of this setting                      *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetIntElem(setting_t *setting, int index, int elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO   // elem [0-len]
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the list to set, from 0 to len(setting)) *
 * elem     the float to store as the elem of this setting                    *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetFloatElem(setting_t *setting, int index, float elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the list to set, from 0 to len(setting)) *
 * elem     the bool to store as the elem of this setting                     *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetBoolElem(setting_t *setting, int index, int elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the list to set, from 0 to len(setting)) *
 * elem     the char to store as the elem of this setting                     *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetCharElem(setting_t *setting, int index, char elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: TODO
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the list to set, from 0 to len(setting)) *
 * elem     the string to store as the elem of this setting                   *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetStringElem(setting_t *setting, int index, char *elem);

#endif
