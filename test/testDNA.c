/******************************************************************************
 * FILE:    testDNA.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  7/15/17                                                           *
 * INFO:    Test file for implementation of the interface located in dna.h.   *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <dna.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 92

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultDNA { DNA_PASS, DNA_FAIL } testResultDNA_t;

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/
testResultDNA_t testStrErrDNA_OUT_OF_MEMORY() {
  return (strcmp(strErrDNA(DNA_OUT_OF_MEMORY), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_PERCENT() {
  return (strcmp(strErrDNA(DNA_INVALID_PERCENT), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_CHROMOSOMES() {
  return (strcmp(strErrDNA(DNA_INVALID_CHROMOSOMES), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_TRAITS() {
  return (strcmp(strErrDNA(DNA_INVALID_TRAITS), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_ELITISM() {
  return (strcmp(strErrDNA(DNA_INVALID_ELITISM), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_RATE() {
  return (strcmp(strErrDNA(DNA_INVALID_RATE), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_BOUNDS() {
  return (strcmp(strErrDNA(DNA_INVALID_BOUNDS), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_ID() {
  return (strcmp(strErrDNA(DNA_INVALID_ID), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_INVALID_PARENTS() {
  return (strcmp(strErrDNA(DNA_INVALID_PARENTS), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_ELITISM() {
  return (strcmp(strErrDNA(DNA_NIL_ELITISM), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_PERCENT() {
  return (strcmp(strErrDNA(DNA_NIL_PERCENT), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_TRAITS() {
  return (strcmp(strErrDNA(DNA_NIL_TRAITS), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_SIZE() {
  return (strcmp(strErrDNA(DNA_NIL_SIZE), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_ID() {
  return (strcmp(strErrDNA(DNA_NIL_ID), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_FITNESS_INT() {
  return (strcmp(strErrDNA(DNA_NIL_FITNESS_INT), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_DNA() {
  return (strcmp(strErrDNA(DNA_NIL_DNA), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_FATHER() {
  return (strcmp(strErrDNA(DNA_NIL_FATHER), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_MOTHER() {
  return (strcmp(strErrDNA(DNA_NIL_MOTHER), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_CHILD() {
  return (strcmp(strErrDNA(DNA_NIL_CHILD), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_IDS() {
  return (strcmp(strErrDNA(DNA_NIL_IDS), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_STRAND() {
  return (strcmp(strErrDNA(DNA_NIL_STRAND), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_FITNESS() {
  return (strcmp(strErrDNA(DNA_NIL_FITNESS), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_LBOUND() {
  return (strcmp(strErrDNA(DNA_NIL_LBOUND), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_UBOUND() {
  return (strcmp(strErrDNA(DNA_NIL_UBOUND), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL_RATE() {
  return (strcmp(strErrDNA(DNA_NIL_RATE), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testStrErrDNA_NIL() {
  return (!strcmp(strErrDNA(DNA_NIL), "")) ? DNA_PASS : DNA_FAIL;
}

testResultDNA_t testMakeDNANilDna() {
  char *ids[3] = { "foo", "bar", "baz" };

  errDNA_t errDNA = makeDNA(NULL, ids, 3, 10);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testMakeDNANilIDs() {
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, NULL, 3, 10);
  return (errDNA != DNA_NIL_IDS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testMakeDNAInvalidStrands() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 0, 10);
  return (errDNA != DNA_INVALID_CHROMOSOMES) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testMakeDNAInvalidTraits() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 0);
  return (errDNA != DNA_INVALID_TRAITS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testMakeDNAValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  return (errDNA != DNA_NIL) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testFreeDNANilDNA() {
  errDNA_t errDNA = freeDNA(NULL);
  return (errDNA != DNA_NIL) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testFreeDNAValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = freeDNA(dna);
  return (errDNA != DNA_NIL) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetFitnessNilFitness() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setFitness(dna, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_FITNESS) ?  DNA_FAIL : DNA_PASS;
}

// simple fitness function just to test with
int testFitness(char *id, int strand[], int traits) {
  int total;
  for(total = 0; traits >= 0; total += strand[--traits]);
  return total;
}

testResultDNA_t testSetFitnessNilDNA() {
  errDNA_t errDNA = setFitness(NULL, testFitness);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetFitnessValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setFitness(dna, testFitness);

  freeDNA(dna);

  return (errDNA != DNA_NIL) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetFitnessNilDNA() {
  int fitness;
  
  errDNA_t errDNA = getFitness(NULL, "foo", &fitness);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetFitnessNilId() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int fitness;
  errDNA = getFitness(dna, NULL, &fitness);

  freeDNA(dna);

  return (errDNA != DNA_NIL_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetFitnessNilFitnessDest() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = getFitness(dna, "foo", NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_FITNESS_INT) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetFitnessNilFitness() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int fitness;
  errDNA = getFitness(dna, "foo", &fitness);

  freeDNA(dna);

  return (errDNA != DNA_NIL_FITNESS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetFitnessInvalidId() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setFitness(dna, testFitness);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int fitness;
  errDNA = getFitness(dna, "foobarber", &fitness);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetFitnessValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setFitness(dna, testFitness);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int fitness = 10;
  errDNA = getFitness(dna, "foo", &fitness);

  freeDNA(dna);

  return (errDNA != DNA_NIL || fitness) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetMutationNilDNA() {
  errDNA_t errDNA = setMutation(NULL, 0, 10, 0.0);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetMutationInvalidBounds() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setMutation(dna, 10, 5, 0.0);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_BOUNDS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetMutationInvalidRate() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setMutation(dna, 1, 5, 1000.0);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_RATE) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetMutationValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setMutation(dna, 0, 50, 0.0);

  freeDNA(dna);

  return (errDNA != DNA_NIL) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetMutationNilDNA() {
  int lbound, ubound;
  float rate;

  errDNA_t errDNA = getMutation(NULL, &lbound, &ubound, &rate);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetMutationNilLowerBound() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int ubound;
  float rate;

  errDNA = getMutation(dna, NULL, &ubound, &rate);

  freeDNA(dna);

  return (errDNA != DNA_NIL_LBOUND) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetMutationNilUpperBound() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int lbound;
  float rate;

  errDNA = getMutation(dna, &lbound, NULL, &rate);

  freeDNA(dna);

  return (errDNA != DNA_NIL_UBOUND) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetMutationNilRate() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int lbound, ubound;

  errDNA = getMutation(dna, &lbound, &ubound, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_RATE) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetMutationValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int lbound, ubound;
  float rate;

  lbound = ubound = 10;
  rate = 10.0;
  errDNA = getMutation(dna, &lbound, &ubound, &rate);

  freeDNA(dna);

  return (errDNA != DNA_NIL || ubound || lbound || rate != 0.0) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetElitismNilDNA() {
  errDNA_t errDNA = setElitism(NULL, 0, 0.0);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetElitismInvalidElitism() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setElitism(dna, 2, 0.0);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_ELITISM) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetElitismInvalidPercent() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setElitism(dna, 1, -1.0);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_PERCENT) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetElitismValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setElitism(dna, 1, 11.0);

  freeDNA(dna);

  return (errDNA != DNA_NIL) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetElitismNilDNA() {
  int elitism;
  float percent;

  errDNA_t errDNA = getElitism(NULL, &elitism, &percent);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetElitismNilElitism() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  float percent;

  errDNA = getElitism(dna, NULL, &percent);

  freeDNA(dna);

  return (errDNA != DNA_NIL_ELITISM) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetElitismNilPercent() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int elitism;

  errDNA = getElitism(dna, &elitism, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_PERCENT) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetElitismValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 10);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int elitism = 10;
  float percent = 10.0;

  errDNA = getElitism(dna, &elitism, &percent);

  freeDNA(dna);

  return (errDNA != DNA_NIL || elitism || percent != 0.0) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetStrandNilDNA() {
  int strand[5] = {0, 1, 2, 3, 4};

  errDNA_t errDNA = setStrand(NULL, "foo", strand, 5);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetStrandNilID() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strand[5] = {0, 1, 2, 3, 4};

  errDNA = setStrand(dna, NULL, strand, 5);

  freeDNA(dna);

  return (errDNA != DNA_NIL_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetStrandNilStrand() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setStrand(dna, "foo", NULL, 5);

  freeDNA(dna);

  return (errDNA != DNA_NIL_STRAND) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetStrandInvalidTraits() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strand[5] = {0, 1, 2, 3, 4};

  errDNA = setStrand(dna, "foo", strand, 6);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_TRAITS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetStrandInvalidID() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strand[5] = {0, 1, 2, 3, 4};

  errDNA = setStrand(dna, "foobarber", strand, 5);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testSetStrandValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strand[5] = {0, 1, 2, 3, 4};

  errDNA = setStrand(dna, "foo", strand, 5);

  freeDNA(dna);

  return (errDNA != DNA_NIL) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetStrandNilDNA() {
  char id[3] = "foo";
  int traits = 5;
  int strand[5] = {0, 0, 0, 0, 0};

  errDNA_t errDNA = getStrand(NULL, id, strand, &traits);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetStrandNilID() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits = 5;
  int strand[5] = {0, 0, 0, 0, 0};

  errDNA = getStrand(dna, NULL, strand, &traits);

  freeDNA(dna);

  return (errDNA != DNA_NIL_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetStrandNilStrand() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits = 5;

  errDNA = getStrand(dna, "foo", NULL, &traits);

  freeDNA(dna);

  return (errDNA != DNA_NIL_STRAND) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetStrandNilTraits() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strand[5] = {0, 0, 0, 0, 0};

  errDNA = getStrand(dna, "foo", strand, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_TRAITS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetStrandInvalidId() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits = 5;
  int strand[5] = {0, 0, 0, 0, 0};

  errDNA = getStrand(dna, "\0\0\0", strand, &traits);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetStrandValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits = 10;
  int strand[5] = {0, 0, 0, 0, 0};

  errDNA = getStrand(dna, "foo", strand, &traits);
  if(errDNA != DNA_NIL || traits != 5) { return DNA_FAIL; }

  for(; traits; traits--) { if(strand[traits-1]) { return DNA_FAIL; } }

  freeDNA(dna);

  return DNA_PASS;
}

testResultDNA_t testGetChromosomesNilDNA() {
  int strands, traits;

  errDNA_t errDNA = getChromosomes(NULL, &strands, &traits);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetChromosomesNilStrand() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits;

  errDNA = getChromosomes(dna, NULL, &traits);

  freeDNA(dna);

  return (errDNA != DNA_NIL_STRAND) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetChromosomesNilTraits() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strands;

  errDNA = getChromosomes(dna, &strands, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_TRAITS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetChromosomesValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strands, traits;
  strands = traits = 0;

  errDNA = getChromosomes(dna, &strands, &traits);

  freeDNA(dna);

  return (errDNA != DNA_NIL || strands != 3 || traits != 5) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetIDsNilDNA() {
  char *ids[3];

  errDNA_t errDNA = getIDs(NULL, ids);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetIDsNilIDs() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = getIDs(dna, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_IDS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testGetIDsValid() {
  char *ids[3] = { "bar", "baz", "foo" }; // strcmp ordered
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  char *ids_cpy[3];
  int i;
  for(i = 0; i < 3; i++) {
    // instead of = "---", since strcpy cannot handle mutating constant strings
    ids_cpy[i] = malloc(sizeof(char) * 4);
  }

  errDNA = getIDs(dna, ids_cpy);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }
  if(strcmp(ids[0], ids_cpy[0])) { return DNA_FAIL; }
  if(strcmp(ids[1], ids_cpy[1])) { return DNA_FAIL; }
  if(strcmp(ids[2], ids_cpy[2])) { return DNA_FAIL; }

  freeDNA(dna);

  return DNA_PASS;
}

testResultDNA_t testCrossoverNilDNA() {
  int traits;
  int child[5];

  errDNA_t errDNA = crossover(NULL, "father", "mother", child, &traits);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testCrossoverNilFather() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits;
  int child[5];

  errDNA = crossover(dna, NULL, "mother", child, &traits);

  freeDNA(dna);

  return (errDNA != DNA_NIL_FATHER) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testCrossoverNilMother() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits;
  int child[5];
  
  errDNA = crossover(dna, "father", NULL, child, &traits);

  freeDNA(dna);

  return (errDNA != DNA_NIL_MOTHER) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testCrossoverNilChild() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits;
  
  errDNA = crossover(dna, "father", "mother", NULL, &traits);

  freeDNA(dna);

  return (errDNA != DNA_NIL_CHILD) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testCrossoverNilTraits() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int child[5];
  
  errDNA = crossover(dna, "father", "mother", child, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_TRAITS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testCrossoverInvalidID() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits;
  int child[5];
  
  errDNA = crossover(dna, "father", "mother", child, &traits);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testCrossoverInvalidParents() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits;
  int child[5];
  
  errDNA = crossover(dna, "foo", "foo", child, &traits);

  freeDNA(dna);

  return (errDNA != DNA_INVALID_PARENTS) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testCrossoverValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 15);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strand1[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  errDNA = setStrand(dna, "foo", strand1, 15);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int strand2[15] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  errDNA = setStrand(dna, "bar", strand2, 15);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits = 10;
  int child[15];
  
  errDNA = crossover(dna, "foo", "bar", child, &traits);
  if(errDNA != DNA_NIL || traits != 15) { return DNA_FAIL; }

  int i, sum; 
  for(i = sum = 0; i < traits; sum += child[i++]);
  // NOTE: small chance of false failure here. basically want to make sure we
  // got traits from both parents.
  if(!sum || sum == 15) { return DNA_FAIL; }

  freeDNA(dna);
  
  return DNA_PASS;
}

testResultDNA_t testMutateNilDNA() {
  errDNA_t errDNA = mutate(NULL, "foo");
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testMutateNilID() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = mutate(dna, NULL);

  freeDNA(dna);

  return (errDNA != DNA_NIL_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testMutateInvalidID() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = mutate(dna, "foobarber");

  freeDNA(dna);

  return (errDNA != DNA_INVALID_ID) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testMutateValid() {
  char *ids[3] = { "foo", "bar", "baz" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 3, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }


  errDNA = setMutation(dna, 1, 100, 100.0);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = mutate(dna, "foo");
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  int traits;
  int strand[5];

  errDNA = getStrand(dna, "foo", strand, &traits);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  for(; traits; traits--) { if(!strand[traits-1]) { return DNA_FAIL; } }

  freeDNA(dna);

  return DNA_PASS;
}

testResultDNA_t testNextGenerationNilDNA() {
  errDNA_t errDNA = nextGeneration(NULL);
  return (errDNA != DNA_NIL_DNA) ?  DNA_FAIL : DNA_PASS;
}

testResultDNA_t testNextGenerationValid() {
  char *ids[4] = { "foo", "bar", "baz", "jim" };
  dna_t *dna;

  errDNA_t errDNA = makeDNA(&dna, ids, 4, 5);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setFitness(dna, testFitness);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setMutation(dna, 1, 2, 100.0);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = setElitism(dna, 1, 25.0);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }

  errDNA = nextGeneration(dna);
  if(errDNA != DNA_NIL) { return DNA_FAIL; }
  
  int traits;
  int foo[5];
  int bar[5];
  int baz[5];
  int jim[5];

  errDNA = getStrand(dna, "foo", foo, &traits);
  if(errDNA != DNA_NIL || traits != 5) { return DNA_FAIL; }

  errDNA = getStrand(dna, "bar", bar, &traits);
  if(errDNA != DNA_NIL || traits != 5) { return DNA_FAIL; }

  errDNA = getStrand(dna, "baz", baz, &traits);
  if(errDNA != DNA_NIL || traits != 5) { return DNA_FAIL; }

  errDNA = getStrand(dna, "jim", jim, &traits);
  if(errDNA != DNA_NIL || traits != 5) { return DNA_FAIL; }

  // 1 should be all 0's and 3, all 1's and 2's
  int i, zeros;
  zeros = 0;
  if(foo[0]) {
    for(i = 0; i < traits; i++) { if(!foo[i]) { return DNA_FAIL; } }
  } else {
    for(i = 0; i < traits; i++) { if(foo[i]) { return DNA_FAIL; } }
    zeros++;
  }
  if(bar[0]) {
    for(i = 0; i < traits; i++) { if(!bar[i]) { return DNA_FAIL; } }
  } else {
    for(i = 0; i < traits; i++) { if(bar[i]) { return DNA_FAIL; } }
    zeros++;
  }
  if(baz[0]) {
    for(i = 0; i < traits; i++) { if(!baz[i]) { return DNA_FAIL; } }
  } else {
    for(i = 0; i < traits; i++) { if(baz[i]) { return DNA_FAIL; } }
    zeros++;
  }
  if(jim[0]) {
    for(i = 0; i < traits; i++) { if(!jim[i]) { return DNA_FAIL; } }
  } else {
    for(i = 0; i < traits; i++) { if(jim[i]) { return DNA_FAIL; } }
    zeros++;
  }

  if(zeros != 1) { return DNA_FAIL; }

  freeDNA(dna);

  return DNA_PASS;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testStrErrDNA_OUT_OF_MEMORY,       "testStrErrDNA_OUT_OF_MEMORY"          },
  { testStrErrDNA_INVALID_PERCENT,     "testStrErrDNA_INVALID_PERCENT"        },
  { testStrErrDNA_INVALID_CHROMOSOMES, "testStrErrDNA_INVALID_CHROMOSOMES"    },
  { testStrErrDNA_INVALID_TRAITS,      "testStrErrDNA_INVALID_TRAITS"         },
  { testStrErrDNA_INVALID_ELITISM,     "testStrErrDNA_INVALID_ELITISM"        },
  { testStrErrDNA_INVALID_RATE,        "testStrErrDNA_INVALID_RATE"           },
  { testStrErrDNA_INVALID_BOUNDS,      "testStrErrDNA_INVALID_BOUNDS"         },
  { testStrErrDNA_INVALID_ID,          "testStrErrDNA_INVALID_ID"             },
  { testStrErrDNA_INVALID_PARENTS,     "testStrErrDNA_INVALID_PARENTS"        },
  { testStrErrDNA_NIL_ELITISM,         "testStrErrDNA_NIL_ELITISM"            },
  { testStrErrDNA_NIL_PERCENT,         "testStrErrDNA_NIL_PERCENT"            },
  { testStrErrDNA_NIL_TRAITS,          "testStrErrDNA_NIL_TRAITS"             },
  { testStrErrDNA_NIL_SIZE,            "testStrErrDNA_NIL_SIZE"               },
  { testStrErrDNA_NIL_ID,              "testStrErrDNA_NIL_ID"                 },
  { testStrErrDNA_NIL_FITNESS_INT,     "testStrErrDNA_NIL_FITNESS_INT"        },
  { testStrErrDNA_NIL_DNA,             "testStrErrDNA_NIL_DNA"                },
  { testStrErrDNA_NIL_FATHER,          "testStrErrDNA_NIL_FATHER"             },
  { testStrErrDNA_NIL_MOTHER,          "testStrErrDNA_NIL_MOTHER"             },
  { testStrErrDNA_NIL_CHILD,           "testStrErrDNA_NIL_CHILD"              },
  { testStrErrDNA_NIL_IDS,             "testStrErrDNA_NIL_IDS"                },
  { testStrErrDNA_NIL_STRAND,          "testStrErrDNA_NIL_STRAND"             },
  { testStrErrDNA_NIL_FITNESS,         "testStrErrDNA_NIL_FITNESS"            },
  { testStrErrDNA_NIL_LBOUND,          "testStrErrDNA_NIL_LBOUND"             },
  { testStrErrDNA_NIL_UBOUND,          "testStrErrDNA_NIL_UBOUND"             },
  { testStrErrDNA_NIL_RATE,            "testStrErrDNA_NIL_RATE"               },
  { testStrErrDNA_NIL,                 "testStrErrDNA_NIL"                    },
  { testMakeDNANilDna,                 "testMakeDNANilDna"                    }, 
  { testMakeDNANilIDs,                 "testMakeDNANilIDs"                    }, 
  { testMakeDNAInvalidStrands,         "testMakeDNAInvalidStrands"            }, 
  { testMakeDNAInvalidTraits,          "testMakeDNAInvalidTraits"             }, 
  { testMakeDNAValid,                  "testMakeDNAValid"                     }, 
  { testFreeDNANilDNA,                 "testFreeDNANilDNA"                    }, 
  { testFreeDNAValid,                  "testFreeDNAValid"                     }, 
  { testSetFitnessNilFitness,          "testSetFitnessNilFitness"             }, 
  { testSetFitnessNilDNA,              "testSetFitnessNilDNA"                 }, 
  { testSetFitnessValid,               "testSetFitnessValid"                  }, 
  { testGetFitnessNilDNA,              "testGetFitnessNilDNA"                 }, 
  { testGetFitnessNilId,               "testGetFitnessNilId"                  }, 
  { testGetFitnessNilFitnessDest,      "testGetFitnessNilFitnessDest"         }, 
  { testGetFitnessNilFitness,          "testGetFitnessNilFitness"             }, 
  { testGetFitnessInvalidId,           "testGetFitnessInvalidId"              }, 
  { testGetFitnessValid,               "testGetFitnessValid"                  }, 
  { testSetMutationNilDNA,             "testSetMutationNilDNA"                },
  { testSetMutationInvalidBounds,      "testSetMutationInvalidBounds"         },
  { testSetMutationInvalidRate,        "testSetMutationInvalidRate"           },
  { testSetMutationValid,              "testSetMutationValid"                 },
  { testGetMutationNilDNA,             "testGetMutationNilDNA"                },
  { testGetMutationNilLowerBound,      "testGetMutationNilLowerBound"         },
  { testGetMutationNilUpperBound,      "testGetMutationNilUpperBound"         },
  { testGetMutationNilRate,            "testGetMutationNilRate"               },
  { testGetMutationValid,              "testGetMutationValid"                 },
  { testSetElitismNilDNA,              "testSetElitismNilDNA"                 },
  { testSetElitismInvalidElitism,      "testSetElitismInvalidElitism"         },
  { testSetElitismInvalidPercent,      "testSetElitismInvalidPercent"         },
  { testSetElitismValid,               "testSetElitismValid"                  },
  { testGetElitismNilDNA,              "testGetElitismNilDNA"                 },
  { testGetElitismNilElitism,          "testGetElitismNilElitism"             },
  { testGetElitismNilPercent,          "testGetElitismNilPercent"             },
  { testGetElitismValid,               "testGetElitismValid"                  },
  { testSetStrandNilDNA,               "testSetStrandNilDNA"                  },
  { testSetStrandNilID,                "testSetStrandNilID"                   },
  { testSetStrandNilStrand,            "testSetStrandNilStrand"               },
  { testSetStrandInvalidTraits,        "testSetStrandInvalidTraits"           },
  { testSetStrandInvalidID,            "testSetStrandInvalidID"               },
  { testSetStrandValid,                "testSetStrandValid"                   },
  { testGetStrandNilDNA,               "testGetStrandNilDNA"                  },
  { testGetStrandNilID,                "testGetStrandNilID"                   },
  { testGetStrandNilStrand,            "testGetStrandNilStrand"               },
  { testGetStrandNilTraits,            "testGetStrandNilTraits"               },
  { testGetStrandInvalidId,            "testGetStrandInvalidId"               },
  { testGetStrandValid,                "testGetStrandValid"                   },
  { testGetChromosomesNilDNA,          "testGetChromosomesNilDNA"             },
  { testGetChromosomesNilStrand,       "testGetChromosomesNilStrand"          },
  { testGetChromosomesNilTraits,       "testGetChromosomesNilTraits"          },
  { testGetChromosomesValid,           "testGetChromosomesValid"              },
  { testGetIDsNilDNA,                  "testGetIDsNilDNA"                     },
  { testGetIDsNilIDs,                  "testGetIDsNilIDs"                     },
  { testGetIDsValid,                   "testGetIDsValid"                      },
  { testCrossoverNilDNA,               "testCrossoverNilDNA"                  },
  { testCrossoverNilFather,            "testCrossoverNilFather"               },
  { testCrossoverNilMother,            "testCrossoverNilMother"               },
  { testCrossoverNilChild,             "testCrossoverNilChild"                },
  { testCrossoverNilTraits,            "testCrossoverNilTraits"               },
  { testCrossoverInvalidID,            "testCrossoverInvalidID"               },
  { testCrossoverInvalidParents,       "testCrossoverInvalidParents"          },
  { testCrossoverValid,                "testCrossoverValid"                   },
  { testMutateNilDNA,                  "testMutateNilDNA"                     },
  { testMutateNilID,                   "testMutateNilID"                      },
  { testMutateInvalidID,               "testMutateInvalidID"                  },
  { testMutateValid,                   "testMutateValid"                      },
  { testNextGenerationNilDNA,          "testNextGenerationNilDNA"             },
  { testNextGenerationValid,           "testNextGenerationValid"              }
};

int main() {

  srand(time(NULL));

  testResultDNA_t result;
  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    result = ((testResultDNA_t (*)(void))(TESTS[test][0]))();
    if(result == DNA_PASS) {
      passes++;
      fprintf(stdout, "PASS: %s\n", (char *)TESTS[test][1]);
    } else {
      fprintf(stdout, "FAIL: %s\n", (char *)TESTS[test][1]);
      fails++;
    }
    fflush(stdout); // so if segfault/crash we know last successful test
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
