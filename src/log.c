/******************************************************************************
 * FILE:    log.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/30/17                                                           *
 * EDITED:  6/1/17                                                            *
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

typedef enum typeLOG {
  LOG_INT, LOG_FLOAT, LOG_BOOL, LOG_CHAR, LOG_STR
} typeLOG_t;

/******************************************************************************
 *                                                                            *
 *   P R I V A T E   F U N C T I O N S                                        *
 *                                                                            *
 ******************************************************************************/
static errLOG_t logSetting(log_t *log, char *key, void *value, typeLOG_t typeLOG) {
  if(!log) { return LOG_NIL_LOG; }
  if(!key) { return LOG_NIL_KEY; }
  if(strlen(key) > log->columns/2) { return LOG_INVALID_KEY; }

  char buffer[log->columns];
  int vlen, klen, dots;

  klen = fprintf(log->fp, "%s", key);
  switch(typeLOG) {
    case LOG_INT:
      vlen = sprintf(buffer, "%i", *(int *)value);
      break;
    case LOG_FLOAT:
      vlen = sprintf(buffer, "%f", *(double *)value);
      break;
    case LOG_BOOL:
      vlen = sprintf(buffer,  *(int *)value ? "true" : "false");
      break;
    case LOG_CHAR:
      vlen = sprintf(buffer, "'%c'", *(char *)value);
      break;
    case LOG_STR:
      vlen = sprintf(buffer, "\"%s\"", *(char **)value);
      break;
    default:
      return LOG_UNKNOWN_TYPE;
  }
  for(dots = log->columns - (klen + vlen); dots; dots--) { fprintf(log->fp, "."); }
  fprintf(log->fp, "%s\n", buffer);
  fflush(log->fp);

  return LOG_NIL;  
}

