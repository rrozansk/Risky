/******************************************************************************
 * FILE:    ini.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  6/27/17                                                           *
 * INFO:    Implementation of the interface located in ini.h.                 *
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
#include <ctype.h>

/******************************************************************************
 *                                                                            *
 *   S T R U C T S                                                            *
 *                                                                            *
 ******************************************************************************/
typedef enum typeINI {
  INT, FLOAT, BOOL, CHAR, STR, INT_ARR, FLOAT_ARR, BOOL_ARR, CHAR_ARR, STR_ARR
} typeINI_t;

typedef struct setting { // setting ::= [key, val, type]
  char *key;
  typeINI_t typeINI;
  int len;               // len of arr/str (if applicable)
  union {
    int i;               // int
    double d;            // float
    int b;               // bool
    char c;              // char
    char *str;           // string
    int *iarr;           // int arr
    int *darr;           // float arr
    int *barr;           // bool arr
    char *carr;          // char arr
    char **sarr;         // string arr
  } val;
} setting_t;

typedef struct arrayList {
  void **arr;
  int cap;
  int size;
} arrayList_t;

typedef struct section {     // section ::= [header, settings*]
  char *header;
  arrayList_t *settings;
} section_t;

typedef struct ini { arrayList_t *sections; } ini_t; // ini ::= section*

/******************************************************************************
 *                                                                            *
 *   P R I V A T E   F U N C T I O N S                                        *
 *                                                                            *
 ******************************************************************************/
static arrayList_t *newArrayList() {
  arrayList_t *arrayList = malloc(sizeof(arrayList_t));
  if(!arrayList) { return NULL; }
  arrayList->arr = calloc(4, sizeof(void *));
  if(!arrayList->arr) {
    free(arrayList);
    return NULL;
  }
  arrayList->cap = 4;
  arrayList->size = 0;
  return arrayList;
}

static void freeArrayList(arrayList_t *arrayList) {
  if(!arrayList) { return; }
  free(arrayList->arr);
  free(arrayList);
}

static int lenArrayList(arrayList_t *arrayList) { return arrayList->size; }

static void *getArrayList(arrayList_t *arrayList, int item) {
  if(!arrayList || item < 0 || item > arrayList->size) { return NULL; }
  return arrayList->arr[item];
}

static void putArrayList(arrayList_t *arrayList, void *item) {
  if(!arrayList) { return; }

  if(arrayList->cap == arrayList->size) {
    arrayList->arr = realloc(arrayList->arr, arrayList->cap *= 2);
    if(!arrayList->arr) { return; }
  }

  arrayList->arr[arrayList->size++] = item;
}

static void delArrayList(arrayList_t *arrayList, int item) {
  if(!arrayList || item < 0 || item > arrayList->size) { return; }
  
  for(; item < arrayList->size; item++) {
    arrayList->arr[item] = arrayList->arr[item+1];
  }
  arrayList->size--;
}

static int isSpace(int c) { return isspace(c); }

static int isDividor(int c) { return c == ':' || c == '=';  }

static int isComment(int c) { return c == '#' || c == ';';  }

static int isSpecial(int c) { return ispunct(c) && !isDividor(c) && !isComment(c); }

static int isChar(int c) { return isalnum(c) | isSpecial(c); }

static int isValidTerm(char *term) {
  for(; *term; term++) { if(!isChar(*term)) { return 0;  } }
  return 1;
}

static int isValidKey(char *key) { return isValidTerm(key); }

static int isValidHeader(char *section) { return isValidTerm(section); }

// FIXME: do getStrLengthINI() and getArrLengthINI() so we never have to
// allocate memeory for getters, only for setters. this allows the library
// to persist the information however it wants.

