/******************************************************************************
 * FILE:    main.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  7/14/17                                                           *
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
  typeINI_t typeINI;
 
  if((errINI = lookupSetting(ini, "Logging", "log", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Logging, key=log", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupLOGfromINI(), section=Logging, key=log", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Logging, key=log", (char *)strErrINI(errINI));
  }

  if(typeINI != BOOL) {
    printError("setupLOGfromINI()", "INI setting section=Logging, key=log must be of type bool");
  }

  int log;
  if((errINI = settingGetBool(setting, &log)) != INI_NIL) {
    printError("settingGetBool(), section=Logging, key=log", (char *)strErrINI(errINI));
  }

  if(!log) {
    *logger = NULL;
    return;
  }

  if((errINI = lookupSetting(ini, "Logging", "dir", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Logging, key=dir", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupLOGfromINI(), section=Logging, key=dir", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Logging, key=dir", (char *)strErrINI(errINI));
  }

  if(typeINI != STRING) {
    printError("setupLOGfromINI()", "INI setting section=Logging, key=dir must be of type string");
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

  if(!setting) {
    printError("setupLOGfromINI(), section=Logging, key=columns", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Logging, key=columns", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupLOGfromINI()", "INI setting section=Logging, key=columns must be of type int");
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
  typeINI_t typeINI;

  if((errINI = lookupSetting(ini, "Chromosomes", "traits", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=traits", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Chromosomes, key=traits", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Chromosomes, key=traits", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=traits must be of type int");
  }

  int traits;
  if((errINI = settingGetInt(setting, &traits)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=traits", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "elitism", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=elitism", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Chromosomes, key=elitism", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Chromosomes, key=elitism", (char *)strErrINI(errINI));
  }

  if(typeINI != BOOL) {
    printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=elitism must be of type bool");
  }

  int elitism;
  if((errINI = settingGetBool(setting, &elitism)) != INI_NIL) {
    printError("settingGetBool(), section=Chromosomes, key=elitism", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "percentile", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=percentile", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Chromosomes, key=percentile", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Chromosomes, key=percentile", (char *)strErrINI(errINI));
  }

  if(typeINI != FLOAT) {
    printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=percentile must be of type float");
  }

  float percentile;
  if((errINI = settingGetFloat(setting, &percentile)) != INI_NIL) {
    printError("settingGetFloat(), section=Chromosomes, key=percentile", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "mutation", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=mutation", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Chromosomes, key=mutation", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Chromosomes, key=mutation", (char *)strErrINI(errINI));
  }

  if(typeINI != FLOAT) {
    printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=mutation must be of type float");
  }

  float rate;
  if((errINI = settingGetFloat(setting, &rate)) != INI_NIL) {
    printError("settingGetFloat(), section=Chromosomes, key=mutation", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "ubound", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=ubound", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Chromosomes, key=ubound", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Chromosomes, key=ubound", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=ubound must be of type int");
  }

  int ubound;
  if((errINI = settingGetInt(setting, &ubound)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=ubound", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "lbound", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=lbound", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Chromosomes, key=lbound", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Chromosomes, key=lbound", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=lbound must be of type int");
  }

  int lbound;
  if((errINI = settingGetInt(setting, &lbound)) != INI_NIL) {
    printError("settingGetInt(), section=Chromosomes, key=lbound", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Chromosomes", "cps", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Chromosomes, key=cps", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Chromosomes, key=cps", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Chromosomes, key=cps", (char *)strErrINI(errINI));
  }

  if(typeINI != STRING_ARRAY) {
    printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=cps must be of type string array");
  }

  int cps;
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
    if((errINI = lookupSetting(ini, "Chromosomes", ids[i], &setting)) != INI_NIL) {
      printError("lookupSetting(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
    }

    if(!setting) {
      printError("setupDNAfromINI(), section=Chromosomes, key=??", "setting not present in conf");
    }

    if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
      printError("settingType(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
    }

    if(typeINI != INT_ARRAY) {
      printError("setupDNAfromINI()", "INI setting section=Chromosomes, key=?? must be of type int array");
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
    free(ids[i]);
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

  setting_t *setting;
  typeINI_t typeINI;

  // TROOP SETTINGS
  if((errINI = lookupSetting(ini, "Troops", "beginning", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Troops, key=beginning", (char *)strErrINI(errINI));
  }
    
  if(!setting) {
    printError("setupRISKfromINI(), section=Troops , key=beginning", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Troops, key=beginning", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupRISKfromINI()", "INI setting section=Troops, key=beginning must be of type int");
  }

  int i;
  if((errINI = settingGetInt(setting, &i)) != INI_NIL) {
    printError("settingGetInt(), section=Troops, key=beginning", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Troops", "minimum", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Troops, key=minimum", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Troops , key=minimum", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Troops, key=minimum", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupRISKfromINI()", "INI setting section=Troops, key=minimum must be of type int");
  }

  int j;
  if((errINI = settingGetInt(setting, &j)) != INI_NIL) {
    printError("settingGetInt(), section=Troops, key=minimum", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Troops", "bonus", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Troops, key=bonus", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Troops , key=bonus", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Troops, key=bonus", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupRISKfromINI()", "INI setting section=Troops, key=bonus must be of type int");
  }

  int k;
  if((errINI = settingGetInt(setting, &k)) != INI_NIL) {
    printError("settingGetInt(), section=Troops, key=bonus", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Troops", "random", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Troops, key=random", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Troops , key=random", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Troops, key=random", (char *)strErrINI(errINI));
  }

  if(typeINI != BOOL) {
    printError("setupRISKfromINI()", "INI setting section=Troops, key=random must be of type bool");
  }

  int n;
  if((errINI = settingGetBool(setting, &n)) != INI_NIL) {
    printError("settingGetBool(), section=Troops, key=random", (char *)strErrINI(errINI));
  }

  if((errRISK = setTroops(*game, i, j, k, n)) != RISK_NIL) {
    printError("setTroops()", (char *)strErrRISK(errRISK));
  }

  // CARD SETTINGS
  if((errINI = lookupSetting(ini, "Cards", "types", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Cards, key=types", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Cards, key=types", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Cards, key=types", (char *)strErrINI(errINI));
  }

  if(typeINI != STRING_ARRAY) {
    printError("setupRISKfromINI()", "INI setting section=Cards, key=types must be of type string array");
  }

  if((errINI = settingLength(setting, &j)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *wilds[j];
  for(i = 0; i < j; i++) {
    if((errINI = settingElemLength(setting, i, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(wilds[i] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Cards , key=??", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, i, wilds[i])) != INI_NIL) {
      printError("settingGetStringElem(), section=Cards, key=??", (char *)strErrINI(errINI));
    }
  }

  if((errINI = lookupSetting(ini, "Cards", "wilds", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Cards, key=wilds", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Cards, key=wilds", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Cards, key=wilds", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupRISKfromINI()", "INI setting section=Cards, key=wilds must be of type int");
  }

  if((errINI = settingGetInt(setting, &n)) != INI_NIL) {
    printError("settingGetBool(), section=Cards, key=wilds", (char *)strErrINI(errINI));
  }

  if((errRISK = setDeck(*game, n, wilds, j)) != RISK_NIL) {
    printError("setDeck()", (char *)strErrRISK(errRISK));
  }

  for(i = 0; i < j; i++) { free(wilds[i]); }

  if((errINI = lookupSetting(ini, "Cards", "trades", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Cards, key=trades", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Cards, key=trades", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Cards, key=trades", (char *)strErrINI(errINI));
  }

  if(typeINI != INT_ARRAY) {
    printError("setupRISKfromINI()", "INI setting section=Cards, key=trades must be of type int array");
  }

  if((errINI = settingLength(setting, &n)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  int trades[n];
  for(i = 0; i < n; i++) {
    if((errINI = settingGetIntElem(setting, i, &trades[i])) != INI_NIL) {
      printError("settingGetIntElem(), section=Cards, key=trades", (char *)strErrINI(errINI));
    }
  }
  
  if((errINI = lookupSetting(ini, "Cards", "incr", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Cards, key=incr", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Cards, key=incr", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Cards, key=incr", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("setupRISKfromINI()", "INI setting section=Cards, key=incr must be of type int");
  }

  if((errINI = settingGetInt(setting, &k)) != INI_NIL) {
    printError("settingGetBool(), section=Cards, key=incr", (char *)strErrINI(errINI));
  }

  if((errRISK = setTrades(*game, trades, n, k)) != RISK_NIL) {
    printError("setTrades()", (char *)strErrRISK(errRISK));
  }

  // MAP SETTINGS
  if((errINI = lookupSetting(ini, "Map", "continents", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Map, key=continents", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Map, key=continents", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Map, key=continents", (char *)strErrINI(errINI));
  }

  if(typeINI != STRING_ARRAY) {
    printError("setupRISKfromINI()", "INI setting section=Map, key=continents must be of type string array");
  }

  if((errINI = settingLength(setting, &n)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *continents[n];
  for(i = 0; i < n; i++) {
    if((errINI = settingElemLength(setting, i, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(continents[i] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Map, key=continents", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, i, continents[i])) != INI_NIL) {
      printError("settingGetIntElem(), section=Map, key=continents", (char *)strErrINI(errINI));
    }
  }

  if((errRISK = setContinents(*game, continents, n)) != RISK_NIL) {
    printError("setContinents()", (char *)strErrRISK(errRISK));
  }

  for(i = 0; i < n; i++) { free(continents[i]); }

  if((errINI = lookupSetting(ini, "Map", "continents_bonus", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Map, key=continents_bonus", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Map, key=continents_bonus", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Map, key=continents_bonus", (char *)strErrINI(errINI));
  }

  if(typeINI != INT_ARRAY) {
    printError("setupRISKfromINI()", "INI setting section=Map, key=continents_bonus must be of type int array");
  }

  if((errINI = settingLength(setting, &n)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  int continents_bonus[n];
  for(i = 0; i < n; i++) {
    if((errINI = settingGetIntElem(setting, i, &continents_bonus[i])) != INI_NIL) {
      printError("settingGetIntElem(), section=Map, key=continents_bonus", (char *)strErrINI(errINI));
    }
  }
 
  if((errRISK = setContinentBonuses(*game, continents_bonus, n)) != RISK_NIL) {
    printError("setContinentBonuses()", (char *)strErrRISK(errRISK));
  }

  if((errINI = lookupSetting(ini, "Map", "random", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Map, key=random", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupDNAfromINI(), section=Map, key=random", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Map, key=random", (char *)strErrINI(errINI));
  }

  if(typeINI != BOOL) {
    printError("setupDNAfromINI()", "INI setting section=Map, key=random must be of type bool");
  }

  if((errINI = settingGetBool(setting, &k)) != INI_NIL) {
    printError("settingGetBool(), section=Map, key=random", (char *)strErrINI(errINI));
  }

  if((errINI = lookupSetting(ini, "Map", "countries", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Map, key=countries", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Map, key=countries", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Map, key=countries", (char *)strErrINI(errINI));
  }

  if(typeINI != STRING_ARRAY) {
    printError("setupRISKfromINI()", "INI setting section=Map, key=countries must be of type string array");
  }

  if((errINI = settingLength(setting, &n)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *countries[n];
  for(i = 0; i < n; i++) {
    if((errINI = settingElemLength(setting, i, &j)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(countries[i] = calloc(j+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Map, key=countries", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, i, countries[i])) != INI_NIL) {
      printError("settingGetIntElem(), section=Map, key=countries", (char *)strErrINI(errINI));
    }
  }

  if((errRISK = setCountries(*game, countries, n, k)) != RISK_NIL) {
    printError("setCountries()", (char *)strErrRISK(errRISK));
  }

  for(i = 0; i < n; i++) {
    if((errINI = lookupSetting(ini, "Map", countries[i], &setting)) != INI_NIL) {
      printError("lookupSetting(), section=Map, key=??", (char *)strErrINI(errINI));
    }

    if(!setting) {
      printError("setupRISKfromINI(), section=Map, key=??", "setting not present in conf");
    }

    if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
      printError("settingType(), section=Map, key=??", (char *)strErrINI(errINI));
    }

    if(typeINI != STRING_ARRAY) {
      printError("setupRISKfromINI()", "INI setting section=Map, key=?? must be of type string array");
    }

    if((errINI = settingLength(setting, &k)) != INI_NIL) {
      printError("settingLength()", (char *)strErrINI(errINI));  
    }

    char *adjacencies[k];
    int l;
    for(j = 0; j < k; j++) {
      if((errINI = settingElemLength(setting, j, &l)) != INI_NIL) {
        printError("settingElemLength()", (char *)strErrINI(errINI));  
      }

      if(!(adjacencies[j] = calloc(l+1, sizeof(char)))) {
        printError("setupRISKfromINI(), section=Map, key=??", "failed to allocate copy");
      }

      if((errINI = settingGetStringElem(setting, i, adjacencies[i])) != INI_NIL) {
        printError("settingGetIntElem(), section=Map, key=??", (char *)strErrINI(errINI));
      }
    }

    if((errRISK = setAdjacencies(*game, countries[i], adjacencies, k)) != RISK_NIL) {
      printError("setAdjacencies()", (char *)strErrRISK(errRISK));
    }

    for(i = 0; i < k; i++) { free(adjacencies[i]); }

    free(countries[i]);
  }

  // PLAYERS
  if((errINI = lookupSetting(ini, "Players", "humans", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Players, key=humans", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Players, key=humans", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Players, key=humans", (char *)strErrINI(errINI));
  }

  if(typeINI != STRING_ARRAY) {
    printError("setupRISKfromINI()", "INI setting section=Players, key=humans must be of type string array");
  }

  if((errINI = settingLength(setting, &n)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *humans[n];
  for(i = 0; i < n; i++) {
    if((errINI = settingElemLength(setting, i, &j)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(humans[i] = calloc(j+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Players, key=humans", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, i, humans[i])) != INI_NIL) {
      printError("settingGetStringElem(), section=Players, key=humans", (char *)strErrINI(errINI));
    }
  }

  if((errINI = lookupSetting(ini, "Players", "computers", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Players, key=computers", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("setupRISKfromINI(), section=Players, key=computers", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Players, key=computers", (char *)strErrINI(errINI));
  }

  if(typeINI != STRING_ARRAY) {
    printError("setupRISKfromINI()", "INI setting section=Players, key=computers must be of type string array");
  }

  if((errINI = settingLength(setting, &j)) != INI_NIL) {
    printError("settingLength()", (char *)strErrINI(errINI));  
  }

  char *computers[j];
  for(i = 0; i < j; i++) {
    if((errINI = settingElemLength(setting, i, &k)) != INI_NIL) {
      printError("settingElemLength()", (char *)strErrINI(errINI));  
    }

    if(!(computers[i] = calloc(k+1, sizeof(char)))) {
      printError("setupRISKfromINI(), section=Players, key=computers", "failed to allocate copy");
    }

    if((errINI = settingGetStringElem(setting, i, computers[i])) != INI_NIL) {
      printError("settingGetStringElem(), section=Players, key=computers", (char *)strErrINI(errINI));
    }
  }

  char *players[n+j];
  for(i = 0; i < n; i++) { players[i] = humans[i]; }
  for(i = 0; i < j; i++) { players[n+i] = computers[i]; }

  if((errRISK = setPlayers(*game, n+j, players)) != RISK_NIL) {
    printError("setPlayers()", (char *)strErrRISK(errRISK));
  }

  for(i = 0; i < n+j; i++) { free(players[i]); }
}

// log the game setup
void logRISK(risk_t *game, log_t *logger) {
  int i, j, k;
  char **names;
  int *trades;

  if((errLOG = logHeader(logger, "S E T T I N G S")) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  // PLAYERS
  if((errLOG = logSection(logger, "PLAYERS")) != LOG_NIL) {
    printError("logSection(), header=PLAYERS", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getPlayers(game, &names, &i)) != RISK_NIL) {
    printError("getPlayers()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logStrArr(logger, names, i)) != LOG_NIL) {
    printError("logStrArr()", (char *)strErrLOG(errLOG));   
  }

  // TROOPS
  if((errLOG = logSection(logger, "TROOPS")) != LOG_NIL) {
    printError("logSection(), section=TROOPS", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getTroops(game, &i, &j, &k)) != RISK_NIL) {
    printError("getTroops()", (char *)strErrRISK(errRISK));
  }

  if((errLOG = logIntSetting(logger, "Beginning count", i)) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logIntSetting(logger, "Minimum/turn", j)) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logIntSetting(logger, "Extra troop/#countries", k)) != LOG_NIL) {
    printError("logHeader(), header=S E T T I N G S", (char *)strErrLOG(errLOG));  
  }

  // CARDS
  if((errLOG = logSection(logger, "CARDS")) != LOG_NIL) {
    printError("logSection(), section=CARDS", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getDeck(game, &i, &names, &j)) != RISK_NIL) {
    printError("getDeck()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logIntSetting(logger, "Wilds", i)) != LOG_NIL) {
    printError("logIntSetting(), setting=Wilds", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logStrArr(logger, names, i)) != LOG_NIL) {
    printError("logStrArray()", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getTrades(game, &trades, &i, &j)) != RISK_NIL) {
    printError("getTrades()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logIntArr(logger, trades, i)) != LOG_NIL) {
    printError("logIntArr()", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logIntSetting(logger, "Trade increment", j)) != LOG_NIL) {
    printError("logIntSetting(), setting=Trade increment", (char *)strErrLOG(errLOG));  
  }

  // MAP
  if((errLOG = logSection(logger, "MAP")) != LOG_NIL) {
    printError("logSection(), section=MAP", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getContinents(game, &names, &i)) != RISK_NIL) {
    printError("getContinents()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logStrArr(logger, names, i)) != LOG_NIL) {
    printError("logStrArr()", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getCountries(game, &names, &i)) != RISK_NIL) {
    printError("getCountries()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logStrArr(logger, names, i)) != LOG_NIL) {
    printError("logStrArr()", (char *)strErrLOG(errLOG));  
  }

  if((errRISK = getContinentBonuses(game, &trades, &j)) != RISK_NIL) {
    printError("getContinentBonuses()", (char *)strErrRISK(errRISK));  
  }

  if((errLOG = logIntArr(logger, trades, j)) != LOG_NIL) {
    printError("logSection(), section=CARDS", (char *)strErrLOG(errLOG));  
  }

  for(k = 0; k < i; k++) { // FIXME: finish
    //logEvent(logger, "Adjacency Matrix:\n");
    //getNeighbors(game, char *country, char ***neighbors, int *size);
    //logIntArr2D(logger, game->board, game->numCountries, game->numCountries);
  }
}

// log game statistics.
void logGameStats(log_t *logger, int seconds) {
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  char val[40];
  sprintf(val, "[%ih-%im-%is]", hours, minutes, seconds);

  if((errLOG = logHeader(logger, "Total Game Time")) != LOG_NIL) {
    printError("logHeader(), header=Total Game Time", (char *)strErrLOG(errLOG));  
  }

  if((errLOG = logStrSetting(logger, "Elapsed game time", val)) != LOG_NIL) {
    printError("logHeader(), key=Elapsed game time", (char *)strErrLOG(errLOG));  
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
      logRISK(game, logger);
      logDNA(dna, logger);
    }

    if(games > 0) { fprintf(stdout, "sessions left: %i\n", games); }

    // [re]set game
    /*
    if((errRISK = initDeck(game)) != RISK_NIL) {
      printError("initDeck()", (char *)strErrRISK(errRISK));
    }
    if((errRISK = initCountries(game)) != RISK_NIL) {
      printError("initCountries()", (char *)strErrRISK(errRISK));
    }
    if((errRISK = initArmies(game)) != RISK_NIL) {
      printError("initArmies()", (char *)strErrRISK(errRISK));
    }
    */

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
      logGameStats(logger, seconds);
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
  typeINI_t typeINI;

  if((errINI = lookupSetting(ini, "Training", "games", &setting)) != INI_NIL) {
    printError("lookupSetting(), section=Training, key=games", (char *)strErrINI(errINI));
  }

  if(!setting) {
    printError("main(), section=Training, key=games", "setting not present in conf");
  }

  if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
    printError("settingType(), section=Training, key=games", (char *)strErrINI(errINI));
  }

  if(typeINI != INT) {
    printError("main()", "INI setting section=Training, key=games must be of type int");
  }

  if((errINI = settingGetInt(setting, &argc)) != INI_NIL) {
    printError("settingGetInt(), section=Training, key=games", (char *)strErrINI(errINI));
  }

  setupDNAfromINI(ini, &dna);

  setupRISKfromINI(ini, &game);
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

      if(!setting) {
        printError("main(), section=Chromosomes, key=??", "setting not present in conf");
      }

      if((errINI = settingType(setting, &typeINI)) != INI_NIL) {
        printError("settingType(), section=Chromosomes, key=??", (char *)strErrINI(errINI));
      }

      if(typeINI != INT_ARRAY) {
        printError("main()", "INI setting section=Chromosomes, key=?? must be of type int array");
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
