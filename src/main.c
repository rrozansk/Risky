/******************************************************************************
 * FILE:    main.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  5/7/17                                                            *
 * INFO:    main.c is the glue which holds together the ini, log, dna, and    *
 *          risky libraries.                                                  *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <ini.h>
#include <log.h>
#include <dna.h>
#include <risk.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   G L O B A L S                                                            *
 *                                                                            *
 ******************************************************************************/
ini_t *ini = NULL;
log_t *logger = NULL;
dna_t *dna = NULL;
risk_t *game = NULL;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/

// Read in an integer, only accepting input between the bounds. Optionally prompt
// user 'are you sure'. Handles all errors appropriately.
void readInt(int lbound, int ubound, int *pick, int prompt) {
  // FIXME: internal errors!
  //if(lbound >= ubound) { return GLUE_INVALID_RANGE; }
  //if(!pick) { return GLUE_NIL_CHOICE; }
  //if(!(prompt == 0 || prompt == 1)) { return GLUE_INVALID_PROMPT; }

  char c;
  char buffer[80];
  fprintf(stdout, "Enter pick (%i-%i): ", lbound, ubound);
  while(fgets(buffer, 80, stdin)) {
    if(!sscanf(buffer, "%d\n", pick) || *pick < lbound || *pick > ubound) {
      fprintf(stdout, "invalid, input must be a single integer between %i-%i\n", lbound, ubound);
      fprintf(stdout, "Enter pick (%i-%i): ", lbound, ubound);
    } else if(prompt) {
      fprintf(stdout, "Entered choice: %i, are you sure (y/n)? ", *pick);
      while(fgets(buffer, 80, stdin)) {
        if(!sscanf(buffer, "%c\n", &c) || !(c == 'y' || c == 'n')) {
          fprintf(stdout, "invalid input, only enter 'y'/'n': ");
        }
        else if(c == 'y') { return; }
        else { break; } // c == 'n'
      }
      //if(c != 'n') { return GLUE_READ_ERROR; }
      fprintf(stdout, "Enter pick (%i-%i): ", lbound, ubound);
    } else { return; }
  }

  //return GLUE_READ_ERROR;
}

// print an array as an enumerated list
void printChoices(char **elems, int size) {
  //if(!elems) { return GLUE_INVALID_INDEX_SIZE; }
  //if(!size || size < 0) { return GLUE_NIL_ELEMS; }

  int i;
  for(i = 0; i < size; i++) { fprintf(stdout, "\t%i) %s\n", i, elems[i]);  }
  fprintf(stdout, "\n");
}


