/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/22/17
 Info:    main.c is the glue which holds together the ini and risky libraries.
          This file attempts to parse an ini configuration file into a risky
          game and output a new configuration file if any AI DNA changed during
          gameplay. It also takes care to report errors, if any.
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <ini.h>
#include <risky.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************

    T Y P E S

*******************************************************************************/
// All the possible errors produced from this file. Mostly parsing arrays.
typedef enum errGULE {
  GLUE_INVALID_ARRAY_LITERAL, GLUE_INVALID_INT_LITERAL, GLUE_NIL, 
  GLUE_OUT_OF_MEMORY, GLUE_INVALID_ARRAY_SEPERATOR
} errGLUE_t;

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// Return the string representation of a given error produced from this file. 
const char *strErrGLUE(errGLUE_t errGLUE) {
  switch(errGLUE) {
    case GLUE_INVALID_INT_LITERAL: return "invalid interger literal";
    case GLUE_INVALID_ARRAY_LITERAL: return "invalid array literal";
    case GLUE_INVALID_ARRAY_SEPERATOR: return "invalid array literal seperator";
    case GLUE_OUT_OF_MEMORY: return "out of memory";
    case GLUE_NIL: return "";
    default:  return "unknown errGLUE_t";
  }
}

// Attempt to parse an integer literal.
errGLUE_t parseInt(char *literal, int *dest) {
  char *end;
  *dest = (int)strtol(literal, &end, 10);
  if(literal == end) { return GLUE_INVALID_INT_LITERAL; }
  if(literal+strlen(literal) != end) { return GLUE_INVALID_INT_LITERAL; }

  return GLUE_NIL;
}

// Attempt to parse the size of an array literal.
errGLUE_t parseArrSize(char *literal, int *size) {
  if(*literal != '{') { return GLUE_INVALID_ARRAY_LITERAL;  }
  char *tmp = NULL;
  for(*size = 0, literal++; *literal != '}'; tmp = literal, literal++) {
    if(*literal == ',') { 
      if(*tmp == ',') { return GLUE_INVALID_ARRAY_LITERAL; }
      (*size)++;
    }
  }
  if(*size) { (*size)++; }
  return GLUE_NIL;
}

// Attempt to parse an array literal of integers.
errGLUE_t parseIntArr(char *literal, int **dest, int *size) {
  errGLUE_t errGLUE;
  if((errGLUE = parseArrSize(literal, size)) != GLUE_NIL) { return errGLUE; }
  if(!(*dest = malloc(sizeof(int) * *size))) { return GLUE_OUT_OF_MEMORY; }

  char *tmp;
  int i;
  for(i = 0, literal++; i < *size; i++, literal = tmp, literal++) {
    (*dest)[i] = (int)strtol(literal, &tmp, 10);
    if(literal == tmp) {
      free(*dest);
      return GLUE_INVALID_INT_LITERAL;  
    }
    if(!(*tmp == ',' || *tmp == '}')) { // invalid seperator or end
      free(*dest);
      return GLUE_INVALID_ARRAY_SEPERATOR;
    }
  }

  return GLUE_NIL;
}

// Attempt to parse an array literal of strings.
errGLUE_t parseStrArr(char *literal, char ***dest, int *size) {
  errGLUE_t errGLUE;
  if((errGLUE = parseArrSize(literal, size)) != GLUE_NIL) { return errGLUE; }
  if(!(*dest = malloc(sizeof(char *) * (*size)))) { return GLUE_OUT_OF_MEMORY; }

  int i, j;
  char *c = calloc(j = strlen(literal)+1, sizeof(char));
  char *orig = c;
  char *token;
  strncpy(c, literal, j-1);
  //printf("literal: %s\t(arr size: %i)\nliteral size: %i\n", literal, *size, j-1); fflush(stdout);
  for(i = 0, c++, token = strtok(c, ",}"); i < *size; i++, token = strtok(NULL, ",}")) {
    j = strlen(token)+1;
    (*dest)[i] = calloc(j, sizeof(char));
    //printf("token size: %i\n", j-1); fflush(stdout);
    if(!((*dest)[i])) {
      for(j = 0; j < i; j++) { free((*dest)[j]); }
      free(*dest);
      return GLUE_OUT_OF_MEMORY;
    }
    strcpy((*dest)[i], token);
  }
  free(orig);

  return GLUE_NIL;
}

