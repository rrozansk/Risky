/******************************************************************************
 * FILE:    ini.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  7/7/17                                                            *
 * INFO:    Implementation of the interface located in ini.h.                 *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <ini.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   S T R U C T S                                                            *
 *                                                                            *
 ******************************************************************************/
typedef struct setting { // setting ::= [key, val, type]
  char *key;
  typeINI_t typeINI;
  int len;               // len of arr/str (if applicable)
  union {
    int i;               // int
    float f;             // float
    int b;               // bool
    char c;              // char
    char *str;           // string
    int *iarr;           // int arr
    float *farr;         // float arr
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

typedef struct ini {         // ini ::= section*
  option_t options;
  arrayList_t *sections;
} ini_t; 

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
static option_t UNUSED_BITS = 0b11111110;

/******************************************************************************
 *                                                                            *
 *   P R I V A T E   F U N C T I O N S                                        *
 *                                                                            *
 ******************************************************************************/

/*********************************ARRAY LISTS**********************************/

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

/***********************************HELPERS************************************/

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

/***********************************GETTER*************************************/

static errINI_t settingGet(setting_t *setting, int index, typeINI_t typeINI, void *value) {
  if(!setting) { return INI_NIL_SETTING; }
  if(setting->typeINI != typeINI) { return INI_TYPE_MISMATCH; }
  if((typeINI == INT_ARRAY || typeINI == FLOAT_ARRAY || typeINI == BOOL_ARRAY ||
        typeINI == CHAR_ARRAY || typeINI == STRING_ARRAY) &&
      (index < 0 || index >= setting->len)) {
    return INI_INVALID_INDEX;
  }
  if(!value) { return INI_NIL_VALUE; }
  
  switch(typeINI) {
    case UNINITIALIZED:
      return INI_NIL;
    case INT:
      *(int *)value = setting->val.i;
      return INI_NIL;
    case FLOAT:
      *(float *)value = setting->val.f;
      return INI_NIL;
    case BOOL:
      *(int *)value = setting->val.b;
      return INI_NIL;
    case CHAR:
      *(char *)value = setting->val.c;
      return INI_NIL;
    case STRING:
      strncpy(*(char **)value, setting->val.str, setting->len);
      return INI_NIL;
    case INT_ARRAY:
        *(int *)value = (setting->val.iarr)[index];
      return INI_NIL;
    case FLOAT_ARRAY:
        *(float *)value = (setting->val.farr)[index];
      return INI_NIL;
    case BOOL_ARRAY:
        *(int *)value = (setting->val.barr)[index];
      return INI_NIL;
    case CHAR_ARRAY:
        *(char *)value = (setting->val.carr)[index];
      return INI_NIL;
    case STRING_ARRAY:
        strncpy(*(char **)value, (setting->val.sarr)[index], strlen((setting->val.sarr)[index]));
      return INI_NIL;
    default:
      return INI_NIL;
  }
}

/***********************************SETTER*************************************/

static errINI_t settingSet(setting_t *setting, int index, typeINI_t typeINI, void *value) {
  if(!setting) { return INI_NIL_SETTING; }
  if(setting->typeINI != typeINI) { return INI_TYPE_MISMATCH; }
  if((typeINI == INT_ARRAY || typeINI == FLOAT_ARRAY || typeINI == BOOL_ARRAY ||
        typeINI == CHAR_ARRAY || typeINI == STRING_ARRAY) &&
      (index < 0 || index > setting->len)) {
    return INI_INVALID_INDEX;
  }
  if(!value) { return INI_NIL_VALUE; }

  switch(typeINI) {
    case UNINITIALIZED: // not used/applicable
      return INI_NIL;
    case INT:
      setting->val.i = *(int *)value;
      return INI_NIL;
    case FLOAT:
      setting->val.f = *(float *)value;
      return INI_NIL;
    case BOOL:
      setting->val.b = *(int *)value;
      return INI_NIL;
    case CHAR:
      setting->val.c = *(char *)value;
      return INI_NIL;
    case STRING:
      if(setting->typeINI == UNINITIALIZED) {
        setting->val.str = calloc(strlen(*(char **)value)+1, sizeof(char));
      }
      if(strlen(setting->val.str) != strlen(*(char **)value)) {
        setting->val.str = realloc(setting->val.iarr, (strlen(*(char **)value)+1) * sizeof(char));
      }
      if(!(setting->val.str)) { return INI_OUT_OF_MEMORY; }
      strncpy(setting->val.str, *(char **)value, strlen(*(char **)value));
      return INI_NIL;
    case INT_ARRAY:
      if(setting->typeINI == UNINITIALIZED) {
        setting->val.iarr = malloc(sizeof(int) * 1);
      }
      if(index == setting->len) {
        setting->val.iarr = realloc(setting->val.iarr, sizeof(int) * ++setting->len);
      }
      if(!(setting->val.iarr)) { return INI_OUT_OF_MEMORY; }
      setting->val.iarr[index] = *(int *)value;
      return INI_NIL;
    case FLOAT_ARRAY:
      if(setting->typeINI == UNINITIALIZED) {
        setting->val.farr = malloc(sizeof(float) * 1);
      }
      if(index == setting->len) {
        setting->val.farr = realloc(setting->val.farr, sizeof(float) * ++setting->len);
      }
      if(!(setting->val.farr)) { return INI_OUT_OF_MEMORY; }
      setting->val.farr[index] = *(float *)value;
      return INI_NIL;
    case BOOL_ARRAY:
      if(setting->typeINI == UNINITIALIZED) {
        setting->val.barr = malloc(sizeof(int) * 1);
      }
      if(index == setting->len) {
        setting->val.barr = realloc(setting->val.barr, sizeof(int) * ++setting->len);
      }
      if(!(setting->val.barr)) { return INI_OUT_OF_MEMORY; }
      setting->val.barr[index] = *(int *)value;
      return INI_NIL;
    case CHAR_ARRAY:
      if(setting->typeINI == UNINITIALIZED) {
        setting->val.carr = malloc(sizeof(char) * 1);
      }
      if(index == setting->len) {
        setting->val.carr = realloc(setting->val.carr, sizeof(char) * ++setting->len);
      }
      if(!(setting->val.carr)) { return INI_OUT_OF_MEMORY; }
      setting->val.carr[index] = *(char *)value;
      return INI_NIL;
    case STRING_ARRAY:
      if(setting->typeINI == UNINITIALIZED) {
        setting->val.sarr = calloc(1, sizeof(char *));
      }
      if(index == setting->len) {
        setting->val.sarr = realloc(setting->val.sarr, sizeof(char *) * ++setting->len);
      }
      if(!(setting->val.sarr)) { return INI_OUT_OF_MEMORY; }
      setting->val.sarr[index] = calloc(strlen(*(char **)value)+1, sizeof(char));
      if(!(setting->val.sarr[index])) { return INI_OUT_OF_MEMORY; }
      strncpy(setting->val.sarr[index], *(char **)value, strlen(*(char **)value));
      return INI_NIL;
    default:
      return INI_NIL;
  }
}

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrINI(errINI_t errINI) {
  switch(errINI) {
    // misc errors
    case INI_OPEN_FAILURE: return "failure to open conf file";
    case INI_CLOSE_FAILURE: return "failure to close conf file";
    case INI_OUT_OF_MEMORY: return "out of memory";
    case INI_TYPE_MISMATCH: return "value type requested does not match value type stored";
    case INI_DUPLICATE_SETTING: return "cannot create duplicate setting";
    // invalid input errors
    case INI_INVALID_CONF: return "invalid conf file";
    case INI_INVALID_KEY: return "key does not adhere to library grammar";
    case INI_INVALID_VALUE: return "value does not adhere to library grammar";
    case INI_INVALID_SECTION: return "header does not adhere to library grammar";
    case INI_INVALID_INDEX: return "invalid array index";
    case INI_INVALID_OPTIONS: return "invalid options";
    // nil arg errors
    case INI_NIL_FNAME: return "nil conf file name";
    case INI_NIL_INI: return "nil ini";
    case INI_NIL_KEY: return "nil key";
    case INI_NIL_VALUE: return "nil value";
    case INI_NIL_SECTION: return "nil section";
    case INI_NIL_OPTIONS: return "nil options";
    case INI_NIL_SETTING: return "nil settings";
    case INI_NIL_TYPE: return "nil type";
    case INI_NIL_LENGTH: return "nil length";
    case INI_NIL: return "";
    default: return "unrecognized INI error code";
  }
}

errINI_t makeINI(ini_t **ini) {
  if(!ini) { return INI_NIL_INI; }

  if(!(*ini = calloc(1, sizeof(ini_t)))) { return INI_OUT_OF_MEMORY; }
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
        case UNINITIALIZED:
        case INT:
        case FLOAT:
        case BOOL:
        case CHAR:
          break;
        case STRING:
          free(setting->val.str);
          break;
        case INT_ARRAY:
          free(setting->val.iarr);
          break;
        case FLOAT_ARRAY:
          free(setting->val.farr);
          break;
        case BOOL_ARRAY:
          free(setting->val.barr);
          break;
        case CHAR_ARRAY:
          free(setting->val.carr);
          break;
        case STRING_ARRAY:
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

errINI_t readINI(ini_t **ini, char *fname) { // FIXME: implement new grammar
  if(!ini) { return INI_NIL_INI; }
  if(!fname) { return INI_NIL_FNAME; }

  FILE *fp = fopen(fname, "r");
  if(!fp) { return INI_OPEN_FAILURE; }

  errINI_t errINI;
  if((errINI = makeINI(ini)) != INI_NIL) { return errINI; }

  //really the reader/parser should haver something like a dynamic buffer char buffer[120];
  //then we can do this ==> sscanf(buffer, "%[type]", &[var]);
  //parsers become trivial ==> if(sscanf(buffer, "%i", &i) > 0) {} // parseInt()
  //can use array lists (as stk) to parse arrays then malloc exact size when done

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
          errINI = INI_INVALID_VALUE;
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
  int sections, settings, i, j, k;
  for(i = 0, sections = lenArrayList(ini->sections); i < sections; i++) {
    section = (section_t *)getArrayList(ini->sections, i);
    fprintf(fp, "[%s]\n", section->header);
    for(j = 0, settings = lenArrayList(section->settings); j < settings; j++) {
      setting = (setting_t *)getArrayList(section->settings, j);
      fprintf(fp, "%s", setting->key);
      fprintf(fp, (ini->options & SETTING_SEPERATOR) ? ":" : "=");
      switch(setting->typeINI) {
        case UNINITIALIZED:
          fprintf(fp, "**UNINITIALIZED**\n");
          break;
        case INT:
          fprintf(fp, "%i\n", setting->val.i);
          break;
        case FLOAT:
          fprintf(fp, "%f\n", setting->val.f);
          break;
        case BOOL:
          fprintf(fp, setting->val.b ? "true\n" : "false\n");
          break;
        case CHAR:
          fprintf(fp, "'%c'\n", setting->val.c);
          break;
        case STRING:
          fprintf(fp, "\"%s\"\n", setting->val.str);
          break;
        case INT_ARRAY:
          fprintf(fp, "{");
          for(k = 0; k < setting->len; k++) {
            fprintf(fp, (k < setting->len-1) ? "%i, " : "%i", setting->val.i);
          }
          fprintf(fp, "}\n");
          break;
        case FLOAT_ARRAY:
          fprintf(fp, "{");
          for(k = 0; k < setting->len; k++) {
            fprintf(fp, (k < setting->len-1) ? "%f, " : "%f", setting->val.f);
          }
          fprintf(fp, "}\n");
          break;
        case BOOL_ARRAY:
          fprintf(fp, "{");
          for(k = 0; k < setting->len; k++) {
            fprintf(fp, setting->val.b ? "true" : "false");
            fprintf(fp, (k < setting->len-1) ? ", " : "");
          }
          fprintf(fp, "}\n");
          break;
        case CHAR_ARRAY:
          fprintf(fp, "{");
          for(k = 0; k < setting->len; k++) {
            fprintf(fp, (k < setting->len-1) ? "'%c', " : "'%c'", setting->val.c);
          }
          fprintf(fp, "}\n");
          break;
        case STRING_ARRAY:
          fprintf(fp, "{");
          for(k = 0; k < setting->len; k++) {
            fprintf(fp, (k < setting->len-1) ? "\"%s\", " : "\"%s\"", setting->val.str);
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

errINI_t getConfigurationINI(ini_t *ini, option_t *options) {
  if(!ini) { return INI_NIL_INI; }
  if(!options) { return INI_NIL_OPTIONS; }

  *options = ini->options;

  return INI_NIL;  
}

errINI_t setConfigurationINI(ini_t *ini, option_t options) {
  if(!ini) { return INI_NIL_INI; }
  if(options & UNUSED_BITS) { return INI_INVALID_OPTIONS; }

  ini->options = options;

  return INI_NIL;  
}

errINI_t createSetting(ini_t *ini, char *section, char *key, setting_t **setting) {
  if(!ini) { return INI_NIL_INI; }
  if(!section) { return INI_NIL_SECTION; }
  if(!key) { return INI_NIL_KEY; }
  if(!setting) { return INI_NIL_SETTING; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }

  section_t *_section;
  int sections, settings;
  for(sections = lenArrayList(ini->sections); sections; sections--) {
    _section = (section_t *)getArrayList(ini->sections, sections-1);
    if(!strcmp(_section->header, section)) { // found section
      for(settings = lenArrayList(_section->settings); settings; settings--) {
        *setting = (setting_t *)getArrayList(_section->settings, settings-1);
        if(!strcmp((*setting)->key, key)) {  return INI_DUPLICATE_SETTING; }
      }
      goto INSERT_SETTING;
    }
  }
  if(!(_section = malloc(sizeof(section_t)))) { return INI_OUT_OF_MEMORY; }
  if(!(_section->settings = newArrayList())) {
    free(_section);
    return INI_OUT_OF_MEMORY;
  }
  if(!(_section->header = calloc(strlen(section)+1, sizeof(char)))) {
    freeArrayList(_section->settings);
    free(_section);
    return INI_OUT_OF_MEMORY;
  }
  strncpy(_section->header, section, strlen(section));

INSERT_SETTING:
  *setting = malloc(sizeof(setting_t));
  if(!*setting) { return INI_OUT_OF_MEMORY; }

  (*setting)->key = calloc(strlen(key)+1, sizeof(char));
  if(!(*setting)->key) {
    free(*setting);
    *setting = NULL;
    return INI_OUT_OF_MEMORY;
  }

  (*setting)->len = 0;
  (*setting)->typeINI = UNINITIALIZED;
  strncpy((*setting)->key, key, strlen(key));
  putArrayList(_section->settings, *setting);
  return INI_NIL;  
}

errINI_t lookupSetting(ini_t *ini, char *section, char *key, setting_t **setting) {
  if(!ini) { return INI_NIL_INI; }
  if(!section) { return INI_NIL_SECTION; }
  if(!key) { return INI_NIL_KEY; }
  if(!setting) { return INI_NIL_SETTING; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }

  section_t *_section;
  int sections, settings;
  for(sections = lenArrayList(ini->sections); sections; sections--) {
    _section = (section_t *)getArrayList(ini->sections, sections-1);
    if(!strcmp(_section->header, section)) { // found section
      for(settings = lenArrayList(_section->settings); settings; settings--) {
        *setting = (setting_t *)getArrayList(_section->settings, settings-1);
        if(!strcmp((*setting)->key, key)) {  return INI_NIL; } // found key/setting
      }
    }
  }

  *setting = NULL;
  return INI_NIL;  
}

errINI_t deleteSetting(ini_t *ini, char *section, char *key) {
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
            case UNINITIALIZED:
            case INT:
            case FLOAT:
            case BOOL:
            case CHAR:
              break;
            case STRING:
              free(setting->val.str);
              break;
            case INT_ARRAY:
              free(setting->val.iarr);
              break;
            case FLOAT_ARRAY:
              free(setting->val.farr);
              break;
            case BOOL_ARRAY:
              free(setting->val.barr);
              break;
            case CHAR_ARRAY:
              free(setting->val.carr);
              break;
            case STRING_ARRAY:
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

errINI_t settingType(setting_t *setting, typeINI_t *typeINI) {
  if(!setting) { return INI_NIL_SETTING; }
  if(!typeINI) { return INI_NIL_TYPE; }
  
  *typeINI = setting->typeINI;

  return INI_NIL;  
}

errINI_t settingKeyLength(setting_t *setting, int *length) {
  if(!setting) { return INI_NIL_SETTING; }
  if(!length) { return INI_NIL_LENGTH; }

  *length = strlen(setting->key);

  return INI_NIL;  
}

errINI_t settingKey(setting_t *setting, char **key) {
  if(!setting) { return INI_NIL_SETTING; }
  if(!key) { return INI_NIL_KEY; }

  strncpy(*key, setting->key, strlen(setting->key));

  return INI_NIL;  
}

errINI_t settingLength(setting_t *setting, int *length) {
  if(!setting) { return INI_NIL_SETTING; }
  if(!length) { return INI_NIL_LENGTH; }

  *length = setting->len;

  return INI_NIL;  
}

errINI_t settingElemLength(setting_t *setting, int index, int *length) {
  if(!setting) { return INI_NIL_SETTING; }
  if(!length) { return INI_NIL_LENGTH; }
  if(setting->typeINI == INT_ARRAY || setting->typeINI == FLOAT_ARRAY ||
     setting->typeINI == BOOL_ARRAY || setting->typeINI == CHAR_ARRAY ||
     setting->typeINI == STRING_ARRAY) { return INI_TYPE_MISMATCH; }
  if(index < 0 || index >= setting->len) { return INI_INVALID_INDEX; }

  if(setting->typeINI == STRING_ARRAY) { *length = strlen(setting->val.sarr[index]); }
  else { *length = 0; }

  return INI_NIL;  
}

errINI_t settingGetInt(setting_t *setting, int *value) {
  return settingGet(setting, -1, INT, value);
}

errINI_t settingGetFloat(setting_t *setting, float *value) {
  return settingGet(setting, -1, FLOAT, value);
}

errINI_t settingGetBool(setting_t *setting, int *value) {
  return settingGet(setting, -1, BOOL, value);
}

errINI_t settingGetChar(setting_t *setting, char *value) {
  return settingGet(setting, -1, CHAR, value);
}

errINI_t settingGetString(setting_t *setting, char **value) {
  return settingGet(setting, -1, STRING, value);
}

errINI_t settingGetIntElem(setting_t *setting, int index, int *elem) {
  return settingGet(setting, index, INT_ARRAY, elem);
}

errINI_t settingGetFloatElem(setting_t *setting, int index, float *elem) {
  return settingGet(setting, index, FLOAT_ARRAY, elem);
}

errINI_t settingGetBoolElem(setting_t *setting, int index, int *elem) {
  return settingGet(setting, index, BOOL_ARRAY, elem);
}

errINI_t settingGetCharElem(setting_t *setting, int index, char *elem) {
  return settingGet(setting, index, CHAR_ARRAY, elem);
}

errINI_t settingGetStringElem(setting_t *setting, int index, char **elem) {
  return settingGet(setting, index, STRING_ARRAY, elem);
}

errINI_t settingSetInt(setting_t *setting, int value) {
  return settingSet(setting, -1, INT, &value);
}

errINI_t settingSetFloat(setting_t *setting, float value) {
  return settingSet(setting, -1, FLOAT, &value);
}

errINI_t settingSetBool(setting_t *setting, int value) {
  return settingSet(setting, -1, BOOL, &value);
}

errINI_t settingSetChar(setting_t *setting, char value) {
  return settingSet(setting, -1, CHAR, &value);
}

errINI_t settingSetString(setting_t *setting, char *value) {
  return settingSet(setting, -1, STRING, &value);
}

errINI_t settingSetIntElem(setting_t *setting, int index, int elem) {
  return settingSet(setting, index, INT_ARRAY, &elem);
}

errINI_t settingSetFloatElem(setting_t *setting, int index, float elem) {
  return settingSet(setting, index, FLOAT_ARRAY, &elem);
}

errINI_t settingSetBoolElem(setting_t *setting, int index, int elem) {
  return settingSet(setting, index, BOOL_ARRAY, &elem);
}

errINI_t settingSetCharElem(setting_t *setting, int index, char elem) {
  return settingSet(setting, index, CHAR_ARRAY, &elem);
}

errINI_t settingSetStringElem(setting_t *setting, int index, char *elem) {
  return settingSet(setting, index, STRING_ARRAY, &elem);
}
