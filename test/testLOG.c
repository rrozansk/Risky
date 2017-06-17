/******************************************************************************
 * FILE:    testLOG.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/17/17                                                           *
 * INFO:    Test file for implementation of the interface located in log.h.   *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <log.h> 

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define columns 120
#define directory "logger_tests"
#define TOTAL_TESTS 43

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultLOG { LOG_PASS, LOG_FAIL } testResultLOG_t;

/******************************************************************************
 *                                                                            *
 *   G L O B A L S                                                            *
 *                                                                            *
 ******************************************************************************/
log_t *logger;

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

testResultLOG_t testMakeLOG() {
  fprintf(stdout, "FAIL: testMakeLOG\n");
  return LOG_FAIL;
/*
  time_t t = time(NULL);
  struct tm *date = localtime(&t);
  char name[80];
  strftime(name, 80, "%Y_%B_%d_%A_%X", date); // yr_mo_day_weekday_time

  char fname[80];
  sprintf(fname, "_LOGGER_TEST.txt", name);

  log_t *logger;
  errLOG_t errLOG;
  if((errLOG = makeLOG(&logger, columns, directory, fname)) != LOG_NIL) {
    fprintf(stderr, "error! failure to make log\nirritant: %s\nexiting...\n", strErrLOG(errLOG));
    exit(EXIT_FAILURE);
  }

  if((errLOG = logTitle(logger, fname)) != LOG_NIL) {
    fprintf(stderr, "error! failure to log title\nirritant: %s\nexiting...\n", strErrLOG(errLOG));
    exit(EXIT_FAILURE);
  }

  logHeader(logger, "testing");

  logSection(logger, "testing integer logging");
  testInt(logger);

  int r, c;
  fprintf(stdout, "rows: ");
  scanf("%i", &r);
  fprintf(stdout, "cols: ");
  scanf("%i", &c);

  logSection(logger, "testing float logging");
  testFloat(logger, 1, 1);

  logSection(logger, "testing boolean logging");
  testBool(logger, 1, 1);

  logSection(logger, "testing character logging");
  testChar(logger, 1, 1);

  logSection(logger, "testing string logging");
  testStr(logger, 1, 1);

  return 0;  
  */
}

testResultLOG_t testFreeLOG() {
  //freeLOG(log_t *log)
  return LOG_FAIL;
}

testResultLOG_t testLogTitle() {
  //logTitle(log_t *log, char *title)
  return LOG_FAIL;
}

testResultLOG_t testLogHeader() {
  //logHeader(log_t *log, char *header)
  return LOG_FAIL;
}

testResultLOG_t testLogSection() {
  //logSection(log_t *log, char *section)
  return LOG_FAIL;
}

testResultLOG_t testLogEvent() {
  //logEvent(log_t *log, int timestamp, char *event)
  return LOG_FAIL;
}

testResultLOG_t testLogIntSetting() {
  //logIntSetting(log_t *log, char *key, int val)
  return LOG_FAIL;
}

testResultLOG_t testLogIntArr() {
  //logIntArr(log_t *log, int *arr, int size)
  return LOG_FAIL;
}

testResultLOG_t testLogIntMatrix() {
  //logIntMatrix(log_t *log, int *matrix, int r, int c)
  return LOG_FAIL;
}

testResultLOG_t testLogFloatSetting() {
  //logFloatSetting(log_t *log, char *key, double val)
  return LOG_FAIL;
}

testResultLOG_t testLogFloatArr() {
  //logFloatArr(log_t *log, double *arr, int size)
  return LOG_FAIL;
}

testResultLOG_t testLogFloatMatrix() {
  //logFloatMatrix(log_t *log, double **matrix, int r, int c)
  return LOG_FAIL;
}

testResultLOG_t testLogBoolSetting() {
  //logBoolSetting(log_t *log, char *key, int val)
  return LOG_FAIL;
}

testResultLOG_t testLogBoolArr() {
  //logBoolArr(log_t *log, int *arr, int size)
  return LOG_FAIL;
}

testResultLOG_t testLogBoolMatrix() {
  //logBoolMatrix(log_t *log, int **matrix, int r, int c)
  return LOG_FAIL;
}

testResultLOG_t testLogCharSetting() {
  //logCharSetting(log_t *log, char *key, char val)
  return LOG_FAIL;
}

testResultLOG_t testLogCharArr() {
  //logCharArr(log_t *log, char *arr, int size)
  return LOG_FAIL;
}

testResultLOG_t testLogCharMatrix() {
  //logCharMatrix(log_t *log, char **matrix, int r, int c)
  return LOG_FAIL;
}

testResultLOG_t testLogStrSetting() {
  //logStrSetting(log_t *log, char *key, char *val)
  return LOG_FAIL;
}

testResultLOG_t testLogStrArr() {
  //logStrArr(log_t *log, char **arr, int size)
  return LOG_FAIL;
}

testResultLOG_t testLogStrMatrix() {
  //logStrMatrix(log_t *log, char ***matrix, int r, int c)
  return LOG_FAIL;
}

