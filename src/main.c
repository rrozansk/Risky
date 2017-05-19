/******************************************************************************
 * FILE:    main.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 4/4/17                                                            *
 * EDITED:  5/13/17                                                           *
 * INFO:    main.c is the glue which holds together the ini, log, dna, and    *
 *          risk libraries.                                                   *
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

errRISK_t errRISK;
errINI_t errINI;
errDNA_t errDNA;
errLOG_t errLOG;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/
void freeStrArr(char **arr, int i) {
  for(; i; i--) { free(arr[i-1]); }
  free(arr);
}

// Read in an integer, only accepting input between the bounds. Optionally prompt
// user 'are you sure'. Handles all errors appropriately.
void readInt(int lbound, int ubound, int *pick, int prompt) {
  if(lbound >= ubound) {
    fprintf(stderr, "internal error!\ninvalid range in readInt()\nexiting...\n");
    exit(EXIT_FAILURE);
  }
  if(!pick) {
    fprintf(stderr, "internal error!\nnil pick in readInt()\nexiting...\n");
    exit(EXIT_FAILURE);
  }
  if(!(prompt == 0 || prompt == 1)) {
    fprintf(stderr, "internal error!\npromt must be 0 or 1 in readInt()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  char c;
  char buffer[80];
  fprintf(stdout, "Enter pick (%i-%i): ", lbound, ubound);
  while(fgets(buffer, 80, stdin)) {
    if(!sscanf(buffer, "%d\n", pick) || *pick < lbound || *pick > ubound) {
      fprintf(stdout, "invalid, input must be a single integer between %i-%i\n", lbound, ubound);
    } else if(prompt) {
      fprintf(stdout, "Entered choice: %i, are you sure (y/n)? ", *pick);
      while(fgets(buffer, 80, stdin)) {
        if(!sscanf(buffer, "%c\n", &c) || !(c == 'y' || c == 'n')) {
          fprintf(stdout, "invalid input, only enter 'y'/'n': ");
        }
        else if(c == 'y') { return; }
        else { break; } // c == 'n'
      }
    } else { return; }
    fprintf(stdout, "Enter pick (%i-%i): ", lbound, ubound);
  }
}

// print an array as an enumerated list
void printChoices(char **elems, int size) {
  if(!elems) {
    fprintf(stderr, "internal error!\nnil elems in printChoices()\nexiting...\n");
    exit(EXIT_FAILURE);
  }
  if(size < 1) {
    fprintf(stderr, "internal error!\ninvalid size in printChoices()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0; i < size; i++) { fprintf(stdout, "\t%i) %s\n", i, elems[i]);  }
  fprintf(stdout, "\n");
}

// TODO: implement. for now just promote higher traits.
int fitness(char *who, int *chromosome, int traits) {
  if(!who || !chromosome || !traits) { return -1; }

  int fitness = 0;
  for(; traits; traits--) {
    switch(traits) {
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
      default:
        fprintf(stderr, "error! unrecognized trait\nexiting...\n");
        exit(EXIT_FAILURE);

    }
  }
  return fitness;
}

// attempt to set up the logger from the INI conf file.
void setupLOGfromINI(ini_t *ini, log_t **logger) {
  int log;
  if((errINI = getBoolINI(ini, "Logging", "log", &log)) != INI_NIL) {
    fprintf(stderr, "error! failure to get log option\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if(!log) {
    *logger = NULL;
    return;
  }

  if((errINI = getIntINI(ini, "Logging", "columns", &log)) != INI_NIL) {
    fprintf(stderr, "error! failure to get log columns\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  char *dir;
  if((errINI = getStrINI(ini, "Logging", "dir", &dir)) != INI_NIL) {
    fprintf(stderr, "error! failure to get log dir\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  time_t t = time(NULL);
  struct tm *date = localtime(&t);
  char name[80];
  strftime(name, 80, "%Y_%B_%d_%A_%X.txt", date); // yr_mo_day_weekday_time

  if((errLOG = makeLOG(logger, log, dir, name)) != LOG_NIL) {
    fprintf(stderr, "error! failure to make log\nirritant: %s\nexiting...\n", strErrLOG(errLOG));
    free(dir);
    exit(EXIT_FAILURE);
  }

  free(dir);
  if((errLOG = logTitle(*logger, name)) != LOG_NIL) {
    fprintf(stderr, "error! failure to log title\nirritant: %s\nexiting...\n", strErrLOG(errLOG));
    exit(EXIT_FAILURE);
  }
}

// attempt to set up all the AI/chromosomes from the INI conf file
void setupDNAfromINI(ini_t *ini, dna_t **dna) {
  int cps, traits, elitism;
  int lbound, ubound, *chromosome;
  char **names;
  double rate, percentile;

  if((errINI = getIntINI(ini, "Chromosomes", "traits", &traits)) != INI_NIL) {
    fprintf(stderr, "error! failure to get chromosome traits\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getBoolINI(ini, "Chromosomes", "elitism", &elitism)) != INI_NIL) {
    fprintf(stderr, "error! failure to get chromosome elitism\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getFloatINI(ini, "Chromosomes", "percentile", &percentile)) != INI_NIL) {
    fprintf(stderr, "error! failure to get chromosome percentile\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getFloatINI(ini, "Chromosomes", "mutation", &rate)) != INI_NIL) {
    fprintf(stderr, "error! failure to get chromosome mutation\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Chromosomes", "ubound", &ubound)) != INI_NIL) {
    fprintf(stderr, "error! failure to get chromosome ubound\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Chromosomes", "lbound", &lbound)) != INI_NIL) {
    fprintf(stderr, "error! failure to get chromosome lbound\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getStrArrINI(ini, "Chromosomes", "cps", &names, &cps)) != INI_NIL) {
    fprintf(stderr, "error! failure to get chromosome cps\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errDNA = makeDNA(dna, cps, traits)) != DNA_NIL) {
    fprintf(stderr, "error! failure to make dna\nirritant: %s\nexiting...\n", strErrDNA(errDNA));
    freeStrArr(names, cps);
    exit(EXIT_FAILURE);
  }

  if((errDNA = setFitness(*dna, fitness)) != DNA_NIL) {
    fprintf(stderr, "error! failure to get chromosome\nirritant: %s\nexiting...\n", strErrDNA(errDNA));
    freeStrArr(names, cps);
    exit(EXIT_FAILURE);
  }

  if((errDNA = setMutation(*dna, lbound, ubound, rate)) != DNA_NIL) {
    fprintf(stderr, "error! failure to get chromosome\nirritant: %s\nexiting...\n", strErrDNA(errDNA));
    freeStrArr(names, cps);
    exit(EXIT_FAILURE);
  }

  if((errDNA = setElitism(*dna, elitism, percentile)) != DNA_NIL) {
    fprintf(stderr, "error! failure to get chromosome\nirritant: %s\nexiting...\n", strErrDNA(errDNA));
    freeStrArr(names, cps);
    exit(EXIT_FAILURE);
  }

  for(; cps; cps--, free(chromosome)) {
    if((errINI = getIntArrINI(ini, "Chromosomes", names[cps-1], &chromosome, &traits)) != INI_NIL) {
      fprintf(stderr, "error! failure to get chromosome %s\nirritant: %s\nexiting...\n", names[cps-1], strErrINI(errINI));
      freeStrArr(names, cps);
      exit(EXIT_FAILURE);
    }
    if((errDNA = setStrand(*dna, names[cps-1], chromosome, traits)) != DNA_NIL) {
      fprintf(stderr, "error! failure to set chromosome %s\nirritant: %s\nexiting...\n", names[cps-1], strErrDNA(errDNA));
      freeStrArr(names, cps);
      free(chromosome);
      exit(EXIT_FAILURE);
    }
  }
  freeStrArr(names, cps);
}

// attempt to set up the risk game from the INI conf file.
void setupRISKfromINI(ini_t *ini, risk_t **game) {
  int i, j, k, n;
  int *iarr;
  char **sarr1, **sarr2, **sarr3;

  if((errRISK = makeRISK(game)) != RISK_NIL) {
    fprintf(stderr, "error! failure to make game\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Troops", "beginning", &i)) != INI_NIL) {
    fprintf(stderr, "error! failure to get troops beginning\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Troops", "minimum", &j)) != INI_NIL) {
    fprintf(stderr, "error! failure to get troops minimumnirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Troops", "bonus", &k)) != INI_NIL) {
    fprintf(stderr, "error! failure to get troops bonus\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getBoolINI(ini, "Troops", "random", &n)) != INI_NIL) {
    fprintf(stderr, "error! failure to get troops random\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errRISK = setTroops(*game, i, j, k, n)) != RISK_NIL) {
    fprintf(stderr, "error! failure to set troops\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    exit(EXIT_FAILURE);
  }

  if((errINI = getStrArrINI(ini, "Players", "humans", &sarr1, &i))!= INI_NIL) {
    fprintf(stderr, "error! failure to get players humans\nnirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getStrArrINI(ini, "Players", "computers", &sarr2, &j)) != INI_NIL) {
    fprintf(stderr, "error! failure to get players computers\nirritant: %s\nexiting...\n", strErrINI(errINI));
    freeStrArr(sarr1, i);
    exit(EXIT_FAILURE);
  }

  if(!(sarr3 = malloc(sizeof(char *) * i+j))) {
    freeStrArr(sarr1, i);
    freeStrArr(sarr2, j);
    fprintf(stderr, "error! out of memory setting up RISK from INI\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  k = 0;
  for(; i; i--) { sarr3[k++] = sarr1[i-1]; }
  for(; j; j--) { sarr3[k++] = sarr2[j-1]; }
  free(sarr1);
  free(sarr2);
  if((errRISK = setPlayers(*game, k, sarr3)) != RISK_NIL) {
    fprintf(stderr, "error! failure to set up players\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    freeStrArr(sarr3, k);
    exit(EXIT_FAILURE);
  }
  freeStrArr(sarr3, k);

  if((errINI = getStrArrINI(ini, "Cards", "types", &sarr2, &i)) != INI_NIL) {
    fprintf(stderr, "error! failure to get cards types\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Cards", "wilds", &j)) != INI_NIL) {
    fprintf(stderr, "error! failure to get cards wilds\nirritant: %s\nexiting...\n", strErrINI(errINI));
    freeStrArr(sarr2, i);
    exit(EXIT_FAILURE);
  }

  if((errRISK = setDeck(*game, i, sarr2, j)) != RISK_NIL) {
    fprintf(stderr, "error! failure to set up deck\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    freeStrArr(sarr2, i);
    exit(EXIT_FAILURE);
  }
  freeStrArr(sarr2, i);

  if((errINI = getIntArrINI(ini, "Cards", "trades", &iarr, &k)) != INI_NIL) {
    fprintf(stderr, "error! failure to get cards trades\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getIntINI(ini, "Cards", "incr", &n)) != INI_NIL) {
    fprintf(stderr, "error! failure to get cards incr\nirritant: %s\nexiting...\n", strErrINI(errINI));
    free(iarr);
    exit(EXIT_FAILURE);
  }

  if((errRISK = setTrades(*game, iarr, k, n)) != RISK_NIL) {
    fprintf(stderr, "error! failure to set up trades\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    free(iarr);
    exit(EXIT_FAILURE);
  }
  free(iarr);

  if((errINI = getStrArrINI(ini, "Map", "continents", &sarr2, &k)) != INI_NIL) {
    fprintf(stderr, "error! failure to get map continents\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }
  if((errRISK = setContinents(*game, sarr2, k)) != RISK_NIL) {
    fprintf(stderr, "error! failure to set continents\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    freeStrArr(sarr2, k);
    exit(EXIT_FAILURE);
  }
  freeStrArr(sarr2, k);

  if((errINI = getIntArrINI(ini, "Map", "continents_bonus", &iarr, &n)) != INI_NIL) {
    fprintf(stderr, "error! failure to get map continents_bonus\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }
  if((errRISK = setContinentBonuses(*game, iarr, n)) != RISK_NIL) {
    fprintf(stderr, "error! ...\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    free(iarr);
    exit(EXIT_FAILURE);
  }
  free(iarr);

  if((errINI = getBoolINI(ini, "Map", "random", &n)) != INI_NIL) {
    fprintf(stderr, "error! failure to get map random\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }

  if((errINI = getStrArrINI(ini, "Map", "countries", &sarr1, &k)) != INI_NIL) {
    fprintf(stderr, "error! failure to get map countries\nirritant: %s\nexiting...\n", strErrINI(errINI));
    exit(EXIT_FAILURE);
  }
  if((errRISK = setCountries(*game, sarr1, k, n)) != RISK_NIL) {
    fprintf(stderr, "error! failure to set countries\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    freeStrArr(sarr1, k);
    exit(EXIT_FAILURE);
  }
  for(i = 0; i < k; i++) {
    if((errINI = getStrArrINI(ini, "Map", sarr1[i], &sarr2, &j)) != INI_NIL) {
      fprintf(stderr, "error! failure to get map adjacencies for %s\nirritant: %s\nexiting...\n", sarr1[i], strErrINI(errINI));
      freeStrArr(sarr1, k);
      exit(EXIT_FAILURE);
    }
    if((errRISK = setAdjacencies(*game, sarr1[i], sarr2, j)) != RISK_NIL) {
      fprintf(stderr, "error! failure to set map adjacencies for %s\nirritant: %s\nexiting...\n", sarr1[i], strErrRISK(errRISK));
      freeStrArr(sarr2, j);
      freeStrArr(sarr1, k);
      exit(EXIT_FAILURE);
    }
    freeStrArr(sarr2, j);
  }
  freeStrArr(sarr1, k);
}

// log the game setup
void logRISK(risk_t *game, log_t *logger) { // TODO: err handling, free, adj mat
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

// log dna
void logDNA(dna_t *dna, log_t *logger) { // TODO: err handling, free
  int i, j;
  double r;
  int *strand;
  char **names;

  logSection(logger, "DNA");

  getMutation(dna, &i, &j, &r);
  logFloatSetting(logger, "Mutation Rate", r);
  logIntSetting(logger, "Lower Bound", i);
  logIntSetting(logger, "Upper Bound", j);

  getElitism(dna, &i, &r);
  logIntSetting(logger, "Elitism", i);
  logFloatSetting(logger, "Percentile", r);

  getNames(dna, &names, &i);
  logHeader(logger, "Chromosomes");
  for(; i; i--) {
    getFitness(dna, names[i-1], &j);
    logIntSetting(logger, names[i-1], j);
    getStrand(dna, names[i-1], &strand, &j);
    logIntArr(logger, strand, j);
  }
}

void logGameTime(log_t *logger, int seconds) {
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;

  char val[40];
  sprintf(val, "[%ih-%im-%is]", hours, minutes, seconds);

  logHeader(logger, "T I M E");
  logStrSetting(logger, "Elapsed game time", val);
}

void printBoard(risk_t *game) { // TODO tabulation board??
  if(!game) {
    fprintf(stderr, "error! nil game in printBoard()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
  exit(EXIT_FAILURE);
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
  if(!game) {
    fprintf(stderr, "error! nil game in computerTurn()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  if(!dna) {
    fprintf(stderr, "error! nil dna in computerTurn()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  if(!player) {
    fprintf(stderr, "error! nil player in computerTurn()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n"); // just skip turn instead??
  exit(EXIT_FAILURE);
}

int getType(risk_t *game, dna_t *dna, char *player) { // TODO
  if(!game) {
    fprintf(stderr, "error! nil game in computerTurn()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  if(!dna) {
    fprintf(stderr, "error! nil dna in computerTurn()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  if(!player) {
    fprintf(stderr, "error! nil player in computerTurn()\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "error! NOT IMPLEMENTED\nexiting...\n");
  exit(EXIT_FAILURE);
}

// play the game, taking care to reset between games if training
void risky(risk_t *game, dna_t *dna, int games) {
  if(games > 0) {
    fprintf(stdout, "training sessions requested: %d\ntraining...\n", games);
  }

  do {
    setupLOGfromINI(ini, &logger);
    if(logger) {
      logRISK(game, logger);
      logDNA(dna, logger);
    }

    if(games > 0) { fprintf(stdout, "sessions left: %i\n", games); }

    // [re]set game
    if((errRISK = initDeck(game)) != RISK_NIL) {
      fprintf(stderr, "error! failure to ini deck\nirritant: %s\nexiting...", strErrRISK(errRISK));
      exit(EXIT_FAILURE);
    }
    if((errRISK = initCountries(game)) != RISK_NIL) {
      fprintf(stderr, "error! failure to ini deck\ncountries: %s\nexiting...", strErrRISK(errRISK));
      exit(EXIT_FAILURE);
    }
    if((errRISK = initArmies(game)) != RISK_NIL) {
      fprintf(stderr, "error! failure to ini deck\narmies: %s\nexiting...", strErrRISK(errRISK));
      exit(EXIT_FAILURE);
    }

    //char *player = NULL;
    if(logger) { logHeader(logger, "G A M E P L A Y"); }
    time_t start = time(NULL);

    // sleep(1) hack
    while(difftime(time(NULL), start) < 1.0);
    //while(1) { // getPlayers(game) > 1) { // TODO: implementeing human/cp turns
      //player = getNextPlayer(game);
      //if(logger) { logEvent(logger, 1, "%s's turn...\n\n"); }
      //fprintf(stdout, "%s's turn...\n\n", player);
      //if(!getType(game, dna, player)) { computerTurn(game, dna, player, logger); }
      //else { humanTurn(game, player, logger); }
    //}
    int seconds = (int)difftime(time(NULL), start);

    if(games) {
      nextGeneration(dna);
      logHeader(logger, "N E W   G E N E R A T I O N");

      char **ids;
      int *strand;
      int i, j, traits;

      if((errDNA = getNames(dna, &ids, &i)) != DNA_NIL) {
        fprintf(stderr, "error! failure to get dna identifiers\nirritant: %s\nexiting...\n", strErrDNA(errDNA));
        exit(EXIT_FAILURE);
      }

      for(j = 0; j < i; j++) {
        if((errDNA = getStrand(dna, ids[j], &strand, &traits)) != DNA_NIL) {
          fprintf(stderr, "error! failure to get dna strand %s\nirritant: %s\nexiting...\n", ids[j], strErrDNA(errDNA));
          freeStrArr(ids, i);
          exit(EXIT_FAILURE);
        }
        if((errLOG = logIntArr(logger, strand, traits)) != LOG_NIL) {
          fprintf(stderr, "error! failure to log strand %s\nirritant: %s\nexiting...\n", ids[j], strErrLOG(errLOG));
          freeStrArr(ids, i);
          free(strand);
          exit(EXIT_FAILURE);
        }
        free(strand);
      }
      freeStrArr(ids, i);
    }

    if(logger) {
      logGameTime(logger, seconds);
      freeLOG(logger);
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

  if(argc != 2) {
    fprintf(stderr, "error! must specify a conf file, exiting...\n");
    exit(EXIT_FAILURE);
  }

  atexit(cleanup); // register cleanup() to be called upon exit()

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

  if((errRISK = isValid(game)) != RISK_NIL) {
    fprintf(stderr, "error! invalid game specified by conf\nirritant: %s\nexiting...\n", strErrRISK(errRISK));
    exit(EXIT_FAILURE);
  }

  srand(time(NULL)); // set random for risk and dna libs
  risky(game, dna, argc);

  if(argc > 1) {
    char **ids;
    int *strand;
    int i, j, traits;

    if((errDNA = getNames(dna, &ids, &i)) != DNA_NIL) {
      fprintf(stderr, "error! failure to get dna identifiers\nirritant: %s\nexiting...\n", strErrDNA(errDNA));
      exit(EXIT_FAILURE);
    }

    for(j = 0; j < i; j++) {
      if((errDNA = getStrand(dna, ids[j], &strand, &traits)) != DNA_NIL) {
        fprintf(stderr, "error! failure to get dna strand %s\nirritant: %s\nexiting...\n", ids[j], strErrDNA(errDNA));
        freeStrArr(ids, i);
        exit(EXIT_FAILURE);
      }
      if((errINI = setIntArrINI(ini, "Chromosomes", ids[j], strand, traits)) != INI_NIL) {
        fprintf(stderr, "error! failure to get dna strand %s\nirritant: %s\nexiting...\n", ids[j], strErrDNA(errDNA));
        freeStrArr(ids, i);
        free(strand);
        exit(EXIT_FAILURE);
      }
      free(strand);
    }
    freeStrArr(ids, i);

    if((errINI = writeINI(ini, argv[1])) != INI_NIL) {
      fprintf(stderr, "error! failure to write conf\nirritant: %s\nexiting...\n", strErrINI(errINI));
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
