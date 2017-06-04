/******************************************************************************
 * FILE:    testLOG.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/4/17                                                            *
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
#define TOTAL_TESTS 1

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultLOG { LOG_SUCC, LOG_FAIL } testResultLOG_t;

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

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
testResultLOG_t (*TESTS[TOTAL_TESTS])() = {
  testMakeLOG,
};

int main() {

  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    ((*TESTS[test])() == LOG_SUCC) ? passes++ : fails++;
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