//static errINI_t getINI(ini_t *ini, char *section, char *key, void *value, int *len, typeINI_t typeINI) {
static errINI_t getINI(ini_t *ini, char *section, char *key, void *value, int **len, typeINI_t typeINI) {
  if(!ini) { return INI_NIL_INI; }
  if(!section) { return INI_NIL_SECTION; }
  if(!key) { return INI_NIL_KEY; }
  if(!value) { return INI_NIL_VAL; }
  if((typeINI == INT_ARR || typeINI == FLOAT_ARR || typeINI == BOOL_ARR ||
     typeINI == CHAR_ARR || typeINI == STR_ARR) && !len) { return INI_NIL_LEN; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }

  setting_t *setting;
  section_t *_section;

  int settings, sections;
  for(sections = lenArrayList(ini->sections); sections; sections--) {
    _section = (section_t *)getArrayList(ini->sections, sections-1);
    if(!strcmp(_section->header, section)) {
      for(settings = lenArrayList(_section->settings); settings; settings--) {
        setting = (setting_t *)getArrayList(_section->settings, settings-1);
        if(!strcmp(setting->key, key)) {
          if(setting->typeINI != typeINI) { return INI_TYPE_MISMATCH; }
          switch(typeINI) { // FIXME: stk/heap alloc left to user, just taking ptrs and assuming the memory is there 
            case INT:
              *(int *)value = setting->val.i;
              return INI_NIL;
            case FLOAT:
              *(double *)value = setting->val.d;
              return INI_NIL;
            case BOOL:
              *(int *)value = setting->val.b;
              return INI_NIL;
            case CHAR:
              *(char *)value = setting->val.c;
              return INI_NIL;
            case STR:
              if(!(*(char **)value = malloc(sizeof(char) * (setting->len + 1)))) { return INI_OUT_OF_MEMORY; }
              strncpy(*(char **)value, setting->val.str, setting->len+1);
              return INI_NIL;
            case INT_ARR:
              *(int **)value = malloc(sizeof(int) * setting->len);
              *(int **)len = malloc(sizeof(int));
              if(!len || !value) { break; }
              for(settings = setting->len; settings; settings--) { 
                (*(int **)value)[settings-1] = (setting->val.iarr)[settings-1];
              }
              **(int **)len = setting->len;
              return INI_NIL;
            case FLOAT_ARR:
              *(double **)value = malloc(sizeof(double) * setting->len);
              *(int **)len = malloc(sizeof(int));
              if(!len || !value) { break; }
              for(settings = setting->len; settings; settings--) { 
                (*(double **)value)[settings-1] = (setting->val.darr)[settings-1];
              }
              **(int **)len = setting->len;
              return INI_NIL;
            case BOOL_ARR:
              *(int **)value = malloc(sizeof(int) * setting->len);
              *(int **)len = malloc(sizeof(int));
              if(!len || !value) { break; }
              for(settings = setting->len; settings; settings--) { 
                (*(int **)value)[settings-1] = (setting->val.barr)[settings-1];
              }
              **(int **)len = setting->len;
              return INI_NIL;
            case CHAR_ARR:
              *(char **)value = malloc(sizeof(char) * setting->len);
              *(int **)len = malloc(sizeof(int));
              if(!len || !value) { break; }
              for(settings = setting->len; settings; settings--) { 
                (*(char **)value)[settings-1] = (setting->val.carr)[settings-1];
              }
              **(int **)len = setting->len;
              return INI_NIL;
            case STR_ARR:
              *(char ***)value = malloc(sizeof(char *) * setting->len);
              *(int **)len = malloc(sizeof(int));
              if(!len || !value) { break; }
              for(settings = setting->len; settings; settings--) {
                if(!((*(char ***)value)[settings-1] = malloc(sizeof(char) * strlen(setting->val.sarr[settings-1])))) {
                  for(; settings; settings--) { free((*(char ***)value)[settings-1]); }
                  return INI_OUT_OF_MEMORY;
                }
                strncpy((*(char ***)value)[settings-1], (setting->val.sarr)[settings-1], setting->len+1);
              }
              **(int **)len = setting->len;
              return INI_NIL;
          }
          return INI_OUT_OF_MEMORY;
        }
      }
    }
  }
  return INI_NOT_FOUND;
}

