/******************************************************************************
 * FILE:    main.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  7/8/17                                                            *
 * INFO:    main.c assimilates the ini, log, dna, and risk libraries into an  *
 *          easily configurable command line version of a risk like game. The *
 *          game supports logging and artificial intellegence whose behavior  *
 *          is easily changed by manipulating only a few things in this file. *
 *          All error handling is properly taken care of, as well as freeing  *
 *          all memory we allocated, and the closing of all files.            *
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

int SESSION = -1;

errRISK_t errRISK;
errINI_t errINI;
errDNA_t errDNA;
errLOG_t errLOG;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/
// print out a standard error message
void printError(char *who, char *irritant) {
  fprintf(stderr, "error!\n");
  if(!who) { fprintf(stderr, "who: printError()\nirritant: nil who\n"); }
  else if(!irritant) { fprintf(stderr, "who: printError()\nirritant: nil irritant\n"); }
  else { fprintf(stderr, "who: %s\nirritant: %s\n", who, irritant); }
  fprintf(stderr, "exiting...\n");
  exit(EXIT_FAILURE);
}

// Read in an integer, only accepting input between the bounds. Optionally
// prompt the user 'are you sure'. Handles all errors appropriately, and runs
// until it gets valid input.
void readInt(int lbound, int ubound, int *choice, int prompt) {
  if(lbound >= ubound) { printError("readInt()", "invalid range"); }
  if(!choice) { printError("readInt()", "nil choice"); }
  if(!(prompt == 0 || prompt == 1)) { printError("readInt()", "prompt must be 0 or 1"); }

  char c;
  char buffer[80];
  for(;;) {
    fprintf(stdout, "Enter choice (%i-%i): ", lbound, ubound);
    if(!fgets(buffer, 80, stdin) ||
       !sscanf(buffer, "%d\n", choice) ||
       *choice < lbound || *choice > ubound) {
      fprintf(stdout, "invalid input\n");
      continue;
    }
    if(!prompt) { return; }
    for(;;) {
      fprintf(stdout, "Entered choice: %i, are you sure (y/n)? ", *choice);
      if(!fgets(buffer, 80, stdin) ||
         !sscanf(buffer, "%c\n", &c) ||
         !(c == 'y' || c == 'n')) {
        fprintf(stdout, "invalid input\n");
        continue;
      }
      if(c == 'y') { return; }
    }
  }
}

// print an array of strings as an enumerated list
void printChoices(char *elems[], int size) {
  if(!elems) { printError("printChoices()", "nil elems"); }
  if(size < 1) { printError("printChoices()", "invalid size"); }

  int i;
  for(i = 0; i < size; i++) { fprintf(stdout, "\t%i) %s\n", i, elems[i]);  }
  fprintf(stdout, "\n");
}

// TODO: implement. for now just promote higher traits.
int fitness(char *who, int chromosome[], int traits) {
  if(!who || !chromosome || (traits >= 0 && traits <= 9)) { return -1; }

  int fitness = 0;
  for(; traits; traits--) {
    switch(traits-1) {
      case 0: //offense:     [world domination speed]
        fitness += chromosome[0];
        break;
      case 1: //defence:     [building up troops]
        fitness += chromosome[1];
        break;
      case 2: //armies:      [higher number of troops]
        fitness += chromosome[2];
        break;
      case 3: //continents:  [continent bonuses]
        fitness += chromosome[3];
        break;
      case 4: //card_b:      [card bonus]
        fitness += chromosome[4];
        break;
      case 5: //troop_b:     [troop bonus]
        fitness += chromosome[5];
        break;
      case 6: //claim:       [country placement at game start]
        fitness += chromosome[6];
        break;
      case 7: //troops:      [troop placement at game start]
        fitness += chromosome[7];
        break;
      case 8: //takeover:    [overtaking opponents for cards]
        fitness += chromosome[8];
        break;
      case 9: //borders:     [fority borders]
        fitness += chromosome[9];
        break;
    }
  }
  return fitness;
}

// attempt to set up the logger from the INI conf file.
void setupLOGfromINI(ini_t *ini, log_t **logger) {
  setting_t *setting;
 
  if((errINI = lookupSetting(ini, "Logging", "log", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Logging, key=log", (char *)strErrINI(errINI));
  }

  int log;
  if((errINI = settingGetInt(setting, &log)) != INI_NIL) {
    printError("settingGetInt(), section=Logging, key=log", (char *)strErrINI(errINI));
  }

  if(!log) {
    *logger = NULL;
    return;
  }

  if((errINI = lookupSetting(ini, "Logging", "dir", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Logging, key=dir", (char *)strErrINI(errINI));
  }

  if((errINI = settingLength(setting, &log)) != INI_NIL) {
    printError("settingLength(), section=Logging, key=dir", (char *)strErrINI(errINI));
  }

  char dir[log];
  if((errINI = settingGetString(setting, dir)) != INI_NIL) {
    printError("settingGetString(), section=Logging, key=dir", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Logging", "columns", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Logging, key=columns", (char *)strErrINI(errINI));
  }

  if((errINI = settingGetInt(setting, &log)) != INI_NIL) {
    printError("settingGetInt(), section=Logging, key=columns", (char *)strErrINI(errINI));
  }

  time_t t = time(NULL);
  struct tm *date = localtime(&t);
  char name[80];
  strftime(name, 80, "%Y_%B_%d_%A_%X", date); // yr_mo_day_weekday_time

  char fname[80];
  sprintf(fname, "%s_SESSION_%i.txt", name, SESSION);

  if((errLOG = makeLOG(logger, log, dir, name)) != LOG_NIL) {
    printError("makeLOG()", (char *)strErrLOG(errLOG));
  }

  if((errLOG = logTitle(*logger, fname)) != LOG_NIL) {
    printError("logTitle()", (char *)strErrLOG(errLOG));
  }
}

// attempt to set up all the AI/chromosomes from the INI conf file
void setupDNAfromINI(ini_t *ini, dna_t **dna) {
  setting_t *setting;
 
  if((errINI = lookupSetting(ini, "Chromosomes", "traits", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=traits", (char *)strErrINI(errINI));
  }

  int traits;
  if((errINI = settingGetInt(setting, &traits)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=traits", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "elitism", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=elitism", (char *)strErrINI(errINI));
  }

  int elitism;
  if((errINI = settingGetBool(setting, &elitism)) != INI_NIL) {
    printError("settingGetBool(), section=Chromosomes, key=elitism", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "percentile", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=percentile", (char *)strErrINI(errINI));
  }

  float percentile;
  if((errINI = settingGetFloat(setting, &percentile)) != INI_NIL) {
    printError("settingGetFloat(), section=Chromosomes, key=percentile", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "mutation", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=mutation", (char *)strErrINI(errINI));
  }

  float rate;
  if((errINI = settingGetFloat(setting, &rate)) != INI_NIL) {
    printError("settingGetFloat(), section=Chromosomes, key=mutation", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "ubound", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=ubound", (char *)strErrINI(errINI));
  }

  int ubound;
  if((errINI = settingGetInt(setting, &ubound)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=ubound", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "lbound", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=lbound", (char *)strErrINI(errINI));
  }

  int lbound;
  if((errINI = settingGetInt(setting, &lbound)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=lbound", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "cps", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=cps", (char *)strErrINI(errINI));
  }

  int cps;
  if((errINI = settingLength(setting, &cps)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=cps", (char *)strErrINI(errINI));
  }

  char *ids[cps];
  
  int i, j;
  for(i = 0; i < cps; i++) {
    if((errINI = settingElemLength(setting, i,&j)) != INI_NIL) {
      printError("settingElemLength(), section=Chromosomes, key=cps", (char *)strErrINI(errINI));
    }

    char cp[j];
    if((errINI = settingGetString(setting, cp)) != INI_NIL) {
      printError("settingGetString(), section=Chromosomes, key=cp", (char *)strErrINI(errINI));
    }
    ids[i] = cp;
  }

  if((errDNA = makeDNA(dna, ids, cps, traits)) != DNA_NIL) {
    printError("makeDNA()", (char *)strErrDNA(errDNA));
  }

  if((errDNA = setFitness(*dna, fitness)) != DNA_NIL) {
    printError("setFitness()", (char *)strErrDNA(errDNA));
  }

  if((errDNA = setMutation(*dna, lbound, ubound, rate)) != DNA_NIL) {
    printError("setMutation()", (char *)strErrDNA(errDNA));
  }

  if((errDNA = setElitism(*dna, elitism, percentile)) != DNA_NIL) {
    printError("setElitism()", (char *)strErrDNA(errDNA));
  }

  int chromosome[traits];
  for(i = 0; i < cps; i++) {
    if((errINI = lookupSetting(ini, "Chromosomes", ids[i], &setting)) != INI_NIL) {
      printError("lookupSetting(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
    }

    if((errINI = settingLength(setting, &j)) != INI_NIL) {
      printError("settingLength(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
    }

    if(j != traits) {
      printError("setupDNAfromINI()", "computer traits does not match specified length");
    }

    for(j = 0; j < traits; j++) {
      if((errINI = settingGetIntElem(setting, j, &chromosome[j])) != INI_NIL) {
        printError("settingGetIntElem(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
      }
    }

    if((errDNA = setStrand(*dna, ids[i], chromosome, traits)) != DNA_NIL) {
      printError("setStrand()", (char *)strErrDNA(errDNA));
    }
  }
}

// attempt to log the dna information
void logDNA(dna_t *dna, log_t *logger) {
  int i, j, chromosomes, traits;
  float r;

  if((errLOG = logHeader(logger, "DNA")) != LOG_NIL) {
    printError("logHeader()", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logSection(logger, "Settings")) != LOG_NIL) {
    printError("logSection()", (char *)strErrLOG(errLOG));  
  }

  if((errDNA = getMutation(dna, &i, &j, &r)) != DNA_NIL) {
    printError("getMutation()", (char *)strErrDNA(errDNA));
  }

  if((errLOG = logFloatSetting(logger, "Mutation Rate", r)) != LOG_NIL) {
    printError("logFloatSetting()", (char *)strErrLOG(errLOG));
  }
  
  if((errLOG = logIntSetting(logger, "Lower Bound", i)) != LOG_NIL) {
    printError("logIntSetting()", (char *)strErrLOG(errLOG));
  }
  
  if((errLOG = logIntSetting(logger, "Upper Bound", j)) != LOG_NIL) {
    printError("logIntSetting()", (char *)strErrLOG(errLOG));
  }

  if((errDNA = getElitism(dna, &i, &r)) != DNA_NIL) {
    printError("getElitism()", (char *)strErrDNA(errDNA));
  }
  
  if((errLOG = logIntSetting(logger, "Elitism", i)) != LOG_NIL) {
    printError("logIntSetting()", (char *)strErrLOG(errLOG));
  }
  
  if((errLOG = logFloatSetting(logger, "Percentile", r)) != LOG_NIL) {
    printError("logFloatSetting()", (char *)strErrLOG(errLOG));
  }
  
  char tmp[] = "";
  
  if((errLOG = logEvent(logger, 0, tmp)) != LOG_NIL) {
    printError("logEvent()", (char *)strErrLOG(errLOG));
  }

  if((errDNA = getChromosomes(dna, &chromosomes, &traits)) != DNA_NIL) {
    printError("getChromosomes()", (char *)strErrDNA(errDNA));
  }
  
  char ids[chromosomes][36];
  
  if((errDNA = getIDs(dna, (char **)ids)) != DNA_NIL) {
    printError("getIDs()", (char *)strErrDNA(errDNA));
  }

  int strand[traits];

  if((errLOG = logSection(logger, "Chromosomes")) != LOG_NIL) {
    printError("logSection()", (char *)strErrLOG(errLOG));
  }
  
  for(; chromosomes; chromosomes--) {
    if((errLOG = logSection(logger, ids[chromosomes-1])) != LOG_NIL) {
      printError("logSection()", (char *)strErrLOG(errLOG));
    }

    if((errDNA = getStrand(dna, ids[chromosomes-1], strand, &j)) != DNA_NIL) {
      printError("getStrand()", (char *)strErrDNA(errDNA));
    }

    if((errLOG = logIntArr(logger, strand, j)) != LOG_NIL) {
      printError("logIntArray()", (char *)strErrLOG(errLOG));
    }

    if((errDNA = getFitness(dna, ids[chromosomes-1], &j)) != DNA_NIL) {
      printError("getFitness()", (char *)strErrDNA(errDNA));
    }

    if((errLOG = logIntSetting(logger, "fitness", j)) != LOG_NIL) {
      printError("logIntSetting(), key=fitness", (char *)strErrLOG(errLOG));
    }
  }
}

/*
// attempt to set up the risk game from the INI conf file.
void setupRISKfromINI(ini_t *ini, risk_t **game) { }
  int i, j, k, n;
  char **sarr1, **sarr2, **sarr3;

  if((errRISK = makeRISK(game)) != RISK_NIL) {
    printError("makeRISK()", (char *)strErrRISK(errRISK));
  }

  if((errINI = getIntINI(ini, "Troops", "beginning", &i)) != INI_NIL) {
    printError("getIntINI(), section=Troops, key=beginning", (char *)strErrINI(errINI));
  }

  if((errINI = getIntINI(ini, "Troops", "minimum", &j)) != INI_NIL) {
    printError("getIntINI(), section=Troops, key=minimum", (char *)strErrINI(errINI));
  }

  if((errINI = getIntINI(ini, "Troops", "bonus", &k)) != INI_NIL) {
    printError("getIntINI(), section=Troops, key=bonus", (char *)strErrINI(errINI));
  }

  if((errINI = getBoolINI(ini, "Troops", "random", &n)) != INI_NIL) {
    printError("getBoolINI(), section=Troops, key=random", (char *)strErrINI(errINI));
  }

  if((errRISK = setTroops(*game, i, j, k, n)) != RISK_NIL) {
    printError("setTroops()", (char *)strErrRISK(errRISK));
  }

  if((errINI = getStrArrINI(ini, "Players", "humans", &sarr1, &i))!= INI_NIL) {
    printError("getStrArrINI(), section=Players, key=humans", (char *)strErrINI(errINI));
  }

  char *humans[i];

  if((errINI = getStrArrINI(ini, "Players", "computers", &sarr2, &j)) != INI_NIL) {
    printError("getStrArrINI(), section=Players, key=computers", (char *)strErrINI(errINI));
  }

  char *computers[j];
  char *players[i+j];

  k = 0;
  for(; i; i--) { sarr3[k++] = sarr1[i-1]; }
  for(; j; j--) { sarr3[k++] = sarr2[j-1]; }

  if((errRISK = setPlayers(*game, k, players)) != RISK_NIL) {
    printError("setPlayers()", (char *)strErrRISK(errRISK));
  }

  if((errINI = getStrArrINI(ini, "Cards", "types", &sarr2, &i)) != INI_NIL) {
    printError("getStrArrINI(), section=Cards, key=types", (char *)strErrINI(errINI));
  }

  char *cards[i];

  if((errINI = getIntINI(ini, "Cards", "wilds", &j)) != INI_NIL) {
    printError("getIntINI(), section=Cards, key=wilds", (char *)strErrINI(errINI));
  }

  if((errRISK = setDeck(*game, i, sarr2, j)) != RISK_NIL) {
    printError("setDeck()", (char *)strErrRISK(errRISK));
  }

  if((errINI = getIntArrINI(ini, "Cards", "trades", &iarr, &k)) != INI_NIL) {
    printError("getIntArrINI(), section=Cards, key=trades", (char *)strErrINI(errINI));
  }

  if((errINI = getIntINI(ini, "Cards", "incr", &n)) != INI_NIL) {
    printError("getIntINI(), section=Cards, key=incr", (char *)strErrINI(errINI));
  }

  if((errRISK = setTrades(*game, iarr, k, n)) != RISK_NIL) {
    printError("setTrades()", (char *)strErrRISK(errRISK));
  }

  if((errINI = getStrArrINI(ini, "Map", "continents", &sarr2, &k)) != INI_NIL) {
    printError("getStrArrINI() section=Map, key=continents", (char *)strErrINI(errINI));
  }

  if((errRISK = setContinents(*game, sarr2, k)) != RISK_NIL) {
    printError("setContinents()", (char *)strErrRISK(errRISK));
  }

  if((errINI = getIntArrINI(ini, "Map", "continents_bonus", &iarr, &n)) != INI_NIL) {
    printError("getIntArrINI(), section=Map, key=continents_bonus", (char *)strErrINI(errINI));
  }

  if((errRISK = setContinentBonuses(*game, iarr, n)) != RISK_NIL) {
    printError("setContinentBonuses()", (char *)strErrRISK(errRISK));
  }

  if((errINI = getBoolINI(ini, "Map", "random", &n)) != INI_NIL) {
    printError("getBoolINI(), section=Map, key=random", (char *)strErrINI(errINI));
  }

  if((errINI = getStrArrINI(ini, "Map", "countries", &sarr1, &k)) != INI_NIL) {
    printError("getBoolINI(), section=Map, key=countries", (char *)strErrINI(errINI));
  }

  if((errRISK = setCountries(*game, sarr1, k, n)) != RISK_NIL) {
    printError("setCountries()", (char *)strErrRISK(errRISK));
  }

  for(i = 0; i < k; i++) {
    if((errINI = getStrArrINI(ini, "Map", sarr1[i], &sarr2, &j)) != INI_NIL) {
      printError("getStrArrINI(), section=Map, key=??", (char *)strErrINI(errINI));
    }

    if((errRISK = setAdjacencies(*game, sarr1[i], sarr2, j)) != RISK_NIL) {
      printError("setAdjacencies()", (char *)strErrRISK(errRISK));
    }
  }
}

// log the game setup 
void logRISK(risk_t *game, log_t *logger) {
  int i, j, k;
  char **names;
  int *trades;

  logHeader(logger, "S E T T I N G S");
  logSection(logger, "PLAYERS");
  getPlayers(game, &names, &i);
  logStrArr(logger, names, i);

  logSection(logger, "TROOPS");
  getTroops(game, &i, &j, &k);
  logIntSetting(logger, "Beginning count", i);
  logIntSetting(logger, "Minimum/turn", j);
  logIntSetting(logger, "Extra troop/#countries", k);

  logSection(logger, "CARDS");
  getDeck(game, &i, &names, &j);
  logIntSetting(logger, "Wilds", i);
  logStrArr(logger, names, i);
  getTrades(game, &trades, &i, &j);
  logIntArr(logger, trades, i);
  logIntSetting(logger, "Trade increment", j);


  logSection(logger, "MAP");
  getContinents(game, &names, &i);
  logStrArr(logger, names, i);
  getCountries(game, &names, &i);
  logStrArr(logger, names, i);
  getContinentBonuses(game, &trades, &i);
  logIntArr(logger, trades, i);

  //logEvent(logger, "Adjacency Matrix:\n");
  //getNeighbors(game, char *country, char ***neighbors, int *size);
  //logIntArr2D(logger, game->board, game->numCountries, game->numCountries);
}
*/

