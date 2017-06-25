/******************************************************************************
 * FILE:    dna.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  6/25/17                                                           *
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
  float rate;        /* mutation rate 0.00 - 100.00 */
  int elitism;       /* enable elitism or not */
  float percent;     /* size of elitist group 0.00 - 100.00 */
  int (*fitness)(char *id, int strand[], int traits);
} dna_t;

/******************************************************************************
 *                                                                            *
 *   P R I V A T E   F U N C T I O N S                                        *
 *                                                                            *
 ******************************************************************************/
static int myGenCmp(const void *whoFitness1, const void *whoFitness2) {
  int fitness1 = ((int *)whoFitness1)[1];
  int fitness2 = ((int *)whoFitness2)[1];

  return fitness2 - fitness1; // decending order
  //return fitness1 - fitness2; // ascending order
}

static int myStrCmp(const void *str1, const void *str2) { 
  //return strcmp((const char *)str1, (const char *)str2);
  return strcmp(*(char **)str1, *(char **)str2);
}

static int find(dna_t *dna, char *id) {
  int cmp, loc, hi, lo;
  for(lo = 0, hi = dna->chromosomes-1; lo <= hi;) {
    loc = lo + ((hi - lo) / 2);
    if((cmp = strcmp(id, dna->ids[loc])) == 0) { return loc; } // cmp == 0
    else if(cmp < 0) { hi = loc-1; }
    else { lo = loc+1; } // cmp > 0
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
    case DNA_INVALID_PERCENT: return "percent must be between 0.00 and 100.00";
    case DNA_INVALID_CHROMOSOMES: return "chromosomes must be > 0";
    case DNA_INVALID_TRAITS: return "traits must be > 0";
    case DNA_INVALID_ELITISM: return "elitism must be 0 or 1";
    case DNA_INVALID_RATE: return "rate must be between 0.00 and 100.00";
    case DNA_INVALID_BOUNDS: return "lower bound must be < upper bound";
    case DNA_INVALID_ID: return "id does not match any know chromosome";
    case DNA_INVALID_PARENTS: return "crossover requires two distinct parents";
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

errDNA_t makeDNA(dna_t **dna, char *ids[], int strands, int traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!ids) { return DNA_NIL_IDS; }
  if(strands < 1) { return DNA_INVALID_CHROMOSOMES; }
  if(traits < 1) { return DNA_INVALID_TRAITS; }

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
  qsort((*dna)->ids, strands, sizeof(char *), myStrCmp);

  (*dna)->chromosomes = strands;
  (*dna)->traits = traits;

  return DNA_NIL;
}

errDNA_t freeDNA(dna_t *dna) {
  if(!dna) { return DNA_NIL; }

  int i;
  for(i = dna->chromosomes; i; i--) {
    if(dna->strands) { free(dna->strands[i-1]); }
    if(dna->ids) { free(dna->ids[i-1]); }
  }
  if(dna->strands) { free(dna->strands); }
  if(dna->ids) { free(dna->ids); }

  free(dna);

  return DNA_NIL;
}

errDNA_t setFitness(dna_t *dna, int (*fitness)(char *id, int strand[], int traits)) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!fitness) { return DNA_NIL_FITNESS; }

  dna->fitness = fitness;

  return DNA_NIL;
}

errDNA_t getFitness(dna_t *dna, char *id, int *fitness) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!id) { return DNA_NIL_ID; }
  if(!fitness) { return DNA_NIL_FITNESS_INT; }
  if(!dna->fitness) { return DNA_NIL_FITNESS; }

  int loc, i;
  if((loc = find(dna, id)) == -1) { return DNA_INVALID_ID; }

  int tmpStrand[dna->traits];
  for(i = dna->traits; i; i--) { tmpStrand[i-1] = dna->strands[loc][i-1]; }

  char tmpID[strlen(id)+1];
  strncpy(tmpID, id, strlen(id)+1);

  *fitness = (dna->fitness)(tmpID, tmpStrand, dna->traits);

  return DNA_NIL;
}

errDNA_t setMutation(dna_t *dna, int lbound, int ubound, float rate) {
  if(!dna) { return DNA_NIL_DNA; }
  if(lbound >= ubound) { return DNA_INVALID_BOUNDS; }
  if(rate < 0.0 || rate > 100.0) { return DNA_INVALID_RATE; }

  dna->lbound = lbound;
  dna->ubound = ubound;
  dna->rate = rate;

  return DNA_NIL;
}

errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, float *rate) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!lbound) { return DNA_NIL_LBOUND; }
  if(!ubound) { return DNA_NIL_UBOUND; }
  if(!rate) { return DNA_NIL_RATE; }

  *lbound = dna->lbound;
  *ubound = dna->ubound;
  *rate = dna->rate;

  return DNA_NIL;
}

errDNA_t setElitism(dna_t *dna, int elitism, float percent) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!(elitism == 0 || elitism == 1)) { return DNA_INVALID_ELITISM; }
  if(percent < 0.0 || percent > 100.0) { return DNA_INVALID_PERCENT; }

  dna->elitism = elitism;
  dna->percent = percent;

  return DNA_NIL;
}

errDNA_t getElitism(dna_t *dna, int *elitism, float *percent) {
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

errDNA_t getStrand(dna_t *dna, char *id, int *strand, int *traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!id) { return DNA_NIL_ID; }
  if(!strand) { return DNA_NIL_STRAND; }
  if(!traits) { return DNA_NIL_TRAITS; }

  int loc = find(dna, id);
  if(loc == -1) { return DNA_INVALID_ID; }

  int i;
  for(i = 0; i < dna->traits; i++) { strand[i] = (dna->strands)[loc][i]; }
  *traits = dna->traits;

  return DNA_NIL;
}

errDNA_t getChromosomes(dna_t *dna, int *strands, int *traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!strands) { return DNA_NIL_STRAND; }
  if(!traits) { return DNA_NIL_TRAITS; }

  *strands = dna->chromosomes;
  *traits = dna->traits;
  
  return DNA_NIL;
}

errDNA_t getIDs(dna_t *dna, char *ids[]) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!ids) { return DNA_NIL_IDS; }

  int id;
  for(id = dna->chromosomes; id; id--) { strcpy(ids[id-1], dna->ids[id-1]); }

  return DNA_NIL;
}

errDNA_t crossover(dna_t *dna, char *father, char *mother, int *child, int *traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!father) { return DNA_NIL_FATHER; }
  if(!mother) { return DNA_NIL_MOTHER; }
  if(!child) { return DNA_NIL_CHILD; }
  if(!traits) { return DNA_NIL_TRAITS; }

  int id1 = find(dna, father);
  int id2 = find(dna, mother);
  if(id1 == -1 || id2 == -1) { return DNA_INVALID_ID; }
  if(id1 == id2) { return DNA_INVALID_PARENTS; }

  int i;
  for(*traits = i = dna->traits; i; i--) {
    child[i-1] = dna->strands[(rand() % 2) ? id1 : id2][i-1];
  }


  return DNA_NIL;
}

errDNA_t mutate(dna_t *dna, char *id) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!id) { return DNA_NIL_ID; }

  int loc, mutation, i;
  if((loc = find(dna, id)) == -1) { return DNA_INVALID_ID; }

  for(i = 0; i < dna->traits; i++) {
    if((rand() % 10000) < (dna->rate * 100)) {
      mutation = (rand() % (dna->ubound + 1 - dna->lbound)) + dna->lbound;
      dna->strands[loc][i] = mutation;
    }
  }

  return DNA_NIL;
}

errDNA_t nextGeneration(dna_t *dna) {
  if(!dna) { return DNA_NIL_DNA; }

  int strands, traits, mother, father;
  int newTrait, loc;
  int fitness[dna->chromosomes][2]; // mapping => id => { loc, fitness }
  int strand[dna->traits];          // tmp strand for fitness func

  for(strands = dna->chromosomes; strands; strands--) {
    for(traits = dna->traits; traits; traits--) {
      strand[traits-1] = dna->strands[strands-1][traits-1];
    }
    fitness[strands-1][0] = strands-1;
    fitness[strands-1][1] = dna->fitness(dna->ids[strands-1], strand, dna->traits);
  }

  qsort(fitness, dna->chromosomes, sizeof(int)*2, myGenCmp);

  int keep = dna->chromosomes - (dna->chromosomes * (dna->rate / 100.0));
  for(strands = keep+1; strands < dna->chromosomes; strands++) {
    mother = rand() % dna->chromosomes;
    do { father = rand() % dna->chromosomes; } while(mother == father); // distinct parents, but some may mate multiple times
    loc = fitness[strands][0];
    for(traits = dna->traits; traits; traits--) {
      if((rand() % 10000) < (dna->rate * 100)) { // mutation
        newTrait = (rand() % (dna->ubound + 1 - dna->lbound)) + dna->lbound;
      } else { // crossover
        newTrait = dna->strands[(rand() % 2) ? mother : father][traits-1];
      }
      dna->strands[loc][traits-1] = newTrait; // overwrite
    }
  }

  return DNA_NIL;
}
