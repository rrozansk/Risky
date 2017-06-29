/******************************************************************************
 * FILE:    testINI.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/29/17                                                           *
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
#define TOTAL_TESTS 204

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultINI { INI_PASS, INI_FAIL } testResultINI_t;

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

testResultINI_t testMakeININilINI() {
  errINI_t errINI = makeINI(NULL);
  return  (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testMakeINIOutOfMemory() {} // cannot test

testResultINI_t testMakeINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testFreeININilINI() {
  errINI_t errINI = freeINI(NULL);
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testFreeINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = freeINI(ini);
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadININilINI() { // TODO
  //errINI_t errINI = readINI(NULL, "fname");
  return INI_FAIL;  
}

testResultINI_t testReadININilFname() { // TODO
  //ini_t *ini;
  //errINI_t errINI = readINI(&ini, NULL);
  return INI_FAIL;  
}

testResultINI_t testReadINIInvalidSection() { // TODO
  // write to a file then read -- declare a var (like ini_const = "...")
  return INI_FAIL;  
}

testResultINI_t testReadINIInvalidKey() { // TODO
  return INI_FAIL;  
}

testResultINI_t testReadINIInvalidArrayComma() { // TODO
  // extra comma at end of array element
  return INI_FAIL;  
}

testResultINI_t testReadINIInvalidArrayType() { // TODO
  // array with more than one type in it
  return INI_FAIL;  
}

testResultINI_t testReadINIInvalidArrayLenght() { // TODO
  // cannot delcare empty array
  return INI_FAIL;  
}

testResultINI_t testReadINIInvalidString() { // TODO
  // cannot delcare string without enclosing ""
  return INI_FAIL;  
}

testResultINI_t testReadINIValid() { // TODO
  return INI_FAIL;  
}

testResultINI_t testWriteININilINI() {
  errINI_t errINI = writeINI(NULL, "fname.txt");
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testWriteININilFileName() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = writeINI(ini, NULL);
  return (errINI == INI_NIL_FNAME) ? INI_PASS : INI_FAIL;
}

testResultINI_t testWriteINIOpenFailure() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = writeINI(ini, "invalid/0foo.txt");
  return (errINI == INI_OPEN_FAILURE) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testWriteINICloseFailure() { } // cannot test

testResultINI_t testWriteINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = writeINI(ini, "testINI.txt");
  if(errINI != INI_NIL) { return INI_FAIL; }

  return remove("testINI.txt") ? INI_FAIL : INI_PASS;
}

testResultINI_t testSetIntININilINI() {
  errINI_t errINI = setIntINI(NULL, "section", "key", 0);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, NULL, "key", 0);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "section", NULL, 0);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "sec tion", "key", 0);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "section", "k ey", 0);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntINIValidSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "section", "key", 55);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntINIValidOverwriteSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "section", "key", 55);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "section", "key", 45);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntININilINI() {
  int value;

  errINI_t errINI = getIntINI(NULL, "section", "key", &value);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getIntINI(ini, NULL, "key", &value);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getIntINI(ini, "section", NULL, &value);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntININilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = getIntINI(ini, "section", "key", NULL);
  return (errINI == INI_NIL_VAL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getIntINI(ini, "sec tion", "key", &value);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getIntINI(ini, "section", "ke y", &value);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntININonPresentKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "section", "foo", 55);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getIntINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntININonPresentSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getIntINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "section", "key", 55);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getIntINI(ini, "section", "key", &value);
  return (errINI == INI_NIL && value == 55) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatININilINI() {
  errINI_t errINI = setFloatINI(NULL, "section", "key", 0);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, NULL, "key", 45.5);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "section", NULL, 0.34);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "sec tion", "key", 0.68);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "section", "k ey", 0.45);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatINIValidSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "section", "key", 55.4);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatINIValidOverwriteSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "section", "key", 55.3);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "section", "key", 45.6);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatININilINI() {
  double value;

  errINI_t errINI = getFloatINI(NULL, "section", "key", &value);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  double value;

  errINI = getFloatINI(ini, NULL, "key", &value);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  double value;

  errINI = getFloatINI(ini, "section", NULL, &value);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatININilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = getFloatINI(ini, "section", "key", NULL);
  return (errINI == INI_NIL_VAL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  double value;

  errINI = getFloatINI(ini, "sec tion", "key", &value);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  double value;

  errINI = getFloatINI(ini, "section", "ke y", &value);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatININonPresentKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "section", "foo", 55.3);
  if(errINI != INI_NIL) { return INI_FAIL; }

  double value;

  errINI = getFloatINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatININonPresentSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  double value;

  errINI = getFloatINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setFloatINI(ini, "section", "key", 55.3);
  if(errINI != INI_NIL) { return INI_FAIL; }

  double value;

  errINI = getFloatINI(ini, "section", "key", &value);
  return (errINI == INI_NIL && value == 55.3) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolININilINI() {
  errINI_t errINI = setBoolINI(NULL, "section", "key", 0);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, NULL, "key", 1);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "section", NULL, 1);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "sec tion", "key", 0);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "section", "k ey", 0);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolINIValidSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "section", "key", 1);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolINIValidOverwriteSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "section", "key", 0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "section", "key", 1);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolININilINI() {
  int value;

  errINI_t errINI = getBoolINI(NULL, "section", "key", &value);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getBoolINI(ini, NULL, "key", &value);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getBoolINI(ini, "section", NULL, &value);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolININilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = getBoolINI(ini, "section", "key", NULL);
  return (errINI == INI_NIL_VAL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getBoolINI(ini, "sec tion", "key", &value);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getBoolINI(ini, "section", "ke y", &value);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolININonPresentKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "section", "foo", 0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getBoolINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolININonPresentSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getBoolINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setBoolINI(ini, "section", "key", 1);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = getBoolINI(ini, "section", "key", &value);
  return (errINI == INI_NIL && value == 1) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharININilINI() {
  errINI_t errINI = setCharINI(NULL, "section", "key", 'c');
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, NULL, "key", 'c');
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "section", NULL, 'c');
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "sec tion", "key", 'c');
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "section", "k ey", 'c');
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharINIValidSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "section", "key", 'c');
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharINIValidOverwriteSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "section", "key", 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "section", "key", 'f');
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharININilINI() {
  char value;

  errINI_t errINI = getCharINI(NULL, "section", "key", &value);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = getCharINI(ini, NULL, "key", &value);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = getCharINI(ini, "section", NULL, &value);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharININilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = getCharINI(ini, "section", "key", NULL);
  return (errINI == INI_NIL_VAL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = getCharINI(ini, "sec tion", "key", &value);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = getCharINI(ini, "section", "ke y", &value);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharININonPresentKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "section", "foo", 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = getCharINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharININonPresentSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = getCharINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setCharINI(ini, "section", "key", 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = getCharINI(ini, "section", "key", &value);
  return (errINI == INI_NIL && value == 'c') ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrININilINI() {
  errINI_t errINI = setStrINI(NULL, "section", "key", "string");
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, NULL, "key", "string");
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "section", NULL, "string");
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "sec tion", "key", "string");
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "section", "k ey", "string");
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrINIValidSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "section", "key", "string");
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrINIValidOverwriteSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "section", "key", "string");
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "section", "key", "string2");
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrININilINI() {
  char *value;

  errINI_t errINI = getStrINI(NULL, "section", "key", &value);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char *value;

  errINI = getStrINI(ini, NULL, "key", &value);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char *value;

  errINI = getStrINI(ini, "section", NULL, &value);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrININilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = getStrINI(ini, "section", "key", NULL);
  return (errINI == INI_NIL_VAL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char *value;

  errINI = getStrINI(ini, "sec tion", "key", &value);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char *value;

  errINI = getStrINI(ini, "section", "ke y", &value);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrININonPresentKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "section", "foo", "string");
  if(errINI != INI_NIL) { return INI_FAIL; }

  char *value;

  errINI = getStrINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrININonPresentSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char *value;

  errINI = getStrINI(ini, "section", "key", &value);
  return (errINI == INI_NOT_FOUND) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setStrINI(ini, "section", "key", "string");
  if(errINI != INI_NIL) { return INI_FAIL; }

  char *value;

  errINI = getStrINI(ini, "section", "key", &value);
  return (errINI == INI_NIL && !strcmp(value, "string")) ? INI_PASS : INI_FAIL;
}

// FIXME: still need to add invalid len error cehcks for arrays??
//     INI_NIL_LEN, INI_INVALID_LEN

//setIntArrArrINI(ini_t *ini, char *section, char *key, int *val, int n)// TODO
testResultINI_t testSetIntArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntArrINIValidSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetIntArrINIValidOverwriteSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//getIntArrArrINI(ini_t *ini, char *section, char *key, int **value, int *n)// TODO
testResultINI_t testGetIntArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrININilValue() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrININonPresentKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrININonPresentSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetIntArrINIValid() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//setFloatArrINI(ini_t *ini, char *section, char *key, double *val, int n)// TODO
testResultINI_t testSetFloatArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatArrINIValidSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetFloatArrINIValidOverwriteSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//getFloatArrINI(ini_t *ini, char *section, char *key, double **value, int *n)// TODO
testResultINI_t testGetFloatArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrININilValue() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrININonPresentKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrININonPresentSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetFloatArrINIValid() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//setBoolArrINI(ini_t *ini, char *section, char *key, int *val, int n)// TODO
testResultINI_t testSetBoolArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolArrINIValidSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetBoolArrINIValidOverwriteSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//getBoolArrINI(ini_t *ini, char *section, char *key, int **value, int *n)// TODO
testResultINI_t testGetBoolArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrININilValue() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrININonPresentKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrININonPresentSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetBoolArrINIValid() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//setCharArrINI(ini_t *ini, char *section, char *key, char *val, int n)// TODO
testResultINI_t testSetCharArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharArrINIValidSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetCharArrINIValidOverwriteSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//getCharArrINI(ini_t *ini, char *section, char *key, char **value, int *n)// TODO
testResultINI_t testGetCharArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrININilValue() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrININonPresentKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrININonPresentSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetCharArrINIValid() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//setStrArrINI(ini_t *ini, char *section, char *key, char **val, int n)// TODO
testResultINI_t testSetStrArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrArrINIValidSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetStrArrINIValidOverwriteSetting() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//getStrArrINI(ini_t *ini, char *section, char *key, char ***value, int *n)// TODO
testResultINI_t testGetStrArrININilINI() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrININilSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrININilKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrININilValue() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrINIInvalidGrammerSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrINIInvalidGrammerKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrININonPresentKey() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrININonPresentSection() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetStrArrINIValid() {
  errINI_t errINI = INI_NIL;
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteININilINI() {
  errINI_t errINI = deleteINI(NULL, "section", "key");
  return  (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteININilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteINI(ini, NULL, "key");
  return  (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteININilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteINI(ini, "section", NULL);
  return  (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteINIInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteINI(ini, "sec tion", "key");
  return  (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteINIInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteINI(ini, "section", "ke y");
  return  (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteININonPresentSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteINI(ini, "nowhere", "key");
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteININonPresentKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "new", "new", 0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteINI(ini, "new", "nowhere");
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = setIntINI(ini, "new", "new", 0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteINI(ini, "new", "new");
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCompleteIOFlow() {
// TODO: read in a written conf constructed from cRUD operators and then to a
// comparison to make sure they are equal to one another
  return INI_FAIL;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testStrErrINI_UNKNOWN_TYPE,                  "testStrErrINI_UNKNOWN_TYPE"                },
  { testStrErrINI_OPEN_FAILURE,                  "testStrErrINI_OPEN_FAILURE"                },
  { testStrErrINI_CLOSE_FAILURE,                 "testStrErrINI_CLOSE_FAILURE"               },
  { testStrErrINI_OUT_OF_MEMORY,                 "testStrErrINI_OUT_OF_MEMORY"               },
  { testStrErrINI_NOT_FOUND,                     "testStrErrINI_NOT_FOUND"                   },
  { testStrErrINI_TYPE_MISMATCH,                 "testStrErrINI_TYPE_MISMATCH"               },
  { testStrErrINI_INVALID_CONF,                  "testStrErrINI_INVALID_CONF"                },
  { testStrErrINI_INVALID_KEY,                   "testStrErrINI_INVALID_KEY"                 },
  { testStrErrINI_INVALID_VAL,                   "testStrErrINI_INVALID_VAL"                 },
  { testStrErrINI_INVALID_SECTION,               "testStrErrINI_INVALID_SECTION"             },
  { testStrErrINI_INVALID_LEN,                   "testStrErrINI_INVALID_LEN"                 },
  { testStrErrINI_NIL_FNAME,                     "testStrErrINI_NIL_FNAME"                   },
  { testStrErrINI_NIL_INI,                       "testStrErrINI_NIL_INI"                     },
  { testStrErrINI_NIL_KEY,                       "testStrErrINI_NIL_KEY"                     },
  { testStrErrINI_NIL_VAL,                       "testStrErrINI_NIL_VAL"                     },
  { testStrErrINI_NIL_LEN,                       "testStrErrINI_NIL_LEN"                     },
  { testStrErrINI_NIL_SECTION,                   "testStrErrINI_NIL_SECTION"                 },
  { testStrErrINI_NIL,                           "testStrErrINI_NIL"                         },
  { testMakeININilINI,                           "testMakeININilINI"                         },
  //{ testMakeINIOutOfMemory,                      "testMakeINIOutOfMemory"                    },
  { testMakeINIValid,                            "testMakeINIValid"                          },
  { testFreeININilINI,                           "testFreeININilINI"                         },
  { testFreeINIValid,                            "testFreeINIValid"                          },
  { testReadININilINI,                           "testReadININilINI"                         },
  { testReadININilFname,                         "testReadININilFname"                       },
  { testReadINIInvalidSection,                   "testReadINIInvalidSection"                 },
  { testReadINIInvalidKey,                       "testReadINIInvalidKey"                     },
  { testReadINIInvalidArrayComma,                "testReadINIInvalidArrayComma"              },
  { testReadINIInvalidArrayType,                 "testReadINIInvalidArrayType"               },
  { testReadINIInvalidArrayLenght,               "testReadINIInvalidArrayLenght"             },
  { testReadINIInvalidString,                    "testReadINIInvalidString"                  },
  { testReadINIValid,                            "testReadINIValid"                          },
  { testWriteININilINI,                          "testWriteININilINI"                        },
  { testWriteININilFileName,                     "testWriteININilFileName"                   },
  { testWriteINIOpenFailure,                     "testWriteINIOpenFailure"                   },
  //{ testWriteINICloseFailure,                    "testWriteINICloseFailure"                  },
  { testWriteINIValid,                           "testWriteINIValid"                         },
  { testSetIntININilINI,                         "testSetIntININilINI"                       },
  { testSetIntININilSection,                     "testSetIntININilSection"                   },
  { testSetIntININilKey,                         "testSetIntININilKey"                       },
  { testSetIntINIInvalidGrammerSection,          "testSetIntINIInvalidGrammerSection"        },
  { testSetIntINIInvalidGrammerKey,              "testSetIntINIInvalidGrammerKey"            },
  { testSetIntINIValidSetting,                   "testSetIntINIValidSetting"                 },
  { testSetIntINIValidOverwriteSetting,          "testSetIntINIValidOverwriteSetting"        },
  { testGetIntININilINI,                         "testGetIntININilINI"                       },
  { testGetIntININilSection,                     "testGetIntININilSection"                   },
  { testGetIntININilKey,                         "testGetIntININilKey"                       },
  { testGetIntININilValue,                       "testGetIntININilValue"                     },
  { testGetIntINIInvalidGrammerSection,          "testGetIntINIInvalidGrammerSection"        },
  { testGetIntINIInvalidGrammerKey,              "testGetIntINIInvalidGrammerKey"            },
  { testGetIntININonPresentKey,                  "testGetIntININonPresentKey"                },
  { testGetIntININonPresentSection,              "testGetIntININonPresentSection"            },
  { testGetIntINIValid,                          "testGetIntINIValid"                        },
  { testSetFloatININilINI,                       "testSetFloatININilINI"                     },
  { testSetFloatININilSection,                   "testSetFloatININilSection"                 },
  { testSetFloatININilKey,                       "testSetFloatININilKey"                     },
  { testSetFloatINIInvalidGrammerSection,        "testSetFloatINIInvalidGrammerSection"      },
  { testSetFloatINIInvalidGrammerKey,            "testSetFloatINIInvalidGrammerKey"          },
  { testSetFloatINIValidSetting,                 "testSetFloatINIValidSetting"               },
  { testSetFloatINIValidOverwriteSetting,        "testSetFloatINIValidOverwriteSetting"      },
  { testGetFloatININilINI,                       "testGetFloatININilINI"                     },
  { testGetFloatININilSection,                   "testGetFloatININilSection"                 },
  { testGetFloatININilKey,                       "testGetFloatININilKey"                     },
  { testGetFloatININilValue,                     "testGetFloatININilValue"                   },
  { testGetFloatINIInvalidGrammerSection,        "testGetFloatINIInvalidGrammerSection"      },
  { testGetFloatINIInvalidGrammerKey,            "testGetFloatINIInvalidGrammerKey"          },
  { testGetFloatININonPresentKey,                "testGetFloatININonPresentKey"              },
  { testGetFloatININonPresentSection,            "testGetFloatININonPresentSection"          },
  { testGetFloatINIValid,                        "testGetFloatINIValid"                      },
  { testSetBoolININilINI,                        "testSetBoolININilINI"                      },
  { testSetBoolININilSection,                    "testSetBoolININilSection"                  },
  { testSetBoolININilKey,                        "testSetBoolININilKey"                      },
  { testSetBoolINIInvalidGrammerSection,         "testSetBoolINIInvalidGrammerSection"       },
  { testSetBoolINIInvalidGrammerKey,             "testSetBoolINIInvalidGrammerKey"           },
  { testSetBoolINIValidSetting,                  "testSetBoolINIValidSetting"                },
  { testSetBoolINIValidOverwriteSetting,         "testSetBoolINIValidOverwriteSetting"       },
  { testGetBoolININilINI,                        "testGetBoolININilINI"                      },
  { testGetBoolININilSection,                    "testGetBoolININilSection"                  },
  { testGetBoolININilKey,                        "testGetBoolININilKey"                      },
  { testGetBoolININilValue,                      "testGetBoolININilValue"                    },
  { testGetBoolINIInvalidGrammerSection,         "testGetBoolINIInvalidGrammerSection"       },
  { testGetBoolINIInvalidGrammerKey,             "testGetBoolINIInvalidGrammerKey"           },
  { testGetBoolININonPresentKey,                 "testGetBoolININonPresentKey"               },
  { testGetBoolININonPresentSection,             "testGetBoolININonPresentSection"           },
  { testGetBoolINIValid,                         "testGetBoolINIValid"                       },
  { testSetCharININilINI,                        "testSetCharININilINI"                      },
  { testSetCharININilSection,                    "testSetCharININilSection"                  },
  { testSetCharININilKey,                        "testSetCharININilKey"                      },
  { testSetCharINIInvalidGrammerSection,         "testSetCharINIInvalidGrammerSection"       },
  { testSetCharINIInvalidGrammerKey,             "testSetCharINIInvalidGrammerKey"           },
  { testSetCharINIValidSetting,                  "testSetCharINIValidSetting"                },
  { testSetCharINIValidOverwriteSetting,         "testSetCharINIValidOverwriteSetting"       },
  { testGetCharININilINI,                        "testGetCharININilINI"                      },
  { testGetCharININilSection,                    "testGetCharININilSection"                  },
  { testGetCharININilKey,                        "testGetCharININilKey"                      },
  { testGetCharININilValue,                      "testGetCharININilValue"                    },
  { testGetCharINIInvalidGrammerSection,         "testGetCharINIInvalidGrammerSection"       },
  { testGetCharINIInvalidGrammerKey,             "testGetCharINIInvalidGrammerKey"           },
  { testGetCharININonPresentKey,                 "testGetCharININonPresentKey"               },
  { testGetCharININonPresentSection,             "testGetCharININonPresentSection"           },
  { testGetCharINIValid,                         "testGetCharINIValid"                       },
  { testSetStrININilINI,                         "testSetStrININilINI"                       },
  { testSetStrININilSection,                     "testSetStrININilSection"                   },
  { testSetStrININilKey,                         "testSetStrININilKey"                       },
  { testSetStrINIInvalidGrammerSection,          "testSetStrINIInvalidGrammerSection"        },
  { testSetStrINIInvalidGrammerKey,              "testSetStrINIInvalidGrammerKey"            },
  { testSetStrINIValidSetting,                   "testSetStrINIValidSetting"                 },
  { testSetStrINIValidOverwriteSetting,          "testSetStrINIValidOverwriteSetting"        },
  { testGetStrININilINI,                         "testGetStrININilINI"                       },
  { testGetStrININilSection,                     "testGetStrININilSection"                   },
  { testGetStrININilKey,                         "testGetStrININilKey"                       },
  { testGetStrININilValue,                       "testGetStrININilValue"                     },
  { testGetStrINIInvalidGrammerSection,          "testGetStrINIInvalidGrammerSection"        },
  { testGetStrINIInvalidGrammerKey,              "testGetStrINIInvalidGrammerKey"            },
  { testGetStrININonPresentKey,                  "testGetStrININonPresentKey"                },
  { testGetStrININonPresentSection,              "testGetStrININonPresentSection"            },
  { testGetStrINIValid,                          "testGetStrINIValid"                        },
  { testSetIntArrININilINI,                      "testSetIntArrININilINI"                    },
  { testSetIntArrININilSection,                  "testSetIntArrININilSection"                },
  { testSetIntArrININilKey,                      "testSetIntArrININilKey"                    },
  { testSetIntArrINIInvalidGrammerSection,       "testSetIntArrINIInvalidGrammerSection"     },
  { testSetIntArrINIInvalidGrammerKey,           "testSetIntArrINIInvalidGrammerKey"         },
  { testSetIntArrINIValidSetting,                "testSetIntArrINIValidSetting"              },
  { testSetIntArrINIValidOverwriteSetting,       "testSetIntArrINIValidOverwriteSetting"     },
  { testGetIntArrININilINI,                      "testGetIntArrININilINI"                    },
  { testGetIntArrININilSection,                  "testGetIntArrININilSection"                },
  { testGetIntArrININilKey,                      "testGetIntArrININilKey"                    },
  { testGetIntArrININilValue,                    "testGetIntArrININilValue"                  },
  { testGetIntArrINIInvalidGrammerSection,       "testGetIntArrINIInvalidGrammerSection"     },
  { testGetIntArrINIInvalidGrammerKey,           "testGetIntArrINIInvalidGrammerKey"         },
  { testGetIntArrININonPresentKey,               "testGetIntArrININonPresentKey"             },
  { testGetIntArrININonPresentSection,           "testGetIntArrININonPresentSection"         },
  { testGetIntArrINIValid,                       "testGetIntArrINIValid"                     },
  { testSetFloatArrININilINI,                    "testSetFloatArrININilINI"                  },
  { testSetFloatArrININilSection,                "testSetFloatArrININilSection"              },
  { testSetFloatArrININilKey,                    "testSetFloatArrININilKey"                  },
  { testSetFloatArrINIInvalidGrammerSection,     "testSetFloatArrINIInvalidGrammerSection"   },
  { testSetFloatArrINIInvalidGrammerKey,         "testSetFloatArrINIInvalidGrammerKey"       },
  { testSetFloatArrINIValidSetting,              "testSetFloatArrINIValidSetting"            },
  { testSetFloatArrINIValidOverwriteSetting,     "testSetFloatArrINIValidOverwriteSetting"   },
  { testGetFloatArrININilINI,                    "testGetFloatArrININilINI"                  },
  { testGetFloatArrININilSection,                "testGetFloatArrININilSection"              },
  { testGetFloatArrININilKey,                    "testGetFloatArrININilKey"                  },
  { testGetFloatArrININilValue,                  "testGetFloatArrININilValue"                },
  { testGetFloatArrINIInvalidGrammerSection,     "testGetFloatArrINIInvalidGrammerSection"   },
  { testGetFloatArrINIInvalidGrammerKey,         "testGetFloatArrINIInvalidGrammerKey"       },
  { testGetFloatArrININonPresentKey,             "testGetFloatArrININonPresentKey"           },
  { testGetFloatArrININonPresentSection,         "testGetFloatArrININonPresentSection"       },
  { testGetFloatArrINIValid,                     "testGetFloatArrINIValid"                   },
  { testSetBoolArrININilINI,                     "testSetBoolArrININilINI"                   },
  { testSetBoolArrININilSection,                 "testSetBoolArrININilSection"               },
  { testSetBoolArrININilKey,                     "testSetBoolArrININilKey"                   },
  { testSetBoolArrINIInvalidGrammerSection,      "testSetBoolArrINIInvalidGrammerSection"    },
  { testSetBoolArrINIInvalidGrammerKey,          "testSetBoolArrINIInvalidGrammerKey"        },
  { testSetBoolArrINIValidSetting,               "testSetBoolArrINIValidSetting"             },
  { testSetBoolArrINIValidOverwriteSetting,      "testSetBoolArrINIValidOverwriteSetting"    },
  { testGetBoolArrININilINI,                     "testGetBoolArrININilINI"                   },
  { testGetBoolArrININilSection,                 "testGetBoolArrININilSection"               },
  { testGetBoolArrININilKey,                     "testGetBoolArrININilKey"                   },
  { testGetBoolArrININilValue,                   "testGetBoolArrININilValue"                 },
  { testGetBoolArrINIInvalidGrammerSection,      "testGetBoolArrINIInvalidGrammerSection"    },
  { testGetBoolArrINIInvalidGrammerKey,          "testGetBoolArrINIInvalidGrammerKey"        },
  { testGetBoolArrININonPresentKey,              "testGetBoolArrININonPresentKey"            },
  { testGetBoolArrININonPresentSection,          "testGetBoolArrININonPresentSection"        },
  { testGetBoolArrINIValid,                      "testGetBoolArrINIValid"                    },
  { testSetCharArrININilINI,                     "testSetCharArrININilINI"                   },
  { testSetCharArrININilSection,                 "testSetCharArrININilSection"               },
  { testSetCharArrININilKey,                     "testSetCharArrININilKey"                   },
  { testSetCharArrINIInvalidGrammerSection,      "testSetCharArrINIInvalidGrammerSection"    },
  { testSetCharArrINIInvalidGrammerKey,          "testSetCharArrINIInvalidGrammerKey"        },
  { testSetCharArrINIValidSetting,               "testSetCharArrINIValidSetting"             },
  { testSetCharArrINIValidOverwriteSetting,      "testSetCharArrINIValidOverwriteSetting"    },
  { testGetCharArrININilINI,                     "testGetCharArrININilINI"                   },
  { testGetCharArrININilSection,                 "testGetCharArrININilSection"               },
  { testGetCharArrININilKey,                     "testGetCharArrININilKey"                   },
  { testGetCharArrININilValue,                   "testGetCharArrININilValue"                 },
  { testGetCharArrINIInvalidGrammerSection,      "testGetCharArrINIInvalidGrammerSection"    },
  { testGetCharArrINIInvalidGrammerKey,          "testGetCharArrINIInvalidGrammerKey"        },
  { testGetCharArrININonPresentKey,              "testGetCharArrININonPresentKey"            },
  { testGetCharArrININonPresentSection,          "testGetCharArrININonPresentSection"        },
  { testGetCharArrINIValid,                      "testGetCharArrINIValid"                    },
  { testSetStrArrININilINI,                      "testSetStrArrININilINI"                    },
  { testSetStrArrININilSection,                  "testSetStrArrININilSection"                },
  { testSetStrArrININilKey,                      "testSetStrArrININilKey"                    },
  { testSetStrArrINIInvalidGrammerSection,       "testSetStrArrINIInvalidGrammerSection"     },
  { testSetStrArrINIInvalidGrammerKey,           "testSetStrArrINIInvalidGrammerKey"         },
  { testSetStrArrINIValidSetting,                "testSetStrArrINIValidSetting"              },
  { testSetStrArrINIValidOverwriteSetting,       "testSetStrArrINIValidOverwriteSetting"     },
  { testGetStrArrININilINI,                      "testGetStrArrININilINI"                    },
  { testGetStrArrININilSection,                  "testGetStrArrININilSection"                },
  { testGetStrArrININilKey,                      "testGetStrArrININilKey"                    },
  { testGetStrArrININilValue,                    "testGetStrArrININilValue"                  },
  { testGetStrArrINIInvalidGrammerSection,       "testGetStrArrINIInvalidGrammerSection"     },
  { testGetStrArrINIInvalidGrammerKey,           "testGetStrArrINIInvalidGrammerKey"         },
  { testGetStrArrININonPresentKey,               "testGetStrArrININonPresentKey"             },
  { testGetStrArrININonPresentSection,           "testGetStrArrININonPresentSection"         },
  { testGetStrArrINIValid,                       "testGetStrArrINIValid"                     },
  { testDeleteININilINI,                         "testDeleteININilINI"                       },
  { testDeleteININilSection,                     "testDeleteININilSection"                   },
  { testDeleteININilKey,                         "testDeleteININilKey"                       },
  { testDeleteINIInvalidGrammerSection,          "testDeleteINIInvalidGrammerSection"        },
  { testDeleteINIInvalidGrammerKey,              "testDeleteINIInvalidGrammerKey"            },
  { testDeleteININonPresentSection,              "testDeleteININonPresentSection"            },
  { testDeleteININonPresentKey,                  "testDeleteININonPresentKey"                },
  { testDeleteINIValid,                          "testDeleteINIValid"                        },
  { testCompleteIOFlow,                          "testCompleteIOFlow"                        },
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
    fflush(stdout); // so if segfault/crash we know last successful test
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