static errINI_t setINI(ini_t *ini, char *section, char *key, void *value, int len, typeINI_t typeINI) {
  if(!ini) { return INI_NIL_INI; }
  if(!section) { return INI_NIL_SECTION; }
  if(!key) { return INI_NIL_KEY; }
  if(!value) { return INI_NIL_VAL; }
  if((typeINI == INT_ARR || typeINI == FLOAT_ARR || typeINI == BOOL_ARR ||
     typeINI == CHAR_ARR || typeINI == STR_ARR) && len < 1) { return INI_INVALID_LEN; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }

  setting_t *setting;
  section_t *_section;

  int settings, sections;
  for(sections = lenArrayList(ini->sections); sections; sections--) {
    _section = (section_t *)getArrayList(ini->sections, sections-1);
    if(!strcmp(_section->header, section)) {
      for(settings = lenArrayList(_section->settings); settings; settings--) {
        setting = (setting_t *)getArrayList(_section->settings, settings-1);
        if(!strcmp(setting->key, key)) {
          if(setting->typeINI != typeINI) { return INI_TYPE_MISMATCH; }        // FIXME
          // free old setting value if applicable
          // malloc copy of new value
          // setting->val = *val
          // TODO: out of memory errors
          switch(typeINI) { /*
            setIntINI(int val)          &val
            setFloatINI(double val)     &val
            setBoolINI(int val)         &val
            setCharINI(char val)        &val
            setStrINI(char *val)        &val
            setIntArrINI(int *val)      val
            setFloatArrINI(double *val) val
            setBoolArrINI(int *val)     val
            setCharArrINI(char *val)    val
            setStrArrINI(char **val)    val */
            case INT:
            case FLOAT:
            case BOOL:
            case CHAR:
            case STR:
            case INT_ARR:
            case FLOAT_ARR:
            case BOOL_ARR:
            case CHAR_ARR:
            case STR_ARR:
              break;
          }
        }
      }
      // wasnt found, make new setting and add to settings list
      return INI_NIL;
    }
  }
  // section not found make new one
  return INI_NIL;
}

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrINI(errINI_t errINI) {
  switch(errINI) {
    // misc errors
    case INI_UNKNOWN_TYPE: return "internal error! unknow value type for setting";
    case INI_OPEN_FAILURE: return "failure to open conf file";
    case INI_CLOSE_FAILURE: return "failure to close conf file";
    case INI_OUT_OF_MEMORY: return "out of memory";
    case INI_NOT_FOUND: return "cannot retrieve non-existant key value pair";
    case INI_TYPE_MISMATCH: return "value type requested does not match value type stored";
    // invalid input errors
    case INI_INVALID_CONF: return "invalid conf file";
    case INI_INVALID_KEY: return "key does not adhere to library grammar";
    case INI_INVALID_VAL: return "value does not adhere to library grammar";
    case INI_INVALID_SECTION: return "header does not adhere to library grammar";
    case INI_INVALID_LEN: return "invalid array len";
    // nil arg errors
    case INI_NIL_FNAME: return "nil conf file name";
    case INI_NIL_INI: return "nil ini";
    case INI_NIL_KEY: return "nil key";
    case INI_NIL_VAL: return "nil value";
    case INI_NIL_LEN: return "nil array len";
    case INI_NIL_SECTION: return "nil section";
    case INI_NIL: return "";
    default: return "unrecognized INI error code";
  }
}

errINI_t makeINI(ini_t **ini) {
  if(!ini) { return INI_NIL_INI; }

  if(!(*ini = malloc(sizeof(ini_t)))) { return INI_OUT_OF_MEMORY; }
  if(!((*ini)->sections = newArrayList())) {
    free(*ini);
    *ini = NULL;
    return INI_OUT_OF_MEMORY;
  }

  return INI_NIL;
}

