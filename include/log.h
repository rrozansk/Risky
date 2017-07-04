/******************************************************************************
 * FILE:    log.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/30/17                                                           *
 * EDITED:  7/3/17                                                            *
 * INFO:    A library to implement simple logging. This includes the ability  *
 *          to log three different styles of headers. The different headers,  *
 *          in decending order of importance, are title, header, and section. *
 *          It is also possible to log any key value pair, termed a setting,  *
 *          as well as arrays and matricies of any basic data type including: *
 *          int, float, bool, char, and str. Other niceties implemented by    *
 *          the library include: error handling, uniform APIs, flushing output*
 *          on every logging method, logging arbitrary strings (events) with  *
 *          optional timestamping, and being able to dictate the max column   *
 *          length when printing to the log file.                             *
 *                                                                            *
 ******************************************************************************/

#ifndef LOGGER_DEFS
#define LOGGER_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct log log_t; /* A representation of a logger */

typedef enum errLOG {
  LOG_OUT_OF_MEMORY, LOG_OPEN_FAIL, LOG_CLOSE_FAIL, LOG_DIR_CREATION_FAIL,
  LOG_INVALID_ROW_SIZE, LOG_INVALID_COL_SIZE, LOG_INVALID_ARR_SIZE, 
  LOG_INVALID_WIDTH, LOG_INVALID_TIMESTAMP, LOG_INVALID_DIR, LOG_INVALID_KEY, 
  LOG_NIL_LOG, LOG_NIL_NAME, LOG_NIL_DIR, LOG_NIL_TITLE, LOG_NIL_HEADER, 
  LOG_NIL_SECTION, LOG_NIL_KEY, LOG_NIL_ARR, LOG_NIL_MATRIX, LOG_NIL,
} errLOG_t;

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
 * errLOG   the error to stringify                                            *
 *                                                                            *
 * RETURNS: A string representation of the error                              *
 *                                                                            *
 ******************************************************************************/