// Attempt to create a matrix.
void mallocMatrix(int ***matrix, int r, int c) {
  if(!(*matrix = malloc(sizeof(int *) * r))) {
    fprintf(stderr, "error! out of memory\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0; i < r; i++) { 
    if(!((*matrix)[i] = calloc(c, sizeof(int)))) {
      for(; i; i--) { free((*matrix)[i-1]); }
      free(*matrix);
      fprintf(stderr, "error! out of memory\nexiting...\n");
      exit(EXIT_FAILURE);
    }
  }
}

void updateChromosomes(ini_t *ini, dna_t *dna, log_t *logger) {
  char chromosome[80];
  int j = 0;
  int size, pos, *intArr;
  int chars;
  char **strArr1, buff[10];
  for(; j; j--) { 
    int pos = 0;
    buff[pos++] = '{';

    int chars;
    for(j = 0; j < size; j++) {
      //chars = sprintf(&buff[pos], "%d", arr[j]);
      if(chars < 0) {}
      pos += chars;
      if(j < size-1) {
        chars = sprintf(&buff[pos], ",");
        if(chars < 0) {}
        pos += chars;
      }
    }

    buff[pos++] = '}';
    buff[pos] = '\0';
    //if((errINI = setINI(ini, "Chromosomes", strArr1[i-1], chromosome)) != INI_NIL) {}
  }
}

// if cannot set up then print error message, but continue playing
void setupLOGfromINI(ini_t *ini, log_t **logger) {
  int log;
  errINI_t errINI;
  if((errINI = getIntINI(ini, "Logging", "log", &log)) != INI_NIL) {
    fprintf(stderr, "failure to set up log...");
    *logger = NULL;
  }
  if(!log) { return; }
   
  time_t t = time(NULL);
  struct tm *date = localtime(&t);
  char name[80];
  strftime(name, 80, "%Y_%B_%d_%A_%X.txt", date); // yr_mo_day_weekday_time

  int columns;
  char *val;
  if((errINI = getIntINI(ini, "Logging", "columns", &columns)) != INI_NIL) {}
  if((errINI = getStrINI(ini, "Logging", "dir", &val)) != INI_NIL) {}

  errLOG_t errLOG;
  if((errLOG = makeLOG(logger, columns, val, name)) != LOG_NIL) {
    fprintf(stderr, "failure to set up log...");
    *logger = NULL;
  }

  if((errLOG = logTitle(*logger, name)) != LOG_NIL) {}
}

void logRISK(risk_t *game, log_t *logger) {
/*
  if((errLOG = logHeader(log, "S E T T I N G S")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSection(log, "PLAYERS")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Humans", game->hps)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Computers", game->cps)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Human names: ")) != LOG_NIL) { return errLOG; }
  if((errLOG = logStrArr(log, game->humans, game->hps)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Computer names: ")) != LOG_NIL) { return errLOG; }
  if((errLOG = logStrArr(log, game->computers, game->cps)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "\n")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSection(log, "TROOPS")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Beginning count", game->beginning)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Minimum/turn", game->minimum)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Extra troop/#countries", game->bonus)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Randomized", game->random)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "\n")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSection(log, "CARDS")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Wilds", game->wilds)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Number types", game->numTypes)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Number trade ins", game->numTrades)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Trade increment", game->tradeIncr)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Types: ")) != LOG_NIL) { return errLOG; }
  if((errLOG = logStrArr(log, game->cardTypes, game->numTypes)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Trade Ins: ")) != LOG_NIL) { return errLOG; }
  if((errLOG = logIntArr(log, game->tradeIns, game->numTrades)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "\n")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSection(log, "MAP")) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Number continents", game->numConts)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Number countries", game->numCountries)) != LOG_NIL) { return errLOG; }
  if((errLOG = logSetting(log, "Randomized countries", game->randomCountries)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Continents: ")) != LOG_NIL) { return errLOG; }
  if((errLOG = logStrArr(log, game->continents, game->numConts)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Continent bonuses: ")) != LOG_NIL) { return errLOG; }
  if((errLOG = logIntArr(log, game->contBonuses, game->numConts)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Countries: ")) != LOG_NIL) { return errLOG; }
  if((errLOG = logStrArr(log, game->countries, game->numCountries)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "Adjacency Matrix:\n")) != LOG_NIL) { return errLOG; }
  if((errLOG = logIntArr2D(log, game->board, game->numCountries, game->numCountries)) != LOG_NIL) { return errLOG; }
  if((errLOG = logEvent(log, "\n")) != LOG_NIL) { return errLOG; }
*/ 
}

void logDNA(dna_t *dna, log_t *logger) {
/*
  logSection(log, "DNA");
  logSetting(log, "Chromosomes", getChromosomes(dna));
  logSetting(log, "Traits", game->traits);
  logSetting(log, "Mutation Rate", game->mutationRate);
  logSetting(log, "Elitism", game->elitism);
  logEvent(log, "AI names: ");
  logStrArr(log, game->names, game->chromosomes);
  logEvent(log, "Strands:\n");
  logIntArr2D(log, game->strands, game->chromosomes, game->traits);
  logEvent(log, "\n");
  logSection(log, "TRAINING");
  logSetting(log, "Sessions", game->trains);
  logEvent(log, "\n");
*/
}

void setupRISKfromINI(ini_t *ini, risk_t **game) { /*
  if((errRISK = makeRISK(game)) != RISK_NIL) {
    fprintf(stderr, "");
    exit(EXIT_FAILURE);
  }

  char **sarr1, **sarr2;
  int i, j, k, n;
  if((errINI = getStrArrINI(ini, "Players", "humans", &sarr1, &i))!= INI_NIL) {
    fprintf(stderr, "");
    exit(EXIT_FAILURE);
  }

  
  if((errINI = getINI(ini, "Players", "computers", &j)) != INI_NIL) {
    fprintf(stderr, "");
    free(sarr1);
    exit(EXIT_FAILURE);
  }

  // concat sarr1, sarr2 and setPlayers(game, newArr, size);

  if((errINI = getIntINI(ini, "Troops", "beginning", &i)) != INI_NIL) {
    fprintf(stderr, "");
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Troops", "minimum", &j)) != INI_NIL) {
    fprintf(stderr, "");
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Troops", "bonus", &k)) != INI_NIL) {
    fprintf(stderr, "");
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Troops", "random", &n)) != INI_NIL) {
    fprintf(stderr, "");
    exit(EXIT_FAILURE);
  }

  if((errRISK = setTroops(game, i, j, k, n)) != RISK_NIL) {
    fprintf(stderr, "");
    exit(EXIT_FAILURE);
  }

  if((errINI = getINI(ini, "Cards", "types", &val)) != INI_NIL) { goto FAIL_INI; } // String arr

  if((errINI = getINI(ini, "Cards", "wilds", &val)) != INI_NIL) { goto FAIL_INI; } // int
  if((errRISK = setDeck(game, i, strArr1, n)) != RISK_NIL) { goto FAIL_RISK; }

  if((errINI = getINI(ini, "Cards", "trades", &val)) != INI_NIL) { goto FAIL_INI; } // TODO: free array after set

  if((errINI = getINI(ini, "Cards", "incr", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errRISK = setTrades(game, intArr, n, i)) != RISK_NIL) { goto FAIL_RISK; }

  if((errINI = getINI(ini, "Map", "continents", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errRISK = setContinents(game, strArr1, n)) != RISK_NIL) { goto FAIL_RISK; }

  if((errINI = getINI(ini, "Map", "continents_bonus", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errRISK = setContinentBonuses(game, intArr, i)) != RISK_NIL) { goto FAIL_RISK; }

  if((errINI = getINI(ini, "Map", "random", &val)) != INI_NIL) { goto FAIL_INI; }

  if((errINI = getINI(ini, "Map", "countries", &val)) != INI_NIL) { goto FAIL_INI; }
  if((errRISK = setCountries(game, strArr1, n, i)) != RISK_NIL) { goto FAIL_RISK; }

  if((errGLUE = mallocMatrix(&matrix, n, n)) != GLUE_NIL) { goto FAIL_GLUE; } // TODO: free array after set
  if((errRISK = setAdjacencies(game, matrix, n)) != RISK_NIL) { goto FAIL_RISK; }

  for(i = 0; i < n; i++) {
    if((errINI = getINI(ini, "Map", strArr1[i], &val)) != INI_NIL) { goto FAIL_INI; } 

    for(; j; j--) {
      for(k = n; k; k--) {
        if(!strcmp(strArr1[k-1], strArr2[j-1])) {
          matrix[i][k-1] = 1;
          break;
        }
      }
    }
    free(strArr2);
  }
*/ }

// Chromosome conf sections
// if cannot setup print error msg and call exit()
void setupDNAfromINI(ini_t *ini, dna_t **dna) { /*
  if((errINI = getINI(ini, section = "Chromosomes", key = "cps", &val)) != INI_NIL) { goto FAIL_INI; } // TODO: free array after set

  if((errINI = getINI(ini, "Chromosomes", key = "traits", &val)) != INI_NIL) { goto FAIL_INI; }

  if((errGLUE = mallocMatrix(&matrix, n, j)) != GLUE_NIL) { goto FAIL_GLUE; } // TODO: free array after set
  //if((errRISK = setCps(game, matrix, strArr1, n, j)) != RISK_NIL) { goto FAIL_RISK; }

  //mutationRate=0.01                 ; type: float, range: 0.00-1.00
  //elitism=1                         ; type: bool, range: 0/1
    for(i = 0; i < n; i++) {
    if((errINI = getINI(ini, "Chromosomes", key = strArr1[i], &val)) != INI_NIL) { goto FAIL_INI; }
    if(j != k) {
      errGLUE = GLUE_INVALID_CHROMOSOME;
      goto FAIL_GLUE;
    }
  }
*/ }

void logGameTime(log_t *logger, int seconds) {
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  char val[40];
  sprintf(val, "[%ih-%im-%is]", hours, minutes, seconds);

  logHeader(logger, "T I M E");
  //logSetting(logger, "Exapsed game time", val);
}

void printBoard(risk_t *game) { // TODO 
  //if(!game) { return GLUE_NIL_GAME; }
}

void humanTurn(risk_t *game, char *player, log_t *logger) {
  int choice;
  int prompt = 1;

  int mainChoices = 6;
  char *mainMenu[] = {"Trade", "Attack", "Maneuver", "Query", "Board", "End"};

  int queryChoices = 5;
  char *queryMenu[] = {"Players", "Countries", "Continents", "Cards", "Main Menu"};

  int done = 0;
  errRISK_t errRISK;

  while(!done) { // TODO: if winner then
    //if(game->log) { fprintf(game->fp, "congratuations %s, you've achieved world domination!\n", player); }
    fprintf(stdout, "%s's turn...\n", player);
    printChoices(mainMenu, mainChoices);
    readInt(0, mainChoices-1, &choice, prompt);
    switch(choice) {
      case 0: // TRADE
        // get which cards getCards(player, *arr, *size);
        // place troops
        //    -- enfore trade rules, timeing(1/turn and beginning?)
        break;
      case 1: // ATTACK
        // src, dest (adjacency)
        // how many
        // ask defender how many (1 or 2)
        //  - draw card (if win), kill ememy (get card/enfore trade)
        break;
      case 2: // MANEUVER
        // src, dest (chain reachable)
        // how many
        done = 1;
        break;
      case 3: // QUERY
        printChoices(queryMenu, queryChoices);
        readInt(0, queryChoices-1, &choice, prompt);
        switch(choice) {
          case 0: // PLAYERS
            break;
          case 1: // COUNTRIES
            break;
          case 2: // CONTINENTS
            break;
          case 3: // CARDS
            break;
          case 4: // MAIN MENU
            break;
          default:
            return;
        }
        break;
      case 4: // BOARD
        printBoard(game);
        break;
      case 5: // END
        done = 1;
        break;
      default:
        return;
    }
  }
}

void computerTurn(risk_t *game, dna_t *dna, char *player, log_t *logger) {}

int getType(risk_t *game, dna_t *dna, char *player) { return 1; }

// play the game, taking care to reset between games if training
void risky(risk_t *game, dna_t *dna, int trainingSessions) {
  if(trainingSessions > 0) {
    fprintf(stdout, "training sessions requested: %d\ntraining...\n", trainingSessions);
  }

  errRISK_t errRISK;

  do {
    setupLOGfromINI(ini, &logger);
    if(logger) {
      logRISK(game, logger);
      logDNA(dna, logger);
    }

    if(trainingSessions > 0) { fprintf(stdout, "sessions left: %i\n", trainingSessions); }

    // [re]set game
    //if((errRISK = initDeck(game)) != RISK_NIL) {
    //  fprintf(stderr, "error! failure to ini deck\nirritant: %s\nexiting...", strErrRISK(errRISK));
    //  exit(EXIT_FAILURE);
    //}
    //if((errRISK = initCountries(game)) != RISK_NIL) {
    //  fprintf(stderr, "error! failure to ini deck\ncountries: %s\nexiting...", strErrRISK(errRISK));
    //  exit(EXIT_FAILURE);
    //}
    //if((errRISK = initArmies(game)) != RISK_NIL) {
    //  fprintf(stderr, "error! failure to ini deck\narmies: %s\nexiting...", strErrRISK(errRISK));
    //  exit(EXIT_FAILURE);
    //}

    char *player = NULL;
    logHeader(logger, "G A M E P L A Y");
    time_t start = time(NULL);
    while(1) { // getPlayers(game) > 1) {
      //player = getNextPlayer(game);
      if(logger) { logEvent(logger, 1, "%s's turn...\n\n"); }
      fprintf(stdout, "%s's turn...\n\n", player);
      if(!getType(game, dna, player)) { computerTurn(game, dna, player, logger); }
      else { humanTurn(game, player, logger); }
    }
    int seconds = (int)difftime(time(NULL), start);

    if(trainingSessions) { 
      //makeNextGeneration(dna); // dna lib
      logHeader(logger, "N E W   G E N E R A T I O N");
      //logIntArr2D(logger, game->strands, game->chromosomes, game->traits);
    }

    if(logger) { 
      logGameTime(logger, seconds);
      freeLOG(logger);
    }
  } while(--trainingSessions > 0);
}

// free all memory we alloc'd, if any, ignoring any errors
void cleanup() {
  freeINI(ini);
  freeLOG(logger);
  freeDNA(dna);
  freeRISK(game);
}

int main(int argc, char *argv[]) {
  fprintf(stdout, "Risky\nv1.0\nRyan Rozanski\n\n");

  if(argc != 2) {
    fprintf(stderr, "error! must specify a conf file, exiting...\n");
    exit(EXIT_FAILURE);
  }

  atexit(cleanup); // register cleanup() to be called upon exit()

  errINI_t errINI = INI_NIL;
  if((errINI = readINI(&ini, argv[1])) != INI_NIL) {
    fprintf(stderr, "error! failure to read conf\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Training", "games", &argc)) != INI_NIL) {
    fprintf(stderr, "error! INI section=Training,key=games\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  setupDNAfromINI(ini, &dna);
  setupRISKfromINI(ini, &game);

  errRISK_t errRISK;
  if((errRISK = isValid(game)) != RISK_NIL) {
    fprintf(stderr, "error! invalid game specified by conf\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    exit(EXIT_FAILURE);
  }

  risky(game, dna, argc);

  if(argc) {
    updateChromosomes(ini, dna, logger);
    if((errINI = writeINI(ini, argv[1])) != INI_NIL) {
      fprintf(stderr, "error! failure to write conf\nirritant: %s\nexiting...\n", strErrINI(errINI));
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
