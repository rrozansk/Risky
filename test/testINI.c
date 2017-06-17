/******************************************************************************
 * FILE:    testINI.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/17/17                                                           *
 * INFO:    Test file for implementation of the interface located in ini.h.   *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ini.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 33

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultINI { INI_PASS, INI_FAIL } testResultINI_t;

/******************************************************************************
 *                                                                            *
 *   G L O B A L S                                                            *
 *                                                                            *
 ******************************************************************************/
ini_t *ini;

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/   
testResultINI_t testStrErrINI_UNKNOWN_TYPE() {
  return (strcmp(strErrINI(INI_UNKNOWN_TYPE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_OPEN_FAILURE() {
  return (strcmp(strErrINI(INI_OPEN_FAILURE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_CLOSE_FAILURE() {
  return (strcmp(strErrINI(INI_CLOSE_FAILURE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_OUT_OF_MEMORY() {
  return (strcmp(strErrINI(INI_OUT_OF_MEMORY), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NOT_FOUND() {
  return (strcmp(strErrINI(INI_NOT_FOUND), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_TYPE_MISMATCH() {
  return (strcmp(strErrINI(INI_TYPE_MISMATCH), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_CONF() {
  return (strcmp(strErrINI(INI_INVALID_CONF), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_KEY() {
  return (strcmp(strErrINI(INI_INVALID_KEY), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_VAL() {
  return (strcmp(strErrINI(INI_INVALID_VAL), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_SECTION() {
  return (strcmp(strErrINI(INI_INVALID_SECTION), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_LEN() {
  return (strcmp(strErrINI(INI_INVALID_LEN), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_FNAME() {
  return (strcmp(strErrINI(INI_NIL_FNAME), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_INI() {
  return (strcmp(strErrINI(INI_NIL_INI), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_KEY() {
  return (strcmp(strErrINI(INI_NIL_KEY), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_VAL() {
  return (strcmp(strErrINI(INI_NIL_VAL), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_LEN() {
  return (strcmp(strErrINI(INI_NIL_LEN), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_SECTION() {
  return (strcmp(strErrINI(INI_NIL_SECTION), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL() {
  return (!strcmp(strErrINI(INI_NIL), "")) ? INI_PASS : INI_FAIL;
}
   
testResultINI_t testMakeINI() {
  //makeINI(ini_t **ini)
  return INI_FAIL; 
}


testResultINI_t testFreeINI() {
  //freeINI(ini_t *ini)
  return INI_FAIL;
}

testResultINI_t testReadINI() {
  //readINI(ini_t **ini, char *fname)
  return INI_FAIL;
}

testResultINI_t testWriteINI() {
  //writeINI(ini_t *ini, char *fname)
  return INI_FAIL;
}

testResultINI_t testIntINI() {
  //setIntINI(ini_t *ini, char *section, char *key, int val)
  //getIntINI(ini_t *ini, char *section, char *key, int *value)
  return INI_FAIL;
}

testResultINI_t testFloatINI() {
  //setFloatINI(ini_t *ini, char *section, char *key, double val)
  //getFloatINI(ini_t *ini, char *section, char *key, double *value)
  return INI_FAIL;
}

testResultINI_t testBoolINI() {
  //setBoolINI(ini_t *ini, char *section, char *key, int val)
  //getBoolINI(ini_t *ini, char *section, char *key, int *value)
  return INI_FAIL;
}

testResultINI_t testCharINI() {
  //setCharINI(ini_t *ini, char *section, char *key, char val)
  //getCharINI(ini_t *ini, char *section, char *key, char *value)
  return INI_FAIL;
}

testResultINI_t testStrINI() {
  //setStrINI(ini_t *ini, char *section, char *key, char *val)
  //getStrINI(ini_t *ini, char *section, char *key, char **value)
  return INI_FAIL;
}

testResultINI_t testIntArrINI() {
  //setIntArrINI(ini_t *ini, char *section, char *key, int *val, int n)
  //getIntArrINI(ini_t *ini, char *section, char *key, int **value, int *n)
  return INI_FAIL;
}

testResultINI_t testFloatArrINI() {
  //setFloatArrINI(ini_t *ini, char *section, char *key, double *val, int n)
  //getFloatArrINI(ini_t *ini, char *section, char *key, double **value, int *n)
  return INI_FAIL;
}

testResultINI_t testBoolArrINI() {
  //setBoolArrINI(ini_t *ini, char *section, char *key, int *val, int n)
  //getBoolArrINI(ini_t *ini, char *section, char *key, int **value, int *n)
  return INI_FAIL;
}

testResultINI_t testCharArrINI() {
  //setCharArrINI(ini_t *ini, char *section, char *key, char *val, int n)
  //getCharArrINI(ini_t *ini, char *section, char *key, char **value, int *n)
  return INI_FAIL;
}

testResultINI_t testStrArrINI() {
  //setStrArrINI(ini_t *ini, char *section, char *key, char **val, int n)
  //getStrArrINI(ini_t *ini, char *section, char *key, char ***value, int *n)
  return INI_FAIL;
}

testResultINI_t testDeleteINI() {
  //deleteINI(ini_t *ini, char *section, char *key)
  return INI_FAIL;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testStrErrINI_UNKNOWN_TYPE,             "testStrErrINI_UNKNOWN_TYPE"      },
  { testStrErrINI_OPEN_FAILURE,             "testStrErrINI_OPEN_FAILURE"      },
  { testStrErrINI_CLOSE_FAILURE,            "testStrErrINI_CLOSE_FAILURE"     },
  { testStrErrINI_OUT_OF_MEMORY,            "testStrErrINI_OUT_OF_MEMORY"     },
  { testStrErrINI_NOT_FOUND,                "testStrErrINI_NOT_FOUND"         },
  { testStrErrINI_TYPE_MISMATCH,            "testStrErrINI_TYPE_MISMATCH"     },
  { testStrErrINI_INVALID_CONF,             "testStrErrINI_INVALID_CONF"      },
  { testStrErrINI_INVALID_KEY,              "testStrErrINI_INVALID_KEY"       },
  { testStrErrINI_INVALID_VAL,              "testStrErrINI_INVALID_VAL"       },
  { testStrErrINI_INVALID_SECTION,          "testStrErrINI_INVALID_SECTION"   },
  { testStrErrINI_INVALID_LEN,              "testStrErrINI_INVALID_LEN"       },
  { testStrErrINI_NIL_FNAME,                "testStrErrINI_NIL_FNAME"         },
  { testStrErrINI_NIL_INI,                  "testStrErrINI_NIL_INI"           },
  { testStrErrINI_NIL_KEY,                  "testStrErrINI_NIL_KEY"           },
  { testStrErrINI_NIL_VAL,                  "testStrErrINI_NIL_VAL"           },
  { testStrErrINI_NIL_LEN,                  "testStrErrINI_NIL_LEN"           },
  { testStrErrINI_NIL_SECTION,              "testStrErrINI_NIL_SECTION"       },
  { testStrErrINI_NIL,                      "testStrErrINI_NIL"               },
  { testMakeINI,                            "testMakeINI"                     },
  { testFreeINI,                            "testFreeINI"                     },
  { testReadINI,                            "testReadINI"                     },
  { testWriteINI,                           "testWriteINI"                    },
  { testIntINI,                             "testIntINI"                      },
  { testFloatINI,                           "testFloatINI"                    },
  { testBoolINI,                            "testBoolINI"                     },
  { testCharINI,                            "testCharINI"                     },
  { testStrINI,                             "testStrINI"                      },
  { testIntArrINI,                          "testIntArrINI"                   },
  { testFloatArrINI,                        "testFloatArrINI"                 },
  { testBoolArrINI,                         "testBoolArrINI"                  },
  { testCharArrINI,                         "testCharArrINI"                  },
  { testStrArrINI,                          "testStrArrINI"                   },
  { testDeleteINI,                          "testDeleteINI"                   },
};

int main() {

  testResultINI_t result;
  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    result = ((testResultINI_t (*)(void))(TESTS[test][0]))();
    if(result == INI_PASS) {
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