const char *strErrLOG(errLOG_t errLOG);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempts to create a new log construct with output to a file in   *
 *          the given directory. If the directory does not exist it will be   *
 *          created. If the file exists it will be overwritten. If any error  *
 *          is returned the value stored at log will be NULL.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      an address to a ptr in which to set the newly created construct   *
 * columns  the max width of the log, must be >= 80                           *
 * dir      the directory to place the log file under                         *
 * name     the filename of the log to create                                 *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_DIR if dir is NULL                                        *
 *          LOG_NIL_NAME if name is NULL                                      *
 *          LOG_INVALID_WIDTH if columns is < 80                              *
 *          LOG_INVALID_DIR if length of name and dir is > 255 chars          *
 *          LOG_DIR_CREATION_FAIL if the creation of the directory failed     *
 *          LOG_OUT_OF_MEMORY if allocation of the new log failed             *
 *          LOG_OPEN_FAIL if opening the log file fails                       *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t makeLOG(log_t **log, int columns, char *dir, char *name);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To free any log construct created through the log constructor.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the ptr to the log construct in which to free                     *
 *                                                                            *
 * RETURNS: LOG_CLOSE_FAIL if closing the log file failed                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t freeLOG(log_t *log);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a title. A title prints as 5 seperate lines. Lines 1 and 5 *
 *          are lines of #'s. Lines 2 and 4 start and end with a single # and *
 *          are sperated by blank space. Line 3 prints like lines 2 and 4,    *
 *          but with the provided title centered.                             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * title    the title to record in the log                                    *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_TITLE if title is NULL                                    *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logTitle(log_t *log, char *title);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a header. A header prints 3 seperate lines. line 1 and 3   *
 *          are lines of *'s. Line 2 starts and ends with a single *,         *
 *          seperated by blank space with the provided header centered.       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * header   the header to record in the log                                   *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_HEADER if header is NULL                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logHeader(log_t *log, char *header);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a section header. A section prints as a single line. It is *
 *          made up of ='s for the entirety of the line, broken up by the     *
 *          provided section in the center.                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * section  the section to record in the log                                  *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_SECTION if section is NULL                                *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logSection(log_t *log, char *section);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an arbitrary event, possibly with a timestamp. The event   *
 *          will be broken up by its whitespace so that it conforms to the    *
 *          column length of the library. If the timestamp is printed it will *
 *          conform to year_month_day_weekday_time with time specified to the *
 *          second.                                                           *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * log       the log construct to use                                         *
 * timestamp to include a timestamp or not                                    *
 * event     the event to record in the log                                   *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_INVALID_TIMESTAMP if timestamp is not 0 or 1                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logEvent(log_t *log, int timestamp, char *event);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an integer setting. Prints the key followed by .'s and the *
 *          integer value such that an entire log line is filled up.          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * key      the key/description of the setting                                *
 * val      the integer value of the setting                                  *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length / 2              *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntSetting(log_t *log, char *key, int val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a comma delimited integer array enclosed by {}. The array  *
 *          will be split inbetween elements when needed to adhere to the     *
 *          logs column lenght.                                               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * arr      the array to record in the log                                    *
 * size     number of elements in array                                       *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_ARR if arr is NULL                                        *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntArr(log_t *log, int *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an integer matrix enclosed by {}. An integer matrix is an  *
 *          array of int ptrs to integer arrays. Each printed matrix element  *
 *          is printed on a seperate tabbed over line enclosed by {}. All     *
 *          matrix elements (1D and 2D) are comma seperated and split         *
 *          accordingly to adhere to the column length of the log.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * matrix   the matrix to record in the log                                   *
 * r        number of the rows in the matrix                                  *
 * c        number of the colums in the matrix                                *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_MATRIX if matrix is NULL                                  *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntMatrix(log_t *log, int **matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a float setting. Prints the key followed by .'s and the    *
 *          float value such that an entire log line is filled up.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * key      the key/description of the setting                                *
 * val      the float value of the setting                                    *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length / 2              *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logFloatSetting(log_t *log, char *key, float val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a comma delimited float array enclosed by {}. The array    *
 *          will be split inbetween elements when needed to adhere to the     *
 *          logs column lenght.                                               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * arr      the array to record in the log                                    *
 * size     number of elements in array                                       *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_ARR if arr is NULL                                        *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logFloatArr(log_t *log, float *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an float matrix enclosed by {}. An float matrix is an      *
 *          array of float ptrs to float arrays. Each printed matrix element  *
 *          is printed on a seperate tabbed over line. enclosed by {}. All    *
 *          matrix elements (1D and 2D) are comma seperated and split         *
 *          accordingly to adhere to the column length of the log.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * matrix   the matrix to record in the log                                   *
 * r        number of the rows in the matrix                                  *
 * c        number of the colums in the matrix                                *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_MATRIX if matrix is NULL                                  *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logFloatMatrix(log_t *log, float **matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a boolean setting. Prints the key followed by .'s and the  *
 *          boolean value such that an entire log line is filled up. Booleans *
 *          are encoded as integers and print as strings (0: false, 1: true). *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * key      the key/description of the setting                                *
 * val      the boolean encoded integer value of the setting                  *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length / 2              *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logBoolSetting(log_t *log, char *key, int val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a comma delimited boolean array enclosed by {}. Booleans   *
 *          are encoded as integers and print as strings (0: false, 1: true). *
 *          The array will be split inbetween elements when needed to adhere  *
 *          to the logs column lenght.                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * arr      the array to record in the log                                    *
 * size     number of elements in array                                       *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_ARR if arr is NULL                                        *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logBoolArr(log_t *log, int *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an boolean matrix, encoded as integers (0: false, 1: true) *
 *          and printed as strings, enclosed by {}. An boolean matrix is an   *
 *          array of int ptrs to int arrays. Each printed matrix element is   *
 *          printed on a seperate tabbed over line. enclosed by {}. All       *
 *          matrix elements (1D and 2D) are comma seperated and split         *
 *          accordingly to adhere to the column length of the log.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * matrix   the matrix to record in the log                                   *
 * r        number of the rows in the matrix                                  *
 * c        number of the colums in the matrix                                *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_MATRIX if matrix is NULL                                  *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logBoolMatrix(log_t *log, int **matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a character setting. Prints the key followed by .'s and    *
 *          the character value such that an entire log line is filled up.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * key      the key/description of the setting                                *
 * val      the character value of the setting                                *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length / 2              *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logCharSetting(log_t *log, char *key, char val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a comma delimited character array enclosed by {}. The array*
 *          will be split inbetween elements when needed to adhere to the     *
 *          logs column lenght.                                               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * arr      the array to record in the log                                    *
 * size     number of elements in array                                       *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_ARR if arr is NULL                                        *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logCharArr(log_t *log, char *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a character matrix enclosed by {}. A character matrix is   *
 *          an array of character ptrs to character arrays. Each printed      *
 *          matrix element is printed on a seperate tabbed over line.         *
 *          enclosed by {}. All matrix elements (1D and 2D) are comma         *
 *          seperated and split accordingly to adhere to the column length of *
 *          the log.                                                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * matrix   the matrix to record in the log                                   *
 * r        number of the rows in the matrix                                  *
 * c        number of the colums in the matrix                                *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_MATRIX if matrix is NULL                                  *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logCharMatrix(log_t *log, char **matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a string setting. Prints the key followed by .'s and the   *
 *          string value such that an entire log line is filled up.           *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * key      the key/description of the setting                                *
 * val      the string value of the setting                                   *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length / 2              *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrSetting(log_t *log, char *key, char *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a comma delimited string array enclosed by {}. The array   *
 *          will be split inbetween elements when needed to adhere to the     *
 *          logs column lenght.                                               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * arr      the array to record in the log                                    *
 * size     number of elements in array                                       *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_ARR if arr is NULL                                        *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrArr(log_t *log, char **arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a string matrix enclosed by {}. A string matrix is an      *
 *          array of string ptrs to string arrays. Each printed matrix element*
 *          is printed on a seperate tabbed over line. enclosed by {}. All    *
 *          matrix elements (1D and 2D) are comma seperated and split         *
 *          accordingly to adhere to the column length of the log.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log construct to use                                          *
 * matrix   the matrix to record in the log                                   *
 * r        number of the rows in the matrix                                  *
 * c        number of the colums in the matrix                                *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_MATRIX if matrix is NULL                                  *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrMatrix(log_t *log, char ***matrix, int r, int c);

#endif
