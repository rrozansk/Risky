/******************************************************************************
 * FILE:    dna.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  5/4/17                                                            *
 * INFO:    FIXME
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
  DNA_NIL,
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
errDNA_t makeDNA(dna_t **dna);

errDNA_t freeDNA(dna_t **dna);

errDNA_t fitness(dna_t *dna, char *who, int *fitness);

errDNA_t crossover(dna_t *dna, char *father, char *mother, int **child);

errDNA_t mutate(dna_t *dna, char *who);

errDNA_t replace(dna_t *dna, char *who, int *chromosome);

#endif
