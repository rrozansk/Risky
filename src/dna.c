/******************************************************************************
 * FILE:    dna.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  5/22/17                                                           *
 * INFO:    Implementation of the interface located in dna.h.                 *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <dna.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct dna {
  char **ids;        /* array of chromosome identifiers */
  int **strands;     /* matrix of chromosomes */
  int chromosomes;   /* rows in matrix */
  int traits;        /* columns in matrix */
  int lbound;        /* lower bound on matrix values */
  int ubound;        /* upper bound on matrix values */
  double rate;       /* mutation rate 0.00 - 1.00 */
  int elitism;       /* enable elitism or not */
  double percent;    /* size of elitist group 0.00 - 1.00 */
  int (*fitness)(char *id, int *strand, int traits);
} dna_t;

/******************************************************************************
 *                                                                            *
 *   P R I V A T E   H E L P E R S                                            *
 *                                                                            *
 ******************************************************************************/
int myStrCmp(const void *str1, const void *str2) { 
  return strcmp((const char *)str1, (const char *)str2);
}

int find(dna_t *dna, char *id) {
  int cmp, loc, hi, lo;
  for(lo = 0, hi = dna->traits; hi > lo;) {
    loc = lo + ((hi - lo) / 2);
    if(!(cmp = myStrCmp(id, dna->ids[loc]))) { return loc; }
    else if(cmp < 0) { hi = loc; }
    else { lo = loc; } // cmp > 0
  }
  return -1; // not found
}

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrDNA(errDNA_t errDNA) {
  switch(errDNA) {
    // misc errors
    case DNA_OUT_OF_MEMORY: return "out of memory";
    // invalid input errors
    case DNA_INVALID_PERCENT: return "percent must be 0 or 1";
    case DNA_INVALID_CHROMOSOMES: return "chromosomes must be > 0";
    case DNA_INVALID_TRAITS: return "traits must be > 0";
    case DNA_INVALID_ELITISM: return "elitism must be 0 or 1";
    case DNA_INVALID_RATE: return "rate must be between 0.00 and 1.00";
    case DNA_INVALID_BOUNDS: return "lower bound must be < upper bound";
    case DNA_INVALID_ID: return "id does not match any know chromosome";
    // nil arg errors
    case DNA_NIL_ELITISM: return "nil elitism";
    case DNA_NIL_PERCENT: return "nil percent";
    case DNA_NIL_TRAITS: return "nil traits";
    case DNA_NIL_SIZE: return "nil size";
    case DNA_NIL_ID: return "nil id";
    case DNA_NIL_FITNESS_INT: return "nil fitness";
    case DNA_NIL_DNA: return "nil dna";
    case DNA_NIL_FATHER: return "nil father";
    case DNA_NIL_MOTHER: return "nil mother";
    case DNA_NIL_CHILD: return "nil child";
    case DNA_NIL_IDS: return "nil ids";
    case DNA_NIL_STRAND: return "nil strand";
    case DNA_NIL_FITNESS: return "nil fitness function";
    case DNA_NIL_LBOUND: return "nil lower bound";
    case DNA_NIL_UBOUND: return "nil upper bound";
    case DNA_NIL_RATE: return "nil rate";
    // no error and unknown error return
    case DNA_NIL: return "";
    default:  return "unknown errDNA_t";
  }
}

errDNA_t makeDNA(dna_t **dna, char **ids, int strands, int traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(strands <= 0) { return DNA_INVALID_CHROMOSOMES; }
  if(traits <= 0) { return DNA_INVALID_TRAITS; }

  if(!(*dna = calloc(1, sizeof(dna_t)))) { return DNA_OUT_OF_MEMORY; }

  (*dna)->strands = calloc(strands, sizeof(int *));
  (*dna)->ids = calloc(strands, sizeof(char *));
  if(!(*dna)->ids || !(*dna)->strands) {
    freeDNA(*dna);
    *dna = NULL;
    return DNA_OUT_OF_MEMORY;
  }

  int id;
  for(id = 0; id < strands; id++) {
    (*dna)->strands[id] = calloc(traits, sizeof(int));
    (*dna)->ids[id] = calloc(strlen(ids[id])+1, sizeof(char));
    if(!(*dna)->ids[id] && !(*dna)->strands[id]) {
      freeDNA(*dna);
      *dna = NULL;
      return DNA_OUT_OF_MEMORY;
    }
    strncpy((*dna)->ids[id], ids[id], strlen(ids[id]));
  }
  qsort((*dna)->strands, strands, sizeof(char *), myStrCmp);

  (*dna)->chromosomes = strands;
  (*dna)->traits = traits;

  return DNA_NIL;
}

