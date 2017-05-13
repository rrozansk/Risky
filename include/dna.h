/******************************************************************************
 * FILE:    dna.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  5/13/17                                                           *
 * INFO:    A library to make working with genetic algorithms easy.           *
 *                                                                            *
 ******************************************************************************/

#ifndef DNA_DEFS
#define DNA_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct dna dna_t; /* A representation of AIs */

typedef enum errDNA { /* All possible errors produced by this library. */
  DNA_NIL, DNA_NIL_DNA, DNA_NIL_FATHER, DNA_NIL_MOTHER, DNA_NIL_CHILD,
  DNA_NIL_NAMES, DNA_NIL_STRANDS, DNA_INVALID_CHROMOSOMES, DNA_INVALID_TRAITS,
  DNA_INVALID_ELITISM, DNA_INVALID_RATE, DNA_NIL_FITNESS, DNA_INVALID_BOUNDS,
} errDNA_t; 

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t makeDNA(dna_t **dna, int chromosomes, int traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
const char *strErrDNA(errDNA_t errDNA);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t setFitness(dna_t *dna, int (*fitness)(char *who, int *strand, int traits));

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t getFitness(dna_t *dna, char *who, int *fitness);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t setMutation(dna_t *dna, int lbound, int ubound, double rate);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, double *rate);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t setElitism(dna_t *dna, int elitism, double percentile);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t getElitism(dna_t *dna, int *elitism, double *percentile);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t setStrand(dna_t *dna, char *name, int *strand, int traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t getStrand(dna_t *dna, char *name, int **strand, int *traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t getNames(dna_t *dna, char ***names, int *size);

/******************************************************************************
 *                                                                            *
 * PURPOSE:  so you can do get/set individually
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t crossover(dna_t *dna, char *father, char *mother, int **child);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t mutate(dna_t *dna, char *who);

/******************************************************************************
 *                                                                            *
 * PURPOSE: automatically does crossover/mutation with fitness/elitism and replaces current generation
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t nextGeneration(dna_t *dna);

/******************************************************************************
 *                                                                            *
 * PURPOSE: 
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 *                                                                            *
 * RETURNS: 
 *                                                                            *
 ******************************************************************************/
errDNA_t freeDNA(dna_t *dna);

#endif
