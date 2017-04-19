/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/16/17
 Info:    main.c uses ini.h to read conf files in order to configure the command
          line version of Risky. It also writes the conf back out to file if the
          AIs were training.
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
typedef enum error {
  INVALID_ARRAY_LITERAL, INVALID_INT_LITERAL, NIL, OUT_OF_MEMORY, 
  INVALID_ARRAY_SEPERATOR
} error_t;

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// Return the string representation of a given error.
const char *errToStr(error_t error) {
  switch(error) {
    case INVALID_ARRAY_LITERAL: return "invalid array literal";
    case OUT_OF_MEMORY: return "out of memory";
    case INVALID_ARRAY_SEPERATOR: return "invalid array literal seperator";
    case INVALID_INT_LITERAL: return "invalid interger literal";
    case NIL: return "";
    default:  return "unknown error code";
  }
}

// Attempt to parse an integer literal.
error_t parseInt(char *literal, int *dest) {
  char *end;
  *dest = (int)strtol(literal, &end, 10);
  if(literal == end) { return INVALID_INT_LITERAL; }
  return NIL;
}

// Attempt to parse an array literal with its size.
error_t parseArrSize(char *literal, int *size) {
  if(*literal != '{') { return INVALID_ARRAY_LITERAL;  }
  for(*size = 0, literal++; *literal != '}'; literal++) {
    if(*literal == ',') { (*size)++; }
  }
  (*size)++; // always 1 more elem than comma seperators
  return NIL;
}

// Attempt to parse an array literal of integers.
error_t parseIntArr(char *literal, int **dest, int *size) {
  error_t error;

  if((error = parseArrSize(literal, size)) != NIL) { return error; }
  if(!(*dest = malloc(sizeof(int) * *size))) { return OUT_OF_MEMORY; }

  int i;
  for(i = 0, literal++; i < *size; i++, literal++) { // read '{'
    (*dest)[i] = (int)strtol(literal, &literal, 10); // FIXME: parseInt()
    if(!(*literal == ',' || *literal == '}')) { // invalid seperator or end
      free(*dest);
      return INVALID_ARRAY_SEPERATOR;
    }
  }
  return NIL;
}

// Attempt to parse an array literal of strings.
error_t parseStrArr(char *literal, char **dest, int *size) {
  error_t error;
  if((error = parseArrSize(literal, size)) != NIL) { return error; }
  if(!(*dest = malloc(sizeof(char *) * *size))) { return OUT_OF_MEMORY; }

  char *c;
  int i, j;
  for(i = 0, literal++, c = strtok(literal, ",}"); i < *size; i++, c = strtok(NULL, ",}")) {
    if(!(dest[i] = calloc(strlen(c)+1, sizeof(char)))) {
      for(j = 0; j < i; j++) { free(dest[i]); }
      return -1;
    }
    strncpy(dest[i], c, strlen(c));
  }
  return NIL;
}

// Attempt to read a setting from the conf.
int readConf(ini_t *ini, char *section, char *key, char **val) {
  errINI_t errINI = getINI(ini, section, key, val);
  if(errINI != INI_NIL) {
    fprintf(stderr, "error! invalid conf\nirritant: %s\nexiting...\n", strErrINI(errINI));
    return 0;
  }
  return 1;
}

// Attempt to get the index of country.
int arrRef(char **countries, char *country, int size) {
 for(; size; size--) {
  if(!strcmp(country, countries[size-1])) { return size-1; }
 }
 return -1;
}

// Attempt to generate an adjacency matrix representing the board. FIXME
int generateAdjacenyMatrix(ini_t *ini, char **countries, int size, int **board) {
  char *literal, *adjacencies;
  *board = calloc(size*size, sizeof(int));
  int i, j;
  for(i = 0; i < size; i++) {
    if(getINI(ini, "Map", countries[i], &literal) != INI_NIL) {
      fprintf(stderr, "error! invalid conf\nirritant: expected '%s' key under [Map]\nexiting...\n", countries[i]);
      return 0;
    }
    parseStrArr(literal, &adjacencies, &j);
    for(; j; j--) { board[i][arrRef(countries, &adjacencies[j-1], size)] = 1; }
    free(adjacencies);
  }
  return 1;
}

// Attempt to update the ini conf with the new chromosome.
void updateChromosome(ini_t *ini, int *chromosome, char *num) {
  char *val = calloc(100, sizeof(char));
  sprintf(val, "{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}", chromosome[0], chromosome[1], 
      chromosome[2], chromosome[3], chromosome[4], chromosome[5], 
      chromosome[6], chromosome[7], chromosome[8], chromosome[9]);
  setINI(ini, "Chromosome", num, val);
  free(val);
}

