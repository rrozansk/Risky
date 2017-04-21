/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/20/17
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
// All the possible errors from setting up the game.
typedef enum errGULE {
  GLUE_INVALID_ARRAY_LITERAL, GLUE_INVALID_INT_LITERAL, GLUE_NIL, 
  GLUE_OUT_OF_MEMORY, GLUE_INVALID_ARRAY_SEPERATOR
} errGLUE_t;

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// Return the string representation of a given error. 
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
errGLUE_t parseInt(char *literal, int *dest) { // FIXME: take char *end??
  char *end;
  *dest = (int)strtol(literal, &end, 10);
  if(literal == end) { return GLUE_INVALID_INT_LITERAL; }
  return GLUE_NIL;
}

// Attempt to parse an array literal with its size.
errGLUE_t parseArrSize(char *literal, int *size) {
  if(*literal != '{') { return GLUE_INVALID_ARRAY_LITERAL;  }
  for(*size = 0, literal++; *literal != '}'; literal++) {
    if(*literal == ',') { (*size)++; }
  }
  (*size)++; // always 1 more elem than comma seperators
  return GLUE_NIL;
}

// Attempt to parse an array literal of integers.
errGLUE_t parseIntArr(char *literal, int **dest, int *size) {
  errGLUE_t errGLUE;

  if((errGLUE = parseArrSize(literal, size)) != GLUE_NIL) { return errGLUE; }
  if(!(*dest = malloc(sizeof(int) * *size))) { return GLUE_OUT_OF_MEMORY; }

  int i;
  for(i = 0, literal++; i < *size; i++, literal++) { // read '{'
    (*dest)[i] = (int)strtol(literal, &literal, 10); // FIXME: parseInt()
    if(!(*literal == ',' || *literal == '}')) { // invalid seperator or end
      free(*dest);
      return GLUE_INVALID_ARRAY_SEPERATOR;
    }
  }
  return GLUE_NIL;
}

// Attempt to parse an array literal of strings.
errGLUE_t parseStrArr(char *literal, char ***dest, int *size) {
  errGLUE_t error;
  if((error = parseArrSize(literal, size)) != GLUE_NIL) { return error; }
  if(!(*dest = malloc(sizeof(char *) * *size))) { return GLUE_OUT_OF_MEMORY; }

  char *c;
  int i;
  for(i = 0, literal++, c = strtok(literal, ",}"); i < *size; i++, c = strtok(NULL, ",}")) {
    (*dest)[i] = calloc(strlen(c)+1, sizeof(char));
    if(!((*dest)[i])) {
      int j;
      for(j = 0; j < i; j++) { free((*dest)[j]); }
      free(*dest);
      return GLUE_OUT_OF_MEMORY;
    }
    strcpy((*dest)[i], c);
  }
  return GLUE_NIL;
}

// Print out game, version, and author information. Make sure a configuration
// file is specified. Then attempts to setup, play, and teardown the game.
// Reports any errors if they occur and free any memory that we allocated
// during the lifetime of the program.
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

  char *val, **tmpArrStr;
  int tmpInt, *tmpArrInt;
  int i, j, k;
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

  for(i = 0; i < tmpInt; i++) {
    if((errINI = getINI(ini, "Chromosomes", tmpArrStr[i], &val)) != INI_NIL) { goto FAIL_INI; }
    if((errGLUE = parseIntArr(val, &tmpArrInt, &j)) != GLUE_NIL) { goto FAIL_GLUE; }
    // set arr
  }
  // FIXME: finish this logic
  //setCps(game_t *game, int **ais, unsigned short chromosomes, unsigned char traits);
  //if((errRISKY = setCps(game, -, tmpInt, j)) != RISKY_NIL) { goto FAIL_RISKY; }

  /******************* MAP *******************/
  if((errINI = getINI(ini, "Map", "continents", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &tmpArrStr, &tmpInt)) != GLUE_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Map", "continents_bonus", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseIntArr(val, &tmpArrInt, &i)) != GLUE_NIL) { goto FAIL_RISKY; }
  //if(i =! tmpInt) { goto FAIL_GLUE; } **FIXME**
  if((errRISKY = setContinents(game, tmpArrStr, tmpArrInt, tmpInt)) != RISKY_NIL) { goto FAIL_RISKY; }

  if((errINI = getINI(ini, "Map", "random", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseInt(val, &tmpInt)) != GLUE_NIL) { goto FAIL_GLUE; }

  if((errINI = getINI(ini, "Map", "countries", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errGLUE = parseStrArr(val, &tmpArrStr, &i)) != GLUE_NIL) { goto FAIL_GLUE; }
  if((errRISKY = setCountries(game, tmpArrStr, i, tmpInt)) != RISKY_NIL) { goto FAIL_RISKY; }

/*
  char *literal, **adjacencies;
  *board = malloc(sizeof(int *) * n);
  for(i = 0; i < n; i++) {
    if(getINI(ini, "Map", countries[i], &literal) != INI_NIL) {
      for(j = 0; j < i; j++) { free(board[j]); }
      free(*board);
      fprintf(stderr, "error! invalid conf\nirritant: expected '%s' key under [Map]\nexiting...\n", countries[i]);
      return 0;
    }
    if(parseStrArr(literal, &adjacencies, &j) != GLUE_NIL) { return 0; } // FIXME: free memory
    (*board)[i] = calloc(n, sizeof(int));
    for(; j; j--) { 
      for(k = 0; k < n; k++) { if(!strcmp(country, countries[k])) { break; } }

      (*board)[i][arrRef(countries, adjacencies[j-1], n)] = 1;
      //free(adjacencies[j-1]); FIXME: causes error. not sure why since i malloc this in parseStrArr()
    }
    free(adjacencies);
  }

  if((errRISKY = setAdjacencies(game, int **board, int n) != RISKY_NIL) { goto FAIL_RISKY; }
*/

  if((errRISKY = risk(game)) != RISKY_NIL) { goto FAIL_RISKY; }
  if((errRISKY = isEvolved(game, val)) != RISKY_NIL) { goto FAIL_RISKY; }
  if(val) {
    //  for each ai in game.computers:
    //     setINI ai new DNA
    //if((errINI = writeINI(ini, argv[1])) != INI_NIL) { goto FAIL_INI; }
  }

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
  freeINI(ini);
  freeRISKY(game);
  return 0;
}
