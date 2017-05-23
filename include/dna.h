/******************************************************************************
 * FILE:    dna.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  5/22/17                                                           *
 * INFO:    A library to make working with genetic algorithms easier through  *
 *          the use of getters and setters to easily track state, as well as  *
 *          some convience functions which perform various tasks such as      *
 *          crossover, mutation, and new generation creation using elitism.   *
 *          The library exposes all this to allow users the ability to create *
 *          custom implementations if new geneartion creation if so needed or *
 *          desired. Please also note that the c random number must be seeded *
 *          (ex. srand(time(NULL))) or mutation will not work. Error handling *
 *          is also provided.                                                 *
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
  DNA_NIL, DNA_NIL_DNA, DNA_NIL_FATHER, DNA_NIL_SIZE, DNA_NIL_RATE, DNA_NIL_IDS,
  DNA_NIL_ELITISM, DNA_NIL_STRAND, DNA_NIL_FITNESS_INT, DNA_INVALID_CHROMOSOMES,
  DNA_INVALID_ELITISM, DNA_INVALID_RATE, DNA_NIL_TRAITS, DNA_INVALID_PERCENT,
  DNA_NIL_MOTHER, DNA_NIL_LBOUND, DNA_NIL_UBOUND, DNA_NIL_ID, DNA_NIL_FITNESS,
  DNA_INVALID_TRAITS, DNA_INVALID_BOUNDS, DNA_NIL_PERCENT, DNA_NIL_CHILD,
  DNA_OUT_OF_MEMORY, DNA_INVALID_ID,
} errDNA_t;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: Returns a string representation of any possible error returned by *
 *          the library.                                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * errDNA   the error to stringify                                            *
 *                                                                            *
 * RETURNS: A string representation of the error.                             *
 *                                                                            *
 ******************************************************************************/
