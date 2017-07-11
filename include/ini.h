/******************************************************************************
 * FILE:    ini.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  7/10/17                                                           *
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

// to output settings with an ':' if set, else '=' between the key value pairs
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
 * PURPOSE: Output the ini configuration to a file with the specified name,   *
 *          using the specified options for output. The output file conforms  *
 *          to the library grammar, and will produce an equal but newly       *
 *          allocated configuration if called with read. Note that write will *
 *          create the file if it does not exist, and will overwrite it if it *
 *          already exists.                                                   *
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
 * PURPOSE: Get the current configuration options for the library, which      *
 *          controls the look of the writer.                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration to query                                    *
 * options  a ptr to an allocated object to put the current write formatting  *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_NIL_OPTIONS if options is NULL                                *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t getConfigurationINI(ini_t *ini, option_t *options);

/******************************************************************************
 *                                                                            *
 * PURPOSE:  To control how write outputs the configuration to a file. Read   *
 *           all the defined macros/constants options above and bit or ( | )  *
 *           all the wanted settings together as the value of options.        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration to query                                    *
 * options  the settings to use for the configuration object                  *
 *                                                                            *
 * RETURNS: INI_NIL_INI if ini is NULL                                        *
 *          INI_INVALID_OPTIONS if options has conflicting bits set           *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t setConfigurationINI(ini_t *ini, option_t options);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To insert a new setting into the configuration object. The new    *
 *          setting will have an UNINITIALIZED type until it is set through   *
 *          any setter below. Once set with a type it cannot be changed,      *
 *          unless the setting is deleted and recreated and set with the      *
 *          newly wanted type. Section are also created automatically if they *
 *          do not already exist.                                             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to manipulate                        *
 * section  the section under which to place the setting                      *
 * key      the key of the setting to create                                  *
 * setting  the address of an allocated ptr to store the setting created      *
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
 * PURPOSE: To search the configuration object for a specific setting. If     *
 *          found the value at setting will hold the result. If the queried   *
 *          setting does not exist in the given configuration then the value  *
 *          stored at setting will be NULL.                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ini      the ini configuration object to query                             *
 * section  the section under which the key is located                        *
 * key      the key of the setting to get                                     *
 * setting  the address of an allocated ptr to store the setting if found     *
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
 * PURPOSE: To delete the setting located under the specified section and key *
 *          if it exists. Requests to remove non-existant keys will be        * 
 *          ignored. Section are also removed automatically if they no longer *
 *          hold any settings.                                                *
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
 * PURPOSE: To query a setting for its type.                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * typeINI  a ptr to an allocated typeINI_t to store the settings type at     *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_TYPE if typeINI is NULL                                   *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingType(setting_t *setting, typeINI_t *typeINI);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To query a setting for the length of its key.                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * length   a ptr to an allocated int to store the length of the key          *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_LENGTH if length is NULL                                  *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingKeyLength(setting_t *setting, int *length);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To retrieve the key of a given setting. The space required to     *
 *          store the key must be allocated by the user and passed in. This   *
 *          is where the usefulness of settingKeyLength() comes in. It also   *
 *          allows for allocation to be done either on the heap or the stack. *
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
 * PURPOSE: To inquire about the length of a given setting. Setting lengths   *
 *          are defined to be 0 for atoms (INT, FLOAT, BOOL, and CHAR), the   *
 *          string length for strings (STRING), and the number of items for   *
 *          array types (INT_ARRAY, FLOAT_ARRAY, BOOL_ARRAY, CHAR_ARRAY,      *
 *          STRING_ARRAY).                                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * length   a ptr to an allocated int to store the resulting length at        *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_NIL_LENGTH if length is NULL                                  *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingLength(setting_t *setting, int *length); 

/******************************************************************************
 *                                                                            *
 * PURPOSE: To inquire about the length of a given element in setting with an *
 *          array type (INT_ARRAY, FLOAT_ARRAY, BOOL_ARRAY, CHAR_ARRAY,       *
 *          STRING_ARRAY). An elements length is defined to be 0 for atoms    *
 *          (INT, FLOAT, BOOL, and CHAR), and the string length for strings   *
 *          (STRING).                                                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the array to query [0 - len(setting)-1]  *
 * length   a ptr to an allocated int to store the length at                  *
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
 * PURPOSE: To copy the integer value stored in the setting to the specified  *
 *          destination.                                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated int to store the relevant value             *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_VALUE_UNINITIALIZED if value has not been set yet             *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetInt(setting_t *setting, int *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the floating point value stored in the setting to the     *
 *          specified destination.                                            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated float to store the relevant value           *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_VALUE_UNINITIALIZED if value has not been set yet             *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetFloat(setting_t *setting, float *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the boolean value (encoded as an integer 0:false, 1:true) *
 *          stored in the setting to the specified destination.               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated int to store the relevant value             *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_VALUE_UNINITIALIZED if value has not been set yet             *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetBool(setting_t *setting, int *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the character value stored in the setting to the          *
 *          specified destination.                                            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated char to store the relevant value            *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_VALUE_UNINITIALIZED if value has not been set yet             *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetChar(setting_t *setting, char *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the string value stored in the setting to the specified   *
 *          destination.                                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * value    a ptr to an allocated char array to store the relevant value,     *
 *          which should be large enough to hold the string stored            *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_VALUE_UNINITIALIZED if value has not been set yet             *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_NIL_VALUE if value is NULL                                    *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetString(setting_t *setting, char *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the integer value stored at the specified index of the    *
 *          array in the setting to the specified destination.                *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the array to copy [0 - len(setting)-1]   *
 * elem     a ptr to an allocated int to store the relevant value             *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetIntElem(setting_t *setting, int index, int *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the floating point value stored at the specified index of *
 *          the array in the setting to the specified destination.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the array to copy [0 - len(setting)-1]   *
 * elem     a ptr to an allocated float to store the relevant value           *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetFloatElem(setting_t *setting, int index, float *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the boolean value (encoded as an integer 0:false, 1:true) *
 *          stored at the specified index of the array in the setting to the  *
 *          specified destination.                                            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the array to copy [0 - len(setting)-1]   *
 * elem     a ptr to an allocated int to store the relevant value             *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetBoolElem(setting_t *setting, int index, int *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the character value stored at the specified index of the  *
 *          array in the setting to the specified destination.                *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the array to copy [0 - len(setting)-1]   *
 * elem     a ptr to an allocated char to store the relevant value            *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetCharElem(setting_t *setting, int index, char *elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To copy the string value stored at the specified index of the     *
 *          array in the setting to the specified destination.                *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to query                                              *
 * index    the index of the item in the array to copy [0 - len(setting)-1]   *
 * elem     a ptr to an allocated char array to store the relevant value,     *
 *          which should be large enough to hold the string stored            *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_VALUE_UNINITIALIZED if value had not been set yet             *
 *          INI_NIL_VALUE if elem is NULL                                     *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingGetStringElem(setting_t *setting, int index, char *elem);
 
/******************************************************************************
 *                                                                            *
 * PURPOSE:  To initialize a new setting with an integer type and a concrete  *
 *           underlying value, or to overwrite the existing integer value     *
 *           already stored in the setting.                                   *
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
 * PURPOSE:  To initialize a new setting with a floating point type and a     *
 *           concrete underlying value, or to overwrite the existing floating *
 *           point value already stored in the setting.                       *
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
 * PURPOSE:  To initialize a new setting with a boolean type and a concrete   *
 *           underlying value (integer 0:false, 1:true), or to overwrite the  *
 *           existing boolean value already stored in the setting.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * value    the bool to store as the value of this setting                    *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_VALUE if value is not 0 or 1                          *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetBool(setting_t *setting, int value);

/******************************************************************************
 *                                                                            *
 * PURPOSE:  To initialize a new setting with a character type and a concrete *
 *           underlying value, or to overwrite the existing character value   *
 *           already stored in the setting.                                   *
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
 * PURPOSE:  To initialize a new setting with a string type and a concrete    *
 *           underlying value, or to overwrite the existing string value      *
 *           already stored in the setting.                                   *
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
 * PURPOSE:  To initialize a new setting with an integer array type and a     *
 *           concrete underlying value at index 0, to overwrite any existing  *
 *           integer value at the specified destination, or to expand the     *
 *           array by an element at index len(setting).                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the array to set, from [0-len(setting)]  *
 * elem     the int to store at the index of the array in this setting        *
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
 * PURPOSE:  To initialize a new setting with a floating point array type and *
 *           a concrete underlying value at index 0, to overwrite any         *
 *           existing floating point value at the specified destination, or   *
 *           to expand the array by an element at index len(setting).         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the array to set, from [0-len(setting)]  *
 * elem     the float to store at the index of the array in this setting      *
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
 * PURPOSE:  To initialize a new setting with a boolean array type and a      *
 *           concrete underlying value (integer 0:false, 1:true) at index 0,  *
 *           to overwrite any existing boolean value at the specified         *
 *           destination, or to expand the array by an element at index       *
 *           len(setting).                                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the array to set, from [0-len(setting)]  *
 * elem     the bool to store at the index of the array in this setting       *
 *                                                                            *
 * RETURNS: INI_NIL_SETTING if setting is NULL                                *
 *          INI_TYPE_MISMATCH if stored value does not match getter type      *
 *          INI_INVALID_INDEX if index is out of range                        *
 *          INI_INVALID_VALUE if value is not 0 or 1                          *
 *          INI_OUT_OF_MEMORY if allocation fails                             *
 *          INI_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errINI_t settingSetBoolElem(setting_t *setting, int index, int elem);

/******************************************************************************
 *                                                                            *
 * PURPOSE:  To initialize a new setting with a character array type and      *
 *           a concrete underlying value at index 0, to overwrite any existing*
 *           character value at the specified destination, or to expand the   *
 *           array by an element at index len(setting).                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the array to set, from [0-len(setting)]  *
 * elem     the char to store at the index of the array in this setting       *
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
 * PURPOSE:  To initialize a new setting with a string array type and a       *
 *           concrete underlying value at index 0, to overwrite any existing  *
 *           string value at the specified destination, or to expand the      *
 *           array by an element at index len(setting).                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * setting  the setting to manipulate                                         *
 * index    the index of the item in the array to set, from [0-len(setting)]  *
 * elem     the string to store at the index of the array in this setting     *
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