errINI_t freeINI(ini_t *ini) {
  if(!ini) { return INI_NIL; }

  section_t *section;
  setting_t *setting;
  int sections, settings;
  for(sections = lenArrayList(ini->sections); sections; sections--) {
    section = (section_t *)getArrayList(ini->sections, sections-1);
    free(section->header);
    for(settings = lenArrayList(section->settings); settings; settings--) {
      setting = (setting_t *)getArrayList(section->settings, sections-1);
      switch(setting->typeINI) {
        case INT:
        case FLOAT:
        case BOOL:
        case CHAR:
          break;
        case STR:
          free(setting->val.str);
          break;
        case INT_ARR:
          free(setting->val.iarr);
          break;
        case FLOAT_ARR:
          free(setting->val.darr);
          break;
        case BOOL_ARR:
          free(setting->val.barr);
          break;
        case CHAR_ARR:
          free(setting->val.carr);
          break;
        case STR_ARR:
          for(; setting->len; setting->len--) {
            free(setting->val.sarr[setting->len-1]);  
          }
          free(setting->val.sarr);
          break;
      }
      free(setting->key);
      free(setting);
    }
    freeArrayList(section->settings);
    free(section);
  }
  freeArrayList(ini->sections);
  free(ini);

  return INI_NIL;
}

errINI_t readINI(ini_t **ini, char *fname) { // TODO
  if(!ini) { return INI_NIL_INI; }
  if(!fname) { return INI_NIL_FNAME; }

  FILE *fp = fopen(fname, "r");
  if(!fp) { return INI_OPEN_FAILURE; }

  errINI_t errINI;
  if((errINI = makeINI(ini)) != INI_NIL) { return errINI; }

  /*
    really the reader/parser should haver something like a dynamic buffer char buffer[120];
    then we can do this ==> sscanf(buffer, "%[type]", &[var]);
    parsers become trivial ==> if(sscanf(buffer, "%i", &i) > 0) {} // parseInt()
    can use array lists (as stk) to parse arrays then malloc exact size when done
  */

  char *section, *key, *val;
  section = key = val = NULL;
  int c, i, size;
  while((c = fgetc(fp)) != EOF) {
    switch(c) {
      case '\t': case '\v': case '\f': case '\n': case '\r': case ' ': break; // read blank space
      case '#': case ';': do { c = fgetc(fp); } while(c != '\n'); break;      // read line comments  ; or #
      case '[':                                                               // read section header [<term>]
        if(section) { free(section); } // free old section
        section = malloc(sizeof(char) * (size = 100));
        for(i = 0; isChar(c = fgetc(fp)) && c != ']';) {
          if(i == (size-1)) { // -1 so always space for str terminator
            section = realloc(section, sizeof(char)*(size *= 2));
          }
          section[i++] = c;
        }
        if(i == 0) { // no term read
          errINI = INI_INVALID_SECTION;
          goto err;
        }
        section[i++] = '\0';
        section = realloc(section, sizeof(char)*i);
        //printf("section:\t\t%s\n", section); fflush(stdout);
        break;
      // LABELS
      key: // read a key <term> until <dividor>
        key = malloc(sizeof(char) * (size = 100));
        for(i = 0; !isDividor(c); c = fgetc(fp)) {
          if(i == (size-1)) { // -1 so always space for str terminator
            key = realloc(key, sizeof(char)*(size *= 2));
          }
          key[i++] = c;
        }
        if(i == 0) { // no term read
          errINI = INI_INVALID_KEY;
          goto err;
        }
        key[i++] = '\0';
        key = realloc(key, sizeof(char)*i);
        //printf("%s\t\t", key); fflush(stdout);
        break;
      value: // read a value <term> until <space>
        val = malloc(sizeof(char) * (size = 100));
        for(i = 0; !isSpace(c); c = fgetc(fp)) {
          if(i == (size-1)) { // -1 so always space for str terminator
            val = realloc(val , sizeof(char)*(size *= 2));
          }
          val[i++] = c;
        }
        if(i == 0) { // no term read
          errINI = INI_INVALID_VAL;
          goto err;
        }
        val[i++] = '\0';
        val = realloc(val, sizeof(char)*i);
        //printf("%s\n", val); fflush(stdout);
        //if((errINI = setINI(*ini, section, key, val)) != INI_NIL) { goto err; }
        free(key);
        key = NULL;
        free(val);
        val = NULL;
        break;
      err:                                                                    // error check
        //printf("**ERROR**\n"); fflush(stdout);
        fclose(fp);    // ignore possible error so syntax error is returned
        freeINI(*ini); // ignore possible error so syntax error is returned
        *ini = NULL;
        if(section) { free(section); }
        if(key) { free(key); }
        if(val) { free(val); }
        return errINI;
      default:                                                                // unknown errors and key/value dispatch
        if(isChar(c)) {
          if(!key) { goto key; }
          goto value;
        }
        errINI = INI_INVALID_CONF;
        goto err;
    }
  }
  if(section) { free(section); } // free last section

  if(fclose(fp)) { return INI_CLOSE_FAILURE; }

  return INI_NIL;
}

