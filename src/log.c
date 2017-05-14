/******************************************************************************
 * FILE:    log.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/30/17                                                           *
 * EDITED:  5/13/17                                                           *
 * INFO:    Implementation of the interface located in log.h.                 *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <log.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct log {
  int columns;
  char *directory;
  char *name;
  FILE *fp;
} log_t;

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrLOG(errLOG_t errLOG) {
  switch(errLOG) {
    case LOG_OUT_OF_MEMORY: return "out of memory";
    case LOG_OPEN_FAIL: return "failed to open log";
    case LOG_CLOSE_FAIL: return "failed to close log";
    case LOG_DIR_CREATION_FAIL: return "failed to create log directory";
    case LOG_INVALID_ARR_SIZE: return "arrays size must be > 0";
    case LOG_INVALID_WIDTH: return "column width must be 80-400";
    case LOG_INVALID_TIMESTAMP: return "timestamp must be 1 or 0";
    case LOG_INVALID_DIR: return "dir must be less than 255 chars long";
    case LOG_NIL_LOG: return "nil log";
    case LOG_NIL_NAME: return "nil file name";
    case LOG_NIL_DIR: return "nil directory";
    case LOG_NIL_TITLE: return "nil title";
    case LOG_NIL_HEADER: return "nil header";
    case LOG_NIL_SECTION: return "nil section";
    case LOG_NIL_KEY: return "nil key";
    case LOG_NIL_STR_ARR: return "nil string array";
    case LOG_NIL: return "";
    default: return "unkown errLOG_t error code";  
  }
}

errLOG_t makeLOG(log_t **log, int columns, char *dir, char *name) {
  if(!log) { return LOG_NIL_LOG; }
  if(!dir) { return LOG_NIL_DIR; }
  if(!name) { return LOG_NIL_NAME; }
  if(columns < 80 || columns > 400) { return LOG_INVALID_WIDTH; }
  if((strlen(dir) + strlen(name)) > 255) { return LOG_INVALID_DIR; }

  if(!(*log = calloc(1, sizeof(log_t)))) { return LOG_OUT_OF_MEMORY; }

  if(!((*log)->directory = calloc(strlen(dir)+1, sizeof(char)))) {
    return LOG_OUT_OF_MEMORY;
  }
  sprintf((*log)->directory, "%s", dir);

  if(!((*log)->name = calloc(strlen(name)+1, sizeof(char)))) {
    return LOG_OUT_OF_MEMORY;
  }
  sprintf((*log)->name, "%s", name);

  (*log)->columns = columns;
  
  struct stat st;
  if(mkdir(dir, 0700) && stat(dir, &st)) { return LOG_DIR_CREATION_FAIL; }
  
  char *path = calloc(strlen(dir)+strlen(name)+6, sizeof(char));
  if(!path) { return LOG_OUT_OF_MEMORY; }
  sprintf(path, "%s/%s.txt", dir, name);
  (*log)->fp = fopen(path, "w");
  free(path);

  return (!(*log)->fp) ? LOG_OPEN_FAIL : LOG_NIL;
}

errLOG_t freeLOG(log_t *log) {
  if(!log) { return LOG_NIL_LOG; }

  if(log->name) { free(log->name); }
  if(log->directory) { free(log->directory); }

  if(log->fp && !fclose(log->fp)) { return LOG_CLOSE_FAIL; }
  
  free(log);

  return LOG_NIL;
}

errLOG_t logIntArr(log_t *log, int *arr, int size) {  // FIXME: adhere to log columns length
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_STR_ARR; }
  if(size <= 0) { return LOG_INVALID_ARR_SIZE; }

  fprintf(log->fp, "{");
  int i;
  for(i = 0; i < size; i++) {
    (i < size -1) ? fprintf(log->fp, "%i, ", arr[i]) : fprintf(log->fp, "%i", arr[i]);  
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logIntArr2D(log_t *log, int **arr, int x, int y) {  // FIXME: adhere to log columns length
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_STR_ARR; }
  if(x <= 0) { return LOG_INVALID_ARR_SIZE; }
  if(y <= 0) { return LOG_INVALID_ARR_SIZE; }

  int i, j;
  fprintf(log->fp, "{\n");
  for(i = 0; i < x; i++) {
    fprintf(log->fp, "\t{");
    for(j = 0; j < y; j++) {
      (j < y-1) ? fprintf(log->fp, "%i, ", arr[i][j]) : fprintf(log->fp, "%i", arr[i][j]);
    }
    (i < x-1) ? fprintf(log->fp, "},\n") : fprintf(log->fp, "}\n");
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logStrArr(log_t *log, char **arr, int size) { // FIXME: adhere to log columns length
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_STR_ARR; }
  if(size <= 0) { return LOG_INVALID_ARR_SIZE; }

  fprintf(log->fp, "{");
  int i;
  for(i = 0; i < size; i++) {
    (i < size -1) ? fprintf(log->fp, "%s, ", arr[i]) : fprintf(log->fp, "%s", arr[i]);  
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logTitle(log_t *log, char *title) {
  if(!log) { return LOG_NIL_LOG; }
  if(!title) { return LOG_NIL_TITLE; }

  int len = strlen(title);
  int lpad = (log->columns / 2) - 1 - (len / 2);
  int rpad = (log->columns - (log->columns / 2)) - 1 - (len - (len / 2));
  for(len = log->columns; len; len--) { fprintf(log->fp, "#"); }
  fprintf(log->fp, "\n");
  fprintf(log->fp, "#%*s#\n", log->columns - 2, ""); 
  fprintf(log->fp, "#%*s%s%*s#\n", lpad, "", title, rpad, "");
  fprintf(log->fp, "#%*s#\n", log->columns - 2, ""); 
  for(len = log->columns; len; len--) { fprintf(log->fp, "#"); }
  fprintf(log->fp, "\n\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logHeader(log_t *log, char *header) {
  if(!log) { return LOG_NIL_LOG; }
  if(!header) { return LOG_NIL_HEADER; }

  int len = strlen(header);
  int lpad = (log->columns / 2) - 1 - (len / 2);
  int rpad = (log->columns - (log->columns / 2)) - 1 - (len - (len / 2));
  for(len = log->columns; len; len--) { fprintf(log->fp, "*"); }
  fprintf(log->fp, "\n");
  fprintf(log->fp, "*%*s%s%*s*\n", lpad, "", header, rpad, ""); 
  for(len = log->columns; len; len--) { fprintf(log->fp, "*"); }
  fprintf(log->fp, "\n\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logSection(log_t *log, char *section) {
  if(!log) { return LOG_NIL_LOG; }
  if(!section) { return LOG_NIL_SECTION; }

  int len = strlen(section);
  int lpad = (log->columns / 2) - (len / 2);
  int rpad = (log->columns - (log->columns / 2))  - (len - (len / 2));
  for(; lpad; lpad--) { fprintf(log->fp, "="); }
  fprintf(log->fp, "%s", section); 
  for(; rpad; rpad--) { fprintf(log->fp, "="); }
  fprintf(log->fp, "\n\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logIntSetting(log_t *log, char *key, int val) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }

  char buffer[11];
  sprintf(buffer, "%d", val);
  fprintf(log->fp, "%s", key);
  for(val = log->columns - strlen(key) + strlen(buffer); val; val--) { 
    fprintf(log->fp, ".");
  }
  fprintf(log->fp, "%s\n", buffer);
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logStrSetting(log_t *log, char *key, char *val) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }
  
  return LOG_NIL;
}

errLOG_t logFloatSetting(log_t *log, char *key, double val) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }
  
  return LOG_NIL;
}

//if(log->level) { fprint(log->fp, "LEVEL"); }
//fprint("fmtstring", args...); // wrap if longer than column width??
errLOG_t logEvent(log_t *log, int timestamp, char *event) {
  if(!log) { return LOG_NIL_LOG; }
  //if(!event) { return LOG_NIL_EVENT; }
  if(!(timestamp == 0 || timestamp == 1)) { return LOG_INVALID_TIMESTAMP; }
  
  if(timestamp) {
    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    char time[80];
    strftime(time, 80, "%Y_%B_%d_%A_%X", date); // yr_mo_day_weekday_time
    fprintf(log->fp, "[%s] ", time);
  }

  fprintf(log->fp, "%s\n", event);
  fflush(log->fp);

  return LOG_NIL;
}
