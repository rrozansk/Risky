/******************************************************************************
 * FILE:    logger.h                                                          *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/30/17                                                           *
 * EDITED:  6/1/17                                                            *
 * INFO:    A library to implement simple logging. This includes the ability  *
 *          to log three different styles of headers. The different headers,  *
 *          in decending order of importance, are title, header, and section. *
 *          It is also possible to log any key value pair, termed a setting,  *
 *          as well as arrays and matricies of any basic data type including: *
 *          int, float, bool, char, and str. Other niceties implemented by    *
 *          the library include: error handling, uniform APIs, flushing output*
 *          on every logging method, logging arbitrary strings (events) with  *
 *          optional timestamping, and being able to dicate the max column    *
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
  LOG_INVALID_ARR_SIZE, LOG_NIL_SECTION, LOG_INVALID_TIMESTAMP, LOG_INVALID_DIR,
  LOG_NIL, LOG_OPEN_FAIL, LOG_CLOSE_FAIL, LOG_DIR_CREATION_FAIL, LOG_NIL_HEADER,
  LOG_NIL_TITLE, LOG_NIL_DIR, LOG_OUT_OF_MEMORY, LOG_NIL_KEY, LOG_INVALID_WIDTH,
  LOG_INVALID_ROW_SIZE, LOG_INVALID_COL_SIZE, LOG_UNKNOWN_TYPE, LOG_INVALID_KEY,
  LOG_NIL_MATRIX, LOG_NIL_NAME, LOG_INVALID_SECONDS, LOG_NIL_ARR, LOG_NIL_LOG, 
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
 * RETURNS: A string representation of the error.                             *
 *                                                                            *
 ******************************************************************************/
const char *strErrLOG(errLOG_t errLOG);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempts to create a new log, if any error is returned the value  *
 *          stored at log will be NULL.                                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the address of the location to store the newly created log        *
 * columns  the max width of the log, must be between >= 80                   *
 * dir      the name of the directory to place the log under, if it does not  *
 *          exist it will be created                                          *
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
 * PURPOSE: To free any log created by makeLOG().                             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to free                                                   *
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
 * log      the log to record the title in                                    *
 * title    the title to create in the log                                    *
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
 *          seperated by blank space and the cenetered header provided.       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the header in                                   *
 * header   the header to create in the log                                   *
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
 * log      the log to record the section in                                  *
 * section  the section to create in the log                                  *
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
 *          column length of the library. This function also mutates the      *
 *          underlying string event.                                          *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * log       the log to record the event in                                   *
 * timestamp to include a timestamp with the event or not                     *
 * event     the event to log                                                 *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_INVALID_TIMESTAMP if timestamp is not 0 or 1                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logEvent(log_t *log, int timestamp, char *event);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by .'s and the the integer value such     *
 *          that an entire log line is filled up.                             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the setting in                                  *
 * key      the key/description of the setting                                *
 * val      the value of the setting                                          *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length - 20             *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntSetting(log_t *log, char *key, int val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an integer array.                                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the array in                                    *
 * arr      the array to log                                                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_INT_ARR if arr is NULL                                    *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntArr(log_t *log, int *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an integer matrix.                                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the matrix in                                   *
 * matrix   the matrix to log                                                 *
 * r        the number of the rows in the matrix                              *
 * c        the number of the colums in the matrix                            *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_INT_MATRIX if matrix is NULL                              *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntMatrix(log_t *log, int *matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by .'s and the the float value such that  *
 *          an entire log line is filled up.                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the setting in                                  *
 * key      the key/description of the setting                                *
 * val      the value of the setting                                          *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length - 20             *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logFloatSetting(log_t *log, char *key, double val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an array of floats.                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the array in                                    *
 * arr      the array to log                                                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_FLOAT_ARR if arr is NULL                                  *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logFloatArr(log_t *log, double *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a matrix of floats.                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the matrix in                                   *
 * matrix   the matrix to log                                                 *
 * r        the number of the rows in the matrix                              *
 * c        the number of the colums in the matrix                            *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_FLOAT_MATRIX if matrix is NULL                            *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logFloatMatrix(log_t *log, double **matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by .'s and the the boolean value such     *
 *          that an entire log line is filled up. booleanes are encoded as an *
 *          integers and prints as strings (0: false, 1: true).               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the setting in                                  *
 * key      the key/description of the setting                                *
 * val      the value of the setting                                          *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length - 10             *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logBoolSetting(log_t *log, char *key, int val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an array of bools, encoded as integers. 0: false, 1: true  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the array in                                    *
 * arr      the array to log                                                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_BOOL_ARR if arr is NULL                                   *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logBoolArr(log_t *log, int *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a matrixof bools, encoded as integers. 0: false, 1: true   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the matrix in                                   *
 * matrix   the matrix to log                                                 *
 * r        the number of the rows in the matrix                              *
 * c        the number of the colums in the matrix                            *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_BOOL_MATRIX if matrix is NULL                             *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logBoolMatrix(log_t *log, int **matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by .'s and the the character value such   *
 *          that an entire log line is filled up.                             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the setting in                                  *
 * key      the key/description of the setting                                *
 * val      the value of the setting                                          *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key > column length - 10             *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logCharSetting(log_t *log, char *key, char val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an array of characters.                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the array in                                    *
 * arr      the array to log                                                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_CHAR_ARR if arr is NULL                                   *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logCharArr(log_t *log, char *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a matrix of characters.                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the matrix in                                   *
 * matrix   the matrix to log                                                 *
 * r        the number of the rows in the matrix                              *
 * c        the number of the colums in the matrix                            *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_CHAR_MATRIX if matrix is NULL                             *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logCharMatrix(log_t *log, char **matrix, int r, int c);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by .'s and the the string value such that *
 *          an entire log line is filled up.                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the setting in                                  *
 * key      the key/description of the setting                                *
 * val      the value of the setting                                          *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_KEY if key is NULL                                        *
 *          LOG_INVALID_KEY if length of key + val + 2 > column length - 10   *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrSetting(log_t *log, char *key, char *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an array of strings.                                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the matrix in                                   *
 * arr      the array to log                                                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_STR_ARR if arr is NULL                                    *
 *          LOG_INVALID_ARR_SIZE if size < 1                                  *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrArr(log_t *log, char **arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a matrix of strings.                                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to record the matrix in                                   *
 * matrix   the matrix to log                                                 *
 * r        the number of the rows in the matrix                              *
 * c        the number of the colums in the matrix                            *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG if log is NULL                                        *
 *          LOG_NIL_STR_MATRIX if matrix is NULL                              *
 *          LOG_INVALID_ROW_SIZE if r < 1                                     *
 *          LOG_INVALID_COL_SIZE if c < 1                                     *
 *          LOG_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrMatrix(log_t *log, char ***matrix, int r, int c);

#endif