errDNA_t freeDNA(dna_t *dna) {
  if(!dna) { return DNA_NIL; }

  if(dna->strands) { free(dna->strands); }
  if(dna->ids) { 
    int i;
    for(i = dna->chromosomes; i; i--) { free(dna->ids[i-1]); }
    free(dna->ids);
  }

  free(dna);

  return DNA_NIL;
}

errDNA_t setFitness(dna_t *dna, int (*fitness)(char *id, int *strand, int traits)) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!fitness) { return DNA_NIL_FITNESS; }

  dna->fitness = fitness;

  return DNA_NIL;
}

errDNA_t getFitness(dna_t *dna, char *id, int *fitness) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!id) { return DNA_NIL_ID; }
  if(!fitness) { return DNA_NIL_FITNESS_INT; }

  int loc = find(dna, id);
  if(loc == -1) { return DNA_INVALID_ID; }

  int tmpStrand[dna->traits];
  int i;
  for(i = 0; i < dna->traits; i++) { tmpStrand[i] = dna->strands[loc][i]; }

  char tmpID[strlen(id)+1];
  strncpy(tmpID, id, strlen(id)+1);

  *fitness = (dna->fitness)(tmpID, tmpStrand, dna->traits);

  return DNA_NIL;
}

errDNA_t setMutation(dna_t *dna, int lbound, int ubound, double rate) {
  if(!dna) { return DNA_NIL_DNA; }
  if(lbound >= ubound) { return DNA_INVALID_BOUNDS; }
  if(rate < 0.0 || rate > 1.0) { return DNA_INVALID_RATE; }

  dna->lbound = lbound;
  dna->ubound = ubound;
  dna->rate = rate;

  return DNA_NIL;
}

errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, double *rate) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!lbound) { return DNA_NIL_LBOUND; }
  if(!ubound) { return DNA_NIL_UBOUND; }
  if(!rate) { return DNA_NIL_RATE; }

  *lbound = dna->lbound;
  *ubound = dna->ubound;
  *rate = dna->rate;

  return DNA_NIL;
}

errDNA_t setElitism(dna_t *dna, int elitism, double percent) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!(elitism == 0 || elitism == 1)) { return DNA_INVALID_ELITISM; }
  if(percent < 0.00 || percent > 1.00) { return DNA_INVALID_PERCENT; }

  dna->elitism = elitism;
  dna->percent = percent;

  return DNA_NIL;
}

errDNA_t getElitism(dna_t *dna, int *elitism, double *percent) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!elitism) { return DNA_NIL_ELITISM; }
  if(!percent) { return DNA_NIL_PERCENT; }

  *elitism = dna->elitism;
  *percent = dna->percent;

  return DNA_NIL;
}

errDNA_t setStrand(dna_t *dna, char *id, int *strand, int traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!id) { return DNA_NIL_ID; }
  if(!strand) { return DNA_NIL_STRAND; }
  if(traits != dna->traits) { return DNA_INVALID_TRAITS; }

  int loc = find(dna, id);
  if(loc == -1) { return DNA_INVALID_ID; }

  for(; traits; traits--) { (dna->strands)[loc][traits-1] = strand[traits-1]; }

  return DNA_NIL;
}

errDNA_t getStrand(dna_t *dna, char *id, int **strand, int *traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!id) { return DNA_NIL_ID; }
  if(!strand) { return DNA_NIL_STRAND; }
  if(!traits) { return DNA_NIL_TRAITS; }

  int loc = find(dna, id);
  if(loc == -1) { return DNA_INVALID_ID; }

  *traits = dna->traits;
  if(!(*strand = malloc(sizeof(int) * dna->traits))) { return DNA_OUT_OF_MEMORY; }

  int i;
  for(i = 0; i < dna->traits; i++) { (*strand)[i] = (dna->strands)[loc][i]; }

  return DNA_NIL;
}

