/******************************************************************************
 * FILE:    testLOG.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  7/2/17                                                            *
 * INFO:    Test file for implementation of the interface located in log.h.   *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <log.h> 

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 107

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultLOG { LOG_PASS, LOG_FAIL } testResultLOG_t;

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/
testResultLOG_t testStrErrLOG_OUT_OF_MEMORY() {
  return (strcmp(strErrLOG(LOG_OUT_OF_MEMORY), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_OPEN_FAIL() {
  return (strcmp(strErrLOG(LOG_OPEN_FAIL), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_CLOSE_FAIL() {
  return (strcmp(strErrLOG(LOG_CLOSE_FAIL), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_DIR_CREATION_FAIL() {
  return (strcmp(strErrLOG(LOG_DIR_CREATION_FAIL), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_UNKNOWN_TYPE() {
  return (strcmp(strErrLOG(LOG_UNKNOWN_TYPE), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_INVALID_ROW_SIZE() {
  return (strcmp(strErrLOG(LOG_INVALID_ROW_SIZE), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_INVALID_COL_SIZE() {
  return (strcmp(strErrLOG(LOG_INVALID_COL_SIZE), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_INVALID_ARR_SIZE() {
  return (strcmp(strErrLOG(LOG_INVALID_ARR_SIZE), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_INVALID_WIDTH() {
  return (strcmp(strErrLOG(LOG_INVALID_WIDTH), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_INVALID_TIMESTAMP() {
  return (strcmp(strErrLOG(LOG_INVALID_TIMESTAMP), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_INVALID_DIR() {
  return (strcmp(strErrLOG(LOG_INVALID_DIR), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_INVALID_KEY() {
  return (strcmp(strErrLOG(LOG_INVALID_KEY), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_LOG() {
  return (strcmp(strErrLOG(LOG_NIL_LOG), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_NAME() {
  return (strcmp(strErrLOG(LOG_NIL_NAME), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_DIR() {
  return (strcmp(strErrLOG(LOG_NIL_DIR), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_TITLE() {
  return (strcmp(strErrLOG(LOG_NIL_TITLE), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_HEADER() {
  return (strcmp(strErrLOG(LOG_NIL_HEADER), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_SECTION() {
  return (strcmp(strErrLOG(LOG_NIL_SECTION), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_KEY() {
  return (strcmp(strErrLOG(LOG_NIL_KEY), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_ARR() {
  return (strcmp(strErrLOG(LOG_NIL_ARR), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL_MATRIX() {
  return (strcmp(strErrLOG(LOG_NIL_MATRIX), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStrErrLOG_NIL() {
  return (!strcmp(strErrLOG(LOG_NIL), "")) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testMakeLOGNilLog() {
  errLOG_t errLOG = makeLOG(NULL, 80, "logs", "log");
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testMakeLOGNilDir() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, NULL, "log");
  return (errLOG == LOG_NIL_DIR) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testMakeLOGNilName() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", NULL);
  return (errLOG == LOG_NIL_NAME) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testMakeLOGInvalidWidth() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 0, "logs", "log");
  return (errLOG == LOG_INVALID_WIDTH) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testMakeLOGInvalidDir() {
  char *dir = "someReallySuperExtremelyLongDirectoryName"
              "someReallySuperExtremelyLongDirectoryName"
              "someReallySuperExtremelyLongDirectoryName"
              "someReallySuperExtremelyLongDirectoryName"
              "someReallySuperExtremelyLongDirectoryName";
  char *f = "anotherReallySuperExtremelyLongTextFileName"
            "anotherReallySuperExtremelyLongTextFileName"
            "anotherReallySuperExtremelyLongTextFileName"
            "anotherReallySuperExtremelyLongTextFileName"
            "anotherReallySuperExtremelyLongTextFileName.txt";
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, dir, f);
  return (errLOG == LOG_INVALID_DIR) ? LOG_PASS : LOG_FAIL;
}

//testResultLOG_t testMakeLOGDirCreationFail() {  } // LOG_DIR_CREATION_FAIL

//testResultLOG_t testMakeLOGOutOFMemory() {  } // LOG_OUT_OF_MEMORY

//testResultLOG_t testMakeLOGOpenFail() {  } // LOG_OPEN_FAIL

testResultLOG_t testMakeLOGValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  remove("logs/log.txt");
  remove("logs");

  return LOG_PASS;
}

//testResultLOG_t testFreeLOGCloseFail() { } // LOG_CLOSE_FAIL

testResultLOG_t testFreeLOGNilLog() {
  errLOG_t errLOG = freeLOG(NULL);
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFreeLOGValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = freeLOG(log);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogTitleNilLog() {
  errLOG_t errLOG = logTitle(NULL, "TITLE");
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogTitleNilTitle() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logTitle(log,  NULL);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_TITLE) ? LOG_PASS : LOG_FAIL;
}

// TODO
testResultLOG_t testLogTitleValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logTitle(log, "TITLE");
  if(errLOG != LOG_NIL) {
    remove("logs/log.txt");
    remove("logs");
    return LOG_FAIL;
  }

  errLOG = LOG_NIL_LOG;

  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogHeaderNilLog() {
  errLOG_t errLOG = logHeader(NULL, "HEADER");
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogHeaderNilHeader() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logHeader(log, NULL);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_HEADER) ? LOG_PASS : LOG_FAIL;
}

//logHeader(log_t *log, char *header); TODO
testResultLOG_t testLogHeaderValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogSectionNilLog() {
  errLOG_t errLOG = logSection(NULL, "SECTION");
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogSectionNilSection() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logSection(log, NULL);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_SECTION) ? LOG_PASS : LOG_FAIL;
}

//logSection(log_t *log, char *section); TODO
testResultLOG_t testLogSectionValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogEventNilLog() {
  errLOG_t errLOG = logEvent(NULL, 0, "EVENT");
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testLogEventInvalidTimestamp() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logEvent(log, 2, "EVENT");

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_TIMESTAMP) ? LOG_PASS : LOG_FAIL;
}

//logEvent(log_t *log, int timestamp, char *event); TODO
testResultLOG_t testLogEventValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntSettingNilLog() {
  errLOG_t errLOG = logIntSetting(NULL, "KEY", 0);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntSettingNilKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logIntSetting(log, NULL, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_KEY) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntSettingInvalidKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *key = "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName";

  errLOG = logIntSetting(log, key, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_KEY) ? LOG_PASS : LOG_FAIL;
}

//logIntSetting(log_t *log, char *key, int val); TODO
testResultLOG_t testIntSettingValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntArrayNilLog() {
  int arr[1] = { 8 };

  errLOG_t errLOG = logIntArr(NULL, arr, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntArrayNilArray() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logIntArr(log, NULL, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_ARR) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntArrayInvalidSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int arr[1] = { 8 };

  errLOG = logIntArr(log, arr, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ARR_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logIntArr(log_t *log, int *arr, int size); TODO
testResultLOG_t testIntArrayValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntMatrixNilLog() {
  int matrix[1][1] = { { 9 } };

  errLOG_t errLOG = logIntMatrix(NULL, (int *)matrix, 1, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntMatrixNilMatrix() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logIntMatrix(log, NULL, 1, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_MATRIX) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntMatrixInvalidRowSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int matrix[1][1] = { { 9 } };

  errLOG = logIntMatrix(log, (int *)matrix, 0, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ROW_SIZE) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntMatrixInvalidColumnSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int matrix[1][1] = { { 9 } };

  errLOG = logIntMatrix(log, (int *)matrix, 1, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_COL_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logIntMatrix(log_t *log, int *matrix, int r, int c); TODO
testResultLOG_t testIntMatrixValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatSettingNilLog() {
  errLOG_t errLOG = logFloatSetting(NULL, "KEY", 0.0);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatSettingNilKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logFloatSetting(log, NULL, 0.0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_KEY) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatSettingInvalidKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *key = "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName";

  errLOG = logFloatSetting(log, key, 0.0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_KEY) ? LOG_PASS : LOG_FAIL;
}

//logFloatSetting(log_t *log, char *key, double val); TODO
testResultLOG_t testFloatSettingValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatArrayNilLog() {
  float arr[1] = { 8.0 };

  errLOG_t errLOG = logFloatArr(NULL, arr, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatArrayNilArray() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logFloatArr(log, NULL, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_ARR) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatArrayInvalidSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  float arr[1] = { 8.0 };

  errLOG = logFloatArr(log, arr, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ARR_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logFloatArr(log_t *log, double *arr, int size); TODO
testResultLOG_t testFloatArrayValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatMatrixNilLog() {
  float matrix[1][1] = { { 9.0 } };

  errLOG_t errLOG = logFloatMatrix(NULL, (float **)matrix, 1, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatMatrixNilMatrix() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logFloatMatrix(log, NULL, 1, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_MATRIX) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatMatrixInvalidRowSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  float matrix[1][1] = { { 9.0 } };

  errLOG = logFloatMatrix(log, (float **)matrix, 0, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ROW_SIZE) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testFloatMatrixInvalidColumnSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }


  float matrix[1][1] = { { 9.0 } };

  errLOG = logFloatMatrix(log, (float **)matrix, 1, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_COL_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logFloatMatrix(log_t *log, double **matrix, int r, int c); TODO
testResultLOG_t testFloatMatrixValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolSettingNilLog() {
  errLOG_t errLOG = logBoolSetting(NULL, "KEY", 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolSettingNilKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logBoolSetting(log, NULL, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_KEY) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolSettingInvalidKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *key = "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName";

  errLOG = logBoolSetting(log, key, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_KEY) ? LOG_PASS : LOG_FAIL;
}

//logBoolSetting(log_t *log, char *key, int val); TODO
testResultLOG_t testBoolSettingValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolArrayNilLog() {
  int arr[1] = { 1 };

  errLOG_t errLOG = logBoolArr(NULL, arr, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolArrayNilArray() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logBoolArr(log, NULL, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_ARR) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolArrayInvalidSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int arr[1] = { 1 };

  errLOG = logBoolArr(log, arr, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ARR_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logBoolArr(log_t *log, int *arr, int size); TODO
testResultLOG_t testBoolArrayValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolMatrixNilLog() {
  int matrix[1][1] = { { 0 } };

  errLOG_t errLOG = logBoolMatrix(NULL, (int **)matrix, 1, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolMatrixNilMatrix() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logBoolMatrix(log, NULL, 1, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_MATRIX) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolMatrixInvalidRowSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int matrix[1][1] = { { 0 } };

  errLOG = logBoolMatrix(log, (int **)matrix, 0, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ROW_SIZE) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testBoolMatrixInvalidColumnSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int matrix[1][1] = { { 0 } };

  errLOG = logBoolMatrix(log, (int **)matrix, 1, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_COL_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logBoolMatrix(log_t *log, int **matrix, int r, int c); TODO
testResultLOG_t testBoolMatrixValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharSettingNilLog() {
  errLOG_t errLOG = logCharSetting(NULL, "KEY", 'c');
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharSettingNilKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logCharSetting(log, NULL, 'c');

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_KEY) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharSettingInvalidKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *key = "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName";

  errLOG = logCharSetting(log, key, 'c');

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_KEY) ? LOG_PASS : LOG_FAIL;
}

//logCharSetting(log_t *log, char *key, char val); TODO
testResultLOG_t testCharSettingValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharArrayNilLog() {
  char arr[1] = { 'c' };

  errLOG_t errLOG = logCharArr(NULL, arr, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharArrayNilArray() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logCharArr(log, NULL, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_ARR) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharArrayInvalidSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char arr[1] = { 'c' };

  errLOG = logCharArr(log, arr, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ARR_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logCharArr(log_t *log, char *arr, int size); TODO
testResultLOG_t testCharArrayValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharMatrixNilLog() {
  char matrix[1][1] = { { 'c' } };

  errLOG_t errLOG = logCharMatrix(NULL, (char **)matrix, 1, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharMatrixNilMatrix() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logCharMatrix(log, NULL, 1, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_MATRIX) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharMatrixInvalidRowSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char matrix[1][1] = { { 'c' } };

  errLOG = logCharMatrix(log, (char **)matrix, 0, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ROW_SIZE) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testCharMatrixInvalidColumnSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char matrix[1][1] = { { 'c' } };

  errLOG = logCharMatrix(log, (char **)matrix, 1, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_COL_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logCharMatrix(log_t *log, char **matrix, int r, int c); TODO
testResultLOG_t testCharMatrixValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringSettingNilLog() {
  errLOG_t errLOG = logStrSetting(NULL, "KEY", "c");
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringSettingNilKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logStrSetting(log, NULL, "c");

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_KEY) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringSettingInvalidKey() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *key = "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName"
              "someReallySuperExtremelyLongKeyName";

  errLOG = logStrSetting(log, key, "c");

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_KEY) ? LOG_PASS : LOG_FAIL;
}

//logStrSetting(log_t *log, char *key, char *val); TODO
testResultLOG_t testStringSettingValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringArrayNilLog() {
  char *arr[1] = { "c" };

  errLOG_t errLOG = logStrArr(NULL, arr, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringArrayNilArray() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logStrArr(log, NULL, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_ARR) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringArrayInvalidSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *arr[1] = { "c" };

  errLOG = logStrArr(log, arr, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ARR_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logStrArr(log_t *log, char **arr, int size); TODO
testResultLOG_t testStringArrayValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringMatrixNilLog() {
  char *matrix[1][1] = { { "c" } };

  errLOG_t errLOG = logStrMatrix(NULL, (char ***)matrix, 1, 1);
  return (errLOG == LOG_NIL_LOG) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringMatrixNilMatrix() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  errLOG = logStrMatrix(log, NULL, 1, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_NIL_MATRIX) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringMatrixInvalidRowSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *matrix[1][1] = { { "c" } };

  errLOG = logStrMatrix(log, (char ***)matrix, 0, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ROW_SIZE) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testStringMatrixInvalidColumnSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *matrix[1][1] = { { "c" } };

  errLOG = logStrMatrix(log, (char ***)matrix, 1, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_COL_SIZE) ? LOG_PASS : LOG_FAIL;
}

//logStrMatrix(log_t *log, char ***matrix, int r, int c); TODO
testResultLOG_t testStringMatrixValid() {
  errLOG_t errLOG = LOG_NIL_LOG;
  return (errLOG == LOG_NIL) ? LOG_PASS : LOG_FAIL;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testStrErrLOG_OUT_OF_MEMORY,       "testStrErrLOG_OUT_OF_MEMORY"         },
  { testStrErrLOG_OPEN_FAIL,           "testStrErrLOG_OPEN_FAIL"             },
  { testStrErrLOG_CLOSE_FAIL,          "testStrErrLOG_CLOSE_FAIL"            },
  { testStrErrLOG_DIR_CREATION_FAIL,   "testStrErrLOG_DIR_CREATION_FAIL"     },
  { testStrErrLOG_UNKNOWN_TYPE,        "testStrErrLOG_UNKNOWN_TYPE"          },
  { testStrErrLOG_INVALID_ROW_SIZE,    "testStrErrLOG_INVALID_ROW_SIZE"      },
  { testStrErrLOG_INVALID_COL_SIZE,    "testStrErrLOG_INVALID_COL_SIZE"      },
  { testStrErrLOG_INVALID_ARR_SIZE,    "testStrErrLOG_INVALID_ARR_SIZE"      },
  { testStrErrLOG_INVALID_WIDTH,       "testStrErrLOG_INVALID_WIDTH"         },
  { testStrErrLOG_INVALID_TIMESTAMP,   "testStrErrLOG_INVALID_TIMESTAMP"     },
  { testStrErrLOG_INVALID_DIR,         "testStrErrLOG_INVALID_DIR"           },
  { testStrErrLOG_INVALID_KEY,         "testStrErrLOG_INVALID_KEY"           },
  { testStrErrLOG_NIL_LOG,             "testStrErrLOG_NIL_LOG"               },
  { testStrErrLOG_NIL_NAME,            "testStrErrLOG_NIL_NAME"              },
  { testStrErrLOG_NIL_DIR,             "testStrErrLOG_NIL_DIR"               },
  { testStrErrLOG_NIL_TITLE,           "testStrErrLOG_NIL_TITLE"             },
  { testStrErrLOG_NIL_HEADER,          "testStrErrLOG_NIL_HEADER"            },
  { testStrErrLOG_NIL_SECTION,         "testStrErrLOG_NIL_SECTION"           },
  { testStrErrLOG_NIL_KEY,             "testStrErrLOG_NIL_KEY"               },
  { testStrErrLOG_NIL_ARR,             "testStrErrLOG_NIL_ARR"               },
  { testStrErrLOG_NIL_MATRIX,          "testStrErrLOG_NIL_MATRIX"            },
  { testStrErrLOG_NIL,                 "testStrErrLOG_NIL"                   },
  { testMakeLOGNilLog,                 "testMakeLOGNilLog"                   },
  { testMakeLOGNilDir,                 "testMakeLOGNilDir"                   },
  { testMakeLOGNilName,                "testMakeLOGNilName"                  },
  { testMakeLOGInvalidWidth,           "testMakeLOGInvalidWidth"             },
  { testMakeLOGInvalidDir,             "testMakeLOGInvalidDir"               },
  //{ testMakeLOGDirCreationFail,        "testMakeLOGDirCreationFail"          },
  //{ testMakeLOGOutOFMemory,            "testMakeLOGOutOFMemory"              },
  //{ testMakeLOGOpenFail,               "testMakeLOGOpenFail"                 },
  { testMakeLOGValid,                  "testMakeLOGValid"                    },
  //{ testFreeLOGCloseFail,              "testFreeLOGCloseFail"                },
  { testFreeLOGNilLog,                 "testFreeLOGNilLog"                   },
  { testFreeLOGValid,                  "testFreeLOGValid"                    },
  { testLogTitleNilLog,                "testLogTitleNilLog"                  },
  { testLogTitleNilTitle,              "testLogTitleNilTitle"                },
  { testLogTitleValid,                 "testLogTitleValid"                   },
  { testLogHeaderNilLog,               "testLogHeaderNilLog"                 },
  { testLogHeaderNilHeader,            "testLogHeaderNilHeader"              },
  { testLogHeaderValid,                "testLogHeaderValid"                  },
  { testLogSectionNilLog,              "testLogSectionNilLog"                },
  { testLogSectionNilSection,          "testLogSectionNilSection"            },
  { testLogSectionValid,               "testLogSectionValid"                 },
  { testLogEventNilLog,                "testLogEventNilLog"                  },
  { testLogEventInvalidTimestamp,      "testLogEventInvalidTimestamp"        },
  { testLogEventValid,                 "testLogEventValid"                   },
  { testIntSettingNilLog,              "testIntSettingNilLog"                },
  { testIntSettingNilKey,              "testIntSettingNilKey"                },
  { testIntSettingInvalidKey,          "testIntSettingInvalidKey"            },
  { testIntSettingValid,               "testIntSettingValid"                 },
  { testIntArrayNilLog,                "testIntArrayNilLog"                  },
  { testIntArrayNilArray,              "testIntArrayNilArray"                },
  { testIntArrayInvalidSize,           "testIntArrayInvalidSize"             },
  { testIntArrayValid,                 "testIntArrayValid"                   },
  { testIntMatrixNilLog,               "testIntMatrixNilLog"                 },
  { testIntMatrixNilMatrix,            "testIntMatrixNilMatrix"              },
  { testIntMatrixInvalidRowSize,       "testIntMatrixInvalidRowSize"         },
  { testIntMatrixInvalidColumnSize,    "testIntMatrixInvalidColumnSize"      },
  { testIntMatrixValid,                "testIntMatrixValid"                  },
  { testFloatSettingNilLog,            "testFloatSettingNilLog"              },
  { testFloatSettingNilKey,            "testFloatSettingNilKey"              },
  { testFloatSettingInvalidKey,        "testFloatSettingInvalidKey"          },
  { testFloatSettingValid,             "testFloatSettingValid"               },
  { testFloatArrayNilLog,              "testFloatArrayNilLog"                },
  { testFloatArrayNilArray,            "testFloatArrayNilArray"              },
  { testFloatArrayInvalidSize,         "testFloatArrayInvalidSize"           },
  { testFloatArrayValid,               "testFloatArrayValid"                 },
  { testFloatMatrixNilLog,             "testFloatMatrixNilLog"               },
  { testFloatMatrixNilMatrix,          "testFloatMatrixNilMatrix"            },
  { testFloatMatrixInvalidRowSize,     "testFloatMatrixInvalidRowSize"       },
  { testFloatMatrixInvalidColumnSize,  "testFloatMatrixInvalidColumnSize"    },
  { testFloatMatrixValid,              "testFloatMatrixValid"                },
  { testBoolSettingNilLog,             "testBoolSettingNilLog"               },
  { testBoolSettingNilKey,             "testBoolSettingNilKey"               },
  { testBoolSettingInvalidKey,         "testBoolSettingInvalidKey"           },
  { testBoolSettingValid,              "testBoolSettingValid"                },
  { testBoolArrayNilLog,               "testBoolArrayNilLog"                 },
  { testBoolArrayNilArray,             "testBoolArrayNilArray"               },
  { testBoolArrayInvalidSize,          "testBoolArrayInvalidSize"            },
  { testBoolArrayValid,                "testBoolArrayValid"                  },
  { testBoolMatrixNilLog,              "testBoolMatrixNilLog"                },
  { testBoolMatrixNilMatrix,           "testBoolMatrixNilMatrix"             },
  { testBoolMatrixInvalidRowSize,      "testBoolMatrixInvalidRowSize"        },
  { testBoolMatrixInvalidColumnSize,   "testBoolMatrixInvalidColumnSize"     },
  { testBoolMatrixValid,               "testBoolMatrixValid"                 },
  { testCharSettingNilLog,             "testCharSettingNilLog"               },
  { testCharSettingNilKey,             "testCharSettingNilKey"               },
  { testCharSettingInvalidKey,         "testCharSettingInvalidKey"           },
  { testCharSettingValid,              "testCharSettingValid"                },
  { testCharArrayNilLog,               "testCharArrayNilLog"                 },
  { testCharArrayNilArray,             "testCharArrayNilArray"               },
  { testCharArrayInvalidSize,          "testCharArrayInvalidSize"            },
  { testCharArrayValid,                "testCharArrayValid"                  },
  { testCharMatrixNilLog,              "testCharMatrixNilLog"                },
  { testCharMatrixNilMatrix,           "testCharMatrixNilMatrix"             },
  { testCharMatrixInvalidRowSize,      "testCharMatrixInvalidRowSize"        },
  { testCharMatrixInvalidColumnSize,   "testCharMatrixInvalidColumnSize"     },
  { testCharMatrixValid,               "testCharMatrixValid"                 },
  { testStringSettingNilLog,           "testStringSettingNilLog"             },
  { testStringSettingNilKey,           "testStringSettingNilKey"             },
  { testStringSettingInvalidKey,       "testStringSettingInvalidKey"         },
  { testStringSettingValid,            "testStringSettingValid"              },
  { testStringArrayNilLog,             "testStringArrayNilLog"               },
  { testStringArrayNilArray,           "testStringArrayNilArray"             },
  { testStringArrayInvalidSize,        "testStringArrayInvalidSize"          },
  { testStringArrayValid,              "testStringArrayValid"                },
  { testStringMatrixNilLog,            "testStringMatrixNilLog"              },
  { testStringMatrixNilMatrix,         "testStringMatrixNilMatrix"           },
  { testStringMatrixInvalidRowSize,    "testStringMatrixInvalidRowSize"      },
  { testStringMatrixInvalidColumnSize, "testStringMatrixInvalidColumnSize"   },
  { testStringMatrixValid,             "testStringMatrixValid"               },
};

int main() {

  testResultLOG_t result;
  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    result = ((testResultLOG_t (*)(void))(TESTS[test][0]))();
    if(result == LOG_PASS) {
      passes++;
      fprintf(stdout, "PASS: %s\n", (char *)TESTS[test][1]);
    } else {
      fprintf(stdout, "FAIL: %s\n", (char *)TESTS[test][1]);
      fails++;
    }
    fflush(stdout); // so if segfault/crash we know last successful test
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