errINI_t writeINI(ini_t *ini, char *fname) {
  if(!ini) { return INI_NIL_INI; }
  if(!fname) { return INI_NIL_FNAME; }

  FILE *fp = fopen(fname, "w+");
  if(!fp) { return INI_OPEN_FAILURE; }

  section_t *section;
  setting_t *setting;
  int sections, settings, i, j;
  for(i = 0, sections = lenArrayList(ini->sections); i < sections; i++) {
    section = (section_t *)getArrayList(ini->sections, i);
    fprintf(fp, "[%s]\n", section->header);
    for(j = 0, settings = lenArrayList(section->settings); j < settings; j++) {
      setting = (setting_t *)getArrayList(section->settings, j);
      fprintf(fp, "%s=", setting->key);
      switch(setting->typeINI) {
        case INT:
          fprintf(fp, "%i\n", setting->val.i);
          break;
        case FLOAT:
          fprintf(fp, "%f\n", setting->val.d);
          break;
        case BOOL:
          fprintf(fp, setting->val.b ? "true\n" : "false\n");
          break;
        case CHAR:
          fprintf(fp, "%c\n", setting->val.c);
          break;
        case STR:
          fprintf(fp, "%s\n", setting->val.str);
          break;
        case INT_ARR:
          fprintf(fp, "{");
          for(i = 0; i < setting->len; i++) {
            fprintf(fp, (i < setting->len-1) ? "%i, " : "%i", setting->val.i);
          }
          fprintf(fp, "}\n");
          break;
        case FLOAT_ARR:
          fprintf(fp, "{");
          for(i = 0; i < setting->len; i++) {
            fprintf(fp, (i < setting->len-1) ? "%f, " : "%f", setting->val.d);
          }
          fprintf(fp, "}\n");
          break;
        case BOOL_ARR:
          fprintf(fp, "{");
          for(i = 0; i < setting->len; i++) {
            fprintf(fp, setting->val.b ? "true" : "false");
            fprintf(fp, (i < setting->len-1) ? ", " : "");
          }
          fprintf(fp, "}\n");
          break;
        case CHAR_ARR:
          fprintf(fp, "{");
          for(i = 0; i < setting->len; i++) {
            fprintf(fp, (i < setting->len-1) ? "%c, " : "%c", setting->val.c);
          }
          fprintf(fp, "}\n");
          break;
        case STR_ARR:
          fprintf(fp, "{");
          for(i = 0; i < setting->len; i++) {
            fprintf(fp, (i < setting->len-1) ? "%s, " : "%s", setting->val.str);
          }
          fprintf(fp, "}\n");
          break;
      }
    }
    fprintf(fp, "\n");
  }

  if(fclose(fp)) { return INI_CLOSE_FAILURE; }

  return INI_NIL;
}

errINI_t setIntINI(ini_t *ini, char *section, char *key, int val) {
  return setINI(ini, section, key, &val, -1, INT);
}

errINI_t getIntINI(ini_t *ini, char *section, char *key, int *value) {
  return getINI(ini, section, key, value, NULL, INT);
}

errINI_t setFloatINI(ini_t *ini, char *section, char *key, double val) {
  return setINI(ini, section, key, &val, -1, FLOAT);
}

errINI_t getFloatINI(ini_t *ini, char *section, char *key, double *value) {
  return getINI(ini, section, key, value, NULL, FLOAT);
}

errINI_t setBoolINI(ini_t *ini, char *section, char *key, int val) {
  return setINI(ini, section, key, &val, -1, BOOL);
}

errINI_t getBoolINI(ini_t *ini, char *section, char *key, int *value) {
  return getINI(ini, section, key, value, NULL, BOOL);
}

