/******************************************************************************
 * FILE:    testDNA.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/4/17                                                            *
 * INFO:    Test file for implementation of the interface located in dna.h.   *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dna.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define STRANDS 3
#define TRAITS  10
#define TOTAL_TESTS 8

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultDNA { DNA_SUCC, DNA_FAIL } testResultDNA_t;

/******************************************************************************
 *                                                                            *
 *   G L O B A L S                                                            *
 *                                                                            *
 ******************************************************************************/
dna_t *dna;

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/
// simple fitness function just to test with
int testFitness(char *id, int *strand, int traits) {
  int total;
  for(total = 0; traits; total += strand[--traits]);
  return total;
}

testResultDNA_t testMakeNilDNA() {
  fprintf(stdout, "FAIL: testMakeNilDNA\n");
  return DNA_FAIL;
}

testResultDNA_t testMakeDNA() {
  dna_t *dna;
  char *ids[STRANDS] = { "id1", "id2", "id3" };

  errDNA_t errDNA = DNA_NIL;
  if((errDNA = makeDNA(&dna, ids, STRANDS, TRAITS)) != DNA_NIL) {
    fprintf(stdout, "FAIL: makeDNA\nerror: %s\n", strErrDNA(errDNA));
  }
 
  int strands, traits;
  if((errDNA = getChromosomes(dna, &strands, &traits)) != DNA_NIL) {
    fprintf(stdout, "FAIL: getChromosomes\nerror: %s\n", strErrDNA(errDNA));
  }

  if(strands != STRANDS) {
    fprintf(stdout, "FAIL: getChromosomes\nerror: improper strands returned\n");
  }

  if(traits != TRAITS) {
    fprintf(stdout, "FAIL: getChromosomes\nerror: improper traits returned\n");
  }

  //errDNA_t freeDNA(dna_t *dna);
  //errDNA_t setFitness(dna_t *dna, int (*fitness)(char *id, int *strand, int traits));
  //errDNA_t getFitness(dna_t *dna, char *id, int *fitness);
  //errDNA_t setMutation(dna_t *dna, int lbound, int ubound, double rate);
  //errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, double *rate);
  //errDNA_t setElitism(dna_t *dna, int elitism, double percent);
  //errDNA_t getElitism(dna_t *dna, int *elitism, double *percent);
  //errDNA_t setStrand(dna_t *dna, char *id, int *strand, int traits);
  //errDNA_t getStrand(dna_t *dna, char *id, int *strand, int *traits);
  //errDNA_t getIDs(dna_t *dna, char ids[][36]);
  //errDNA_t crossover(dna_t *dna, char *father, char *mother, int *child, int *traits);
  //errDNA_t mutate(dna_t *dna, char *id);
  //errDNA_t nextGeneration(dna_t *dna);

  fprintf(stdout, "PASS: testMakeDNA\n");
  return DNA_SUCC;
}

testResultDNA_t testFreeNilDNA() {
  fprintf(stdout, "FAIL: testFreeNilDNA\n");
  return DNA_FAIL;
}

testResultDNA_t testFreeDNA() {
  fprintf(stdout, "FAIL: testFreeDNA\n");
  return DNA_FAIL;
}

testResultDNA_t testCrossoverDNA() {
  fprintf(stdout, "FAIL: testCrossoverDNA\n");
  return DNA_FAIL;
}

testResultDNA_t testMutateDNA() {
  fprintf(stdout, "FAIL: testMutateDNA\n");
  return DNA_FAIL;
}

testResultDNA_t testNextGenDNA() {
  fprintf(stdout, "FAIL: testNextGenDNA\n");
  return DNA_FAIL;
}

testResultDNA_t testStrErrDNA() {
 // test to make sure error enums have non-empty error messages
  if(strcmp(strErrDNA(DNA_NIL), "")) { // special case empty
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL error message is non-empty\n");
  }

  if(!strcmp(strErrDNA(DNA_NIL_DNA), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_DNA error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_FATHER), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_FATHER error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_SIZE), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_SIZE error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_RATE), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_RATE error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_IDS), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_IDS error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_ELITISM), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_ELITISM error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_STRAND), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_STRANDS error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_FITNESS_INT), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_FITNESS_INT error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_CHROMOSOMES), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_CHROMOSOMES error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_ELITISM), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_ELITISM error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_RATE), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_RATE error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_TRAITS), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_TRAITS error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_PERCENT), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_PERCENT error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_MOTHER), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_MOTHER error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_LBOUND), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_LBOUND error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_UBOUND), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_UBOUND error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_ID), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_ID error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_FITNESS), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_FITNESS error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_TRAITS), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_TRAITS error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_BOUNDS), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_BOUNDS error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_PERCENT), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_PERCENT error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_NIL_CHILD), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_NIL_CHILD error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_OUT_OF_MEMORY), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_OUT_OF_MEMORY error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_ID), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_ID error message is empty\n");
  }
  if(!strcmp(strErrDNA(DNA_INVALID_IDS), "")) {
    fprintf(stdout, "FAIL: strErrDNA\nerror: DNA_INVALID_IDS error message is empty\n");
  }

  fprintf(stdout, "PASS: testStrErrDNA\n");
  return DNA_SUCC; 
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
testResultDNA_t (*TESTS[TOTAL_TESTS])() = {
  testMakeDNA,
  testMakeNilDNA,
  testFreeNilDNA,
  testFreeDNA,
  testCrossoverDNA,
  testMutateDNA,
  testNextGenDNA,
  testStrErrDNA
};

int main() {

  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    ((*TESTS[test])() == DNA_SUCC) ? passes++ : fails++;
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
