/******************************************************************************
 * FILE:    testINI.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  7/8/17                                                            *
 * INFO:    Test file for implementation of the interface located in ini.h.   *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <ini.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 162

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
testResultINI_t testStrErrINI_OPEN_FAILURE() {
  return (strcmp(strErrINI(INI_OPEN_FAILURE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_CLOSE_FAILURE() {
  return (strcmp(strErrINI(INI_CLOSE_FAILURE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_OUT_OF_MEMORY() {
  return (strcmp(strErrINI(INI_OUT_OF_MEMORY), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_TYPE_MISMATCH() {
  return (strcmp(strErrINI(INI_TYPE_MISMATCH), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_DUPLICATE_SETTING() {
  return (strcmp(strErrINI(INI_DUPLICATE_SETTING), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_CONF() {
  return (strcmp(strErrINI(INI_INVALID_CONF), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_KEY() {
  return (strcmp(strErrINI(INI_INVALID_KEY), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_VALUE() {
  return (strcmp(strErrINI(INI_INVALID_VALUE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_SECTION() {
  return (strcmp(strErrINI(INI_INVALID_SECTION), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_INDEX() {
  return (strcmp(strErrINI(INI_INVALID_INDEX), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_INVALID_OPTIONS() {
  return (strcmp(strErrINI(INI_INVALID_OPTIONS), "")) ? INI_PASS : INI_FAIL;
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

testResultINI_t testStrErrINI_NIL_VALUE() {
  return (strcmp(strErrINI(INI_NIL_VALUE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_SECTION() {
  return (strcmp(strErrINI(INI_NIL_SECTION), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_OPTIONS() {
  return (strcmp(strErrINI(INI_NIL_OPTIONS), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_SETTING() {
  return (strcmp(strErrINI(INI_NIL_SETTING), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_TYPE() {
  return (strcmp(strErrINI(INI_NIL_TYPE), "")) ? INI_PASS : INI_FAIL;
}

testResultINI_t testStrErrINI_NIL_LENGTH() {
  return (strcmp(strErrINI(INI_NIL_LENGTH), "")) ? INI_PASS : INI_FAIL;
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

testResultINI_t testGetConfigurationNilINI() {
  option_t options;

  errINI_t errINI = getConfigurationINI(NULL, &options);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetConfigurationNilOptions() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = getConfigurationINI(ini, NULL);
  return (errINI == INI_NIL_OPTIONS) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetConfigurationValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  option_t options;

  errINI = getConfigurationINI(ini, &options);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetConfigurationNilINI() {
  errINI_t errINI = setConfigurationINI(NULL, SETTING_SEPERATOR);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetConfigurationInvalidOptions() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  option_t options = 0b10000001;

  errINI = setConfigurationINI(ini, options);
  return (errINI == INI_INVALID_OPTIONS) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetConfigurationValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  option_t options = 0;

  errINI = setConfigurationINI(ini, options);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingNilINI() {
  setting_t *setting;

  errINI_t errINI = createSetting(NULL, "section", "key", &setting);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingNilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, NULL, "key", &setting);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingNilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", NULL, &setting);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingNilSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = createSetting(ini, "section", "key", NULL);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingInvalidSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "sec tion", "key", &setting);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingInvalidKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "ke y", &setting);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingDuplicateSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = createSetting(ini, "section", "key", &setting);
  return (errINI == INI_DUPLICATE_SETTING) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testCreateSettingOutOfMemory() {}

testResultINI_t testCreateSettingValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  return (errINI == INI_NIL && setting) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingNilINI() {
  setting_t *setting;

  errINI_t errINI = lookupSetting(NULL, "section", "key", &setting);
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingNilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, NULL, "key", &setting);
  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingNilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "section", NULL, &setting);
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingNilSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = lookupSetting(ini, "section", "key", NULL);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingInvalidSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "sec tion", "key", &setting);
  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingInvalidKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "section", "k ey", &setting);
  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupNonPresentSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "section", "key", &setting);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = lookupSetting(ini, "section", "key", &setting);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingNilINI() {
  errINI_t errINI = deleteSetting(NULL, "section", "key");
  return  (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingNilSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, NULL, "key");
  return  (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingNilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "section", NULL);
  return  (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "sec tion", "key");
  return  (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "section", "ke y");
  return  (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingNonPresentSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "nowhere", "key");
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "section", "key");
  return  (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingLookupDeleted() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "section", "key");
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = lookupSetting(ini, "section", "key", &setting);
  return  (errINI == INI_NIL && !setting) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingCompleteFlow() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting1;

  errINI = createSetting(ini, "section", "key", &setting1);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting2;

  errINI = lookupSetting(ini, "section", "key", &setting2);
  if(errINI != INI_NIL) { return INI_FAIL; }

  if(setting1 != setting2) { return INI_FAIL; }

  errINI = deleteSetting(ini, "section", "key");
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingTypeNilSettings() {                          /*********TODO: rest of tests**************/
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingTypeNilType() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_TYPE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingTypeValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyLengthNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyLengthNilLength() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_LENGTH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyLengthValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyNilKey() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingLengthNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingLengthNilLength() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_LENGTH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingLengthValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthNilLength() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_LENGTH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetStringOutOfMemory() {}

