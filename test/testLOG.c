/******************************************************************************
 * FILE:    testLOG.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  7/3/17                                                            *
 * INFO:    Test file for implementation of the interface located in log.h.   *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <log.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 106

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

testResultLOG_t testLogTitleValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logtitle.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logTitle(log, "TITLES")) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logtitle.txt", "r"))) { goto FAIL; }

  int i;
  for(i = 0; i < 80; i++) { if(fgetc(fp) != '#') { goto FAIL; } }
  if(fgetc(fp) != '\n') { goto FAIL; }

  if(fgetc(fp) != '#') { goto FAIL; }
  for(i = 0; i < 78; i++) { if(fgetc(fp) != ' ') { goto FAIL; } }
  if(fgetc(fp) != '#') { goto FAIL; }
  if(fgetc(fp) != '\n') { goto FAIL; }

  if(fgetc(fp) != '#') { goto FAIL; }
  for(i = 0; i < 36; i++) { if(fgetc(fp) != ' ') { goto FAIL; } }
  char title[6];
  for(i = 0; i < 6; i++) { title[i] = fgetc(fp); }
  if(strncmp(title, "TITLES", 6)) { goto FAIL; }
  for(i = 0; i < 36; i++) { if(fgetc(fp) != ' ') { goto FAIL; } }
  if(fgetc(fp) != '#') { goto FAIL; }
  if(fgetc(fp) != '\n') { goto FAIL; }

  if(fgetc(fp) != '#') { goto FAIL; }
  for(i = 0; i < 78; i++) { if(fgetc(fp) != ' ') { goto FAIL; } }
  if(fgetc(fp) != '#') { goto FAIL; }
  if(fgetc(fp) != '\n') { goto FAIL; }

  for(i = 0; i < 80; i++) { if(fgetc(fp) != '#') { goto FAIL; } }
  if(fgetc(fp) != '\n') { goto FAIL; }

  remove("logs/logtitle.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logtitle.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testLogHeaderValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logheader.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logHeader(log, "HEADER")) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logheader.txt", "r"))) { goto FAIL; }

  int i;
  for(i = 0; i < 80; i++) { if(fgetc(fp) != '*') { goto FAIL; } }
  if(fgetc(fp) != '\n') { goto FAIL; }

  if(fgetc(fp) != '*') { goto FAIL; }
  for(i = 0; i < 36; i++) { if(fgetc(fp) != ' ') { goto FAIL; } }
  char header[6];
  for(i = 0; i < 6; i++) { header[i] = fgetc(fp); }
  if(strncmp(header, "HEADER", 6)) { goto FAIL; }
  for(i = 0; i < 36; i++) { if(fgetc(fp) != ' ') { goto FAIL; } }
  if(fgetc(fp) != '*') { goto FAIL; }
  if(fgetc(fp) != '\n') { goto FAIL; }

  for(i = 0; i < 80; i++) { if(fgetc(fp) != '*') { goto FAIL; } }
  if(fgetc(fp) != '\n') { goto FAIL; }

  remove("logs/logheader.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logheader.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testLogSectionValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logsection.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logSection(log, "FOOBAR")) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logsection.txt", "r"))) { goto FAIL; }

  int i;
  for(i = 0; i < 37; i++) { if(fgetc(fp) != '=') { goto FAIL; } }
  char section[6];
  for(i = 0; i < 6; i++) { section[i] = fgetc(fp); }
  if(strncmp(section, "FOOBAR", 6)) { goto FAIL; }
  for(i = 0; i < 37; i++) { if(fgetc(fp) != '=') { goto FAIL; } }
  if(fgetc(fp) != '\n') { goto FAIL; }

  remove("logs/logsection.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logsection.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testLogEventValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logevent.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logEvent(log, 0, "some event ...FOOBAR")) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logevent.txt", "r"))) { goto FAIL; }

  char event[21];

  int i;
  for(i = 0; i < 21; i++) { event[i] = fgetc(fp); }
  if(strncmp(event, "some event ...FOOBAR ", 21)) { goto FAIL; } // space inserted after every word
  if(fgetc(fp) != '\n') { goto FAIL; }

  remove("logs/logevent.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logevent.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testIntSettingValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logintsetting.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logIntSetting(log, "intKey", 555)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logintsetting.txt", "r"))) { goto FAIL; }

  int i;
  char key[6];
  for(i = 0; i < 6; i++) { key[i] = fgetc(fp); }
  if(strncmp(key, "intKey", 6)) { goto FAIL; }

  for(i = 0; i < 71; i++) { if(fgetc(fp) != '.') { goto FAIL; } }

  int val;
  i = fscanf(fp, "%i", &val);
  if(!i || val != 555) { goto FAIL; }

  remove("logs/logintsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logintsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testIntArrayValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logintarr.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int size = 10;
  if((errLOG = logIntArr(log, arr, size)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logintarr.txt", "r"))) { goto FAIL; }

  if(fgetc(fp) != '{') { goto FAIL; }
  int val, i;
  for(i = 0; i < 10; i++) {
    if(!fscanf(fp, "%i", &val) || val != arr[i]) { goto FAIL; }
    if(i < 9) { if(fscanf(fp, ", ")) { goto FAIL; } }
    else { if(fscanf(fp, "}\n")) { goto FAIL; } }
  }

  remove("logs/logintarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logintarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
}

testResultLOG_t testIntMatrixNilLog() {
  int matrix[1][1] = { { 9 } };

  errLOG_t errLOG = logIntMatrix(NULL, (int **)matrix, 1, 1);
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

  errLOG = logIntMatrix(log, (int **)matrix, 0, 1);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_ROW_SIZE) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntMatrixInvalidColumnSize() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "log.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int matrix[1][1] = { { 9 } };

  errLOG = logIntMatrix(log, (int **)matrix, 1, 0);

  remove("logs/log.txt");
  remove("logs");

  return (errLOG == LOG_INVALID_COL_SIZE) ? LOG_PASS : LOG_FAIL;
}

testResultLOG_t testIntMatrixValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logintmatrix.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  FILE *fp = NULL;
  // for stk allocation instead
  //int *matrix[2] = { NULL, NULL };
  int **matrix = malloc(sizeof(int *) * 2);
  int r, c;
  for(r = 0; r < 2; r++) {
    //int col[5] = { 0, 1, 2, 3, 4 };
    //matrix[r] = col;
    matrix[r] = malloc(sizeof(int) * 5);
    for(c = 0; c < 5; c++) { matrix[r][c] = c*(r+1); }
  }

  if((errLOG = logIntMatrix(log, matrix, 2, 5)) != LOG_NIL) { goto FAIL; }
  if(!(fp = fopen("logs/logintmatrix.txt", "r"))) { goto FAIL; }

  int val;
  if(fscanf(fp, "{\n")) { goto FAIL; }
  for(r = 0; r < 2; r++) {
    if(fscanf(fp, "\t{")) { goto FAIL; }
    for(c = 0; c < 5; c++) {
      if(!fscanf(fp, "%i", &val) || val != matrix[r][c]) { goto FAIL; }
      if(c < 4) { if(fscanf(fp, ", ")) { goto FAIL; } }
      else { if(fscanf(fp, "}")) { goto FAIL; } }
    }
    if(r < 1) { if(fscanf(fp, ",\n")) { goto FAIL; } }
    else { if(fscanf(fp, "\n")) { goto FAIL; } }
  }
  if(fscanf(fp, "}\n")) { goto FAIL; }

  remove("logs/logintmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logintmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testFloatSettingValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logfloatsetting.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logFloatSetting(log, "floatKey", 555.5)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logfloatsetting.txt", "r"))) { goto FAIL; }

  int i;
  char key[8];
  for(i = 0; i < 8; i++) { key[i] = fgetc(fp); }
  if(strncmp(key, "floatKey", 8)) { goto FAIL; }

  for(i = 0; i < 66; i++) { if(fgetc(fp) != '.') { goto FAIL; } }

  float val;
  i = fscanf(fp, "%f", &val); // 555.50
  if(!i || val != 555.5) { goto FAIL; }

  remove("logs/logfloatsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logfloatsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testFloatArrayValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logfloatarr.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  float arr[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
  float size = 10;
  if((errLOG = logFloatArr(log, arr, size)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logfloatarr.txt", "r"))) { goto FAIL; }

  if(fgetc(fp) != '{') { goto FAIL; }
  float val;
  int i;
  for(i = 0; i < 10; i++) {
    if(!fscanf(fp, "%f", &val) || val != arr[i]) { goto FAIL; }
    if(i < 9) { if(fscanf(fp, ", ")) { goto FAIL; } }
    else { if(fscanf(fp, "}\n")) { goto FAIL; } }
  }

  remove("logs/logfloatarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logfloatarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testFloatMatrixValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logfloatmatrix.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  FILE *fp = NULL;
  float **matrix = malloc(sizeof(float *) * 2);
  int r, c;
  for(r = 0; r < 2; r++) {
    matrix[r] = malloc(sizeof(float) * 5);
    for(c = 0; c < 5; c++) { matrix[r][c] = c*(r+1); }
  }

  if((errLOG = logFloatMatrix(log, matrix, 2, 5)) != LOG_NIL) { goto FAIL; }
  if(!(fp = fopen("logs/logfloatmatrix.txt", "r"))) { goto FAIL; }

  float val;
  if(fscanf(fp, "{\n")) { goto FAIL; }
  for(r = 0; r < 2; r++) {
    if(fscanf(fp, "\t{")) { goto FAIL; }
    for(c = 0; c < 5; c++) {
      if(!fscanf(fp, "%f", &val) || val != matrix[r][c]) { goto FAIL; }
      if(c < 4) { if(fscanf(fp, ", ")) { goto FAIL; } }
      else { if(fscanf(fp, "}")) { goto FAIL; } }
    }
    if(r < 1) { if(fscanf(fp, ",\n")) { goto FAIL; } }
    else { if(fscanf(fp, "\n")) { goto FAIL; } }
  }
  if(fscanf(fp, "}\n")) { goto FAIL; }

  remove("logs/logfloatmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logfloatmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testBoolSettingValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logboolsetting.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logBoolSetting(log, "boolKey", 0)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logboolsetting.txt", "r"))) { goto FAIL; }

  int i;
  char key[7];
  for(i = 0; i < 7; i++) { key[i] = fgetc(fp); }
  if(strncmp(key, "boolKey", 7)) { goto FAIL; }

  for(i = 0; i < 68; i++) { if(fgetc(fp) != '.') { goto FAIL; } }

  char val[5];
  i = fscanf(fp, "%s", (char *)&val);
  if(!i || strcmp(val, "false")) { goto FAIL; }

  remove("logs/logboolsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logboolsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testBoolArrayValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logboolarr.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  int arr[10] = { 0, 0, 1, 0, 1, 1, 0, 1, 0, 1 };
  int size = 10;
  if((errLOG = logBoolArr(log, arr, size)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logboolarr.txt", "r"))) { goto FAIL; }

  if(fgetc(fp) != '{') { goto FAIL; }
  char val[6];
  int i;
  for(i = 0; i < 10; i++) {
    if(arr[i]) {
      if(!fscanf(fp, "%4s", (char *)&val)) { goto FAIL; }
      if(strncmp(val, "true", 4)) { goto FAIL; }
    } else  {
      if(!fscanf(fp, "%5s", (char *)&val)) { goto FAIL; }
      if(strncmp(val, "false", 5)) { goto FAIL; }
    }
    if(i < 9) { if(fscanf(fp, ", ")) { goto FAIL; } }
    else { if(fscanf(fp, "}\n")) { goto FAIL; } }
  }

  remove("logs/logboolarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logboolarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testBoolMatrixValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logboolmatrix.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  FILE *fp = NULL;
  int **matrix = malloc(sizeof(int *) * 2);
  int r, c;
  for(r = 0; r < 2; r++) {
    matrix[r] = malloc(sizeof(int) * 5);
    for(c = 0; c < 5; c++) { matrix[r][c] = (c*(r+1))%2; }
  }

  if((errLOG = logBoolMatrix(log, matrix, 2, 5)) != LOG_NIL) { goto FAIL; }
  if(!(fp = fopen("logs/logboolmatrix.txt", "r"))) { goto FAIL; }

  char val[5];
  if(fscanf(fp, "{\n")) { goto FAIL; }
  for(r = 0; r < 2; r++) {
    if(fscanf(fp, "\t{")) { goto FAIL; }
    for(c = 0; c < 5; c++) {
      if(matrix[r][c]) {
        if(!fscanf(fp, "%4s", (char *)&val) || strncmp(val, "true", 4)) { goto FAIL; }
      } else {
        if(!fscanf(fp, "%5s", (char *)&val) || strncmp(val, "false", 5)) { goto FAIL; }
      }
      if(c < 4) { if(fscanf(fp, ", ")) { goto FAIL; } }
      else { if(fscanf(fp, "}")) { goto FAIL; } }
    }
    if(r < 1) { if(fscanf(fp, ",\n")) { goto FAIL; } }
    else { if(fscanf(fp, "\n")) { goto FAIL; } }
  }
  if(fscanf(fp, "}\n")) { goto FAIL; }

  remove("logs/logboolmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logboolmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testCharSettingValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logcharsetting.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logCharSetting(log, "charKey", 'c')) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logcharsetting.txt", "r"))) { goto FAIL; }

  int i;
  char key[7];
  for(i = 0; i < 7; i++) { key[i] = fgetc(fp); }
  if(strncmp(key, "charKey", 7)) { goto FAIL; }

  for(i = 0; i < 70; i++) { if(fgetc(fp) != '.') { goto FAIL; } }

  char val;
  i = fscanf(fp, "'%c'", &val);
  if(!i || val != 'c') { goto FAIL; }

  remove("logs/logcharsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logcharsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testCharArrayValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logchararr.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char arr[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
  int size = 10;
  if((errLOG = logCharArr(log, arr, size)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logchararr.txt", "r"))) { goto FAIL; }

  if(fgetc(fp) != '{') { goto FAIL; }
  char val;
  int i;
  for(i = 0; i < 10; i++) {
    if(!fscanf(fp, "'%c'", &val) || arr[i] != val) { goto FAIL; }
    if(i < 9) { if(fscanf(fp, ", ")) { goto FAIL; } }
    else { if(fscanf(fp, "}\n")) { goto FAIL; } }
  }

  remove("logs/logchararr.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logchararr.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testCharMatrixValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logcharmatrix.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  FILE *fp = NULL;
  char **matrix = malloc(sizeof(char *) * 2);
  int r, c;
  for(r = 0; r < 2; r++) {
    matrix[r] = malloc(sizeof(char) * 5);
    for(c = 0; c < 5; c++) { matrix[r][c] = (char)(90+(c*(r+1))); }
  }

  if((errLOG = logCharMatrix(log, matrix, 2, 5)) != LOG_NIL) { goto FAIL; }
  if(!(fp = fopen("logs/logcharmatrix.txt", "r"))) { goto FAIL; }

  char val;
  if(fscanf(fp, "{\n")) { goto FAIL; }
  for(r = 0; r < 2; r++) {
    if(fscanf(fp, "\t{")) { goto FAIL; }
    for(c = 0; c < 5; c++) {
      if(!fscanf(fp, "'%c'", &val) || val != matrix[r][c]) { goto FAIL; }
      if(c < 4) { if(fscanf(fp, ", ")) { goto FAIL; } }
      else { if(fscanf(fp, "}")) { goto FAIL; } }
    }
    if(r < 1) { if(fscanf(fp, ",\n")) { goto FAIL; } }
    else { if(fscanf(fp, "\n")) { goto FAIL; } }
  }
  if(fscanf(fp, "}\n")) { goto FAIL; }

  remove("logs/logcharmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logcharmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testStringSettingValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logstringsetting.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  if((errLOG = logStrSetting(log, "stringKey", "c")) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logstringsetting.txt", "r"))) { goto FAIL; }

  int i;
  char key[9];
  for(i = 0; i < 9; i++) { key[i] = fgetc(fp); }
  if(strncmp(key, "stringKey", 9)) { goto FAIL; }

  for(i = 0; i < 68; i++) { if(fgetc(fp) != '.') { goto FAIL; } }

  char val[3];
  i = fscanf(fp, "%s", (char *)&val);
  if(!i || strcmp(val, "\"c\"")) { goto FAIL; }

  remove("logs/logstringsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logstringsetting.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testStringArrayValid() {
  log_t *log;
  FILE *fp = NULL;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logstrarr.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  char *arr[10] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
  int size = 10;
  if((errLOG = logStrArr(log, arr, size)) != LOG_NIL) { goto FAIL; }

  if(!(fp = fopen("logs/logstrarr.txt", "r"))) { goto FAIL; }

  if(fgetc(fp) != '{') { goto FAIL; }
  char val[5];
  int i;
  for(i = 0; i < 10; i++) {
    if(!fscanf(fp, "\"%1s\"", (char *)&val) || strncmp(arr[i], val, 1)) { goto FAIL; }
    if(i < 9) { if(fscanf(fp, ", ")) { goto FAIL; } }
    else { if(fscanf(fp, "}\n")) { goto FAIL; } }
  }

  remove("logs/logstrarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logstrarr.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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

testResultLOG_t testStringMatrixValid() {
  log_t *log;

  errLOG_t errLOG = makeLOG(&log, 80, "logs", "logstrmatrix.txt");
  if(errLOG != LOG_NIL) { return LOG_FAIL; }

  FILE *fp = NULL;
  char ***matrix = malloc(sizeof(char **) * 2);
  int r, c;
  for(r = 0; r < 2; r++) {
    matrix[r] = malloc(sizeof(char *) * 5);
    for(c = 0; c < 5; c++) { matrix[r][c] = "FOOBARBER"; }
  }

  if((errLOG = logStrMatrix(log, matrix, 2, 5)) != LOG_NIL) { goto FAIL; }
  if(!(fp = fopen("logs/logstrmatrix.txt", "r"))) { goto FAIL; }

  char val[10];
  if(fscanf(fp, "{\n")) { goto FAIL; }
  for(r = 0; r < 2; r++) {
    if(fscanf(fp, "\t{")) { goto FAIL; }
    for(c = 0; c < 5; c++) {
      if(!fscanf(fp, "\"%9s\"", (char *)&val) || strcmp(val, matrix[r][c])) { goto FAIL; }
      if(c < 4) { if(fscanf(fp, ", ")) { goto FAIL; } }
      else { if(fscanf(fp, "}")) { goto FAIL; } }
    }
    if(r < 1) { if(fscanf(fp, ",\n")) { goto FAIL; } }
    else { if(fscanf(fp, "\n")) { goto FAIL; } }
  }
  if(fscanf(fp, "}\n")) { goto FAIL; }

  remove("logs/logstrmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_PASS;

FAIL:
  remove("logs/logstrmatrix.txt");
  remove("logs");
  fclose(fp);
  return LOG_FAIL;
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
