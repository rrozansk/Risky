/******************************************************************************
 * FILE:    dna.h                                                             *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 5/4/17                                                            *
 * EDITED:  6/24/17                                                           *
 * INFO:    A library to make working with genetic algorithms easier through  *
 *          the use of getters and setters to easily track and change state.  *
 *          The library also provides an API to easily construct successive   *
 *          generations if desired. It follows the policies for elitism and   *
 *          mutations set out by the user, but crossover is fixed. Other high *
 *          level API's are also exposed to allow custom implementations of   *
 *          constructing successive generations. This presents a versatile    *
 *          interface to the user allowing both low level and/or high level   *
 *          control, whichever is desired. The exposed library API's also     *
 *          follow a uniform interface where only errors are returned from    *
 *          functions, if any, and all getters take ptr's to destinations in  *
 *          which to set the requested information. Please also note that the *
 *          c random number generator must be seeded (ex. srand(time(NULL))), *
 *          if it is not then mutation will not function properly.            *
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
  DNA_OUT_OF_MEMORY, DNA_INVALID_PERCENT, DNA_INVALID_CHROMOSOMES,
  DNA_INVALID_TRAITS, DNA_INVALID_ELITISM, DNA_INVALID_RATE, DNA_INVALID_BOUNDS,
  DNA_INVALID_ID, DNA_INVALID_PARENTS, DNA_NIL_ELITISM, DNA_NIL_PERCENT,
  DNA_NIL_TRAITS, DNA_NIL_SIZE, DNA_NIL_ID, DNA_NIL_FITNESS_INT, DNA_NIL_DNA,
  DNA_NIL_FATHER, DNA_NIL_MOTHER, DNA_NIL_CHILD, DNA_NIL_IDS, DNA_NIL_STRAND,
  DNA_NIL_FITNESS, DNA_NIL_LBOUND, DNA_NIL_UBOUND, DNA_NIL_RATE, DNA_NIL,
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
 * RETURNS: A string representation of the error                              *
 *                                                                            *
 ******************************************************************************/
