/******************************************************************************
 * FILE:    ini.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 3/27/17                                                           *
 * EDITED:  4/24/17                                                           *
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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/******************************************************************************
 *                                                                            *
 *   S T R U C T S                                                            *
 *                                                                            *
 ******************************************************************************/
typedef struct setting { char *key, *val; } setting_t; /* [key . val] */

typedef struct settings { /* ([key . val] ...) */
 setting_t *setting;
 struct settings *rest;
} settings_t;

typedef struct section { /* { [section header] . ([key . val] ...) } */
  char *header;
  settings_t *settings;
} section_t;
  
typedef struct ini { /* ( { [section header] . ([key . val] ...) } ... ) */
  section_t *section;
  struct ini *rest;
} ini_t;

/******************************************************************************
 *                                                                            *
 *   P R I V A T E   F U N C T I O N S                                        *
 *                                                                            *
 ******************************************************************************/
setting_t *make_setting(char *key, char *val) {
  setting_t *new_setting = malloc(sizeof(setting_t));
  if(!new_setting) { return NULL; }
  new_setting->key = calloc(strlen(key)+1, sizeof(char));
  if(!new_setting->key) {
    free(new_setting);
    return NULL;
  }
  strcpy(new_setting->key, key);
  new_setting->val = calloc(strlen(val)+1, sizeof(char));
  if(!new_setting->val) {
    free(new_setting->key);
    free(new_setting);
    return NULL;
  }
  strcpy(new_setting->val, val);
  return new_setting;
}

settings_t *make_settings(setting_t *setting, settings_t *rest) {
  settings_t *new_settings = malloc(sizeof(settings_t));
  if(!new_settings) { return NULL; }
  new_settings->setting = setting;
  new_settings->rest = rest;
  return new_settings;
}

section_t *make_section(char *header, settings_t *settings) {
  section_t *new_section = malloc(sizeof(section_t));
  if(!new_section) { return NULL; }
  new_section->header = calloc(strlen(header)+1, sizeof(char));
  if(!new_section->header) {
    free(new_section);
    return NULL;
  }
  strcpy(new_section->header, header);
  new_section->settings = settings;
  return new_section;
}

ini_t *make_ini(section_t *section, ini_t *confs) {
  ini_t *new_ini = malloc(sizeof(ini_t));
  if(!new_ini) { return NULL; }
  new_ini->section = section;
  new_ini->rest = confs;
  return new_ini;
}

int isSpace(int c) { return isspace(c); }
int isDividor(int c) { return c == ':' || c == '=';  }
int isComment(int c) { return c == '#' || c == ';';  }
int isSpecial(int c) { return ispunct(c) && !isDividor(c) && !isComment(c); }
int isChar(int c) { return isalnum(c) | isSpecial(c); }

int isValidTerm(char *term) {
  for(; *term; term++) { if(!isChar(*term)) { return 0;  } }
  return 1;
}

int isValidKey(char *key) { return isValidTerm(key); }
int isValidHeader(char *section) { return isValidTerm(section); }
int isValidVal(char *val) { return isValidTerm(val); }

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrINI(errINI_t errINI) {
  switch(errINI) {
    case INI_OPEN_FAILURE: return "failure to open conf file";
    case INI_CLOSE_FAILURE: return "failure to close conf file";
    case INI_NULL_FNAME: return "nil conf file name";
    case INI_INVALID_CONF: return "invalid conf file";
    case INI_INVALID_KEY: return "key does not adhere to library grammar";
    case INI_INVALID_VAL: return "value does not adhere to library grammar";
    case INI_INVALID_SECTION: return "header does not adhere to library grammar";
    case INI_NULL_INI: return "nil ini";
    case INI_NULL_KEY: return "nil key";
    case INI_NULL_VAL: return "nil value";
    case INI_NULL_SECTION: return "nil section";
    case INI_OUT_OF_MEMORY: return "out of memory";
    case INI_NIL: return "";
    default: return "unrecognized INI error code";
  }
}

errINI_t readINI(ini_t **ini, char *fname) {
  if(!ini) { return INI_NULL_INI; }
  if(!fname) { return INI_NULL_FNAME; }

  FILE *fp = fopen(fname, "r");
  if(!fp) { return INI_OPEN_FAILURE; }

  errINI_t errINI;
  if((errINI = makeINI(ini)) != INI_NIL) { return errINI; }

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
        if((errINI = setINI(*ini, section, key, val)) != INI_NIL) { goto err; }
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
  if(!ini) { return INI_NULL_INI; }
  if(!fname) { return INI_NULL_FNAME; }

  FILE *fp = fopen(fname, "w+");
  if(!fp) { return INI_OPEN_FAILURE; }

  settings_t *settings;
  for(; ini; ini = ini->rest) {
    if(ini->section) {
      fprintf(fp, "[%s]\n", ini->section->header);
      for(settings = ini->section->settings; settings; settings = settings->rest) {
        fprintf(fp, "%s=%s\n", settings->setting->key, settings->setting->val);
      }
      fprintf(fp, "\n");
    }
  }

  if(fclose(fp)) { return INI_CLOSE_FAILURE; }

  return INI_NIL;
}

