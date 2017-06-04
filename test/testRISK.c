/******************************************************************************
 * FILE:    testRISK.c                                                        *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/4/17                                                            *
 * INFO:    Test file for implementation of the interface located in risk.h.  *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<risk.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 1

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultRISK { RISK_SUCC, RISK_FAIL } testResultRISK_t;

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/
testResultRISK_t testMakeRISK() {
  fprintf(stdout, "FAIL: testMakeRISK\n");
  return RISK_FAIL;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
testResultRISK_t (*TESTS[TOTAL_TESTS])() = {
  testMakeRISK
};

int main() {

  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    ((*TESTS[test])() == RISK_SUCC) ? passes++ : fails++;
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
