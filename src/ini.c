/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  4/4/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************

    P A R S I N G   E R R O R S

*******************************************************************************/
char *NIL_SECTION = "section cannot be NULL"; 
char *NIL_KEY = "key cannot be NULL";
char *NIL_VAL = "val cannot be NULL";
char *F_OPEN = "failure to open conf file"; 
char *F_CLOSE = "failure to close conf file"; 

/*******************************************************************************

    S T R U C T S

*******************************************************************************/
typedef struct setting {  // for atomic config setting --> [key . val]
  char *key, *val; 
} setting_t;

typedef struct settings { // list of config setting/section  --> ([key . val] ...)
 setting_t *setting;
 struct settings *rest;
} settings_t;

typedef struct section {  // config section settings --> { [section header] . ([key . val] ...) }
  char *header;
  settings_t *settings;
} section_t;

typedef struct ini {      // list of ( { [section header] . ([key . val] ...) } ... )
  section_t *section;
  struct ini *rest;
} ini_t;

/*******************************************************************************

    P R I V A T E   F U N C T I O N S

*******************************************************************************/
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

/*******************************************************************************

    P U B L I C   F U N C T I O N S

*******************************************************************************/
const char *readINI(ini_t **ini, char *fname) {
  FILE *fp = fopen(fname, "r");
  if(!fp) { return F_OPEN; }

  *ini = malloc(sizeof(ini_t));
  (*ini)->section = NULL;
  (*ini)->rest = NULL;

  // parse the ini file following bnf grammar

  if(fclose(fp)) { return F_CLOSE; }

  return NULL;
}

int writeINI(ini_t *ini, char *fname) {
  if(!ini) { return 1; }

  FILE *fp = fopen(fname, "w+");
  if(!fp) { return 1; }

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

  if(fclose(fp)) { return 1; }

  return 0;
}

char  *getINI(ini_t *ini, char *section, char *key) {
  if(!ini | !section | !key) { return NULL; }
  settings_t *settings;
  for(; ini; ini = ini->rest) {
    if(ini->section && !strcmp(ini->section->header, section)) {
      for(settings = ini->section->settings; settings; settings = settings->rest) { 
        if(!strcmp(settings->setting->key, key)) {
          return settings->setting->val;  
        }
      }
    }
  }
  return NULL; // not found
}

int setINI(ini_t *ini, char *section, char *key, char *val) {
  if(!ini | !section | !key | !val) { return 1; }
  settings_t *settings;
  ini_t *tmp_ini = ini;
  for(; ini; ini = ini->rest) {
    if(ini->section) {
      if(!strcmp(ini->section->header, section)) { // found section to place pr in
        for(settings = ini->section->settings; settings; settings = settings->rest) { 
          if(!strcmp(settings->setting->key ,key)) { // overwrite existing value for pr if found
            free(settings->setting->val);
            settings->setting->val = calloc(strlen(val)+1, sizeof(char));
            if(!settings->setting->val) { return 1; }
            strcpy(settings->setting->val, val);
            return 0;
          }
        } // add new pr to the settings for this section if key not found
        ini->section->settings = make_settings(make_setting(key, val), ini->section->settings);
        return 0;
      }
    }
  } // if never found section, add new section and key/val pr
  tmp_ini->rest = make_ini(make_section(section, make_settings(make_setting(key, val), NULL)), tmp_ini->rest);
  return 0;
}

ini_t *makeINI() {
  return make_ini(NULL, NULL);  
}

void freeINI(ini_t *ini) {
  if(!ini) { return; }
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
}