errINI_t setCharINI(ini_t *ini, char *section, char *key, char val) {
  return setINI(ini, section, key, &val, -1, CHAR);
}

errINI_t getCharINI(ini_t *ini, char *section, char *key, char *value) {
  return getINI(ini, section, key, value, NULL, CHAR);
}

errINI_t setStrINI(ini_t *ini, char *section, char *key, char *val) {
  return setINI(ini, section, key, &val, -1, STR);
}

errINI_t getStrINI(ini_t *ini, char *section, char *key, char **value) {
  return getINI(ini, section, key, value, NULL, STR);
}

errINI_t setIntArrINI(ini_t *ini, char *section, char *key, int *val, int n) {
  return setINI(ini, section, key, val, n, INT_ARR);
}

errINI_t getIntArrINI(ini_t *ini, char *section, char *key, int **value, int *n) {
  return getINI(ini, section, key, value, &n, INT_ARR);
}

errINI_t setFloatArrINI(ini_t *ini, char *section, char *key, double *val, int n) {
  return setINI(ini, section, key, val, n, FLOAT_ARR);
}

errINI_t getFloatArrINI(ini_t *ini, char *section, char *key, double **value, int *n) {
  return getINI(ini, section, key, value, &n, FLOAT_ARR);
}

errINI_t setBoolArrINI(ini_t *ini, char *section, char *key, int *val, int n) {
  return setINI(ini, section, key, val, n, BOOL_ARR);
}

errINI_t getBoolArrINI(ini_t *ini, char *section, char *key, int **value, int *n) {
  return getINI(ini, section, key, value, &n, BOOL_ARR);
}

errINI_t setCharArrINI(ini_t *ini, char *section, char *key, char *val, int n) {
  return setINI(ini, section, key, val, n, CHAR_ARR);
}

errINI_t getCharArrINI(ini_t *ini, char *section, char *key, char **value, int *n) {
  return getINI(ini, section, key, value, &n, CHAR_ARR);
}

errINI_t setStrArrINI(ini_t *ini, char *section, char *key, char **val, int n) {
  return setINI(ini, section, key, val, n, STR_ARR);
}

errINI_t getStrArrINI(ini_t *ini, char *section, char *key, char ***value, int *n) {
  return getINI(ini, section, key, value, &n, STR_ARR);
}

errINI_t deleteINI(ini_t *ini, char *section, char *key) {
  if(!ini) { return INI_NIL_INI; }
  if(!section) { return INI_NIL_SECTION; }
  if(!key) { return INI_NIL_KEY; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }

  section_t *_section;
  setting_t *setting;
  int sections, settings;
  for(sections = lenArrayList(ini->sections); sections; sections--) {
    _section = (section_t *)getArrayList(ini->sections, sections-1);
    if(!strcmp(_section->header, section)) { // found section containg key to delete
      for(settings = lenArrayList(_section->settings); settings; settings--) {
        setting = (setting_t *)getArrayList(_section->settings, settings-1);
        if(!strcmp(setting->key ,key)) { // found setting to delete
          switch(setting->typeINI) {
            case INT:
            case FLOAT:
            case BOOL:
            case CHAR:
              break;
            case STR:
              free(setting->val.str);
              break;
            case INT_ARR:
              free(setting->val.iarr);
              break;
            case FLOAT_ARR:
              free(setting->val.darr);
              break;
            case BOOL_ARR:
              free(setting->val.barr);
              break;
            case CHAR_ARR:
              free(setting->val.carr);
              break;
            case STR_ARR:
              for(; setting->len; setting->len--) {
                free(setting->val.sarr[setting->len-1]);  
              }
              free(setting->val.sarr);
              break;
          }
          free(setting->key);
          free(setting);
          delArrayList(_section->settings, settings-1);
          if(!lenArrayList(_section->settings)) { // section is now empty; delete it.
            free(_section->header);
            freeArrayList(_section->settings);
            free(_section);
            delArrayList(ini->sections, sections-1);
          }
          return INI_NIL;
        }
      }
    }
  }

  return INI_NIL;
}