// Print out game, version, and author information. Make sure a configuration
// file is specified. Then attempts to setup, play, and teardown the game.
// Reports any errors if they occur and free any memory which was allocated.
int main(int argc, char *argv[]) {
  fprintf(stdout, "Risky\nv1.0\nRyan Rozanski\n\n");

  if(argc != 2) {
    fprintf(stderr, "error! must specify a conf file, exiting...\n");
    return 0;
  }

  ini_t *ini;
  errINI_t errINI = readINI(&ini, argv[1]);
  if(errINI != INI_NIL) {
    fprintf(stderr, "error! failure to read conf file: %s\nirritant: %s\nexiting...\n", argv[1], strErrINI(errINI));
    return 0;
  }

  game_t *game;
  errRISKY_t errRISKY = makeRISKY(&game);
  if(errRISKY != RISKY_NIL) {
    fprintf(stderr, "error! failure to make a risky game\nirritant: %s\nexiting...\n", strErrRISKY(errRISKY));
    goto FREE;
  }

  char *val;
  char **tmpArrStr;

  int tmpInt, i, j, k;
  int *tmpArrInt;
  int **matrix; // for chromosomes and board

  errGLUE_t errGLUE;

  /******************* PLAYERS *******************/
  if((errINI = getINI(ini, "Players", "humans", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setHumans(game, tmpInt)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Players", "computers", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &tmpArrStr, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setComputers(game, tmpInt, tmpArrStr)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* TRAINING *******************/
  if((errINI = getINI(ini, "Training", "games", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setTraining(game, tmpInt)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Training", "log", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Training", "dir", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errRISKY = setLogging(game, tmpInt, val)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* TROOPS *******************/
  if((errINI = getINI(ini, "Troops", "beginning", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Troops", "minimum", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Troops", "bonus", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &j)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Troops", "random", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &k)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setTroops(game, tmpInt, i, j, k)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* CARDS *******************/
  if((errINI = getINI(ini, "Cards", "types", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &tmpArrStr, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Cards", "wilds", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setDeck(game, i, tmpArrStr, tmpInt)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Cards", "trades", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseIntArr(val, &tmpArrInt, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Cards", "incr", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setTrades(game, tmpArrInt, tmpInt, i)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* CHROMOSOMES *******************/
  if((errINI = getINI(ini, "Chromosomes", "cps", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &tmpArrStr, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }

  if(!(matrix = malloc(sizeof(int *) * tmpInt))) {
    errGLUE = GLUE_OUT_OF_MEMORY;
    goto FAIL_GLUE;
  }
  for(i = 0; i < tmpInt; i++) { // FIXME: free chromosomes correctly
    if((errINI = getINI(ini, "Chromosomes", tmpArrStr[i], &val)) != INI_NIL) { goto FAIL_INI; }
    if((errGLUE = parseIntArr(val, &tmpArrInt, &j)) != GLUE_NIL) { goto FAIL_GLUE; }
    if(!(matrix[i] = malloc(sizeof(int) * j))) { // FIXME: all chromosomes same size!! move this loop out
        errGLUE = GLUE_OUT_OF_MEMORY;
        goto FAIL_GLUE;
    }
    for(k = 0; k < j; k++) { matrix[i][k] = tmpArrInt[k]; } // need to free tmpArrInt? since dont use it but it did malloc
  }
  if((errRISKY = setCps(game, matrix, tmpArrStr, tmpInt, k)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* MAP *******************/
  if((errINI = getINI(ini, "Map", "continents", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &tmpArrStr, &tmpInt)) != GLUE_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Map", "continents_bonus", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseIntArr(val, &tmpArrInt, &i)) != GLUE_NIL) { goto FAIL_RISKY; }
  // if(tmpInt != i) { **ERROR** }
  if((errRISKY = setContinents(game, tmpArrStr, tmpArrInt, tmpInt)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Map", "random", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Map", "countries", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &tmpArrStr, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setCountries(game, tmpArrStr, tmpInt, i)) != RISKY_NIL) { goto FAIL_RISKY; }

  if(!(matrix= malloc(sizeof(int *) * tmpInt))) { // GENERATE THE ADJACENCY MATRIX
    errGLUE = GLUE_OUT_OF_MEMORY;
    goto FAIL_GLUE;
  }
  for(i = 0; i < tmpInt; i++) { 
    if(!(matrix[i] = calloc(tmpInt, sizeof(int)))) {
      for(; i; i--) { free(matrix[i-1]); }
      errGLUE = GLUE_OUT_OF_MEMORY;
      goto FAIL_GLUE;
    }
  }

  char **tmpStr;
  for(i = 0; i < tmpInt; i++) {
    if((errINI = getINI(ini, "Map", tmpArrStr[i], &val)) != INI_NIL) { goto FAIL_INI; } 
    //fprintf(stderr, "error! invalid conf\nirritant: expected '%s' key under [Map]\nexiting...\n", tmpArrStr[i]);
    if((errGLUE = parseStrArr(val, &tmpStr, &j)) != GLUE_NIL) { goto FAIL_GLUE; }

    for(; j; j--) { // for every country in adjacency list
      for(k = 0; k < tmpInt; k++) { // for every country
        if(!strcmp(tmpArrStr[k], tmpStr[j-1])) { break; } 
      }
      matrix[i][k] = 1;
    }
  }

  if((errRISKY = setAdjacencies(game, matrix, i)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errRISKY = risky(game)) != RISKY_NIL) { goto FAIL_RISKY; }

  //unsigned char *uval = NULL;
  //if((errRISKY = isEvolved(game, uval)) != RISKY_NIL) { goto FAIL_RISKY; }
  //if(uval) {
    //  for each ai in game.computers:
    //     setINI ai new DNA
    //if((errINI = writeINI(ini, argv[1])) != INI_NIL) { goto FAIL_INI; }
  //}

  goto FREE;

FAIL_GLUE:
  fprintf(stderr, "error in main.c!\nirritant: %s\nexiting...\n", strErrGLUE(errGLUE));
  goto FREE;

FAIL_RISKY:
  fprintf(stderr, "error in RISKY lib!\nirritant: %s\nexiting...\n", strErrRISKY(errRISKY));
  goto FREE;

FAIL_INI:
  fprintf(stderr, "error in INI lib!\nirritant: %s\nexiting...\n", strErrINI(errINI));
  goto FREE;

FREE:
  //freeINI(ini);
  //freeRISKY(game);
  return 0;
}