const char *strErrDNA(errDNA_t errDNA);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempts to create a new dna construct to easily track and mutate *
 *          state. An internal representation of all chromosomes will be      *
 *          generated and initialized to 0. Also, all ids will be copied for  *
 *          internal use as well as being paired with the corresponding       *
 *          chromosomes. If any problem is encountered during initialization  *
 *          all memory will be freed, an error will be returned, and the      *
 *          value stored at dna will be NULL.                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      an address to a ptr in which to set the newly created construct   *
 * ids      an array of ptrs to null terminated strings which will be used to *
 *          identify the corresponding chromosomes                            *
 * strands  the number of chromosomes to track                                *
 * traits   the number of traits in each chromosome                           *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_IDS if ids is NULL                                        *
 *          DNA_INVALID_CHROMOSOMES if strands is < 1                         *
 *          DNA_INVALID_TRAITS if taits < 1                                   *
 *          DNA_OUT_OF_MEMORY if failure to allocate                          *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t makeDNA(dna_t **dna, char *ids[], int strands, int traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To free any dna construct created through the dna constructor.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the ptr to the dna construct in which to free                     *
 *                                                                            *
 * RETURNS: DNA_NIL                                                           *
 *                                                                            *
 ******************************************************************************/
errDNA_t freeDNA(dna_t *dna);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To give the criteria needed in order to properly evaluate every   *
 *          strand of dna. Note that the fitness function will recieve a copy *
 *          of the id and strand to evaluate so it may mutate them freely.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * fitness  a function to determine the 'fitness' of a strand of dna          *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_FITNESS if fitness is NULL                                *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setFitness(dna_t *dna, int (*fitness)(char *id, int strand[], int traits));

/******************************************************************************
 *                                                                            *
 * PURPOSE: Retrieves the fitness of any strand of dna given its identifier.  *
 *          Care is also taken to make copies of the id and strand before     *
 *          passing them into the fitness function for evaluation.            *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * id       the identifier of the strand to evaluate                          *
 * fitness  a ptr to an int in which to store the evaluated fitness of the    *
 *          strand in question                                                *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ID if id is NULL                                          *
 *          DNA_NIL_FITNESS_INT if fitness is NULL                            *
 *          DNA_NIL_FITNESS if there is no currently tracked fitness function *
 *          DNA_INVALID_ID if id does not match any tracked chromosome id     *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getFitness(dna_t *dna, char *id, int *fitness);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Set the mutation rate and bounds of possible values for a trait   *
 *          to take on when crossover is performed.                           *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * lbound   the lower bound of acceptable values for a trait to take on       *
 * ubound   the upper bound of acceptable values for a trait to take on       *
 * rate     the rate of mutation, which must be between 0.00-100.00           *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_INVALID_BOUNDS if lbound >= ubound                            *
 *          DNA_INVALID_RATE if rate is not between 0.0-100.0                 *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setMutation(dna_t *dna, int lbound, int ubound, float rate);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Get the current mutation rate and bounds of acceptable values for *
 *          a given trait to take on.                                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
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
errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, float *rate);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Indicate whether or not to perform elitism when making new        *
 *          generations, and how much of the population to consider 'elite'.  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * elitism  contol whether elitism is on(1) or off(0)                         *
 * percent  the percentage to retain per generation if elitism is on          *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_INVALID_ELITISM if elitism is not 0 or 1                      *
 *          DNA_INVALID_PERCENT if percent is not between 0.0-100.0           *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setElitism(dna_t *dna, int elitism, float percent);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Gather whether or not elitism is being performed when new         *
 *          generations are being constructed, as well as the amount of the   *
 *          population to keep around during the next generations creation.   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * elitism  a ptr to a int to store the value of elitism: on(1) or off(0)     *
 * percent  a ptr to a float to store the generational retention rate of the  *
 *          populations most valuable individuals.                            *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ELITISM if elitism is NULL                                *
 *          DNA_NIL_PERCENT if percent is NULL                                *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getElitism(dna_t *dna, int *elitism, float *percent);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Set the strand of dna identified by id to have the given traits.  *
 *          Note that the array will be copied to the internal representation *
 *          of chromosomes.                                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * id       the identifier for the stand in which to set                      *
 * strand   an array of new traits of length traits                           *
 * traits   the number of traits in the strand                                *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ID if id is NULL                                          *
 *          DNA_NIL_STRAND if strand is NULL                                  *
 *          DNA_INVALID_TRAITS if traits != number of tracked dna traits      *
 *          DNA_INVALID_ID if id does not match any tracked chromosome        *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t setStrand(dna_t *dna, char *id, int *strand, int traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To make a copy of a specific strand of dna.                       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * id       the identifier for the stand in which to get                      *
 * strand   a ptr to a heap or stk allocated array with enough space to hold  *
 *          all the traits.                                                   *
 * traits   the number of traits in the strand                                *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_ID if id is NULL                                          *
 *          DNA_NIL_STRAND if strand is NULL                                  *
 *          DNA_NIL_TRAITS if traits is NULL                                  *
 *          DNA_INVALID_ID if id does not match any tracked chromosome id     *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getStrand(dna_t *dna, char *id, int *strand, int *traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To get the details about number of tracked dna strands and how    *
 *          many traits each one has. This information is needed so the user  *
 *          may alloc strands on the stack or heap when using other functions *
 *          in this library.                                                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * strands  the number of tracked chromosomes in dna                          *
 * traits   the number of tracked traits per chromosome of dna                *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_STRAND if strand is NULL                                  *
 *          DNA_NIL_TRAITS if traits is NULL                                  *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getChromosomes(dna_t *dna, int *strands, int *traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To get copies of all the identifiers corresponding to each        *
 *          strand of dna contained in the dna construct.                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * ids      a ptr to an array of char ptrs to destinations capable of holding *
 *          the largest tracked identifier.                                   *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_IDS if ids is NULL                                        *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t getIDs(dna_t *dna, char *ids[]);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Create a new strand given two distinct parents. Each trait in the *
 *          resulting child strand will be randomly choosen from the parents. *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * father   the identifier of the first parent to use                         *
 * mother   the identifier of the second parent to use                        *
 * child    a ptr to a stack or heap allocated array where to store the       *
 *          resulting child                                                   *
 * traits   the number of traits in the resulting child                       *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL_FATHER is father is NULL                                  *
 *          DNA_NIL_MOTHER if mother is NULL                                  *
 *          DNA_NIL_CHILD if child is NULL                                    *
 *          DNA_NIL_TRAITS if traits is NULL                                  *
 *          DNA_INVALID_ID if mother or father does not match any tracked id  *
 *          DNA_INVALID_PARENTS if mother and father are the same             *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t crossover(dna_t *dna, char *father, char *mother, int *child, int *traits);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To perform mutation on a specific strand of dna following the     *
 *          policies currently tracked in the dna construct for lower and     *
 *          upper bounds, as well as rate.                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 * id       the identifier of the chromosome to mutate                        *
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
 * PURPOSE: Automatically perform crossover/mutation with fitness/elitism and *
 *          replacement of the current generation following currently tracked *
 *          policies inside the dna construct. Parents are choosen randomly   *
 *          and distincly from one another. However, a single parent may be   *
 *          responsible for contributing to several children.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * dna      the dna construct to use                                          *
 *                                                                            *
 * RETURNS: DNA_NIL_DNA if dna in NULL                                        *
 *          DNA_NIL if no error                                               *
 *                                                                            *
 ******************************************************************************/
errDNA_t nextGeneration(dna_t *dna);

#endif