void logGameTime(log_t *logger, int seconds) {
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  char val[40];
  sprintf(val, "[%ih-%im-%is]", hours, minutes, seconds);

  if((errLOG = logHeader(logger, "T I M E")) != LOG_NIL) {
    printError("logHeader()", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logStrSetting(logger, "Elapsed game time", val)) != LOG_NIL) {
    printError("logHeader()", (char *)strErrLOG(errLOG));  
  }
}

void printBoard(risk_t *game) { // TODO
  if(!game) { printError("printBoard()", "nil game parameter"); }

  /*
    |*******************************************************|
    |  | country | owner | armies | continent | adjacencies |
    |-------------------------------------------------------|
    |0 |                                                    |
    |-------------------------------------------------------|
    |1 |                                                    |
    |-------------------------------------------------------|
    |2 |                                                    |
    |-------------------------------------------------------|
    |..|                                                    |
    |-------------------------------------------------------|
    |n |                                                    |
    |-------------------------------------------------------|
    |_______________________________________________________|
  */

  printError("printBoard()", "NOT IMPLEMENTED");
}

void humanTurn(risk_t *game, char *player, log_t *logger) { // TODO
  int choice;
  int prompt = 1;

  int mainChoices = 6;
  char *mainMenu[] = {"Trade", "Attack", "Maneuver", "Query", "Board", "End"};

  int queryChoices = 5;
  char *queryMenu[] = {"Players", "Countries", "Continents", "Cards", "Main Menu"};

  int done = 0;
  while(!done) { // TODO: if winner then
    //if(game->log) { fprintf(game->fp, "congratuations %s, you've achieved world domination!\n", player); }
    fprintf(stdout, "%s's turn...\n", player);
    printChoices(mainMenu, mainChoices);
    readInt(0, mainChoices-1, &choice, prompt);
    switch(choice) {
      case 0: // TRADE
        fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
        // get which cards getCards(player, *arr, *size);
        // place troops
        //    -- enfore trade rules, timeing(1/turn and beginning?)
        break;
      case 1: // ATTACK
        fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
        // src, dest (adjacency)
        // how many
        // ask defender how many (1 or 2)
        //  - draw card (if win), kill ememy (get card/enfore trade)
        break;
      case 2: // MANEUVER
        fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
        // src, dest (chain reachable)
        // how many
        done = 1;
        break;
      case 3: // QUERY
        printChoices(queryMenu, queryChoices);
        readInt(0, queryChoices-1, &choice, prompt);
        switch(choice) {
          case 0: // PLAYERS
            fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
            break;
          case 1: // COUNTRIES
            fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
            break;
          case 2: // CONTINENTS
            fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
            break;
          case 3: // CARDS
            fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
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

void computerTurn(risk_t *game, dna_t *dna, char *player, log_t *logger) { // TODO
  if(!game) { printError("computerTurn()", "nil game"); }

  if(!dna) { printError("computerTurn()", "nil dna"); }

  if(!player) { printError("computerTurn()", "nil player"); }

  printError("computerTurn()", "NOT IMPLEMENTED");
}

int getType(risk_t *game, dna_t *dna, char *player) { // TODO
  if(!game) { printError("getType()", "nil game"); }

  if(!dna) { printError("getType()", "nil dna"); }

  if(!player) { printError("getType()", "nil player"); }

  printError("getType()", "NOT IMPLEMENTED");

  return 0;
}

// play the game, taking care to reset between games if training
void risky(risk_t *game, dna_t *dna, int games) {
  if(games > 0) {
    fprintf(stdout, "training sessions requested: %d\ntraining...\n", games);
  }

  do {
    SESSION = games;
    setupLOGfromINI(ini, &logger);
    if(logger) {
      //logRISK(game, logger);
      logDNA(dna, logger);
    }

    if(games > 0) { fprintf(stdout, "sessions left: %i\n", games); }

    // [re]set game
    if((errRISK = initDeck(game)) != RISK_NIL) {
      printError("initDeck()", (char *)strErrRISK(errRISK));
    }
    if((errRISK = initCountries(game)) != RISK_NIL) {
      printError("initCountries()", (char *)strErrRISK(errRISK));
    }
    if((errRISK = initArmies(game)) != RISK_NIL) {
      printError("initArmies()", (char *)strErrRISK(errRISK));
    }

    //char *player = NULL;
    if(logger) { logHeader(logger, "G A M E P L A Y"); }
    time_t start = time(NULL);
    char tmp[] = "starting game...\n";
    logEvent(logger, 1, tmp);

    // sleep(1) hack
    //while(difftime(time(NULL), start) < 1.0);
    //while(1) { // getPlayers(game) > 1) { // TODO: implementeing human/cp turns
      //player = getNextPlayer(game);
      //if(logger) { logEvent(logger, 1, "%s's turn...\n\n"); }
      //fprintf(stdout, "%s's turn...\n\n", player);
      //if(!getType(game, dna, player)) { computerTurn(game, dna, player, logger); }
      //else { humanTurn(game, player, logger); }
    //}
    char tmp2[] = "ending game...\n";
    if((errLOG = logEvent(logger, 1, tmp2)) != LOG_NIL) {
      printError("logEvent()", (char *)strErrLOG(errLOG));
    }

    int seconds = (int)difftime(time(NULL), start);

    if(games) {
      if((errDNA = nextGeneration(dna)) != DNA_NIL) {
        printError("nextGeneration()", (char *)strErrDNA(errDNA));
      }

      if((errLOG = logHeader(logger, "N E W   G E N E R A T I O N")) != LOG_NIL) {
        printError("logHeader()", (char *)strErrLOG(errLOG));
      }

      int chromosomes, traits;
      if((errDNA = getChromosomes(dna, &chromosomes, &traits)) != DNA_NIL) {
        printError("getChromosomes()", (char *)strErrDNA(errDNA));
      }

      char ids[chromosomes][36];
      if((errDNA = getIDs(dna, (char **)ids)) != DNA_NIL) {
        printError("getIDs()", (char *)strErrDNA(errDNA));
      }

      int strand[traits];
      for(; chromosomes; chromosomes--) {
        errDNA = getStrand(dna, ids[chromosomes-1], strand, &traits);
        if(errDNA != DNA_NIL) {
          printError("getStrand()", (char *)strErrDNA(errDNA));
        }

        if((errLOG = logIntArr(logger, strand, traits)) != LOG_NIL) {
          printError("logIntArr()", (char *)strErrLOG(errLOG));
        }
      }
    }

    if(logger) {
      logGameTime(logger, seconds);
      freeLOG(logger);
      logger = NULL;
    }
  } while(--games > 0);
}

// free all memory we alloc'd, if any, ignoring any errors. This is the reason
// we have four globals tracking these data structures
void cleanup() {
  freeINI(ini);
  freeLOG(logger);
  freeDNA(dna);
  freeRISK(game);
}

int main(int argc, char *argv[]) {
  fprintf(stdout, "Risky\nv1.0\nRyan Rozanski\n\n");

  if(argc != 2) { printError("main()", "must specify a conf file"); }

  atexit(cleanup); // register cleanup() to be called upon exit()
  if((errINI = readINI(&ini, argv[1])) != INI_NIL) {
    printError("readINI()", (char *)strErrINI(errINI));
  }

  setting_t *setting;
  if((errINI = lookupSetting(ini, "Training", "games", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Training, key=games", (char *)strErrINI(errINI));
  }

  if((errINI = settingGetInt(setting, &argc)) != INI_NIL) {
    printError("settingGetInt(), section=Training, key=games", (char *)strErrINI(errINI));
  }

  if((errINI = makeINI(&ini)) != INI_NIL) {
    printError("makeINI()", (char *)strErrINI(errINI));
  }

  setupDNAfromINI(ini, &dna);

  //setupRISKfromINI(ini, &game);
  if((errRISK = isValid(game)) != RISK_NIL) {
    printError("isValid()", (char *)strErrRISK(errRISK));
  }

  srand(time(NULL)); // set random for risk and dna libs
  risky(game, dna, 1);

  if(argc > 1) { // replace all chromosomes in conf once, when done training
    int strands, traits;
    if((errDNA = getChromosomes(dna, &strands, &traits)) != DNA_NIL) {
      printError("getChromosomes()", (char *)strErrDNA(errDNA));
    }

    char ids[strands][36];
    if((errDNA = getIDs(dna, (char **)ids)) != DNA_NIL) {
      printError("getIDs()", (char *)strErrDNA(errDNA));
    }

    int strand[traits];
    for(; strands; strands--) {
      errDNA = getStrand(dna, ids[strands-1], strand, &traits);
      if(errDNA != DNA_NIL) {
        printError("getStrands()", (char *)strErrDNA(errDNA));
      }

      if((errINI = lookupSetting(ini, "Chromosomes", ids[strands-1], &setting)) != INI_NIL) {
        printError("lookupSetting(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
      }

      int i;
      if((errINI = settingLength(setting, &i)) != INI_NIL) {
        printError("settingLength(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
      }

      if(i != traits) {
        printError("main()", "failure to overwrite strand, length mismatch");
      }

      for(; i; i--) {
        if((errINI = settingSetIntElem(setting, i-1, strand[i-1])) != INI_NIL) {
          printError("settingSetIntElem(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
        }
      }
    }

    if((errINI = writeINI(ini, argv[1])) != INI_NIL) {
      printError("writeINI()", (char *)strErrINI(errINI));
    }
  }

  exit(EXIT_SUCCESS);
}