const char *strErrDNA(errDNA_t errDNA);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempts to create a new dna, if any error is returned the value  *
 *          stored at dna will be NULL.                                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * strands  the number of chromosomes to track                                *
 * traits   the number of traits in each chromosome                           *
 * ids      the ids used to identify the strands                              *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_INVALID_CHROMOSOMES if chromosomes is < 1                     *
 *          DNA_INVALID_TRAITS if taits < 1                                   *
 *          DNA_OUT_OF_MEMORY if failure to allocate                          *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t makeDNA(dna_t **dna, char **ids, int strands, int traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To free any dna created by makeDNA().                             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 *                                                                            *
 * RETURNS: DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t freeDNA(dna_t *dna);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To give the criteria needed in order to properly evaluate every   *
 *          strand of dna.                                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * fitness  a function to determine the 'fitness' of a strand of dna          *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_FITNESS if fitness is NULL                                *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setFitness(dna_t *dna, int (*fitness)(char *id, int *strand, int traits));

/******************************************************************************
 *                                                                            *
 * PURPOSE: Retrieves the fitness of any strand of dna given its identifier.  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * id       the id of the strand to get                                       *
 * fitness  the fitness of the strand in question                             *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ID if id is NULL                                          *
 *          DNA_NIL_FITNESS_INT if fitness is NULL                            *
 *          DNA_INVALID_ID if id does not match any tracked chromosome id     *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getFitness(dna_t *dna, char *id, int *fitness);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Set the mutation rate of the dna when crossover is performed.     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * lbound   the lower bound of acceptable values for a trait to take on       *
 * ubound   the upper bound of acceptable values for a trait to take on       *
 * rate     the rate of mutation between 0.0-1.0                              *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_INVALID_BOUNDS if lbound >= ubound                            *
 *          DNA_INVALID_RATE if rate is not between 0.0-1.0                   *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setMutation(dna_t *dna, int lbound, int ubound, double rate);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Get the current mutation rate and the upper and lower bounds of   *
 *          acceptable trait values.                                          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * lbound   the lower limit of acceptable trait values                        *
 * ubound   the upper limit of acceptable trait values                        *
 * rate     the mutation rate of the dna                                      *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_LBOUND if lbound is NULL                                  *
 *          DNA_NIL_UBOUND if ubound is NULL                                  *
 *          DNA_NIL_RATE if rate is NULL                                      *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, double *rate);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Perform elitism or not (0: no, 1: yes). If yes, then determine    *
 *          how much elitism to perform.                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * elitism  to turn elitism on/off                                            *
 * percent  the percentage to retain per generation if elitism is on          *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_INVALID_ELITISM if elitism is not 0 or 1                      *
 *          DNA_INVALID_PERCENT if percent is not between 0.0-1.0             *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setElitism(dna_t *dna, int elitism, double percent);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Gather if elitism is bening performed during crossover or not,    *
 *          and if so, the amount being keep around per generation.           *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * elitism  if elitism is turned on/off                                       *
 * percent  the generational retnetion rate if elitism is turned on           *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ELITISM if elitism is NULL                                *
 *          DNA_NIL_PERCENT if percent is NULL                                *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getElitism(dna_t *dna, int *elitism, double *percent);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Set a strand of dna to be tracked using the library with a given  *
 *          identifier.                                                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * id       the identifier for stand                                          *
 * strand   the stand                                                         *
 * traits   the number of traits in the strand                                *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ID if id is NULL                                          *
 *          DNA_NIL_STRAND if strand is NULL                                  *
 *          DNA_INVALID_TRAITS if traits < 1                                  *
 *          DNA_INVALID_ID if id does not match any tracked chromosome id     *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setStrand(dna_t *dna, char *id, int *strand, int traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To create a copy of a specific strand of dna, the user must free. *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * id       the identifier for stand to get                                   *
 * strand   the stand gotten                                                  *
 * traits   the number of traits in the strand                                *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ID if id is NULL                                          *
 *          DNA_NIL_STRAND if strand is NULL                                  *
 *          DNA_NIL_TRAITS if traits is NULL                                  *
 *          DNA_INVALID_ID if id does not match any tracked chromosome id     *
 *          DNA_OUT_OF_MEMORY if allocation of strand fails                   *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getStrand(dna_t *dna, char *id, int **strand, int *traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To allocate a new array of strings containing the identifiers of  *
 *          each strand contained in the dna.                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * ids      an array of identifiers to corresponding strands                  *
 * size     the size of the array                                             *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_IDS if ids is NULL                                        *
 *          DNA_NIL_SIZE if size is NULL                                      *
 *          DNA_OUT_OF_MEMORY if allocation of ids fails                      *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getNames(dna_t *dna, char ***ids, int *size);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create a new strand given to parent ids, and store the resulting  *
 *          strand at child.                                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * father   the id of the first parent to use                                 *
 * mother   the id of the second parent to use                                *
 * child    the resulting child                                               *
 * traits   the number of items in child                                      *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_FATHER is father is NULL                                  *
 *          DNA_NIL_MOTHER if mother is NULL                                  *
 *          DNA_NIL_CHILD if child is NULL                                    *
 *          DNA_INVALID_ID if mother or father does not match any tracked id  *
 *          DNA_OUT_OF_MEMORY if allocation of child fails                    *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t crossover(dna_t *dna, char *father, char *mother, int **child, int *traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To mutate a specific strand given an identifier.                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 * id       the id of the strand to mutate                                    *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ID if id is NULL                                          *
 *          DNA_INVALID_ID if id does not match any tracked chromosome id     *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t mutate(dna_t *dna, char *id);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Automatically does crossover/mutation with fitness/elitism and    *
 *          replaces current generation.                                      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna to use                                                    *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL if no error                                               *
 *          NOTE: any error from functions: crossover, mutate, getNames,      *
 *          getFitness, and setStrand is also possible                        *
 *                                                                            *
 ******************************************************************************/
errDNA_t nextGeneration(dna_t *dna);

#endif