/*
void testInt(log_t *logger) {
  logEvent(logger, 0, "testing logger int abilities\n");
  logEvent(logger, 0, "static setting");
  logIntSetting(logger, "int test", 5);
  logEvent(logger, 0, "dynamic setting on stk");
  int i = 5;
  logIntSetting(logger, "int test", i);
  logEvent(logger, 0, "dynamic setting on heap");
  int *k = malloc(sizeof(int));
  *k = 6;
  logIntSetting(logger, "int test", *k);
  free(k);
  int ia[5] = { 0, 1, 2, 3, 4 };
  int ial[20] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
  int im[2][5]  = { { 0, 9, 8, 7, 6 }, { 1, 2, 3, 4, 5 } };
  int j = 20;
  int *iml[i = 10];
  for(; i; i--) {
    int arr[j];
    iml[i-1] = arr;
    for(; j; j--) {
      iml[i-1][j-1] = j;
    }
  }
  int imls[3][20]  = {
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 }
  };
  //logEvent(logger, 0, "dynamic array on stk");   // arr[N]
  //logEvent(logger, 0, "dynamic array on heap");  // malloc(N * sizeof(int))
  logEvent(logger, 0, "static array");           // arr[#]
  logIntArr(logger, ia, 5);
  logIntArr(logger, ial, 20);
  logEvent(logger, 0, "static matrix");           // arr[#]
  //logIntMatrix(logger, im, 2, 5);
  logEvent(logger, 0, "dynamic matrix on stk");   // arr[N]
  //logIntMatrix(logger, iml, 10, 20);
  //logEvent(logger, 0, "dynamic matrix on heap");  // malloc(N * sizeof(int))
  logEvent(logger, 0, "\n");
}

void testFloat(log_t *logger, int m, int n) {
  // floats
  double f = 5.23;
  double fa[5] = { 0.9, 1.8, 2.7, 3.6, 4.5 };
  double fal[20] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0 };
  double fm[2][5]  = { { 0.9, 1.8, 2.7, 3.6, 4.5 }, { 0.9, 1.8, 2.7, 3.6, 4.5 } };
  double fml[3][20] = {
    { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0 },
    { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0 },
    { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0 }
  };

  logEvent(logger, 0, "testing logger float abilities");
  logFloatSetting(logger, "float test", f);
  logFloatArr(logger, fa, 15);
  logFloatArr(logger, fal, 20);
  //logFloatMatrix(logger, fm, 2, 5);
  //logFloatMatrix(logger, fml, 10, 20);
  logEvent(logger, 0, "\n");
}

void testBool(log_t *logger, int m, int n) {
  // bools
  int b = 1;
  int ba[5] = { 0, 1, 0, 0, 1 };
  int bal[20] = { 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0 };
  int bm[2][5]  = { { 0, 1, 0, 0, 1 }, { 1, 0, 1, 1, 0 } };
  int bml[3][20] = {
    { 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0 },
    { 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0 },
    { 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0 }
  };
  logEvent(logger, 0, "testing logger bool abilities");
  logBoolSetting(logger, "bool test", b);
  logBoolArr(logger, ba, 5);
  logBoolArr(logger, bal, 20);
  //logBoolMatrix(logger, bm, 2, 5);
  //logBoolMatrix(logger, bml, 10, 20);
  logEvent(logger, 0, "\n");
}

void testChar(log_t *logger, int m, int n) {
  // chars
  char c = 'h';
  char ca[5] = { 'h', 'e', 'l', 'l', 'o' };
  char cal[30] = { 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd' };
  char cm[2][5] = { { 'h', 'e', 'l', 'l', 'o' }, { 'w', 'o', 'r', 'l', 'd' } };
  char cml[3][30] = {
    { 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd' },
    { 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd' },
    { 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd' }
  };
  logEvent(logger, 0, "testing logger char abilities");
  logCharSetting(logger, "char test", c);
  logCharArr(logger, ca, 5);
  logCharArr(logger, cal, 30);
  //logCharMatrix(logger, cm, 2, 5);
  //logCharMatrix(logger, cml, 10, 30);
  logEvent(logger, 0, "\n");
}

void testStr(log_t *logger, int m, int n) {
 // strings
  char *s = "sup!";
  char *sa[5] = { "hello", "there", "small", "world", ":-)" };
  char *sal[20] = { "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)" };
  char *sm[2][5] = { { "hello", "there", "small", "world", ":-)" }, { "hello", "there", "small", "world", ":-)" } };
  char *sml[3][20] = {
    { "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)" },
    { "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)" },
    { "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)", "hello", "there", "small", "world", ":-)" }
  }; 

  logStrSetting(logger, "str test", s);
  logStrArr(logger, sa, 5);
  logStrArr(logger, sal, 20);
  //logStrMatrix(logger, sm, 2, 5);
  //logStrMatrix(logger, sml, 10, 20);
  logEvent(logger, 0, "\n");
}
*/

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
  { testMakeLOG,                       "testMakeLOG"                         },
  { testFreeLOG,                       "testFreeLOG"                         },
  { testLogTitle,                      "testLogTitle"                        },
  { testLogHeader,                     "testLogHeader"                       },
  { testLogSection,                    "testLogSection"                      },
  { testLogEvent,                      "testLogEvent"                        },
  { testLogIntSetting,                 "testLogIntSetting"                   },
  { testLogIntArr,                     "testLogIntArr"                       },
  { testLogIntMatrix,                  "testLogIntMatrix"                    },
  { testLogFloatSetting,               "testLogFloatSetting"                 },
  { testLogFloatArr,                   "testLogFloatArr"                     },
  { testLogFloatMatrix,                "testLogFloatMatrix"                  },
  { testLogBoolSetting,                "testLogBoolSetting"                  },
  { testLogBoolArr,                    "testLogBoolArr"                      },
  { testLogBoolMatrix,                 "testLogBoolMatrix"                   },
  { testLogCharSetting,                "testLogCharSetting"                  },
  { testLogCharArr,                    "testLogCharArr"                      },
  { testLogCharMatrix,                 "testLogCharMatrix"                   },
  { testLogStrSetting,                 "testLogStrSetting"                   },
  { testLogStrArr,                     "testLogStrArr"                       },
  { testLogStrMatrix,                  "testLogStrMatrix"                    },
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
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
