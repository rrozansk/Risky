/******************************************************************************
 * FILE:    log.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/30/17                                                           *
 * EDITED:  5/18/17                                                           *
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
    // misc errors
    case LOG_OUT_OF_MEMORY: return "out of memory";
    case LOG_OPEN_FAIL: return "failed to open log";
    case LOG_CLOSE_FAIL: return "failed to close log";
    case LOG_DIR_CREATION_FAIL: return "failed to create log directory";
    // invalid input errors
    case LOG_INVALID_ROW_SIZE: return "matrix row size must be > 0";
    case LOG_INVALID_COL_SIZE: return "matrix column size must be > 0";
    case LOG_INVALID_ARR_SIZE: return "array size must be > 0";
    case LOG_INVALID_WIDTH: return "column width must be >= 80";
    case LOG_INVALID_TIMESTAMP: return "timestamp must be 1 or 0";
    case LOG_INVALID_DIR: return "dir must be less than 255 chars long";
    case LOG_INVALID_KEY: return "key must be short enough to accomadate the value";
    // nil arg errors
    case LOG_NIL_LOG: return "nil log";
    case LOG_NIL_NAME: return "nil file name";
    case LOG_NIL_DIR: return "nil directory";
    case LOG_NIL_TITLE: return "nil title";
    case LOG_NIL_HEADER: return "nil header";
    case LOG_NIL_SECTION: return "nil section";
    case LOG_NIL_KEY: return "nil key";
    case LOG_NIL_INT_ARR: return "nil int array";
    case LOG_NIL_FLOAT_ARR: return "nil float array";
    case LOG_NIL_BOOL_ARR: return "nil bool array";
    case LOG_NIL_CHAR_ARR: return "nil char array";
    case LOG_NIL_STR_ARR: return "nil string array";
    case LOG_NIL_INT_MATRIX: return "nil int matrix";
    case LOG_NIL_FLOAT_MATRIX: return "nil float matrix";
    case LOG_NIL_BOOL_MATRIX: return "nil bool matrix";
    case LOG_NIL_CHAR_MATRIX: return "nil char matrix";
    case LOG_NIL_STR_MATRIX: return "nil string matrix";
    // no error and unknown error return
    case LOG_NIL: return "";
    default: return "unkown errLOG_t error code";  
  }
}

errLOG_t makeLOG(log_t **log, int columns, char *dir, char *name) {
  if(!log) { return LOG_NIL_LOG; }
  if(!dir) { return LOG_NIL_DIR; }
  if(!name) { return LOG_NIL_NAME; }
  if(columns < 80) { return LOG_INVALID_WIDTH; }
  if((strlen(dir) + strlen(name) + 4) > 255) { return LOG_INVALID_DIR; } // +4 for .txt

  struct stat st;
  if(mkdir(dir, 0700) && stat(dir, &st)) { return LOG_DIR_CREATION_FAIL; }

  if(!(*log = calloc(1, sizeof(log_t)))) { return LOG_OUT_OF_MEMORY; }

  (*log)->directory = calloc(strlen(dir)+1, sizeof(char));
  (*log)->name = calloc(strlen(name)+1, sizeof(char));
  if(!(*log)->directory || !(*log)->name) {
    freeLOG(*log);
    *log = NULL;
    return LOG_OUT_OF_MEMORY;
  }

  sprintf((*log)->directory, "%s", dir);
  sprintf((*log)->name, "%s", name);
  (*log)->columns = columns;   

  char path[255];
  sprintf(path, "%s/%s.txt", dir, name);
  if(!((*log)->fp = fopen(path, "w"))) {
    freeLOG(*log); // ignore possible close file error
    *log = NULL;
    return LOG_OPEN_FAIL;
  }

  return LOG_NIL;
}

errLOG_t freeLOG(log_t *log) {
  if(!log) { return LOG_NIL; }

  if(log->name) { free(log->name); }
  if(log->directory) { free(log->directory); }

  errLOG_t errLOG = LOG_NIL;
  if(log->fp && !fclose(log->fp)) { errLOG = LOG_CLOSE_FAIL; }
  
  free(log);

  return errLOG;
}

errLOG_t logIntArr(log_t *log, int *arr, int size) {
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_INT_ARR; }
  if(size < 1) { return LOG_INVALID_ARR_SIZE; }

  int col = fprintf(log->fp, "{");
  int i;
  char buffer[log->columns];
  for(i = 0; i < size; i++) {
    col += sprintf(buffer, (i < size -1) ? "%i, " : "%i", arr[i]);
    if(col > log->columns) {
      fprintf(log->fp, "\n ");
      col = 0;
    }
    fprintf(log->fp, "%s", buffer);  
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logIntMatrix(log_t *log, int **matrix, int r, int c) {
  if(!log) { return LOG_NIL_LOG; }
  if(!matrix) { return LOG_NIL_INT_MATRIX; }
  if(r < 1) { return LOG_INVALID_ROW_SIZE; }
  if(c < 1) { return LOG_INVALID_COL_SIZE; }

  fprintf(log->fp, "{\n");

  int i, j, col;
  char buffer[log->columns];
  for(col = i = 0; i < r; i++) {
    col = fprintf(log->fp, "\t{");
    for(j = 0; j < c; j++) {
      col += sprintf(buffer, (j < r-1) ? "%i, " : "%i", matrix[r][c]);
      if(col > log->columns) {
        fprintf(log->fp, "\n\t ");
        col = 0;
      }
      fprintf(log->fp, "%s", buffer);
    }
    fprintf(log->fp, (i < c-1) ? "},\n" : "}\n");
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logFloatArr(log_t *log, double *arr, int size) {
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_FLOAT_ARR; }
  if(size < 1) { return LOG_INVALID_ARR_SIZE; }

  int col = fprintf(log->fp, "{");
  int i;
  char buffer[log->columns];
  for(i = 0; i < size; i++) {
    col += sprintf(buffer, (i < size -1) ? "%f, " : "%f", arr[i]);
    if(col > log->columns) {
      fprintf(log->fp, "\n ");
      col = 0;
    }
    fprintf(log->fp, "%s", buffer);  
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logFloatMatrix(log_t *log, double **matrix, int r, int c) {
  if(!log) { return LOG_NIL_LOG; }
  if(!matrix) { return LOG_NIL_FLOAT_MATRIX; }
  if(r < 1) { return LOG_INVALID_ROW_SIZE; }
  if(c < 1) { return LOG_INVALID_COL_SIZE; }

  fprintf(log->fp, "{\n");

  int i, j, col;
  char buffer[log->columns];
  for(col = i = 0; i < r; i++) {
    col = fprintf(log->fp, "\t{");
    for(j = 0; j < c; j++) {
      col += sprintf(buffer, (j < r-1) ? "%f, " : "%f", matrix[r][c]);
      if(col > log->columns) {
        fprintf(log->fp, "\n\t ");
        col = 0;
      }
      fprintf(log->fp, "%s", buffer);
    }
    fprintf(log->fp, (i < c-1) ? "},\n" : "}\n");
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logBoolArr(log_t *log, int *arr, int size) {
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_BOOL_ARR; }
  if(size < 1) { return LOG_INVALID_ARR_SIZE; }

  int col = fprintf(log->fp, "{");
  int i;
  char buffer[log->columns];
  for(i = 0; i < size; i++) {
    col += sprintf(buffer,  arr[i] ? "true" : "false");
    if(i < size - 1) { col += sprintf(buffer, ","); }
    if(col > log->columns) {
      fprintf(log->fp, "\n ");
      col = 0;
    }
    fprintf(log->fp, "%s", buffer);  
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logBoolMatrix(log_t *log, int **matrix, int r, int c) {
  if(!log) { return LOG_NIL_LOG; }
  if(!matrix) { return LOG_NIL_BOOL_MATRIX; }
  if(r < 1) { return LOG_INVALID_ROW_SIZE; }
  if(c < 1) { return LOG_INVALID_COL_SIZE; }

  fprintf(log->fp, "{\n");

  int i, j, col;
  char buffer[log->columns];
  for(col = i = 0; i < r; i++) {
    col = fprintf(log->fp, "\t{");
    for(j = 0; j < c; j++) {
      col += sprintf(buffer,  matrix[r][c] ? "true" : "false");
      if(j < c - 1) { col += sprintf(buffer, ","); }
      if(col > log->columns) {
        fprintf(log->fp, "\n\t ");
        col = 0;
      }
      fprintf(log->fp, "%s", buffer);
    }
    fprintf(log->fp, (i < c-1) ? "},\n" : "}\n");
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logCharArr(log_t *log, char *arr, int size) {
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_CHAR_ARR; }
  if(size < 1) { return LOG_INVALID_ARR_SIZE; }

  int col = fprintf(log->fp, "{");
  int i;
  char buffer[log->columns];
  for(i = 0; i < size; i++) {
    col += sprintf(buffer, (i < size -1) ? "%c, " : "%c", arr[i]);
    if(col > log->columns) {
      fprintf(log->fp, "\n ");
      col = 0;
    }
    fprintf(log->fp, "%s", buffer);  
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);


  return LOG_NIL;
}

errLOG_t logCharMatrix(log_t *log, char **matrix, int r, int c) {
  if(!log) { return LOG_NIL_LOG; }
  if(!matrix) { return LOG_NIL_CHAR_MATRIX; }
  if(r < 1) { return LOG_INVALID_ROW_SIZE; }
  if(c < 1) { return LOG_INVALID_COL_SIZE; }

  fprintf(log->fp, "{\n");

  int i, j, col;
  char buffer[log->columns];
  for(col = i = 0; i < r; i++) {
    col = fprintf(log->fp, "\t{");
    for(j = 0; j < c; j++) {
      col += sprintf(buffer, (j < r-1) ? "%c, " : "%c", matrix[r][c]);
      if(col > log->columns) {
        fprintf(log->fp, "\n\t ");
        col = 0;
      }
      fprintf(log->fp, "%s", buffer);
    }
    fprintf(log->fp, (i < c-1) ? "},\n" : "}\n");
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);
  
  return LOG_NIL;
}

errLOG_t logStrArr(log_t *log, char **arr, int size) {
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_STR_ARR; }
  if(size <= 0) { return LOG_INVALID_ARR_SIZE; }

  int col = fprintf(log->fp, "{");
  int i;
  char buffer[log->columns];
  for(i = 0; i < size; i++) {
    col += sprintf(buffer, (i < size -1) ? "%s, " : "%s", arr[i]);
    if(col > log->columns) {
      fprintf(log->fp, "\n ");
      col = 0;
    }
    fprintf(log->fp, "%s", buffer);  
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logStrMatrix(log_t *log, char ***matrix, int r, int c) {
  if(!log) { return LOG_NIL_LOG; }
  if(!matrix) { return LOG_NIL_STR_MATRIX; }
  if(r < 1) { return LOG_INVALID_ROW_SIZE; }
  if(c < 1) { return LOG_INVALID_COL_SIZE; }

  fprintf(log->fp, "{\n");

  int i, j, col;
  char buffer[log->columns];
  for(col = i = 0; i < r; i++) {
    col = fprintf(log->fp, "\t{");
    for(j = 0; j < c; j++) {
      col += sprintf(buffer, (j < r-1) ? "%s, " : "%s", matrix[r][c]);
      if(col > log->columns) {
        fprintf(log->fp, "\n\t ");
        col = 0;
      }
      fprintf(log->fp, "%s", buffer);
    }
    fprintf(log->fp, (i < c-1) ? "},\n" : "}\n");
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
  if((strlen(key) + 20) > log->columns) { return LOG_INVALID_KEY; }

  char buffer[20];
  int vlen = sprintf(buffer, "%d", val);
  int klen = fprintf(log->fp, "%s", key);
  for(val = log->columns - klen + vlen; val; val--) { fprintf(log->fp, "."); }
  fprintf(log->fp, "%s\n", buffer);
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logFloatSetting(log_t *log, char *key, double val) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }
  if((strlen(key) + 20) > log->columns) { return LOG_INVALID_KEY; }

  char buffer[20];
  int vlen = sprintf(buffer, "%f", val);
  int klen = fprintf(log->fp, "%s", key);
  for(val = log->columns - klen + vlen; val; val--) { fprintf(log->fp, "."); }
  fprintf(log->fp, "%s\n", buffer);
  fflush(log->fp);
 
  return LOG_NIL;
}

errLOG_t logBoolSetting(log_t *log, char *key, int val) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }
  if((strlen(key) + 10) > log->columns) { return LOG_INVALID_KEY; }
 
  int klen = fprintf(log->fp, "%s", key);
  for(val = log->columns - klen + (val ? 4 : 5); val; val--) { fprintf(log->fp, "."); }
  fprintf(log->fp, val ? "true" : "false");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logCharSetting(log_t *log, char *key, char val) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }
  if((strlen(key) + 10) > log->columns) { return LOG_INVALID_KEY; }

  int klen = fprintf(log->fp, "%s", key);
  for(val = log->columns - klen + 3; val; val--) { fprintf(log->fp, "."); }
  fprintf(log->fp, "'%c'\n", val);
  fflush(log->fp);
  
  return LOG_NIL;
  
}

errLOG_t logStrSetting(log_t *log, char *key, char *val) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }
  if((strlen(key) + strlen(val) + 2) > log->columns) { return LOG_INVALID_KEY; }

  int klen = fprintf(log->fp, "%s", key);
  for(klen = log->columns - klen + strlen(val) + 2; klen; klen--) { fprintf(log->fp, "."); }
  fprintf(log->fp, "\"%s\"\n", val);
  fflush(log->fp);
  
  return LOG_NIL;
}

errLOG_t logEvent(log_t *log, int timestamp, char *event) {
  if(!log) { return LOG_NIL_LOG; }
  if(!(timestamp == 0 || timestamp == 1)) { return LOG_INVALID_TIMESTAMP; }
 
  int col = 0;
  if(timestamp) {
    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    char time[80];
    col = strftime(time, 80, "%Y_%B_%d_%A_%X", date); // yr_mo_day_weekday_time
    fprintf(log->fp, "[%s] ", time);
  }

  char *token = strtok(event, "\t\n\r\v\f ");
  for(; token; token = strtok(NULL, "\t\n\r\v\f ")) {
    if(col + strlen(token) > log->columns) {
      fprintf(log->fp, "\n");
      col = 0;
    }
    col += fprintf(log->fp, "%s\n", token);
  }

  fflush(log->fp);

  return LOG_NIL;
}
