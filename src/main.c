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
  for(i = 0, c++, token = strtok(c, ",}"); i < *size; i++, token = strtok(NULL, ",}")) {
    j = strlen(token)+1;
    (*dest)[i] = calloc(j, sizeof(char));
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

// Attempt to create a matrix.
errGLUE_t mallocMatrix(int ***matrix, int r, int c) {
  if(!(*matrix = malloc(sizeof(int *) * r))) { return GLUE_OUT_OF_MEMORY; }

  int i;
  for(i = 0; i < r; i++) { 
    if(!((*matrix)[i] = calloc(c, sizeof(int)))) {
      for(; i; i--) { free((*matrix)[i-1]); }
      free(*matrix);
      *matrix = NULL;
      return GLUE_OUT_OF_MEMORY;
    }
  }

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

  char *section, *key, *val;
  char **strArr1, **strArr2;

  int i, j, k, n;
  int *intArr;
  int **matrix;

  errINI_t errINI;
  errGLUE_t errGLUE;
  errRISKY_t errRISKY;

  ini_t *ini;
  game_t *game;

  if((errINI = readINI(&ini, argv[1])) != INI_NIL) {
    fprintf(stderr, "error! failure to read conf file: %s\nirritant: %s\nexiting...\n", argv[1], strErrINI(errINI));
    return 0;
  }

  if((errRISKY = makeRISKY(&game)) != RISKY_NIL) {
    fprintf(stderr, "error! failure to make a risky game\nirritant: %s\nexiting...\n", strErrRISKY(errRISKY));
    goto FREE;
  }

  /******************* PLAYERS *******************/
  if((errINI = getINI(ini, section = "Players", key = "humans", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &n)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setHumans(game, n)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Players", key = "computers", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &strArr1, &n)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setComputers(game, n, strArr1)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* TRAINING *******************/
  if((errINI = getINI(ini, section = "Training", key = "games", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &n)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setTraining(game, n)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Training", key = "log", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &n)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Training", key = "dir", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errRISKY = setLogging(game, n, val)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* TROOPS *******************/
  if((errINI = getINI(ini, section = "Troops", key = "beginning", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &n)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Troops", key = "minimum", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Troops", key = "bonus", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &j)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Troops", key = "random", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &k)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setTroops(game, n, i, j, k)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* CARDS *******************/
  if((errINI = getINI(ini, section = "Cards", key = "types", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &strArr1, &n)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Cards", key = "wilds", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setDeck(game, i, strArr1, n)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Cards", key = "trades", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseIntArr(val, &intArr, &n)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Cards", key = "incr", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setTrades(game, intArr, n, i)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* CHROMOSOMES *******************/
  if((errINI = getINI(ini, section = "Chromosomes", key = "cps", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &strArr1, &n)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Chromosomes", key = "traits", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &j)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errGLUE = mallocMatrix(&matrix, n, j)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setCps(game, matrix, strArr1, n, j)) != RISKY_NIL) { goto FAIL_RISKY; }

  for(i = 0; i < n; i++) {
    if((errINI = getINI(ini, "Chromosomes", strArr1[i], &val)) != INI_NIL) { goto FAIL_INI; }
    // FIXME: invalid CP
    // FIXME: key =
    if((errGLUE = parseIntArr(val, matrix+i, &k)) != GLUE_NIL) { goto FAIL_GLUE; } // FIXME: matrix[i] addr??
    //if(j != k) {  }  FIXME: invalid chromosome!!
  }

  /******************* MAP *******************/
  if((errINI = getINI(ini, section = "Map", key = "continents", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &strArr1, &n)) != GLUE_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Map", key = "continents_bonus", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseIntArr(val, &intArr, &i)) != GLUE_NIL) { goto FAIL_RISKY; }

  if((errRISKY = setContinents(game, strArr1, intArr, n)) != RISKY_NIL) { goto FAIL_RISKY; }
  // FIXME: another just for the bonuses.

  if((errINI = getINI(ini, "Map", key = "random", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &i)) != GLUE_NIL) { goto FAIL_GLUE; }
  // FIXME: another just for random.

  if((errINI = getINI(ini, "Map", key = "countries", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &strArr1, &n)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setCountries(game, strArr1, n, i)) != RISKY_NIL) { goto FAIL_RISKY; }

  // GENERATE THE ADJACENCY MATRIX
  if((errGLUE = mallocMatrix(&matrix, n, n)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setAdjacencies(game, matrix, n)) != RISKY_NIL) { goto FAIL_RISKY; } // FIXME: break randomCountries as own setting
 
  for(i = 0; i < n; i++) {
    if((errINI = getINI(ini, "Map", key = strArr1[i], &val)) != INI_NIL) { goto FAIL_INI; } 
    // FIXME fprintf(stderr, "error! invalid conf\nirritant: expected '%s' key under [Map]\nexiting...\n", strArr1[i]);
    if((errGLUE = parseStrArr(val, &strArr2, &j)) != GLUE_NIL) { goto FAIL_GLUE; }
    // FIXME j <= n -- cannot have more adjacencies than there are countries

    for(; j; j--) { // for every country in adjacency list
      for(k = n; k; k--) { // for every country
        if(!strcmp(strArr1[k-1], strArr2[j-1])) {
          matrix[i][k-1] = 1;
          break;
        }
      }
    }
    free(strArr2);
  }

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
  fprintf(stderr, "error in main.c!\nirritant: %s\nsection: %s, key: %s\nexiting...\n",
      section, key, strErrGLUE(errGLUE));
  goto FREE;

FAIL_RISKY:
  fprintf(stderr, "error in RISKY lib!\nirritant: %s\nsection: %s, key: %s\nexiting...\n",
      section, key, strErrRISKY(errRISKY));
  goto FREE;

FAIL_INI:
  fprintf(stderr, "error in INI lib!\nirritant: %s\nsection: %s, key: %s\nexiting...\n",
      section, key, strErrINI(errINI));
  goto FREE;

FREE:
  freeINI(ini);
  //freeRISKY(game);
  return 0;
}
