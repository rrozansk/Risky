/******************************************************************************
 * FILE:    logger.h                                                          *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/30/17                                                           *
 * EDITED:  5/13/17                                                           *
 * INFO:    A library to implement simple logging.                            *
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
  LOG_NIL, LOG_OPEN_FAIL, LOG_CLOSE_FAIL, LOG_NIL_LOG, LOG_INVALID_WIDTH,
  LOG_NIL_NAME, LOG_NIL_DIR, LOG_OUT_OF_MEMORY, LOG_INVALID_SECONDS, 
  LOG_NIL_KEY, LOG_NIL_HEADER, LOG_NIL_TITLE, LOG_NIL_STR_ARR, 
  LOG_INVALID_ARR_SIZE, LOG_INVALID_SET, LOG_NIL_SECTION, LOG_DIR_CREATION_FAIL,
  LOG_INVALID_TIMESTAMP, LOG_INVALID_DIR,
} errLOG_t;

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
 * errLOG   the error to strigify                                             *
 *                                                                            *
 * RETURNS: String representation of the error.                               *
 *                                                                            *
 ******************************************************************************/
const char *strErrLOG(errLOG_t errLOG);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To create a new log.                                              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log created                                                   *
 * columns  the width of the log                                              *
 * dir      the directory to place the log under                              *
 * name     the name of the log to create                                     *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG, LOG_NIL_DIR, LOG_NIL_NAME, LOG_INVALID_WIDTH,        *
 *          LOG_OUT_OF_MEMORY, LOG_DIR_CREATION_FAIL, LOG_OPEN_FAIL, or       *
 *          LOG_NIL if no error.                                              *
 *                                                                            *
 ******************************************************************************/
errLOG_t makeLOG(log_t **log, int columns, char *dir, char *name);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To free the created log.                                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to free                                                   *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG, LOG_CLOSE_FAIL, or LOG_NIL if no error               *
 *                                                                            *
 ******************************************************************************/
errLOG_t freeLOG(log_t *log);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the integer array.                                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 * arr      the array to log                                                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG, LOG_NIL_STR_ARR, LOG_INVALID_ARR_SIZE, or LOG_NIL if *
 *          no error.                                                         *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntArr(log_t *log, int *arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the integer matrix.                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 * arr      the array to log                                                  *
 * x        the size of the rows                                              *
 * y        the size of the colums                                            *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG, LOG_NIL_STR_ARR, LOG_INVALID_ARR_SIZE, or LOG_NIL if *
 *          no error.                                                         *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntArr2D(log_t *log, int **arr, int x, int y);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the array of strings.                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 * arr      the array to log                                                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG, LOG_NIL_STR_ARR, LOG_INVALID_ARR_SIZE, or LOG_NIL if *
 *          no error.                                                         *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrArr(log_t *log, char **arr, int size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a title.                                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 * title    the title to create in the log                                    *
 *                                                                            *
 * RETURNS: LOG_NIL_TITLE, or LOG_NIL if no error.                            *
 *                                                                            *
 ******************************************************************************/
errLOG_t logTitle(log_t *log, char *title);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a header.                                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 * header   the header to create in the log                                   *
 *                                                                            *
 * RETURNS: LOG_NIL_HEADER, or LOG_NIL if no error.                           *
 *                                                                            *
 ******************************************************************************/
errLOG_t logHeader(log_t *log, char *header);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log a section header.                                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 * section  the section to create in the log                                  *
 *                                                                            *
 * RETURNS: LOG_NIL_SECTION, or LOG_NIL if no error.                          *
 *                                                                            *
 ******************************************************************************/
errLOG_t logSection(log_t *log, char *section);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by '...' and the the val.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 *                                                                            *
 * RETURNS: LOG_NIL_KEY, or LOG_NIL if no error.                              *
 *                                                                            *
 ******************************************************************************/
errLOG_t logIntSetting(log_t *log, char *key, int val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by '...' and the the val.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 *                                                                            *
 * RETURNS: LOG_NIL_KEY, or LOG_NIL if no error.                              *
 *                                                                            *
 ******************************************************************************/
errLOG_t logStrSetting(log_t *log, char *key, char *val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log the key followed by '...' and the the val.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * log      the log to print to                                               *
 *                                                                            *
 * RETURNS: LOG_NIL_KEY, or LOG_NIL if no error.                              *
 *                                                                            *
 ******************************************************************************/
errLOG_t logFloatSetting(log_t *log, char *key, double val);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To log an arbitrary event, possibly with a timestamp.             *
 *                                                                            *
 * ARGUMENT  DESCRIPTION                                                      *
 * --------  -----------                                                      *
 * log       the log to print to                                              *
 * timestamp to include a timestamp with the event or not                     *
 * event     the event to log                                                 *
 *                                                                            *
 * RETURNS: LOG_NIL_LOG, LOG_INVALID_TIMESTAMP, or LOG_NIL if no error.       *
 *                                                                            *
 ******************************************************************************/
errLOG_t logEvent(log_t *log, int timestamp, char *event);

#endif
