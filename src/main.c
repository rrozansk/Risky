/******************************************************************************
 * FILE:    main.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  9/12/17                                                           *
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
ini_t  *ini    = NULL;
log_t  *logger = NULL;
dna_t  *dna    = NULL;
risk_t *game   = NULL;

int SESSION = -1;

errRISK_t errRISK = RISK_NIL;
errINI_t  errINI  = INI_NIL;
errDNA_t  errDNA  = DNA_NIL;
errLOG_t  errLOG  = LOG_NIL;

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

// print an array of strings as an enumerated list
void printChoices(char *elems[], int size) {
  if(!elems) { printError("printChoices()", "nil elems"); }
  if(size < 1) { printError("printChoices()", "invalid size"); }

  int i;
  for(i = 0; i < size; i++) { fprintf(stdout, "\t%i)\t%s\n", i, elems[i]);  }
  fprintf(stdout, "\n");
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
      if(c == 'n') { break; }
    }
  }
}

// attempt to retrieve and type check a setting from the conf file
void getConfSetting(ini_t *ini, char *section, char *key, typeINI_t typeINI, setting_t **setting) {
  char buffer[35+strlen(section)+strlen(key)];
  if((errINI = lookupSetting(ini, section, key, setting)) != INI_NIL) {
    sprintf(buffer, "lookupSetting(), section=%s, key=%s", section, key);
    printError(buffer, (char *)strErrINI(errINI));
  }

  if(!setting) {
    sprintf(buffer, "getConfSetting(), section=%s, key=%s", section, key);
    printError(buffer, "setting not present in conf");
  }
  
  typeINI_t tmpType;
  if((errINI = settingType(*setting, &tmpType)) != INI_NIL) {
    sprintf(buffer, "settingType(), section=%s, key=%s", section, key);
    printError(buffer, (char *)strErrINI(errINI));
  }

  if(typeINI != tmpType) {
    sprintf(buffer, "getConfSetting(), section=%s, key=%s", section, key);
    printError(buffer, "unexpected type");
  }
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

  int log;
  getConfSetting(ini, "Logging", "log", BOOL, &setting);
  if((errINI = settingGetBool(setting, &log)) != INI_NIL) {
    printError("settingGetBool(), section=Logging, key=log", (char *)strErrINI(errINI));
  }

  if(!log) {
    *logger = NULL;
    return;
  }

  getConfSetting(ini, "Logging", "dir", STRING, &setting);
  if((errINI = settingLength(setting, &log)) != INI_NIL) {
    printError("settingLength(), section=Logging, key=dir", (char *)strErrINI(errINI));
  }

  char dir[log];
  if((errINI = settingGetString(setting, dir)) != INI_NIL) {
    printError("settingGetString(), section=Logging, key=dir", (char *)strErrINI(errINI));
  }

  getConfSetting(ini, "Logging", "columns", INT, &setting);
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

  int traits;
  getConfSetting(ini, "Chromosomes", "traits", INT, &setting);
  if((errINI = settingGetInt(setting, &traits)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=traits", (char *)strErrINI(errINI));
  }

  int elitism;
  getConfSetting(ini, "Chromosomes", "elitism", BOOL, &setting);
  if((errINI = settingGetBool(setting, &elitism)) != INI_NIL) {
    printError("settingGetBool(), section=Chromosomes, key=elitism", (char *)strErrINI(errINI));
  }

  float percentile;
  getConfSetting(ini, "Chromosomes", "percentile", FLOAT, &setting);
  if((errINI = settingGetFloat(setting, &percentile)) != INI_NIL) {
    printError("settingGetFloat(), section=Chromosomes, key=percentile", (char *)strErrINI(errINI));
  }

  float rate;
  getConfSetting(ini, "Chromosomes", "mutation", FLOAT, &setting);
  if((errINI = settingGetFloat(setting, &rate)) != INI_NIL) {
    printError("settingGetFloat(), section=Chromosomes, key=mutation", (char *)strErrINI(errINI));
  }

  int ubound;
  getConfSetting(ini, "Chromosomes", "ubound", INT, &setting);
  if((errINI = settingGetInt(setting, &ubound)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=ubound", (char *)strErrINI(errINI));
  }

  int lbound;
  getConfSetting(ini, "Chromosomes", "lbound", INT, &setting);
  if((errINI = settingGetInt(setting, &lbound)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=lbound", (char *)strErrINI(errINI));
  }

  int cps;
  getConfSetting(ini, "Chromosomes", "cps", STRING_ARRAY, &setting);
  if((errINI = settingLength(setting, &cps)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=cps", (char *)strErrINI(errINI));
  }

  char *ids[cps];
  
  int i, j;
  for(i = 0; i < cps; i++) {
    if((errINI = settingElemLength(setting, i, &j)) != INI_NIL) {
      printError("settingElemLength(), section=Chromosomes, key=cps", (char *)strErrINI(errINI));
    }

    char *cp = calloc(j+1, sizeof(char));
    if((errINI = settingGetStringElem(setting, i, cp)) != INI_NIL) {
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
    getConfSetting(ini, "Chromosomes", ids[i], INT_ARRAY, &setting);
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
    free(ids[i]);
  }
}

// output changes in ai dna to ini configuration
void outputNewDNAtoINI(dna_t *dna, ini_t *ini) {
  int strands, traits, i;
  setting_t *setting;

  if((errDNA = getChromosomes(dna, &strands, &traits)) != DNA_NIL) {
    printError("getChromosomes()", (char *)strErrDNA(errDNA));
  }

  char ids[strands][36]; // TODO: update
  if((errDNA = getIDs(dna, (char **)ids)) != DNA_NIL) {
    printError("getIDs()", (char *)strErrDNA(errDNA));
  }

  int strand[traits];
  for(; strands; strands--) {
    errDNA = getStrand(dna, ids[strands-1], strand, &traits);
    if(errDNA != DNA_NIL) {
      printError("getStrands()", (char *)strErrDNA(errDNA));
    }

    getConfSetting(ini, "Chromosomes", ids[strands-1], INT_ARRAY, &setting);
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
}

// attempt to log the dna information
void logDNA(dna_t *dna, log_t *logger) {
  int i, j, chromosomes, traits;
  float r;

  if((errLOG = logHeader(logger, "DNA")) != LOG_NIL) {
    printError("logHeader(), header=DNA", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logSection(logger, "Settings")) != LOG_NIL) {
    printError("logSection(), section=Settings", (char *)strErrLOG(errLOG));  
  }

  if((errDNA = getMutation(dna, &i, &j, &r)) != DNA_NIL) {
    printError("getMutation()", (char *)strErrDNA(errDNA));
  }

  if((errLOG = logFloatSetting(logger, "Mutation Rate", r)) != LOG_NIL) {
    printError("logFloatSetting(), key=Mutation Rate", (char *)strErrLOG(errLOG));
  }
  
  if((errLOG = logIntSetting(logger, "Lower Bound", i)) != LOG_NIL) {
    printError("logIntSetting(), key=Lower Bound", (char *)strErrLOG(errLOG));
  }
  
  if((errLOG = logIntSetting(logger, "Upper Bound", j)) != LOG_NIL) {
    printError("logIntSetting(), key=Upper Bound", (char *)strErrLOG(errLOG));
  }

  if((errDNA = getElitism(dna, &i, &r)) != DNA_NIL) {
    printError("getElitism()", (char *)strErrDNA(errDNA));
  }
  
  if((errLOG = logIntSetting(logger, "Elitism", i)) != LOG_NIL) {
    printError("logIntSetting(), key=Elitism", (char *)strErrLOG(errLOG));
  }
  
  if((errLOG = logFloatSetting(logger, "Percentile", r)) != LOG_NIL) {
    printError("logFloatSetting(), key=Percentile", (char *)strErrLOG(errLOG));
  }
  
  if((errDNA = getChromosomes(dna, &chromosomes, &traits)) != DNA_NIL) {
    printError("getChromosomes()", (char *)strErrDNA(errDNA));
  }

  char *ids[chromosomes];
  for(i = 0; i < chromosomes; i++) { ids[i] = calloc(255, sizeof(char)); }
  
  if((errDNA = getIDs(dna, ids)) != DNA_NIL) {
    printError("getIDs()", (char *)strErrDNA(errDNA));
  }

  if((errLOG = logEvent(logger, 0, "")) != LOG_NIL) { // for the newline
    printError("logEvent()", (char *)strErrLOG(errLOG));
  }

  if((errLOG = logSection(logger, "Chromosomes")) != LOG_NIL) {
    printError("logSection(), section=Chromosomes", (char *)strErrLOG(errLOG));
  }
  
  int strand[traits];
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
    free(ids[chromosomes-1]);
  }
}

// attempt to set up the risk game from the INI conf file.
void setupRISKfromINI(ini_t *ini, risk_t **game) {
  if((errRISK = makeRISK(game)) != RISK_NIL) {
    printError("makeRISK()", (char *)strErrRISK(errRISK));
  }

  int i, j, k, n;
  setting_t *setting;

  // TROOP SETTINGS
  getConfSetting(ini, "Troops", "beginning", INT, &setting);
  if((errINI = settingGetInt(setting, &i)) != INI_NIL) {
    printError("settingGetInt(), section=Troops, key=beginning", (char *)strErrINI(errINI));
  }

  if((errINI = setStartingTroopCount(*game, i)) != INI_NIL) {
    printError("setStartingTroopCount()", (char *)strErrINI(errINI));
  }

  getConfSetting(ini, "Troops", "minimum", INT, &setting);
  if((errINI = settingGetInt(setting, &i)) != INI_NIL) {
    printError("settingGetInt(), section=Troops, key=minimum", (char *)strErrINI(errINI));
  }

  if((errINI = setMinimumTroopHandout(*game, i)) != INI_NIL) {
    printError("setMinimumTroopHandout()", (char *)strErrINI(errINI));
  }

  getConfSetting(ini, "Troops", "bonus", INT, &setting);
  if((errINI = settingGetInt(setting, &i)) != INI_NIL) {
    printError("settingGetInt(), section=Troops, key=bonus", (char *)strErrINI(errINI));
  }

  if((errINI = setTroopTerritoryBonus(*game, i)) != INI_NIL) {
    printError("setTroopTerritoryBonus()", (char *)strErrINI(errINI));
  }

  getConfSetting(ini, "Troops", "random", BOOL, &setting);
  if((errINI = settingGetBool(setting, &i)) != INI_NIL) {
    printError("settingGetBool(), section=Troops, key=random", (char *)strErrINI(errINI));
  }

  if((errINI = setRandomTroops(*game, i)) != INI_NIL) {
    printError("setRandomTroops()", (char *)strErrINI(errINI));
  }

  // CARD SETTINGS
  getConfSetting(ini, "Cards", "types", STRING_ARRAY, &setting);
  if((errINI = settingLength(setting, &i)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *types[i];
  for(j = 0; j < i; j++) {
    if((errINI = settingElemLength(setting, j, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(types[j] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Cards , key=??", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, j, types[j])) != INI_NIL) {
      printError("settingGetStringElem(), section=Cards, key=??", (char *)strErrINI(errINI));
    }
  }

  if((errINI = setDeckTypes(*game, i, types)) != INI_NIL) {
    printError("setDeckTypes()", (char *)strErrINI(errINI));
  }

  for(; i; i--) { free(types[i-1]); }

  getConfSetting(ini, "Cards", "wilds", INT, &setting);
  if((errINI = settingGetInt(setting, &i)) != INI_NIL) {
    printError("settingGetInt(), section=Cards, key=wilds", (char *)strErrINI(errINI));
  }

  if((errINI = setDeckWilds(*game, i)) != INI_NIL) {
    printError("setDeckWilds()", (char *)strErrINI(errINI));
  }

  getConfSetting(ini, "Cards", "trades", INT_ARRAY, &setting);
  if((errINI = settingLength(setting, &i)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  int trades[i];
  for(j = 0; j < i; j++) {
    if((errINI = settingGetIntElem(setting, j, &trades[j])) != INI_NIL) {
      printError("settingGetIntElem(), section=Cards, key=trades", (char *)strErrINI(errINI));
    }
  }

  if((errINI = setTradeRewards(*game, i, trades)) != INI_NIL) {
    printError("setTradeRewards()", (char *)strErrINI(errINI));
  }
  
  getConfSetting(ini, "Cards", "incr", INT, &setting);
  if((errINI = settingGetInt(setting, &i)) != INI_NIL) {
    printError("settingGetInt(), section=Cards, key=incr", (char *)strErrINI(errINI));
  }

  if((errINI = setTradeIncrReward(*game, i)) != INI_NIL) {
    printError("setTradeIncrReward()", (char *)strErrINI(errINI));
  }

  // MAP SETTINGS
  getConfSetting(ini, "Map", "continents", STRING_ARRAY, &setting);
  if((errINI = settingLength(setting, &i)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *continents[i];
  for(j = 0; j < i; j++) {
    if((errINI = settingElemLength(setting, j, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(continents[j] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Map, key=continents", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, j, continents[j])) != INI_NIL) {
      printError("settingGetIntElem(), section=Map, key=continents", (char *)strErrINI(errINI));
    }
  }

  if((errINI = setContinents(*game, i, continents)) != INI_NIL) {
    printError("setContinents()", (char *)strErrINI(errINI));
  }

  for(; i; i--) { free(continents[i-1]); }

  getConfSetting(ini, "Map", "continents_bonus", INT_ARRAY, &setting);
  if((errINI = settingLength(setting, &i)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  int continents_bonus[i];
  for(j = 0; j < i; j++) {
    if((errINI = settingGetIntElem(setting, j, &continents_bonus[j])) != INI_NIL) {
      printError("settingGetIntElem(), section=Map, key=continents_bonus", (char *)strErrINI(errINI));
    }
  }

  if((errINI = setContinentBonuses(*game, i, continents_bonus)) != INI_NIL) {
    printError("setContinentBonuses()", (char *)strErrINI(errINI));
  }

  getConfSetting(ini, "Map", "random", BOOL, &setting);
  if((errINI = settingGetBool(setting, &i)) != INI_NIL) {
    printError("settingGetBool(), section=Map, key=random", (char *)strErrINI(errINI));
  }

  if((errINI = setRandomCountries(*game, i)) != INI_NIL) {
    printError("setRandomCountries()", (char *)strErrINI(errINI));
  }

  getConfSetting(ini, "Map", "countries", STRING_ARRAY, &setting);
  if((errINI = settingLength(setting, &i)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *countries[i];
  for(j = 0; j < i; j++) {
    if((errINI = settingElemLength(setting, j, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(countries[j] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Map, key=countries", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, j, countries[j])) != INI_NIL) {
      printError("settingGetIntElem(), section=Map, key=countries", (char *)strErrINI(errINI));
    }
  }

  if((errINI = setCountries(*game, i, countries)) != INI_NIL) {
    printError("setCountries()", (char *)strErrINI(errINI));
  }

  /* TODO: setup country adjacencies and country<-continent assignement 
  for(j = 0; j < i; j++) {
    getConfSetting(ini, "Map", countries[j], STRING_ARRAY, &setting);
    if((errINI = settingLength(setting, &n)) != INI_NIL) {
      printError("settingLength()", (char *)strErrINI(errINI));  
    }

    char *adjacencies[n];
    int l;
    for(k = 0; k < n; k++) {
      if((errINI = settingElemLength(setting, k, &l)) != INI_NIL) {
        printError("settingElemLength()", (char *)strErrINI(errINI));  
      }

      if(!(adjacencies[k] = calloc(l+1, sizeof(char)))) {
        printError("setupRISKfromINI(), section=Map, key=??", "failed to allocate copy");
      }

      if((errINI = settingGetStringElem(setting, k, adjacencies[k])) != INI_NIL) {
        printError("settingGetIntElem(), section=Map, key=??", (char *)strErrINI(errINI));
      }
    }

    // setBorders()
    for(; i; i--) { free(adjacencies[i-1]); }

    free(countries[i]);
  }
  */

  // PLAYERS
  getConfSetting(ini, "Players", "humans", STRING_ARRAY, &setting);
  if((errINI = settingLength(setting, &i)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *humans[i];
  for(j = 0; j < i; j++) {
    if((errINI = settingElemLength(setting, j, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(humans[j] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Players, key=humans", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, j, humans[j])) != INI_NIL) {
      printError("settingGetStringElem(), section=Players, key=humans", (char *)strErrINI(errINI));
    }
  }

  getConfSetting(ini, "Players", "computers", STRING_ARRAY, &setting);
  if((errINI = settingLength(setting, &n)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *computers[n];
  for(j = 0; j < n; j++) {
    if((errINI = settingElemLength(setting, j, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(computers[j] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Players, key=computers", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, j, computers[j])) != INI_NIL) {
      printError("settingGetStringElem(), section=Players, key=computers", (char *)strErrINI(errINI));
    }
  }

  char *players[i+n];
  for(j = 0; j < i; j++) { players[j] = humans[j]; }
  for(j = 0; j < n; j++) { players[i+j] = computers[j]; }

  if((errRISK = setPlayers(*game, i+n, players)) != RISK_NIL) {
    printError("setPlayers()", (char *)strErrRISK(errRISK));
  }

  for(i = i+n; 1; i--) { free(players[i-1]); }
}

// log the game setup
void logRISK(risk_t *game, log_t *logger) {
  if((errLOG = logHeader(logger, "S E T T I N G S")) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  // PLAYERS
  if((errLOG = logSection(logger, "PLAYERS")) != LOG_NIL) {
    printError("logSection(), header=PLAYERS", (char *)strErrLOG(errLOG));  
  }

  int i, j, k;
  if((errRISK = getLengthPlayers(game, &i)) != RISK_NIL) {
      printError("getLengthPlayers()", (char *)strErrRISK(errRISK));  
  }

  char *players[i];
  for(j = 0; j < i; j++) {
    if((errRISK = getLengthPlayersElem(game, j, &k)) != RISK_NIL) {
        printError("getLengthPlayersElem()", (char *)strErrRISK(errRISK));  
    }

    if(!(players[j] = calloc(k, sizeof(char)))) {
        printError("logRISK()", "out of memory");
    }

    if((errRISK = getPlayer(game, j, players[j])) != RISK_NIL) {
        printError("getPlayer()", (char *)strErrRISK(errRISK));  
    }
  }

  if((errLOG = logStrArr(logger, players, i)) != LOG_NIL) {
    printError("logStrArr()", (char *)strErrLOG(errLOG));   
  }

  for(; i; i--) { free(players[i-1]); }

  // TROOPS
  if((errLOG = logSection(logger, "TROOPS")) != LOG_NIL) {
    printError("logSection(), section=TROOPS", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getStartingTroopCount(game, &i)) != RISK_NIL) {
    printError("getStartingTroopCount()", (char *)strErrRISK(errRISK));
  }

  if((errLOG = logIntSetting(logger, "Beginning count", i)) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getMinimumTroopHandout(game, &i)) != RISK_NIL) {
    printError("getMinimumTroopHandout()", (char *)strErrRISK(errRISK));
  }

  if((errLOG = logIntSetting(logger, "Minimum/turn", i)) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getTroopTerritoryBonus(game, &i)) != RISK_NIL) {
    printError("getTroopTerritoryBonus()", (char *)strErrRISK(errRISK));
  }

  if((errLOG = logIntSetting(logger, "Extra troop/#countries", i)) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getRandomTroops(game, &i)) != RISK_NIL) {
    printError("getRandomTroops()", (char *)strErrRISK(errRISK));
  }

  if((errLOG = logBoolSetting(logger, "Randomly distribute at game start", i)) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  // CARDS
  if((errLOG = logSection(logger, "CARDS")) != LOG_NIL) {
    printError("logSection(), section=CARDS", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getDeckWilds(game, &i)) != RISK_NIL) {
    printError("getDeckWilds()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logIntSetting(logger, "Wilds", i)) != LOG_NIL) {
    printError("logIntSetting(), setting=Wilds", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getLengthDeckTypes(game, &i)) != RISK_NIL) {
    printError("getLengthDeckTypes()", (char *)strErrRISK(errRISK));  
  }

  char *types[i];
  for(j = 0; j < i; j++) {
    if((errRISK = getLengthDeckTypesElem(game, j, &k)) != RISK_NIL) {
      printError("getLengthDeckTypesElem()", (char *)strErrRISK(errRISK));  
    }

    if(!(types[j] = calloc(k, sizeof(char)))) {
        printError("logRISK()", "out of memory");
    }

    if((errRISK = getDeckTypesElem(game, j, types[j])) != RISK_NIL) {
      printError("getDeckTypesElem()", (char *)strErrRISK(errRISK));  
    }
  }

  if((errLOG = logStrArr(logger, types, i)) != LOG_NIL) {
    printError("logStrArray()", (char *)strErrLOG(errLOG));  
  }

  for(; i; i--) { free(types[i-1]); }

  if((errRISK = getLengthTradeRewards(game, &i)) != RISK_NIL) {
    printError("getLengthTradeRewards()", (char *)strErrRISK(errRISK));  
  }

  int rewards[i];
  if((errRISK = getTradeRewards(game, i, rewards)) != RISK_NIL) {
    printError("getTradeRewards()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logIntArr(logger, rewards, i)) != LOG_NIL) {
    printError("logIntArr()", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getTradeIncrReward(game, &i)) != RISK_NIL) {
    printError("getTradeIncrReward()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logIntSetting(logger, "Trade increment", i)) != LOG_NIL) {
    printError("logIntSetting(), setting=Trade increment", (char *)strErrLOG(errLOG));  
  }

  // MAP
  if((errLOG = logSection(logger, "MAP")) != LOG_NIL) {
    printError("logSection(), section=MAP", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getLengthContinents(game, &i)) != RISK_NIL) {
    printError("getLengthContinents()", (char *)strErrRISK(errRISK));  
  }

  char *continents[i];
  for(j = 0; j < i; j++) {
    if((errRISK = getLengthContinentsElem(game, j, &k)) != RISK_NIL) {
      printError("getLengthContinentsElem()", (char *)strErrRISK(errRISK));  
    }

    if(!(types[j] = calloc(k, sizeof(char)))) {
        printError("logRISK()", "out of memory");
    }

    if((errRISK = getContinentElem(game, j, types[j])) != RISK_NIL) {
      printError("getContinentElem()", (char *)strErrRISK(errRISK));  
    }
  }

  if((errLOG = logStrArr(logger, continents, i)) != LOG_NIL) {
    printError("logStrArr()", (char *)strErrLOG(errLOG));  
  }

  for(; i; i--) { free(continents[i-1]); }

  if((errRISK = getLengthContinentBonuses(game, &i)) != RISK_NIL) {
    printError("getLengthContinents()", (char *)strErrRISK(errRISK));  
  }

  int bonuses[i];

  if((errRISK = getContinentBonuses(game, i, bonuses)) != RISK_NIL) {
    printError("getContinentBonuses()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logIntArr(logger, bonuses, i)) != LOG_NIL) {
    printError("logIntArr()", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getLengthCountries(game, &i)) != RISK_NIL) {
    printError("getLengthCountries()", (char *)strErrRISK(errRISK));  
  }

  char *countries[i];
  for(j = 0; j < i; j++) {
    if((errRISK = getLengthCountriesElem(game, j, &k)) != RISK_NIL) {
      printError("getLengthCountriesElem()", (char *)strErrRISK(errRISK));  
    }

    if(!(countries[j] = calloc(k, sizeof(char)))) {
        printError("logRISK()", "out of memory");
    }

    if((errRISK = getCountryElem(game, j, countries[j])) != RISK_NIL) {
      printError("getCountryElem()", (char *)strErrRISK(errRISK));  
    }
  }

  if((errLOG = logStrArr(logger, countries, i)) != LOG_NIL) {
    printError("logStrArr()", (char *)strErrLOG(errLOG));  
  }

  for(; i; i--) { free(countries[i-1]); }

  if((errRISK = getRandomCountries(game, &i)) != RISK_NIL) {
    printError("getRandomCountries()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logBoolSetting(logger, "Randomly distribute at game start", i)) != LOG_NIL) {
    printError("logIntSetting(), setting=", (char *)strErrLOG(errLOG));  
  }

// TODO: Adjacency Matrix + country/continent relationship
}

// log game statistics.
void logGameStats(log_t *logger, int seconds) {
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  char val[40];
  sprintf(val, "[%ih-%im-%is]", hours, minutes, seconds);

  if((errLOG = logHeader(logger, "Gameplay Statistics")) != LOG_NIL) {
    printError("logHeader(), header=Gameplay Statistics", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logStrSetting(logger, "Elapsed game time", val)) != LOG_NIL) {
    printError("logHeader(), key=Elapsed game time", (char *)strErrLOG(errLOG));  
  }
  // TODO: expand information logged
  // - time each player took
  // - list players places (reverse order or losers)
  // - min/max # countries a player held
  // - min/max # armies a player held
  // - who got what bonuses, and how many times
  // -   etc...
}

void printCardsInfo(risk_t *game) { // TODO
  if(!game) { printError("printCardsInfo()", "nil game parameter"); }

  /*
    |***********************|
    | card | country | type |
    |-----------------------|
    | 0    |                |
    |-----------------------|
    | 1    |                |
    |-----------------------|
    | ...  |                |
    |-----------------------|
    | n-1  |  ---    | wild |
    |-----------------------|
    | n    |                |
    |-----------------------|
    |_______________________|
  */

  printError("printCardsInfo()", "NOT IMPLEMENTED");
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

  for(;;) {
    fprintf(stdout, "%s's turn...\n", player);
    printChoices(mainMenu, mainChoices);
    readInt(0, mainChoices-1, &choice, prompt);
    switch(choice) {
      case 0: // TRADE
        fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
        // get which cards getCards(player, *arr, *size); through menu choices??
        // place troops
        //    -- enfore trade rules, timeing(1/turn and beginning?) -> plus if
        //    take over a person and have to enforece card trades and palcements
        break;
      case 1: // ATTACK
        fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
        // src, dest (adjacency), how many (attacker [1-3] AND defender [1-2])
        //  - draw card (if win), kill ememy (get card/enfore trade) but only ONCE/turn
        break;
      case 2: // MANEUVER
        fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
        // get src
        // get dest
        // how many -- API does all error handling?? 
        return;
      case 3: // QUERY
        printChoices(queryMenu, queryChoices);
        readInt(0, queryChoices-1, &choice, prompt);
        switch(choice) {
          case 0: // PLAYERS
            fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
            //printPlayerInfo();
            // list players
            // get input
            // list countries owned w/ troop count, continent bonuses held,
            // #cards
            break;
          case 1: // COUNTRIES
            fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
            //printCountryInfo();
            // list countries
            // get input
            // list owner, armies, continent, adjacnecies
            break;
          case 2: // CONTINENTS
            fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
            //printContinentInfo(game, continent);
            // list continents 
            // get input
            // list bonus, bonus holder, total armies?, countries contained
            // (+army count?) and list % ownerships of continent?? 
            // can only do last one if tablularize like the rest. no one
            // specific continent can be queried??
            break;
          case 3: // CARDS
            printCardsInfo(game);
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

void createNextGeneration(dna_t *dna, log_t *logger) {
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

// play the game, taking care to reset between games if training
void risky(risk_t *game, dna_t *dna, int games) {
  if(games > 0) {
    fprintf(stdout, "training sessions requested: %d\ntraining...\n", games);
  }

  int gameTimeSecs;
  time_t _start;

  do {
    SESSION = games; // TODO: better mech for passing log name down
    setupLOGfromINI(ini, &logger); // new logger each game
    if(logger) {
      logRISK(game, logger);
      logDNA(dna, logger);
    }

    if(games > 0) { fprintf(stdout, "games left: %i\n", games); }

    if((errRISK = start(game)) != RISK_NIL) {
      printError("start()", (char *)strErrRISK(errRISK));
    }

    //char *player = NULL;
    if(logger) { logHeader(logger, "G A M E P L A Y"); }
    char tmp[] = "starting game...\n";
    logEvent(logger, 1, tmp);
    _start = time(NULL);

    // sleep(1) hack
    //while(difftime(time(NULL), start) < 1.0);
    //while(1) { // getPlayers(game) > 1) { // TODO: implementeing human/cp turns
      //player = getNextPlayer(game);
      //if(logger) { logEvent(logger, 1, "%s's turn...\n\n"); }
      //fprintf(stdout, "%s's turn...\n\n", player);
      //if(!getType(game, dna, player)) { computerTurn(game, dna, player, logger); }
      //else { humanTurn(game, player, logger); }
    //}
    //if(game->log) { fprintf(game->fp, "congratuations %s, you've achieved world domination!\n", player); }

    char tmp2[] = "ending game...\n";
    if((errLOG = logEvent(logger, 1, tmp2)) != LOG_NIL) {
      printError("logEvent()", (char *)strErrLOG(errLOG));
    }

    if((errRISK = end(game)) != RISK_NIL) {
      printError("end()", (char *)strErrRISK(errRISK));
    }

    gameTimeSecs = (int)difftime(time(NULL), _start);

    if(games) { createNextGeneration(dna, logger); }

    if(logger) {
      logGameStats(logger, gameTimeSecs);
      freeLOG(logger);
      logger = NULL;
    }
  } while(--games > 0);
}

void getTrainingSessions(ini_t *ini, int *sessions) {
  setting_t *setting;
  getConfSetting(ini, "Training", "games", INT, &setting);
  if((errINI = settingGetInt(setting, sessions)) != INI_NIL) {
    printError("settingGetInt(), section=Training, key=games", (char *)strErrINI(errINI));
  }
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

  getTrainingSessions(ini, &argc);

  setupDNAfromINI(ini, &dna);
  setupRISKfromINI(ini, &game);
/*
  if((errRISK = isValid(game)) != RISK_NIL) {
    printError("isValid()", (char *)strErrRISK(errRISK));
  }
*/
  srand(time(NULL)); // seed random for risk and dna libs

//  risky(game, dna, argc); // play

  if(argc > 1) { // replace all chromosomes in conf if there was any training
    outputNewDNAtoINI(dna, ini);
    if((errINI = writeINI(ini, argv[1])) != INI_NIL) {
      printError("writeINI()", (char *)strErrINI(errINI));
    }
  }

  exit(EXIT_SUCCESS);
}