// Print out game, version, and author information. Make sure a configuration
// file is specified. Then attempts to setup, play, and teardown the game.
// Reports any errors if they occur and frees any memory that we allocated
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

  char *val;
  game_conf_t game;
  error_t error;

  /******************* PLAYERS *******************/
  if(!readConf(ini, "Players", "humans", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.hps)) != NIL) { goto DONE; }

  if(!readConf(ini, "Players", "computers", &val)) { goto FAIL; }
  if((error = parseStrArr(val, &game.computers, &game.cps)) != NIL) { goto DONE; }

  /******************* TRAINING *******************/
  if(!readConf(ini, "Training", "games", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.trains)) != NIL) { goto DONE; }

  if(!readConf(ini, "Training", "log", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.log)) != NIL) { goto DONE; }

  if(!readConf(ini, "Training", "dir", &game.dir)) { goto FAIL; }

  /******************* TROOPS *******************/
  if(!readConf(ini, "Troops", "beginning", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.beginning)) != NIL) { goto DONE; }

  if(!readConf(ini, "Troops", "minimum", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.minimum)) != NIL) { goto DONE; }

  if(!readConf(ini, "Troops", "bonus", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.bonus)) != NIL) { goto DONE; }

  if(!readConf(ini, "Troops", "random", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.random)) != NIL) { goto DONE; }

  /******************* CARDS *******************/
  if(!readConf(ini, "Cards", "types", &val)) { goto FAIL; }
  if((error = parseStrArr(val, &game.cardTypes, &game.numTypes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Cards", "wilds", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.wilds)) != NIL) { goto DONE; }

  if(!readConf(ini, "Cards", "trades", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.tradeIns, &game.numTrades)) != NIL) { goto DONE; }

  if(!readConf(ini, "Cards", "incr", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.tradeIncr)) != NIL) { goto DONE; }

  /******************* CHROMOSOMES *******************/
  if(!readConf(ini, "Chromosomes", "cp0", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp0, &game.numChromosomes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Chromosomes", "cp1", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp1, &game.numChromosomes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Chromosomes", "cp2", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp2, &game.numChromosomes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Chromosomes", "cp3", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp3, &game.numChromosomes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Chromosomes", "cp4", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp4, &game.numChromosomes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Chromosomes", "cp5", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp5, &game.numChromosomes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Chromosomes", "cp6", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp6, &game.numChromosomes)) != NIL) { goto DONE; }

  if(!readConf(ini, "Chromosomes", "cp7", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.cp7, &game.numChromosomes)) != NIL) { goto DONE; }

  /******************* MAP *******************/
  if(!readConf(ini, "Map", "continents", &val)) { goto FAIL; }
  if((error = parseStrArr(val, &game.continents, &game.numConts)) != NIL) { goto DONE; }

  if(!readConf(ini, "Map", "continents_bonus", &val)) { goto FAIL; }
  if((error = parseIntArr(val, &game.contBonuses, &game.numConts)) != NIL) { goto DONE; }

  if(!readConf(ini, "Map", "random", &val)) { goto FAIL; }
  if((error = parseInt(val, &game.randomCountries)) != NIL) { goto DONE; }

  if(!readConf(ini, "Map", "countries", &val)) { goto FAIL; }
  if((error = parseStrArr(val, &game.continents, &game.numCountries)) != NIL) { goto DONE; }

  if(!generateAdjacenyMatrix(ini, &game.countries, game.numCountries, &game.board)) { goto FAIL; }

  char *err;
  if((err = risk(&game))) {
    fprintf(stderr, "error! exception during gameplay\nirritant: %s\nexiting...\n", err);
    goto FAIL;
  }

  if(!game.hps && !game.cps) { // output new conf file if we were training
    updateChromosome(ini, game.cp0, "cp0");
    updateChromosome(ini, game.cp1, "cp1");
    updateChromosome(ini, game.cp2, "cp2");
    updateChromosome(ini, game.cp3, "cp3");
    updateChromosome(ini, game.cp4, "cp4");
    updateChromosome(ini, game.cp5, "cp5");
    updateChromosome(ini, game.cp6, "cp6");
    updateChromosome(ini, game.cp7, "cp7");

    if(writeINI(ini, argv[1]) != INI_NIL) {
      fprintf(stderr, "error! failure to output new conf file: %s\nexiting...\n", argv[1]);
      goto FAIL;
    }
  }

  return 0; // EXIT SUCCESSFULLY

DONE:
    fprintf(stderr, "error! invalid conf\nirritant: %s\nexiting...\n", errToStr(error));
    goto FAIL;

FAIL:
  freeINI(ini); //free conf file and allocated game arrays
  if(game.computers) { free(game.computers); }
  if(game.cardTypes) { free(game.cardTypes); }
  if(game.tradeIns) { free(game.tradeIns); }
  if(game.cp0) { free(game.cp0); }
  if(game.cp1) { free(game.cp1); }
  if(game.cp2) { free(game.cp2); }
  if(game.cp3) { free(game.cp3); }
  if(game.cp4) { free(game.cp4); }
  if(game.cp5) { free(game.cp5); }
  if(game.cp6) { free(game.cp6); }
  if(game.cp7) { free(game.cp7); }
  if(game.continents) { free(game.continents); }
  if(game.contBonuses) { free(game.contBonuses); }
  if(game.countries) { free(game.countries); }
  if(game.board) { free(game.board); }
  return 0;
}