errDNA_t getNames(dna_t *dna, char ***ids, int *size) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!ids) { return DNA_NIL_IDS; }
  if(!size) { return DNA_NIL_SIZE; }

  if(!(*ids = malloc(sizeof(char *) * dna->chromosomes))) { return DNA_OUT_OF_MEMORY; }

  int id;
  for(id = 0; id < dna->chromosomes; id++) {
    if(!((*ids)[id] = calloc(strlen(dna->ids[id])+1, sizeof(char)))) {
      for(; id; id--) { free((*ids)[id-1]); }
      free(*ids);
      *ids = NULL;
      return DNA_OUT_OF_MEMORY;
    }
    strncpy((*ids)[id], dna->ids[id], strlen(dna->ids[id]));
  }

  *size = dna->chromosomes;

  return DNA_NIL;
}

errDNA_t crossover(dna_t *dna, char *father, char *mother, int **child, int *traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!father) { return DNA_NIL_FATHER; }
  if(!mother) { return DNA_NIL_MOTHER; }
  if(!child) { return DNA_NIL_CHILD; }

  int id1 = find(dna, father);
  int id2 = find(dna, mother);
  if(id1 == -1 || id2 == -1) { return DNA_INVALID_ID; }

  if(!(*child = malloc(sizeof(int) * dna->traits))) { return DNA_OUT_OF_MEMORY; }

  int i;
  for(i = 0; i < dna->traits; i++) { (*child)[i] = dna->strands[(rand() % 2) ? id1 : id2][i]; }

  *traits = dna->traits;

  return DNA_NIL;
}

errDNA_t mutate(dna_t *dna, char *id) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!id) { return DNA_NIL_ID; }

  int loc = find(dna, id);
  if(loc == -1) { return DNA_INVALID_ID; }

  int i, mutation;
  for(i = 0; i < dna->traits; i++) {
    if((rand() % 100) < (dna->rate * 100)) {
      mutation = (rand() % (dna->ubound + 1 - dna->lbound)) + dna->lbound;
      dna->strands[loc][i] = mutation;
    }
  }

  return DNA_NIL;
}


int myGenCmp(const void *map1, const void *map2) {
  int fit1 = ((int *)map1)[1];
  int fit2 = ((int *)map2)[1];
  
  if(fit1 == fit2) { return 0; }
  else if(fit1 < fit2) { return -1; }
  else { return 1; } // fit1 > fit2
}

errDNA_t nextGeneration(dna_t *dna) {
  if(!dna) { return DNA_NIL_DNA; }

  char **ids;
  int i, j, k;

  errDNA_t errDNA;
  if((errDNA = getNames(dna, &ids, &i)) != DNA_NIL) { return errDNA; }

  int fitness[i][2]; // mapping => id => { loc, fitness }
  for(j = 0; j < i; j++) {
    fitness[j][0] = j;
    if((errDNA = getFitness(dna, ids[j], &fitness[j][1])) != DNA_NIL) {
      for(j = 0; j < i; j++) { free(ids[j]); }
      free(ids);
      return errDNA;  
    }
  }

  qsort(fitness, i, sizeof(int)*2, myGenCmp);

  int *child, mother, father;
  int keep = (int)(dna->chromosomes * dna->rate); // FIXME: get rid of struct '->' refs
  for(j = dna->chromosomes - keep; j ; j--) {
    mother = rand() % dna->chromosomes;
    father = rand() % dna->chromosomes;
    if((errDNA = crossover(dna, ids[mother], ids[father], &child, &k)) != DNA_NIL) {
      for(j = 0; j < i; j++) { free(ids[j]); }
      free(ids);
      return errDNA;
    }
    if((errDNA = setStrand(dna, ids[fitness[j-1][0]], child, k)) != DNA_NIL) {
      for(j = 0; j < i; j++) { free(ids[j]); }
      free(ids);
      return errDNA;
    }
    if((errDNA = mutate(dna, ids[fitness[j-1][0]])) != DNA_NIL) {
      for(j = 0; j < i; j++) { free(ids[j]); }
      free(ids);
      return errDNA;
    }
  }

  for(j = 0; j < i; j++) { free(ids[j]); }
  free(ids);

  return DNA_NIL;
}
