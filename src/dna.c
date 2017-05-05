/******************************************************************************
 * FILE:    dna.c                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  5/4/17                                                            *
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
  char **AIs;        /* array of AI names */
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
    case DNA_NIL: return "";
    default:  return "unknown errDNA_t";
  }
}

// take params of have getters/setters??
errDNA_t makeDNA(dna_t **dna) {
  return DNA_NIL;
}

errDNA_t freeDNA(dna_t *dna) {
  return DNA_NIL;
}

errDNA_t crossover(dna_t *dna, char *father, char *mother, int **child) {
  return DNA_NIL;
}

errDNA_t mutate(dna_t *dna, char *who) {
  return DNA_NIL;
}

errDNA_t replace(dna_t *dna, char *who, int *chromosome) {
  return DNA_NIL;
}
