/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  4/1/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <ini.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    F U N C T I O N S

*******************************************************************************/
ini_t *parseINI(char *fname) {
  FILE *fp = fopen(fname, "r");
  if(!fp) { 
    fprintf(stderr, "error! failure to open conf file: %s, exiting...\n", fname); 
    exit(EXIT_FAILURE);
  }

  ini_t *ini = malloc(sizeof(ini_t));
  ini->section = NULL;
  ini->rest = NULL;

  // parse the ini file following bnf grammar
  // if(err) { return NULL; }

  if(fclose(fp)) {
    fprintf(stderr, "error! failure to close conf file: %s, exiting...\n", fname);
    exit(EXIT_FAILURE);
  }

  return ini;
}

void  writeINI(ini_t *ini, char *fname) {
  FILE *fp = fopen(fname, "w+");
  if(!fp) { 
    fprintf(stderr, "error! failure to open conf file: %s, exiting...\n", fname); 
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "; ***AUTO GENERATED RISKY INI CONFIG***\n\n");

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

  if(fclose(fp)) {
    fprintf(stderr, "error! failure to close conf file: %s, exiting...\n", fname);
    exit(EXIT_FAILURE);
  }
}

char  *getINI(ini_t *ini, char *section, char *key) { // how to return error?
  settings_t *settings;
  for(; ini; ini = ini->rest) {
    if(ini->section->header == section) {
      for(settings = ini->section->settings; settings; settings = settings->rest) { 
        if(settings->setting->key == key) {
          return settings->setting->val;  
        }
      }
    }
  }
  return NULL; // not found
}

// over write if found, add if not found
void  setINI(ini_t *ini, char *section, char *key, char *val) { // error check for NULL char*?
  settings_t *settings;
  ini_t *tmp_ini = ini;
  for(; ini; ini = ini->rest) {
    if(ini->section) {
      if(!strcmp(ini->section->header, section)) { // found section to place pr in
        for(settings = ini->section->settings; settings; settings = settings->rest) { 
          if(!strcmp(settings->setting->key ,key)) { // overwrite existing value for pr if found
            free(settings->setting->val);
            settings->setting->val = calloc(strlen(val)+1, sizeof(char));
            strcpy(settings->setting->val, val);
            return;
          }
        } // add new pr to the settings for this section if key not found
        setting_t *new_setting = malloc(sizeof(setting_t));
        new_setting->key = calloc(strlen(key)+1, sizeof(char));
        strcpy(new_setting->key, key);
        new_setting->val = calloc(strlen(val)+1, sizeof(char));
        strcpy(new_setting->val, val);
        settings_t *new_settings = malloc(sizeof(settings_t));
        new_settings->setting = new_setting;
        new_settings->rest = ini->section->settings;
        ini->section->settings = new_settings;
        return;
      }
    }
  } // if never found section, add new section and key/val pr
  setting_t *new_setting = malloc(sizeof(setting_t));
  new_setting->key = calloc(strlen(key)+1, sizeof(char));
  strcpy(new_setting->key, key);
  new_setting->val = calloc(strlen(val)+1, sizeof(char));
  strcpy(new_setting->val, val);
  settings_t *new_settings = malloc(sizeof(settings_t));
  new_settings->setting = new_setting;
  new_settings->rest = NULL;
  section_t *new_section = malloc(sizeof(section_t));
  new_section->header = calloc(strlen(section)+1, sizeof(char));
  strcpy(new_section->header, section);
  new_section->settings = new_settings;
  ini_t *new_ini = malloc(sizeof(ini_t));
  new_ini->section = new_section;
  new_ini->rest = tmp_ini->rest;
  tmp_ini->rest = new_ini;
}

//freeINI(ini_t *ini) { } // FIXME: ??