testResultINI_t testSettingSetStringValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetIntElemOutOfMemory() {}

testResultINI_t testSettingSetIntElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetFloatElemOutOfMemory() {}

testResultINI_t testSettingSetFloatElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetBoolElemOutOfMemory() {}

testResultINI_t testSettingSetBoolElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetCharElemOutOfMemory() {}

testResultINI_t testSettingSetCharElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemNilSetting() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemTypeMismatch() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemInvalidIndex() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemNilValue() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetStringElemOutOfMemory() {}

testResultINI_t testSettingSetStringElemValid() {
  errINI_t errINI = INI_NIL_INI;
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
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
  { testStrErrINI_OPEN_FAILURE,             "testStrErrINI_OPEN_FAILURE"              },
  { testStrErrINI_CLOSE_FAILURE,            "testStrErrINI_CLOSE_FAILURE"             },
  { testStrErrINI_OUT_OF_MEMORY,            "testStrErrINI_OUT_OF_MEMORY"             },
  { testStrErrINI_TYPE_MISMATCH,            "testStrErrINI_TYPE_MISMATCH"             },
  { testStrErrINI_DUPLICATE_SETTING,        "testStrErrINI_DUPLICATE_SETTING"         },
  { testStrErrINI_INVALID_CONF,             "testStrErrINI_INVALID_CONF"              },
  { testStrErrINI_INVALID_KEY,              "testStrErrINI_INVALID_KEY"               },
  { testStrErrINI_INVALID_VALUE,            "testStrErrINI_INVALID_VALUE"             },
  { testStrErrINI_INVALID_SECTION,          "testStrErrINI_INVALID_SECTION"           },
  { testStrErrINI_INVALID_INDEX,            "testStrErrINI_INVALID_INDEX"             },
  { testStrErrINI_INVALID_OPTIONS,          "testStrErrINI_INVALID_OPTIONS"           },
  { testStrErrINI_NIL_FNAME,                "testStrErrINI_NIL_FNAME"                 },
  { testStrErrINI_NIL_INI,                  "testStrErrINI_NIL_INI"                   },
  { testStrErrINI_NIL_KEY,                  "testStrErrINI_NIL_KEY"                   },
  { testStrErrINI_NIL_VALUE,                "testStrErrINI_NIL_VALUE"                 },
  { testStrErrINI_NIL_SECTION,              "testStrErrINI_NIL_SECTION"               },
  { testStrErrINI_NIL_OPTIONS,              "testStrErrINI_NIL_OPTIONS"               },
  { testStrErrINI_NIL_SETTING,              "testStrErrINI_NIL_SETTING"               },
  { testStrErrINI_NIL_TYPE,                 "testStrErrINI_NIL_TYPE"                  },
  { testStrErrINI_NIL_LENGTH,               "testStrErrINI_NIL_LENGTH"                },
  { testStrErrINI_NIL,                      "testStrErrINI_NIL"                       },
  { testMakeININilINI,                      "testMakeININilINI"                       },
//  { testMakeINIOutOfMemory,                 "testMakeINIOutOfMemory"                  }, 
  { testMakeINIValid,                       "testMakeINIValid"                        },
  { testFreeININilINI,                      "testFreeININilINI"                       },
  { testFreeINIValid,                       "testFreeINIValid"                        },
  { testReadININilINI,                      "testReadININilINI"                       },
  { testReadININilFname,                    "testReadININilFname"                     },
  { testReadINIInvalidSection,              "testReadINIInvalidSection"               },
  { testReadINIInvalidKey,                  "testReadINIInvalidKey"                   },
  { testReadINIInvalidArrayComma,           "testReadINIInvalidArrayComma"            },
  { testReadINIInvalidArrayType,            "testReadINIInvalidArrayType"             },
  { testReadINIInvalidString,               "testReadINIInvalidString"                },
  { testReadINIValid,                       "testReadINIValid"                        },
  { testWriteININilINI,                     "testWriteININilINI"                      },
  { testWriteININilFileName,                "testWriteININilFileName"                 },
  { testWriteINIOpenFailure,                "testWriteINIOpenFailure"                 },
//  { testWriteINICloseFailure,               "testWriteINICloseFailure"                },
  { testWriteINIValid,                      "testWriteINIValid"                       },
  { testGetConfigurationNilINI,             "testGetConfigurationNilINI"              },
  { testGetConfigurationNilOptions,         "testGetConfigurationNilOptions"          },
  { testGetConfigurationValid,              "testGetConfigurationValid"               },
  { testSetConfigurationNilINI,             "testSetConfigurationNilINI"              },
  { testSetConfigurationInvalidOptions,     "testSetConfigurationInvalidOptions"      },
  { testSetConfigurationValid,              "testSetConfigurationValid"               },
  { testCreateSettingNilINI,                "testCreateSettingNilINI"                 },
  { testCreateSettingNilSection,            "testCreateSettingNilSection"             },
  { testCreateSettingNilKey,                "testCreateSettingNilKey"                 },
  { testCreateSettingNilSetting,            "testCreateSettingNilSetting"             },
  { testCreateSettingInvalidSection,        "testCreateSettingInvalidSection"         },
  { testCreateSettingInvalidKey,            "testCreateSettingInvalidKey"             },
  { testCreateSettingDuplicateSetting,      "testCreateSettingDuplicateSetting"       },
//  { testCreateSettingOutOfMemory,           "testCreateSettingOutOfMemory"            },
  { testCreateSettingValid,                 "testCreateSettingValid"                  },
  { testLookupSettingNilINI,                "testLookupSettingNilINI"                 },
  { testLookupSettingNilSection,            "testLookupSettingNilSection"             },
  { testLookupSettingNilKey,                "testLookupSettingNilKey"                 },
  { testLookupSettingNilSetting,            "testLookupSettingNilSetting"             },
  { testLookupSettingInvalidSection,        "testLookupSettingInvalidSection"         },
  { testLookupSettingInvalidKey,            "testLookupSettingInvalidKey"             },
  { testLookupNonPresentSetting,            "testLookupNonPresentSetting"             },
  { testLookupSettingValid,                 "testLookupSettingValid"                  },
  { testDeleteSettingNilINI,                "testDeleteSettingNilINI"                 },
  { testDeleteSettingNilSection,            "testDeleteSettingNilSection"             },
  { testDeleteSettingNilKey,                "testDeleteSettingNilKey"                 },
  { testDeleteSettingInvalidGrammerSection, "testDeleteSettingInvalidGrammerSection"  },
  { testDeleteSettingInvalidGrammerKey,     "testDeleteSettingInvalidGrammerKey"      },
  { testDeleteSettingNonPresentSetting,     "testDeleteSettingNonPresentSetting"      },
  { testDeleteSettingValid,                 "testDeleteSettingValid"                  },
  { testSettingLookupDeleted,               "testSettingLookupDeleted"                },
  { testSettingCompleteFlow,                "testSettingCompleteFlow"                 },
  { testSettingTypeNilSettings,             "testSettingTypeNilSettings"              },
  { testSettingTypeNilType,                 "testSettingTypeNilType"                  },
  { testSettingTypeValid,                   "testSettingTypeValid"                    },
  { testSettingKeyLengthNilSetting,         "testSettingKeyLengthNilSetting"          },
  { testSettingKeyLengthNilLength,          "testSettingKeyLengthNilLength"           },
  { testSettingKeyLengthValid,              "testSettingKeyLengthValid"               },
  { testSettingKeyNilSetting,               "testSettingKeyNilSetting"                },
  { testSettingKeyNilKey,                   "testSettingKeyNilKey"                    },
  { testSettingKeyValid,                    "testSettingKeyValid"                     },
  { testSettingLengthNilSetting,            "testSettingLengthNilSetting"             },
  { testSettingLengthNilLength,             "testSettingLengthNilLength"              },
  { testSettingLengthValid,                 "testSettingLengthValid"                  },
  { testSettingElemLengthNilSetting,        "testSettingElemLengthNilSetting"         },
  { testSettingElemLengthNilLength,         "testSettingElemLengthNilLength"          },
  { testSettingElemLengthTypeMismatch,      "testSettingElemLengthTypeMismatch"       },
  { testSettingElemLengthInvalidIndex,      "testSettingElemLengthInvalidIndex"       },
  { testSettingElemLengthValid,             "testSettingElemLengthValid"              },
  { testSettingGetIntNilSetting,            "testSettingGetIntNilSetting"             },
  { testSettingGetIntTypeMismatch,          "testSettingGetIntTypeMismatch"           },
  { testSettingGetIntNilValue,              "testSettingGetIntNilValue"               },
  { testSettingGetIntValid,                 "testSettingGetIntValid"                  },
  { testSettingGetFloatNilSetting,          "testSettingGetFloatNilSetting"           },
  { testSettingGetFloatTypeMismatch,        "testSettingGetFloatTypeMismatch"         },
  { testSettingGetFloatNilValue,            "testSettingGetFloatNilValue"             },
  { testSettingGetFloatValid,               "testSettingGetFloatValid"                },
  { testSettingGetBoolNilSetting,           "testSettingGetBoolNilSetting"            },
  { testSettingGetBoolTypeMismatch,         "testSettingGetBoolTypeMismatch"          },
  { testSettingGetBoolNilValue,             "testSettingGetBoolNilValue"              },
  { testSettingGetBoolValid,                "testSettingGetBoolValid"                 },
  { testSettingGetCharNilSetting,           "testSettingGetCharNilSetting"            },
  { testSettingGetCharTypeMismatch,         "testSettingGetCharTypeMismatch"          },
  { testSettingGetCharNilValue,             "testSettingGetCharNilValue"              },
  { testSettingGetCharValid,                "testSettingGetCharValid"                 },
  { testSettingGetStringNilSetting,         "testSettingGetStringNilSetting"          },
  { testSettingGetStringTypeMismatch,       "testSettingGetStringTypeMismatch"        },
  { testSettingGetStringNilValue,           "testSettingGetStringNilValue"            },
  { testSettingGetStringValid,              "testSettingGetStringValid"               },
  { testSettingGetIntElemNilSetting,        "testSettingGetIntElemNilSetting"         },
  { testSettingGetIntElemTypeMismatch,      "testSettingGetIntElemTypeMismatch"       },
  { testSettingGetIntElemInvalidIndex,      "testSettingGetIntElemInvalidIndex"       },
  { testSettingGetIntElemNilValue,          "testSettingGetIntElemNilValue"           },
  { testSettingGetIntElemValid,             "testSettingGetIntElemValid"              },
  { testSettingGetFloatElemNilSetting,      "testSettingGetFloatElemNilSetting"       },
  { testSettingGetFloatElemTypeMismatch,    "testSettingGetFloatElemTypeMismatch"     },
  { testSettingGetFloatElemInvalidIndex,    "testSettingGetFloatElemInvalidIndex"     },
  { testSettingGetFloatElemNilValue,        "testSettingGetFloatElemNilValue"         },
  { testSettingGetFloatElemValid,           "testSettingGetFloatElemValid"            },
  { testSettingGetBoolElemNilSetting,       "testSettingGetBoolElemNilSetting"        },
  { testSettingGetBoolElemTypeMismatch,     "testSettingGetBoolElemTypeMismatch"      },
  { testSettingGetBoolElemInvalidIndex,     "testSettingGetBoolElemInvalidIndex"      },
  { testSettingGetBoolElemNilValue,         "testSettingGetBoolElemNilValue"          },
  { testSettingGetBoolElemValid,            "testSettingGetBoolElemValid"             },
  { testSettingGetCharElemNilSetting,       "testSettingGetCharElemNilSetting"        },
  { testSettingGetCharElemTypeMismatch,     "testSettingGetCharElemTypeMismatch"      },
  { testSettingGetCharElemInvalidIndex,     "testSettingGetCharElemInvalidIndex"      },
  { testSettingGetCharElemNilValue,         "testSettingGetCharElemNilValue"          },
  { testSettingGetCharElemValid,            "testSettingGetCharElemValid"             },
  { testSettingGetStringElemNilSetting,     "testSettingGetStringElemNilSetting"      },
  { testSettingGetStringElemTypeMismatch,   "testSettingGetStringElemTypeMismatch"    },
  { testSettingGetStringElemInvalidIndex,   "testSettingGetStringElemInvalidIndex"    },
  { testSettingGetStringElemNilValue,       "testSettingGetStringElemNilValue"        },
  { testSettingGetStringElemValid,          "testSettingGetStringElemValid"           },
  { testSettingSetIntNilSetting,            "testSettingSetIntNilSetting"             },
  { testSettingSetIntTypeMismatch,          "testSettingSetIntTypeMismatch"           },
  { testSettingSetIntValid,                 "testSettingSetIntValid"                  },
  { testSettingSetFloatNilSetting,          "testSettingSetFloatNilSetting"           },
  { testSettingSetFloatTypeMismatch,        "testSettingSetFloatTypeMismatch"         },
  { testSettingSetBoolNilSetting,           "testSettingSetBoolNilSetting"            },
  { testSettingSetBoolTypeMismatch,         "testSettingSetBoolTypeMismatch"          },
  { testSettingSetCharNilSetting,           "testSettingSetCharNilSetting"            },
  { testSettingSetCharTypeMismatch,         "testSettingSetCharTypeMismatch"          },
  { testSettingSetStringNilSetting,         "testSettingSetStringNilSetting"          },
  { testSettingSetStringTypeMismatch,       "testSettingSetStringTypeMismatch"        },
  { testSettingSetStringNilValue,           "testSettingSetStringNilValue"            },
//  { testSettingSetStringOutOfMemory,        "testSettingSetStringOutOfMemory"         },
  { testSettingSetIntElemNilSetting,        "testSettingSetIntElemNilSetting"         },
  { testSettingSetIntElemTypeMismatch,      "testSettingSetIntElemTypeMismatch"       },
  { testSettingSetIntElemInvalidIndex,      "testSettingSetIntElemInvalidIndex"       },
//  { testSettingSetIntElemOutOfMemory,       "testSettingSetIntElemOutOfMemory"        },
  { testSettingSetFloatElemNilSetting,      "testSettingSetFloatElemNilSetting"       },
  { testSettingSetFloatElemTypeMismatch,    "testSettingSetFloatElemTypeMismatch"     },
  { testSettingSetFloatElemInvalidIndex,    "testSettingSetFloatElemInvalidIndex"     },
//  { testSettingSetFloatElemOutOfMemory,     "testSettingSetFloatElemOutOfMemory"      },
  { testSettingSetBoolElemNilSetting,       "testSettingSetBoolElemNilSetting"        },
  { testSettingSetBoolElemTypeMismatch,     "testSettingSetBoolElemTypeMismatch"      },
  { testSettingSetBoolElemInvalidIndex,     "testSettingSetBoolElemInvalidIndex"      },
//  { testSettingSetBoolElemOutOfMemory,      "testSettingSetBoolElemOutOfMemory"       },
  { testSettingSetBoolElemValid,            "testSettingSetBoolElemValid"             },
  { testSettingSetCharElemNilSetting,       "testSettingSetCharElemNilSetting"        },
  { testSettingSetCharElemTypeMismatch,     "testSettingSetCharElemTypeMismatch"      },
  { testSettingSetCharElemInvalidIndex,     "testSettingSetCharElemInvalidIndex"      },
//  { testSettingSetCharElemOutOfMemory,      "testSettingSetCharElemOutOfMemory"       },
  { testSettingSetCharElemValid,            "testSettingSetCharElemValid"             },
  { testSettingSetStringElemNilSetting,     "testSettingSetStringElemNilSetting"      },
  { testSettingSetStringElemTypeMismatch,   "testSettingSetStringElemTypeMismatch"    },
  { testSettingSetStringElemInvalidIndex,   "testSettingSetStringElemInvalidIndex"    },
  { testSettingSetStringElemNilValue,       "testSettingSetStringElemNilValue"        },
//  { testSettingSetStringElemOutOfMemory,    "testSettingSetStringElemOutOfMemory"     },
  { testSettingSetStringElemValid,          "testSettingSetStringElemValid"           },
  { testCompleteIOFlow,                     "testCompleteIOFlow"                      }
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
