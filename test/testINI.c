/******************************************************************************
 * FILE:    testINI.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  7/15/17                                                           *
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
#define TOTAL_TESTS 188

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
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testMakeINIOutOfMemory() {} // cannot test

testResultINI_t testMakeINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testFreeININilINI() {
  errINI_t errINI = freeINI(NULL);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testFreeINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = freeINI(ini);
  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadININilINI() {
  errINI_t errINI = readINI(NULL, "fname");
  return (errINI == INI_NIL_INI) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadININilFname() {
  ini_t *ini;

  errINI_t errINI = readINI(&ini, NULL);
  return (errINI == INI_NIL_FNAME) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadINIOpenFailure() {
  ini_t *ini;

  errINI_t errINI = readINI(&ini, "doesNotExist.txt");
  return (errINI == INI_OPEN_FAILURE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadININilSection() {
  char *_ini = "[]\n"
               "key=5\n";

  char *tmpfile = "testReadININilSection.txt";
  FILE *fp;

  if(!(fp = fopen(tmpfile, "w"))) { return INI_FAIL; }
  fprintf(fp, "%s", _ini);
  fclose(fp);

  ini_t *ini;

  errINI_t errINI = readINI(&ini, tmpfile);

  if(remove(tmpfile)) { return INI_FAIL; }

  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadINIInvalidSection() {
  char *_ini = "[test Section 1]\n"
               "string=\"foobarber\"\n";

  char *tmpfile = "testReadINIInvalidSection.txt";
  FILE *fp;

  if(!(fp = fopen(tmpfile, "w"))) { return INI_FAIL; }
  fprintf(fp, "%s", _ini);
  fclose(fp);

  ini_t *ini;

  errINI_t errINI = readINI(&ini, tmpfile);

  if(remove(tmpfile)) { return INI_FAIL; }

  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadININilKey() {
  char *_ini = "[Section]\n"
               "=5\n";

  char *tmpfile = "testReadININilKey.txt";
  FILE *fp;

  if(!(fp = fopen(tmpfile, "w"))) { return INI_FAIL; }
  fprintf(fp, "%s", _ini);
  fclose(fp);

  ini_t *ini;

  errINI_t errINI = readINI(&ini, tmpfile);

  if(remove(tmpfile)) { return INI_FAIL; }

  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadINIInvalidKey() {
  char *_ini = "[testSection1]\n"
               "floating point=19.45\n";

  char *tmpfile = "testReadINIInvalidKey.txt";
  FILE *fp;

  if(!(fp = fopen(tmpfile, "w"))) { return INI_FAIL; }
  fprintf(fp, "%s", _ini);
  fclose(fp);

  ini_t *ini;

  errINI_t errINI = readINI(&ini, tmpfile);

  if(remove(tmpfile)) { return INI_FAIL; }

  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testReadINIInvalidArrayComma() { // TODO
  return INI_FAIL;
}

testResultINI_t testReadINIInvalidArrayType() { // TODO
  return INI_FAIL;
}

// NOTE: this also acts like invalid char/bool too!
testResultINI_t testReadINIInvalidString() { // TODO
  return INI_FAIL;
}

testResultINI_t testReadINIValid() {
  char *_ini = "[testSection1]\n"
               "integer=5\n"
               "floating point=19.45\n"
               "boolean=true\n"
               "character='r'\n"
               "string=\"foobarber\"\n";

  char *tmpfile = "testReadINIValid.txt";
  FILE *fp;

  if(!(fp = fopen(tmpfile, "w"))) { return INI_FAIL; }
  fprintf(fp, "%s", _ini);
  fclose(fp);

  ini_t *ini;

  errINI_t errINI = readINI(&ini, tmpfile);

  if(remove(tmpfile)) { return INI_FAIL; }

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
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

  freeINI(ini);

  return (errINI == INI_NIL_FNAME) ? INI_PASS : INI_FAIL;
}

testResultINI_t testWriteINIOpenFailure() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = writeINI(ini, "invalid/0foo.txt");

  freeINI(ini);

  return (errINI == INI_OPEN_FAILURE) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testWriteINICloseFailure() { } // cannot test

testResultINI_t testWriteINIValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = writeINI(ini, "testINI.txt");
  if(errINI != INI_NIL) { return INI_FAIL; }

  freeINI(ini);

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

  freeINI(ini);

  return (errINI == INI_NIL_OPTIONS) ? INI_PASS : INI_FAIL;
}

testResultINI_t testGetConfigurationValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  option_t options;

  errINI = getConfigurationINI(ini, &options);

  freeINI(ini);

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

  freeINI(ini);

  return (errINI == INI_INVALID_OPTIONS) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSetConfigurationValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  option_t options = 0;

  errINI = setConfigurationINI(ini, options);

  freeINI(ini);

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

  freeINI(ini);

  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingNilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", NULL, &setting);

  freeINI(ini);

  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingNilSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = createSetting(ini, "section", "key", NULL);

  freeINI(ini);

  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingInvalidSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "sec tion", "key", &setting);

  freeINI(ini);

  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testCreateSettingInvalidKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "ke y", &setting);

  freeINI(ini);

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

  freeINI(ini);

  return (errINI == INI_DUPLICATE_SETTING) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testCreateSettingOutOfMemory() {}

testResultINI_t testCreateSettingValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);

  freeINI(ini);

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

  freeINI(ini);

  return (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingNilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "section", NULL, &setting);

  freeINI(ini);

  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingNilSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = lookupSetting(ini, "section", "key", NULL);

  freeINI(ini);

  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingInvalidSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "sec tion", "key", &setting);

  freeINI(ini);

  return (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupSettingInvalidKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "section", "k ey", &setting);

  freeINI(ini);

  return (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testLookupNonPresentSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = lookupSetting(ini, "section", "key", &setting);

  freeINI(ini);

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

  freeINI(ini);

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

  freeINI(ini);

  return  (errINI == INI_NIL_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingNilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "section", NULL);

  freeINI(ini);

  return  (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingInvalidGrammerSection() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "sec tion", "key");

  freeINI(ini);

  return  (errINI == INI_INVALID_SECTION) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingInvalidGrammerKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "section", "ke y");

  freeINI(ini);

  return  (errINI == INI_INVALID_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testDeleteSettingNonPresentSetting() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = deleteSetting(ini, "nowhere", "key");

  freeINI(ini);

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

  freeINI(ini);

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

  freeINI(ini);

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

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingTypeNilSettings() {
  typeINI_t typeINI;

  errINI_t errINI = settingType(NULL, &typeINI);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingTypeNilType() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_TYPE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingTypeValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  typeINI_t typeINI;

  errINI = settingType(setting, &typeINI);

  freeINI(ini);

  return (errINI == INI_NIL && typeINI == UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyLengthNilSetting() {
  int len;

  errINI_t errINI = settingKeyLength(NULL, &len);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyLengthNilLength() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingKeyLength(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_LENGTH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyLengthValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int len;

  errINI = settingKeyLength(setting, &len);

  freeINI(ini);

  return (errINI == INI_NIL && len == 3) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyNilSetting() {
  char keycpy[5];

  errINI_t errINI = settingKey(NULL, keycpy);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyNilKey() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingKey(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_KEY) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingKeyValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int len;

  errINI = settingKeyLength(setting, &len);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char keycpy[len];

  errINI = settingKey(setting, keycpy); 

  freeINI(ini);

  return (errINI == INI_NIL && !strncmp(keycpy, "key", 3)) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingLengthNilSetting() {
  int len;

  errINI_t errINI = settingLength(NULL, &len);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingLengthNilLength() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingLength(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_LENGTH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingLengthValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int len;

  errINI = settingLength(setting, &len);

  freeINI(ini);

  return (errINI == INI_NIL && !len) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthNilSetting() {
  int len;

  errINI_t errINI = settingElemLength(NULL, 0, &len);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthNilLength() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingElemLength(setting, 0, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_LENGTH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int len;

  errINI = settingElemLength(setting, -1, &len);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int len;

  errINI = settingElemLength(setting, 0, &len);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingElemLengthValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetStringElem(setting, 0, "string");
  if(errINI != INI_NIL) { return INI_FAIL; }

  int len;

  errINI = settingElemLength(setting, 0, &len);

  freeINI(ini);

  return (errINI == INI_NIL && len == 6) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntNilSetting() {
  errINI_t errINI = settingSetInt(NULL, 0);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBool(setting, 0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 0);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 0);

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatNilSetting() {
  errINI_t errINI = settingSetFloat(NULL, 8.90);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetChar(setting, 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloat(setting, 0.0);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloat(setting, 5.34);

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolNilSetting() {
  errINI_t errINI = settingSetBool(NULL, 1);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetChar(setting, 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBool(setting, 0);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolInvalidValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBool(setting, 3);

  freeINI(ini);

  return (errINI == INI_INVALID_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBool(setting, 1);

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharNilSetting() {
  errINI_t errINI = settingSetChar(NULL, 'g');
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 90);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetChar(setting, 'f');

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetChar(setting, 'f');

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringNilSetting() {
  errINI_t errINI = settingSetString(NULL, "g");
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 90);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetString(setting, "f");

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetString(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetStringOutOfMemory() {}

testResultINI_t testSettingSetStringValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetString(setting, "f");

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}
                                
testResultINI_t testSettingSetIntElemNilSetting() {
  errINI_t errINI = settingSetIntElem(NULL, 0, 10);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 90);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 10);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetIntElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 1, 10);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetIntElemOutOfMemory() {}

testResultINI_t testSettingSetIntElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 10);

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatElemNilSetting() {
  errINI_t errINI = settingSetFloatElem(NULL, 0, 10.34);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloat(setting, 90.23);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloatElem(setting, 0, -10.2);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetFloatElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloatElem(setting, 1, 10.234);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetFloatElemOutOfMemory() {}

testResultINI_t testSettingSetFloatElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloatElem(setting, 0, 1.00);

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolElemNilSetting() {
  errINI_t errINI = settingSetBoolElem(NULL, 0, 1);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 90);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBoolElem(setting, 0, 1);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolElemInvalidValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBoolElem(setting, 0, 3);

  freeINI(ini);

  return (errINI == INI_INVALID_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetBoolElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBoolElem(setting, 1, 1);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetBoolElemOutOfMemory() {}

testResultINI_t testSettingSetBoolElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBoolElem(setting, 0, 1);

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharElemNilSetting() {
  errINI_t errINI = settingSetCharElem(NULL, 0, 'c');
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 90);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetCharElem(setting, 0, 'c');

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetCharElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetCharElem(setting, 1, 'c');

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetCharElemOutOfMemory() {}

testResultINI_t testSettingSetCharElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetCharElem(setting, 0, 'c');

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemNilSetting() {
  errINI_t errINI = settingSetStringElem(NULL, 0, "c");
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 90);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetStringElem(setting, 0, "c");

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetStringElem(setting, 1, "c");

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingSetStringElemNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetString(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

//testResultINI_t testSettingSetStringElemOutOfMemory() {}

testResultINI_t testSettingSetStringElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetStringElem(setting, 0, "c");

  freeINI(ini);

  return (errINI == INI_NIL) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntNilSetting() {
  int value;

  errINI_t errINI = settingGetInt(NULL, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetInt(setting, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloat(setting, 10.0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetInt(setting, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetInt(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetInt(setting, &value);

  freeINI(ini);

  return (errINI == INI_NIL && value == 10) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatNilSetting() {
  float value;

  errINI_t errINI = settingGetFloat(NULL, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float value;

  errINI = settingGetFloat(setting, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float value;

  errINI = settingGetFloat(setting, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloat(setting, 10.45);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetFloat(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloat(setting, 10.45);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float value;

  errINI = settingGetFloat(setting, &value);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float e = 0.009; // epsilon

  freeINI(ini);

  return ((value <= (10.45+e)) && (value >= (10.45-e))) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolNilSetting() {
  int value;

  errINI_t errINI = settingGetBool(NULL, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetBool(setting, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 35);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetBool(setting, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBool(setting, 1);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetBool(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBool(setting, 1);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetBool(setting, &value);

  freeINI(ini);

  return (errINI == INI_NIL && value) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharNilSetting() {
  char value;

  errINI_t errINI = settingGetChar(NULL, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = settingGetChar(setting, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 35);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = settingGetChar(setting, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetChar(setting, 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetChar(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetChar(setting, 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = settingGetChar(setting, &value);

  freeINI(ini);

  return (errINI == INI_NIL && value == 'c') ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringNilSetting() {
  char value[5];

  errINI_t errINI = settingGetString(NULL, value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value[5];

  errINI = settingGetString(setting, value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetInt(setting, 35);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value[4];

  errINI = settingGetString(setting, value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetString(setting, "c");
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetString(setting, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetString(setting, "c");
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value[1];

  errINI = settingGetString(setting, value);

  freeINI(ini);

  return (errINI == INI_NIL && !strncmp(value, "c", 1)) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemNilSetting() {
  int value;

  errINI_t errINI = settingGetIntElem(NULL, 0, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetIntElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloatElem(setting, 0, 10.678);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetIntElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetIntElem(setting, 1, &value);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 678);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetIntElem(setting, 0, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 678);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetIntElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_NIL && value == 678) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetIntElemsValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int i;
  int elems[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  for(i = 0; i < 10; i++) {
    errINI = settingSetIntElem(setting, i, elems[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  int val;
  for(i = 0; i < 10; i++) {
    errINI = settingGetIntElem(setting, i, &val);
    if(errINI != INI_NIL) { return INI_FAIL; }

    if(val != elems[i]) { return INI_FAIL; }
  }

  freeINI(ini);

  return INI_PASS;
}

testResultINI_t testSettingGetFloatElemNilSetting() {
  float value;

  errINI_t errINI = settingGetFloatElem(NULL, 0, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float value;

  errINI = settingGetFloatElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float value;

  errINI = settingGetFloatElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloatElem(setting, 0, 5.672);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float value;

  errINI = settingGetFloatElem(setting, 1, &value);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloatElem(setting, 0, 678.98);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetFloatElem(setting, 0, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetFloatElem(setting, 0, 678.45);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float value;

  errINI = settingGetFloatElem(setting, 0, &value);
  if(errINI != INI_NIL) { return INI_FAIL; }

  float e = .009;

  freeINI(ini);

  return (value <= 678.45+e && value >= 678.45-e) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetFloatElemsValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int i;

  float e = 0.009;
  float elems[] = { 0.45, 1.45, 2.45, 3.45, 4.45, 5.45, 6.45, 7.45, 8.45, 9.45 };

  for(i = 0; i < 10; i++) {
    errINI = settingSetFloatElem(setting, i, elems[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  float val;
  for(i = 0; i < 10; i++) {
    errINI = settingGetFloatElem(setting, i, &val);
    if(errINI != INI_NIL) { return INI_FAIL; }

    if(val < elems[i]-e || val > elems[i]+e) { return INI_FAIL; }
  }

  freeINI(ini);

  return INI_PASS;
}

testResultINI_t testSettingGetBoolElemNilSetting() {
  int value;

  errINI_t errINI = settingGetBoolElem(NULL, 0, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetBoolElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetBoolElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBoolElem(setting, 0, 0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetBoolElem(setting, 1, &value);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBoolElem(setting, 0, 1);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetBoolElem(setting, 0, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetBoolElem(setting, 0, 0);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int value;

  errINI = settingGetBoolElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_NIL && value == 0) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetBoolElemsValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int i;
  int elems[] = { 0, 1, 0, 0, 0, 1, 1, 0, 1, 0 };

  for(i = 0; i < 10; i++) {
    errINI = settingSetBoolElem(setting, i, elems[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  int val;
  for(i = 0; i < 10; i++) {
    errINI = settingGetBoolElem(setting, i, &val);
    if(errINI != INI_NIL) { return INI_FAIL; }

    if(val != elems[i]) { return INI_FAIL; }
  }

  freeINI(ini);

  return INI_PASS;
}

testResultINI_t testSettingGetCharElemNilSetting() {
  char value;

  errINI_t errINI = settingGetCharElem(NULL, 0, &value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = settingGetCharElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = settingGetCharElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetCharElem(setting, 0, 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = settingGetCharElem(setting, 1, &value);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  
  errINI = settingSetCharElem(setting, 0, 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetCharElem(setting, 0, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetCharElem(setting, 0, 'c');
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value;

  errINI = settingGetCharElem(setting, 0, &value);

  freeINI(ini);

  return (errINI == INI_NIL && value == 'c') ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetCharElemsValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int i;
  char elems[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

  for(i = 0; i < 10; i++) {
    errINI = settingSetCharElem(setting, i, elems[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  char val;
  for(i = 0; i < 10; i++) {
    errINI = settingGetCharElem(setting, i, &val);
    if(errINI != INI_NIL) { return INI_FAIL; }

    if(val != elems[i]) { return INI_FAIL; }
  }

  freeINI(ini);

  return INI_PASS;
}

testResultINI_t testSettingGetStringElemNilSetting() {
  char value[4];

  errINI_t errINI = settingGetStringElem(NULL, 0, value);
  return (errINI == INI_NIL_SETTING) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemValueUninitialized() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value[1];

  errINI = settingGetStringElem(setting, 0, value);

  freeINI(ini);

  return (errINI == INI_VALUE_UNINITIALIZED) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemTypeMismatch() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetIntElem(setting, 0, 10);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value[1];

  errINI = settingGetStringElem(setting, 0, value);

  freeINI(ini);

  return (errINI == INI_TYPE_MISMATCH) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemInvalidIndex() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetStringElem(setting, 0, "string");
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value[4];

  errINI = settingGetStringElem(setting, 1, value);

  freeINI(ini);

  return (errINI == INI_INVALID_INDEX) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemNilValue() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetStringElem(setting, 0, "foo");
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingGetStringElem(setting, 0, NULL);

  freeINI(ini);

  return (errINI == INI_NIL_VALUE) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingSetStringElem(setting, 0, "c");
  if(errINI != INI_NIL) { return INI_FAIL; }

  int len;

  errINI = settingElemLength(setting, 0, &len);
  if(errINI != INI_NIL) { return INI_FAIL; }

  char value[len];

  errINI = settingGetStringElem(setting, 0, value);

  freeINI(ini);

  return (errINI == INI_NIL && !strncmp(value, "c", 1)) ? INI_PASS : INI_FAIL;
}

testResultINI_t testSettingGetStringElemsValid() {
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, "section", "key", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  int i;
  char *elems[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };

  for(i = 0; i < 10; i++) {
    errINI = settingSetStringElem(setting, i, elems[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  char val[2];
  for(i = 0; i < 10; i++) {
    errINI = settingGetStringElem(setting, i, val);
    if(errINI != INI_NIL) { return INI_FAIL; }

    if(strncmp(val, elems[i], 1)) { return INI_FAIL; }
  }

  freeINI(ini);

  return INI_PASS;
}

testResultINI_t testCompleteIOFlow() {
  char *_section = "test_section";
  char *_ini = "[test_section]\n"
               "integer=45\n"
               "floatingPoint=4.52\n"
               "boolean=true\n"
               "character='r'\n"
               "string=\"foobar\"\n"
               "iarr={0, 1, 2, 3, 4}\n"
               "farr={0.5, 1.5, 2.5, 3.5, 4.5}\n"
               "barr={0, 0, 1, 0, 1}\n"
               "carr={'a', 'b', 'c', 'd', 'e'}\n"
               "sarr={\"foo\", \"bar\", \"baz\", \"zip\", \"zap\"}\n";
  ini_t *ini;

  errINI_t errINI = makeINI(&ini);
  if(errINI != INI_NIL) { return INI_FAIL; }

  setting_t *setting;

  errINI = createSetting(ini, _section, "integer", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  errINI = settingSetInt(setting, 45);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = createSetting(ini, _section, "floatingPoint", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  errINI = settingSetFloat(setting, 4.52);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = createSetting(ini, _section, "boolean", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  errINI = settingSetBool(setting, 1);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = createSetting(ini, _section, "character", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  errINI = settingSetChar(setting, 'r');
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = createSetting(ini, _section, "string", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  errINI = settingSetString(setting, "foobar");
  if(errINI != INI_NIL) { return INI_FAIL; }

  int i;

  int iarr[] = {0, 1, 2, 3, 4};
  errINI = createSetting(ini, _section, "iarr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  for(i = 0; i < 5; i++) {
    errINI = settingSetIntElem(setting, i, iarr[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }
  
  float farr[] = {0.5, 1.5, 2.5, 3.5, 4.5};
  errINI = createSetting(ini, _section, "farr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  for(i = 0; i < 5; i++) {
    errINI = settingSetFloatElem(setting, i, farr[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  int barr[] = {0, 0, 1, 0, 1};
  errINI = createSetting(ini, _section, "barr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  for(i = 0; i < 5; i++) {
    errINI = settingSetBoolElem(setting, i, barr[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  char carr[] = {'a', 'b', 'c', 'd', 'e'};
  errINI = createSetting(ini, _section, "carr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  for(i = 0; i < 5; i++) {
    errINI = settingSetCharElem(setting, i, carr[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  char *sarr[] = {"foo", "bar", "baz", "zip", "zap"};
  errINI = createSetting(ini, _section, "sarr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }
  for(i = 0; i < 5; i++) {
    errINI = settingSetStringElem(setting, i, sarr[i]);
    if(errINI != INI_NIL) { return INI_FAIL; }
  }

  char *tmpfile = "testCompleteIOFlow.txt";
  FILE *fp;

  if(!(fp = fopen(tmpfile, "w"))) { return INI_FAIL; }
  fprintf(fp, "%s", _ini);
  fclose(fp);

  ini_t *rini;
  errINI = readINI(&rini, tmpfile);
  if(remove(tmpfile)) { return INI_FAIL; }
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = lookupSetting(rini, _section, "integer", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  typeINI_t typeINI;
  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != INT) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i) { return INI_FAIL; }

  errINI = settingGetInt(setting, &i);
  if(errINI != INI_NIL || i != 45) { return INI_FAIL; }

  errINI = lookupSetting(rini, _section, "floatingPoint", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != FLOAT) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i) { return INI_FAIL; }

  float f;
  float e = 0.009;
  errINI = settingGetFloat(setting, &f);
  if(errINI != INI_NIL || f < 4.52-e || f > 4.52+e) { return INI_FAIL; }

  errINI = lookupSetting(rini, _section, "boolean", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != BOOL) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i) { return INI_FAIL; }

  errINI = settingGetBool(setting, &i);
  if(errINI != INI_NIL || i != 1) { return INI_FAIL; }

  errINI = lookupSetting(rini, _section, "character", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != CHAR) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i) { return INI_FAIL; }

  char c;
  errINI = settingGetChar(setting, &c);
  if(errINI != INI_NIL || c != 'r') { return INI_FAIL; }

  errINI = lookupSetting(rini, _section, "string", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != STRING) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i != 6) { return INI_FAIL; }

  char str[6];
  errINI = settingGetString(setting, str);
  if(errINI != INI_NIL || strncmp("foobar", str, 6)) { return INI_FAIL; }

  errINI = lookupSetting(rini, _section, "iarr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != INT_ARRAY) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i != 5) { return INI_FAIL; }

  int j;
  for(i = 0; i < 5; i++) {
    errINI = settingElemLength(setting, i, &j);
    if(errINI != INI_NIL || j) { return INI_FAIL; }

    errINI = settingGetIntElem(setting, i, &j);
    if(errINI != INI_NIL || j != iarr[i]) { return INI_FAIL; }
  }

  errINI = lookupSetting(rini, _section, "farr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != FLOAT_ARRAY) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i != 5) { return INI_FAIL; }

  for(i = 0; i < 5; i++) {
    errINI = settingElemLength(setting, i, &j);
    if(errINI != INI_NIL || j) { return INI_FAIL; }

    errINI = settingGetFloatElem(setting, i, &f);
    if(errINI != INI_NIL || f > farr[i]+e || f < farr[i]-e) { return INI_FAIL; }
  }

  errINI = lookupSetting(rini, _section, "barr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != BOOL_ARRAY) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i != 5) { return INI_FAIL; }

  for(i = 0; i < 5; i++) {
    errINI = settingElemLength(setting, i, &j);
    if(errINI != INI_NIL || j) { return INI_FAIL; }

    errINI = settingGetBoolElem(setting, i, &j);
    if(errINI != INI_NIL || j != barr[i]) { return INI_FAIL; }
  }

  errINI = lookupSetting(rini, _section, "carr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != CHAR_ARRAY) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i != 5) { return INI_FAIL; }

  for(i = 0; i < 5; i++) {
    errINI = settingElemLength(setting, i, &j);
    if(errINI != INI_NIL || j) { return INI_FAIL; }

    errINI = settingGetCharElem(setting, i, &c);
    if(errINI != INI_NIL || c != carr[i]) { return INI_FAIL; }
  }

  errINI = lookupSetting(rini, _section, "sarr", &setting);
  if(errINI != INI_NIL) { return INI_FAIL; }

  errINI = settingType(setting, &typeINI);
  if(errINI != INI_NIL || typeINI != STRING_ARRAY) { return INI_FAIL; }

  errINI = settingLength(setting, &i);
  if(errINI != INI_NIL || i != 5) { return INI_FAIL; }

  for(i = 0; i < 5; i++) {
    errINI = settingElemLength(setting, i, &j);
    if(errINI != INI_NIL || j != 3) { return INI_FAIL; }

    errINI = settingGetStringElem(setting, i, str);
    if(errINI != INI_NIL || strcmp(sarr[i], str)) { return INI_FAIL; }
  }

  freeINI(ini);

  return INI_PASS;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testStrErrINI_OPEN_FAILURE,                  "testStrErrINI_OPEN_FAILURE"                     },
  { testStrErrINI_CLOSE_FAILURE,                 "testStrErrINI_CLOSE_FAILURE"                    },
  { testStrErrINI_OUT_OF_MEMORY,                 "testStrErrINI_OUT_OF_MEMORY"                    },
  { testStrErrINI_TYPE_MISMATCH,                 "testStrErrINI_TYPE_MISMATCH"                    },
  { testStrErrINI_DUPLICATE_SETTING,             "testStrErrINI_DUPLICATE_SETTING"                },
  { testStrErrINI_INVALID_CONF,                  "testStrErrINI_INVALID_CONF"                     },
  { testStrErrINI_INVALID_KEY,                   "testStrErrINI_INVALID_KEY"                      },
  { testStrErrINI_INVALID_VALUE,                 "testStrErrINI_INVALID_VALUE"                    },
  { testStrErrINI_INVALID_SECTION,               "testStrErrINI_INVALID_SECTION"                  },
  { testStrErrINI_INVALID_INDEX,                 "testStrErrINI_INVALID_INDEX"                    },
  { testStrErrINI_INVALID_OPTIONS,               "testStrErrINI_INVALID_OPTIONS"                  },
  { testStrErrINI_NIL_FNAME,                     "testStrErrINI_NIL_FNAME"                        },
  { testStrErrINI_NIL_INI,                       "testStrErrINI_NIL_INI"                          },
  { testStrErrINI_NIL_KEY,                       "testStrErrINI_NIL_KEY"                          },
  { testStrErrINI_NIL_VALUE,                     "testStrErrINI_NIL_VALUE"                        },
  { testStrErrINI_NIL_SECTION,                   "testStrErrINI_NIL_SECTION"                      },
  { testStrErrINI_NIL_OPTIONS,                   "testStrErrINI_NIL_OPTIONS"                      },
  { testStrErrINI_NIL_SETTING,                   "testStrErrINI_NIL_SETTING"                      },
  { testStrErrINI_NIL_TYPE,                      "testStrErrINI_NIL_TYPE"                         },
  { testStrErrINI_NIL_LENGTH,                    "testStrErrINI_NIL_LENGTH"                       },
  { testStrErrINI_NIL,                           "testStrErrINI_NIL"                              },
  { testMakeININilINI,                           "testMakeININilINI"                              },
  //  { testMakeINIOutOfMemory,                      "testMakeINIOutOfMemory"                         },
  { testMakeINIValid,                            "testMakeINIValid"                               },
  { testFreeININilINI,                           "testFreeININilINI"                              },
  { testFreeINIValid,                            "testFreeINIValid"                               },
  { testReadININilINI,                           "testReadININilINI"                              },
  { testReadININilFname,                         "testReadININilFname"                            },
  { testReadINIOpenFailure,                      "testReadINIOpenFailure"                         },
  //  { testReadINICloseFailure,                     "testReadINICloseFailure"                        },
  //  { testReadINIOutOfMemory,                      "testReadINIOutOfMemory"                         },
  { testReadININilSection,                       "testReadININilSection"                          },
  { testReadINIInvalidSection,                   "testReadINIInvalidSection"                      },
  { testReadININilKey,                           "testReadININilKey"                              },
  { testReadINIInvalidKey,                       "testReadINIInvalidKey"                          },
  { testReadINIInvalidArrayComma,                "testReadINIInvalidArrayComma"                   },
  { testReadINIInvalidArrayType,                 "testReadINIInvalidArrayType"                    },
  { testReadINIInvalidString,                    "testReadINIInvalidString"                       },
  { testReadINIValid,                            "testReadINIValid"                               },
  { testWriteININilINI,                          "testWriteININilINI"                             },
  { testWriteININilFileName,                     "testWriteININilFileName"                        },
  { testWriteINIOpenFailure,                     "testWriteINIOpenFailure"                        },
  //  { testWriteINICloseFailure,                    "testWriteINICloseFailure"                       },
  { testWriteINIValid,                           "testWriteINIValid"                              },
  { testGetConfigurationNilINI,                  "testGetConfigurationNilINI"                     },
  { testGetConfigurationNilOptions,              "testGetConfigurationNilOptions"                 },
  { testGetConfigurationValid,                   "testGetConfigurationValid"                      },
  { testSetConfigurationNilINI,                  "testSetConfigurationNilINI"                     },
  { testSetConfigurationInvalidOptions,          "testSetConfigurationInvalidOptions"             },
  { testSetConfigurationValid,                   "testSetConfigurationValid"                      },
  { testCreateSettingNilINI,                     "testCreateSettingNilINI"                        },
  { testCreateSettingNilSection,                 "testCreateSettingNilSection"                    },
  { testCreateSettingNilKey,                     "testCreateSettingNilKey"                        },
  { testCreateSettingNilSetting,                 "testCreateSettingNilSetting"                    },
  { testCreateSettingInvalidSection,             "testCreateSettingInvalidSection"                },
  { testCreateSettingInvalidKey,                 "testCreateSettingInvalidKey"                    },
  { testCreateSettingDuplicateSetting,           "testCreateSettingDuplicateSetting"              },
  //  { testCreateSettingOutOfMemory,                "testCreateSettingOutOfMemory"                   },
  { testCreateSettingValid,                      "testCreateSettingValid"                         },
  { testLookupSettingNilINI,                     "testLookupSettingNilINI"                        },
  { testLookupSettingNilSection,                 "testLookupSettingNilSection"                    },
  { testLookupSettingNilKey,                     "testLookupSettingNilKey"                        },
  { testLookupSettingNilSetting,                 "testLookupSettingNilSetting"                    },
  { testLookupSettingInvalidSection,             "testLookupSettingInvalidSection"                },
  { testLookupSettingInvalidKey,                 "testLookupSettingInvalidKey"                    },
  { testLookupNonPresentSetting,                 "testLookupNonPresentSetting"                    },
  { testLookupSettingValid,                      "testLookupSettingValid"                         },
  { testDeleteSettingNilINI,                     "testDeleteSettingNilINI"                        },
  { testDeleteSettingNilSection,                 "testDeleteSettingNilSection"                    },
  { testDeleteSettingNilKey,                     "testDeleteSettingNilKey"                        },
  { testDeleteSettingInvalidGrammerSection,      "testDeleteSettingInvalidGrammerSection"         },
  { testDeleteSettingInvalidGrammerKey,          "testDeleteSettingInvalidGrammerKey"             },
  { testDeleteSettingNonPresentSetting,          "testDeleteSettingNonPresentSetting"             },
  { testDeleteSettingValid,                      "testDeleteSettingValid"                         },
  { testSettingLookupDeleted,                    "testSettingLookupDeleted"                       },
  { testSettingCompleteFlow,                     "testSettingCompleteFlow"                        },
  { testSettingTypeNilSettings,                  "testSettingTypeNilSettings"                     },
  { testSettingTypeNilType,                      "testSettingTypeNilType"                         },
  { testSettingTypeValid,                        "testSettingTypeValid"                           },
  { testSettingKeyLengthNilSetting,              "testSettingKeyLengthNilSetting"                 },
  { testSettingKeyLengthNilLength,               "testSettingKeyLengthNilLength"                  },
  { testSettingKeyLengthValid,                   "testSettingKeyLengthValid"                      },
  { testSettingKeyNilSetting,                    "testSettingKeyNilSetting"                       },
  { testSettingKeyNilKey,                        "testSettingKeyNilKey"                           },
  { testSettingKeyValid,                         "testSettingKeyValid"                            },
  { testSettingLengthNilSetting,                 "testSettingLengthNilSetting"                    },
  { testSettingLengthNilLength,                  "testSettingLengthNilLength"                     },
  { testSettingLengthValid,                      "testSettingLengthValid"                         },
  { testSettingElemLengthNilSetting,             "testSettingElemLengthNilSetting"                },
  { testSettingElemLengthNilLength,              "testSettingElemLengthNilLength"                 },
  { testSettingElemLengthInvalidIndex,           "testSettingElemLengthInvalidIndex"              },
  { testSettingElemLengthTypeMismatch,           "testSettingElemLengthTypeMismatch"              },
  { testSettingElemLengthValid,                  "testSettingElemLengthValid"                     },
  { testSettingSetIntNilSetting,                 "testSettingSetIntNilSetting"                    },
  { testSettingSetIntTypeMismatch,               "testSettingSetIntTypeMismatch"                  },
  { testSettingSetIntValid,                      "testSettingSetIntValid"                         },
  { testSettingSetFloatNilSetting,               "testSettingSetFloatNilSetting"                  },
  { testSettingSetFloatTypeMismatch,             "testSettingSetFloatTypeMismatch"                },
  { testSettingSetFloatValid,                    "testSettingSetFloatValid"                       },
  { testSettingSetBoolNilSetting,                "testSettingSetBoolNilSetting"                   },
  { testSettingSetBoolTypeMismatch,              "testSettingSetBoolTypeMismatch"                 },
  { testSettingSetBoolInvalidValue,              "testSettingSetBoolInvalidValue"                 },
  { testSettingSetBoolValid,                     "testSettingSetBoolValid"                        },
  { testSettingSetCharNilSetting,                "testSettingSetCharNilSetting"                   },
  { testSettingSetCharTypeMismatch,              "testSettingSetCharTypeMismatch"                 },
  { testSettingSetCharValid,                     "testSettingSetCharValid"                        },
  { testSettingSetStringNilSetting,              "testSettingSetStringNilSetting"                 },
  { testSettingSetStringTypeMismatch,            "testSettingSetStringTypeMismatch"               },
  { testSettingSetStringNilValue,                "testSettingSetStringNilValue"                   },
  //  { testSettingSetStringOutOfMemory,             "testSettingSetStringOutOfMemory"                },
  { testSettingSetStringValid,                   "testSettingSetStringValid"                      },
  { testSettingSetIntElemNilSetting,             "testSettingSetIntElemNilSetting"                },
  { testSettingSetIntElemTypeMismatch,           "testSettingSetIntElemTypeMismatch"              },
  { testSettingSetIntElemInvalidIndex,           "testSettingSetIntElemInvalidIndex"              },
  //  { testSettingSetIntElemOutOfMemory,            "testSettingSetIntElemOutOfMemory"               },
  { testSettingSetIntElemValid,                  "testSettingSetIntElemValid"                     },
  { testSettingSetFloatElemNilSetting,           "testSettingSetFloatElemNilSetting"              },
  { testSettingSetFloatElemTypeMismatch,         "testSettingSetFloatElemTypeMismatch"            },
  { testSettingSetFloatElemInvalidIndex,         "testSettingSetFloatElemInvalidIndex"            },
  //  { testSettingSetFloatElemOutOfMemory,          "testSettingSetFloatElemOutOfMemory"             },
  { testSettingSetFloatElemValid,                "testSettingSetFloatElemValid"                   },
  { testSettingSetBoolElemNilSetting,            "testSettingSetBoolElemNilSetting"               },
  { testSettingSetBoolElemTypeMismatch,          "testSettingSetBoolElemTypeMismatch"             },
  { testSettingSetBoolElemInvalidValue,          "testSettingSetBoolElemInvalidValue"             },
  { testSettingSetBoolElemInvalidIndex,          "testSettingSetBoolElemInvalidIndex"             },
  //  { testSettingSetBoolElemOutOfMemory,           "testSettingSetBoolElemOutOfMemory"              },
  { testSettingSetBoolElemValid,                 "testSettingSetBoolElemValid"                    },
  { testSettingSetCharElemNilSetting,            "testSettingSetCharElemNilSetting"               },
  { testSettingSetCharElemTypeMismatch,          "testSettingSetCharElemTypeMismatch"             },
  { testSettingSetCharElemInvalidIndex,          "testSettingSetCharElemInvalidIndex"             },
  //  { testSettingSetCharElemOutOfMemory,           "testSettingSetCharElemOutOfMemory"              },
  { testSettingSetCharElemValid,                 "testSettingSetCharElemValid"                    },
  { testSettingSetStringElemNilSetting,          "testSettingSetStringElemNilSetting"             },
  { testSettingSetStringElemTypeMismatch,        "testSettingSetStringElemTypeMismatch"           },
  { testSettingSetStringElemInvalidIndex,        "testSettingSetStringElemInvalidIndex"           },
  { testSettingSetStringElemNilValue,            "testSettingSetStringElemNilValue"               },
  //  { testSettingSetStringElemOutOfMemory,         "testSettingSetStringElemOutOfMemory"            },
  { testSettingSetStringElemValid,               "testSettingSetStringElemValid"                  },
  { testSettingGetIntNilSetting,                 "testSettingGetIntNilSetting"                    },
  { testSettingGetIntValueUninitialized,         "testSettingGetIntValueUninitialized"            },
  { testSettingGetIntTypeMismatch,               "testSettingGetIntTypeMismatch"                  },
  { testSettingGetIntNilValue,                   "testSettingGetIntNilValue"                      },
  { testSettingGetIntValid,                      "testSettingGetIntValid"                         },
  { testSettingGetFloatNilSetting,               "testSettingGetFloatNilSetting"                  },
  { testSettingGetFloatValueUninitialized,       "testSettingGetFloatValueUninitialized"          },
  { testSettingGetFloatTypeMismatch,             "testSettingGetFloatTypeMismatch"                },
  { testSettingGetFloatNilValue,                 "testSettingGetFloatNilValue"                    },
  { testSettingGetFloatValid,                    "testSettingGetFloatValid"                       },
  { testSettingGetBoolNilSetting,                "testSettingGetBoolNilSetting"                   },
  { testSettingGetBoolValueUninitialized,        "testSettingGetBoolValueUninitialized"           },
  { testSettingGetBoolTypeMismatch,              "testSettingGetBoolTypeMismatch"                 },
  { testSettingGetBoolNilValue,                  "testSettingGetBoolNilValue"                     },
  { testSettingGetBoolValid,                     "testSettingGetBoolValid"                        },
  { testSettingGetCharNilSetting,                "testSettingGetCharNilSetting"                   },
  { testSettingGetCharValueUninitialized,        "testSettingGetCharValueUninitialized"           },
  { testSettingGetCharTypeMismatch,              "testSettingGetCharTypeMismatch"                 },
  { testSettingGetCharNilValue,                  "testSettingGetCharNilValue"                     },
  { testSettingGetCharValid,                     "testSettingGetCharValid"                        },
  { testSettingGetStringNilSetting,              "testSettingGetStringNilSetting"                 },
  { testSettingGetStringValueUninitialized,      "testSettingGetStringValueUninitialized"         },
  { testSettingGetStringTypeMismatch,            "testSettingGetStringTypeMismatch"               },
  { testSettingGetStringNilValue,                "testSettingGetStringNilValue"                   },
  { testSettingGetStringValid,                   "testSettingGetStringValid"                      },
  { testSettingGetIntElemNilSetting,             "testSettingGetIntElemNilSetting"                },
  { testSettingGetIntElemValueUninitialized,     "testSettingGetIntElemValueUninitialized"        },
  { testSettingGetIntElemTypeMismatch,           "testSettingGetIntElemTypeMismatch"              },
  { testSettingGetIntElemInvalidIndex,           "testSettingGetIntElemInvalidIndex"              },
  { testSettingGetIntElemNilValue,               "testSettingGetIntElemNilValue"                  },
  { testSettingGetIntElemValid,                  "testSettingGetIntElemValid"                     },
  { testSettingGetIntElemsValid,                 "testSettingGetIntElemsValid"                    },
  { testSettingGetFloatElemNilSetting,           "testSettingGetFloatElemNilSetting"              },
  { testSettingGetFloatElemValueUninitialized,   "testSettingGetFloatElemValueUninitialized"      },
  { testSettingGetFloatElemTypeMismatch,         "testSettingGetFloatElemTypeMismatch"            },
  { testSettingGetFloatElemInvalidIndex,         "testSettingGetFloatElemInvalidIndex"            },
  { testSettingGetFloatElemNilValue,             "testSettingGetFloatElemNilValue"                },
  { testSettingGetFloatElemValid,                "testSettingGetFloatElemValid"                   },
  { testSettingGetFloatElemsValid,               "testSettingGetFloatElemsValid"                  },
  { testSettingGetBoolElemNilSetting,            "testSettingGetBoolElemNilSetting"               },
  { testSettingGetBoolElemValueUninitialized,    "testSettingGetBoolElemValueUninitialized"       },
  { testSettingGetBoolElemTypeMismatch,          "testSettingGetBoolElemTypeMismatch"             },
  { testSettingGetBoolElemInvalidIndex,          "testSettingGetBoolElemInvalidIndex"             },
  { testSettingGetBoolElemNilValue,              "testSettingGetBoolElemNilValue"                 },
  { testSettingGetBoolElemValid,                 "testSettingGetBoolElemValid"                    },
  { testSettingGetBoolElemsValid,                "testSettingGetBoolElemsValid"                   },
  { testSettingGetCharElemNilSetting,            "testSettingGetCharElemNilSetting"               },
  { testSettingGetCharElemValueUninitialized,    "testSettingGetCharElemValueUninitialized"       },
  { testSettingGetCharElemTypeMismatch,          "testSettingGetCharElemTypeMismatch"             },
  { testSettingGetCharElemInvalidIndex,          "testSettingGetCharElemInvalidIndex"             },
  { testSettingGetCharElemNilValue,              "testSettingGetCharElemNilValue"                 },
  { testSettingGetCharElemValid,                 "testSettingGetCharElemValid"                    },
  { testSettingGetCharElemsValid,                "testSettingGetCharElemsValid"                   },
  { testSettingGetStringElemNilSetting,          "testSettingGetStringElemNilSetting"             },
  { testSettingGetStringElemValueUninitialized,  "testSettingGetStringElemValueUninitialized"     },
  { testSettingGetStringElemTypeMismatch,        "testSettingGetStringElemTypeMismatch"           },
  { testSettingGetStringElemInvalidIndex,        "testSettingGetStringElemInvalidIndex"           },
  { testSettingGetStringElemNilValue,            "testSettingGetStringElemNilValue"               },
  { testSettingGetStringElemValid,               "testSettingGetStringElemValid"                  },
  { testSettingGetStringElemsValid,              "testSettingGetStringElemsValid"                 },
  { testCompleteIOFlow,                          "testCompleteIOFlow"                             }
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