static errLOG_t logArr(log_t *log, void *arr, int size, typeLOG_t typeLOG) {
  if(!log) { return LOG_NIL_LOG; }
  if(!arr) { return LOG_NIL_ARR; }
  if(size < 1) { return LOG_INVALID_ARR_SIZE; }

  int col = fprintf(log->fp, "{");
  int i;
  char buffer[log->columns];
  for(i = 0; i < size; i++) {
    switch(typeLOG) {
      case LOG_INT:
        col += sprintf(buffer, "%i", ((int *)arr)[i]);
        break;
      case LOG_FLOAT:
        col += sprintf(buffer, "%f", ((double *)arr)[i]);
        break;
      case LOG_BOOL:
        col += sprintf(buffer, ((int *)arr)[i] ? "true" : "false");
        break;
      case LOG_CHAR:
        col += sprintf(buffer, "'%c'", ((char *)arr)[i]);
        break;
      case LOG_STR:
        col += sprintf(buffer, "\"%s\"", ((char **)arr)[i]);
        break;
      default:
        return LOG_UNKNOWN_TYPE;
    }
    if(col > log->columns) {
      fprintf(log->fp, "\n ");
      col = 0;
    }
    fprintf(log->fp, "%s", buffer);
    if(i < (size - 1)) { col += fprintf(log->fp, ", "); }
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

static errLOG_t logMatrix(log_t *log, void *matrix, int r, int c, typeLOG_t typeLOG) {
  if(!log) { return LOG_NIL_LOG; }
  if(!matrix) { return LOG_NIL_MATRIX; }
  if(r < 1) { return LOG_INVALID_ROW_SIZE; }
  if(c < 1) { return LOG_INVALID_COL_SIZE; }

  fprintf(log->fp, "{\n");
  int i, j, col;
  char buffer[log->columns];
  for(col = i = 0; i < r; i++) {
    col = fprintf(log->fp, "\t{");
    for(j = 0; j < c; j++) {
      switch(typeLOG) {
        case LOG_INT:
          col += sprintf(buffer, "%i", *(((int *)matrix + i * c) + j)); // matrix[r][c]
          break;
        case LOG_FLOAT:
          col += sprintf(buffer, "%f", ((double **)matrix)[r][c]);
          break;
        case LOG_BOOL:
          col += sprintf(buffer,  ((int **)matrix)[r][c] ? "true" : "false");
          break;
        case LOG_CHAR:
          col += sprintf(buffer, "'%c'", ((char **)matrix)[r][c]);
          break;
        case LOG_STR:
          col += sprintf(buffer, "\"%s\"", ((char ***)matrix)[r][c]);
          break;
        default:
          return LOG_UNKNOWN_TYPE;
      }
      if(col > log->columns) {
        fprintf(log->fp, "\n\t ");
        col = 0;
      }
      fprintf(log->fp, "%s", buffer);
      if(j < c - 1) { col += fprintf(log->fp, ", "); }
    }
    fprintf(log->fp, (i < r - 1) ? "},\n" : "}\n");
  }
  fprintf(log->fp, "}\n");
  fflush(log->fp);

  return LOG_NIL;
}

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
    case LOG_UNKNOWN_TYPE: return "internal error in type representation";
    // invalid input errors
    case LOG_INVALID_ROW_SIZE: return "matrix row size must be > 0";
    case LOG_INVALID_COL_SIZE: return "matrix column size must be > 0";
    case LOG_INVALID_ARR_SIZE: return "array size must be > 0";
    case LOG_INVALID_WIDTH: return "column width must be >= 80";
    case LOG_INVALID_TIMESTAMP: return "timestamp must be 1 or 0";
    case LOG_INVALID_DIR: return "dir must be less than 255 chars long";
    case LOG_INVALID_KEY: return "key must be than column length / 2";
    // nil arg errors
    case LOG_NIL_LOG: return "nil log";
    case LOG_NIL_NAME: return "nil file name";
    case LOG_NIL_DIR: return "nil directory";
    case LOG_NIL_TITLE: return "nil title";
    case LOG_NIL_HEADER: return "nil header";
    case LOG_NIL_SECTION: return "nil section";
    case LOG_NIL_KEY: return "nil key";
    case LOG_NIL_ARR: return "nil array";
    case LOG_NIL_MATRIX: return "nil matrix";
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
  if((strlen(dir) + strlen(name)) > 255) { return LOG_INVALID_DIR; }

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
  sprintf(path, "%s/%s", dir, name);
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
  
  char buff[strlen(event)+1];
  strncpy(buff, event, strlen(event)+1);
  char *token = strtok(buff, " ");
  for(; token; token = strtok(NULL, " ")) {
    if((col + strlen(token)) > log->columns) {
      fprintf(log->fp, "\n");
      col = 0;
    }
    col += fprintf(log->fp, "%s ", token);
  }

  fprintf(log->fp, "\n");
  fflush(log->fp);

  return LOG_NIL;
}

errLOG_t logIntSetting(log_t *log, char *key, int val) {
  return logSetting(log, key, &val, LOG_INT);
}

errLOG_t logIntArr(log_t *log, int *arr, int size) {
  return logArr(log, arr, size, LOG_INT);
}

errLOG_t logIntMatrix(log_t *log, int *matrix, int r, int c) {
  return logMatrix(log, matrix, r, c, LOG_INT);
}

errLOG_t logFloatSetting(log_t *log, char *key, double val) {
  return logSetting(log, key, &val, LOG_FLOAT);
}

errLOG_t logFloatArr(log_t *log, double *arr, int size) {
  return logArr(log, arr, size, LOG_FLOAT);
}

errLOG_t logFloatMatrix(log_t *log, double **matrix, int r, int c) {
  return logMatrix(log, matrix, r, c, LOG_FLOAT);
}

errLOG_t logBoolSetting(log_t *log, char *key, int val) {
  return logSetting(log, key, &val, LOG_BOOL);
}

errLOG_t logBoolArr(log_t *log, int *arr, int size) {
  return logArr(log, arr, size, LOG_BOOL);
}

errLOG_t logBoolMatrix(log_t *log, int **matrix, int r, int c) {
  return logMatrix(log, matrix, r, c, LOG_BOOL);
}

errLOG_t logCharSetting(log_t *log, char *key, char val) {
  return logSetting(log, key, &val, LOG_CHAR);
}

errLOG_t logCharArr(log_t *log, char *arr, int size) {
  return logArr(log, arr, size, LOG_CHAR);
}

errLOG_t logCharMatrix(log_t *log, char **matrix, int r, int c) {
  return logMatrix(log, matrix, r, c, LOG_CHAR);
}

errLOG_t logStrSetting(log_t *log, char *key, char *val) {
  return logSetting(log, key, &val, LOG_STR);
}

errLOG_t logStrArr(log_t *log, char **arr, int size) {
  return logArr(log, arr, size, LOG_STR);
}

errLOG_t logStrMatrix(log_t *log, char ***matrix, int r, int c) {
  return logMatrix(log, matrix, r, c, LOG_STR);
}
