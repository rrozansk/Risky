/******************************************************************************
 * FILE:    dna.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  5/13/17                                                           *
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
  char **names;      /* array of AI names */
  int **strands;     /* strands of DNA */
  int chromosomes;   /* lenght of strands and AIs */
  int traits;        /* # traits per chromosome in strands */
  int lbound;        /* lower bound on trait value */
  int ubound;        /* upper bound on trait value */
  double rate;       /* mutation rate */
  int elitism;       /* have or not during ne wgeneration creation */
  int (*fitness)(char *who, int *chromosome, int traits);
} dna_t;

/******************************************************************************
 *                                                                            *
 *   P U B L I C   F U N C T I O N S                                          *
 *                                                                            *
 ******************************************************************************/
const char *strErrDNA(errDNA_t errDNA) {
  switch(errDNA) {
    case DNA_INVALID_PERCENTILE: return "percentile must be 0 or 1";
    case DNA_INVALID_CHROMOSOMES: return "chromosomes must be > 0";
    case DNA_INVALID_TRAITS: return "traits must be > 0";
    case DNA_INVALID_ELITISM: return "elitism must be 0 or 1";
    case DNA_INVALID_RATE: return "rate must be between 0.00 and 1.00";
    case DNA_INVALID_BOUNDS: return "lower bound must be < upper bound";
    case DNA_NIL_ELITISM: return "nil elitism";
    case DNA_NIL_PERCENTILE: return "nil percentile";
    case DNA_NIL_TRAITS: return "nil traits";
    case DNA_NIL_SIZE: return "nil size";
    case DNA_NIL_WHO: return "nil strand identifier";
    case DNA_NIL_NAME: return "nil name";
    case DNA_NIL_FITNESS_INT: return "nil fitness";
    case DNA_NIL_DNA: return "nil dna";
    case DNA_NIL_FATHER: return "nil father";
    case DNA_NIL_MOTHER: return "nil mother";
    case DNA_NIL_CHILD: return "nil child";
    case DNA_NIL_NAMES: return "nil names";
    case DNA_NIL_STRAND: return "nil strand";
    case DNA_NIL_FITNESS: return "nil fitness function";
    case DNA_NIL_LBOUND: return "nil lower bound";
    case DNA_NIL_UBOUND: return "nil upper bound";
    case DNA_NIL_RATE: return "nil rate";
    case DNA_NIL: return "";
    default:  return "unknown errDNA_t";
  }
}

errDNA_t makeDNA(dna_t **dna, int chromosomes, int traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(chromosomes <= 0) { return DNA_INVALID_CHROMOSOMES; }
  if(traits <= 0) { return DNA_INVALID_TRAITS; }

  return DNA_NIL;
}

errDNA_t freeDNA(dna_t *dna) {
  if(!dna) { return DNA_NIL_DNA; }

  return DNA_NIL;
}

errDNA_t setFitness(dna_t *dna, int (*fitness)(char *who, int *strand, int traits)) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!fitness) { return DNA_NIL_FITNESS; }

  return DNA_NIL;
}

errDNA_t getFitness(dna_t *dna, char *who, int *fitness) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!who) { return DNA_NIL_NAME; }
  if(!fitness) { return DNA_NIL_FITNESS_INT; }

  return DNA_NIL;  
}

errDNA_t setMutation(dna_t *dna, int lbound, int ubound, double rate) {
  if(!dna) { return DNA_NIL_DNA; }
  if(lbound <= ubound) { return DNA_INVALID_BOUNDS; }
  if(rate < 0.0 || rate > 1.0) { return DNA_INVALID_RATE; }

  return DNA_NIL;
}

errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, double *rate) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!lbound) { return DNA_NIL_LBOUND; }
  if(!ubound) { return DNA_NIL_UBOUND; }
  if(!rate) { return DNA_NIL_RATE; }

  return DNA_NIL;
}

errDNA_t setElitism(dna_t *dna, int elitism, double percentile) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!(elitism == 0 || elitism == 1)) { return DNA_INVALID_ELITISM; }
  if(percentile < 0.00 || percentile > 1.00) { return DNA_INVALID_PERCENTILE; }

  return DNA_NIL;
}

errDNA_t getElitism(dna_t *dna, int *elitism, double *percentile) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!elitism) { return DNA_NIL_ELITISM; }
  if(!percentile) { return DNA_NIL_PERCENTILE; }

  return DNA_NIL;
}

errDNA_t setStrand(dna_t *dna, char *name, int *strand, int traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!name) { return DNA_NIL_NAME; }
  if(!strand) { return DNA_NIL_STRAND; }
  if(traits != dna->traits) { return DNA_INVALID_TRAITS; }

  return DNA_NIL;
}

errDNA_t getStrand(dna_t *dna, char *name, int **strand, int *traits) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!name) { return DNA_NIL_NAME; }
  if(!strand) { return DNA_NIL_STRAND; }
  if(!traits) { return DNA_NIL_TRAITS; }

  return DNA_NIL;
}

errDNA_t getNames(dna_t *dna, char ***names, int *size) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!names) { return DNA_NIL_NAMES; }
  if(!size) { return DNA_NIL_SIZE; }

  return DNA_NIL;
}

errDNA_t crossover(dna_t *dna, char *father, char *mother, int **child) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!father) { return DNA_NIL_FATHER; }
  if(!mother) { return DNA_NIL_MOTHER; }
  if(!child) { return DNA_NIL_CHILD; }

  return DNA_NIL;
}

errDNA_t mutate(dna_t *dna, char *who) {
  if(!dna) { return DNA_NIL_DNA; }
  if(!who) { return DNA_NIL_WHO; }

  return DNA_NIL;
}

errDNA_t nextGeneration(dna_t *dna) {
  if(!dna) { return DNA_NIL_DNA; }

  return DNA_NIL;
}