errINI_t makeINI(ini_t **ini) {
  if(!ini) { return INI_NULL_INI; }

  *ini = make_ini(NULL, NULL);

  return *ini ? INI_NIL : INI_OUT_OF_MEMORY;
}

errINI_t freeINI(ini_t *ini) {
  if(!ini) { return INI_NULL_INI; }

  settings_t *sets;
  settings_t *tmp_set;
  ini_t *tmp_ini;
  for(; ini; tmp_ini = ini->rest, free(ini), ini = tmp_ini) {
    if(ini->section) {
      free(ini->section->header);
      for(sets = ini->section->settings; sets; tmp_set = sets->rest, free(sets), sets = tmp_set) {
        free(sets->setting->val);
        free(sets->setting->key);
        free(sets->setting);
      }
      free(ini->section);
    }
  }

  return INI_NIL;
}

errINI_t getINI(ini_t *ini, char *section, char *key, char **val) {
  if(!ini) { return INI_NULL_INI; }
  if(!section) { return INI_NULL_SECTION; }
  if(!key) { return INI_NULL_KEY; }
  if(!val) { return INI_NULL_VAL; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }

  settings_t *settings;
  for(; ini; ini = ini->rest) {
    if(ini->section && !strcmp(ini->section->header, section)) {
      for(settings = ini->section->settings; settings; settings = settings->rest) { 
        if(!strcmp(settings->setting->key, key)) {
          *val = settings->setting->val;  
          return INI_NIL;
        }
      }
    }
  }

  *val = NULL;
  return INI_NIL;
}

errINI_t setINI(ini_t *ini, char *section, char *key, char *val) {
  if(!ini) { return INI_NULL_INI; }
  if(!section) { return INI_NULL_SECTION; }
  if(!key) { return INI_NULL_KEY; }
  if(!val) { return INI_NULL_VAL; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }
  if(!isValidVal(val)) { return INI_INVALID_VAL; }

  settings_t *settings;
  ini_t *tmp_ini = ini;
  for(; ini; ini = ini->rest) {
    if(ini->section) {
      if(!strcmp(ini->section->header, section)) { // found section to place pr in
        for(settings = ini->section->settings; settings; settings = settings->rest) { 
          if(!strcmp(settings->setting->key ,key)) { // overwrite existing value for pr if found
            free(settings->setting->val);
            settings->setting->val = calloc(strlen(val)+1, sizeof(char));
            if(!settings->setting->val) { return INI_NULL_VAL; }
            strcpy(settings->setting->val, val);
            return INI_NIL;  
          }
        } // add new pr to the settings for this section if key not found
        ini->section->settings = make_settings(make_setting(key, val), ini->section->settings);
        return INI_NIL;  
      }
    }
  } // if never found section, add new section and key/val pr
  tmp_ini->rest = make_ini(make_section(section, make_settings(make_setting(key, val), NULL)), tmp_ini->rest);

  return INI_NIL;  
}

errINI_t deleteINI(ini_t *ini, char *section, char *key) {
  if(!ini) { return INI_NULL_INI; }
  if(!section) { return INI_NULL_SECTION; }
  if(!key) { return INI_NULL_KEY; }
  if(!isValidHeader(section)) { return INI_INVALID_SECTION; }
  if(!isValidKey(key)) { return INI_INVALID_KEY; }

  settings_t *settings, *prevSetting = NULL;
  ini_t *prevINI = NULL;
  int keys;
  for(; ini; prevINI = ini, ini = ini->rest) {
    if(ini->section) {
      if(!strcmp(ini->section->header, section)) { // found section containg key to delete
        for(keys = 0, settings = ini->section->settings; settings; settings = settings->rest, keys++) {
          if(!strcmp(settings->setting->key ,key)) { // found setting to delete
            free(settings->setting->val);
            free(settings->setting->key);
            if(prevSetting) { prevSetting->rest = settings->rest; } // fix settings list
            free(settings->setting);
            keys--;
          }
          prevSetting = settings;
        }
        if(keys == 0) { // no other settings in section
          free(ini->section->settings);
          free(ini->section->header);
          if(prevINI) { prevINI->rest = ini->rest; } // fix ini/sections list
          free(ini->section);
        }
        return INI_NIL;  
      }
    }
  }

  return INI_NIL;  
}
