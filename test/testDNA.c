/******************************************************************************
 * FILE:    testDNA.c                                                         *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 6/3/17                                                            *
 * EDITED:  6/17/17                                                           *
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
#define TOTAL_TESTS 39

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultDNA { DNA_PASS, DNA_FAIL } testResultDNA_t;

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

testResultDNA_t testStrErrDNA_INVALID_IDS() {
  return (strcmp(strErrDNA(DNA_INVALID_IDS), "")) ? DNA_PASS : DNA_FAIL;
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

// simple fitness function just to test with
int testFitness(char *id, int *strand, int traits) {
  int total;
  for(total = 0; traits; total += strand[--traits]);
  return total;
}

testResultDNA_t testMakeNilDNA() {
  return DNA_FAIL;
}

testResultDNA_t testMakeDNA() {
  dna_t *dna;
  char *ids[STRANDS] = { "id1", "id2", "id3" };

  errDNA_t errDNA = DNA_NIL;
  if((errDNA = makeDNA(&dna, ids, STRANDS, TRAITS)) != DNA_NIL) {
  }
 
  int strands, traits;
  if((errDNA = getChromosomes(dna, &strands, &traits)) != DNA_NIL) {
  }

  if(strands != STRANDS) {
  }

  if(traits != TRAITS) {
  }

  return DNA_PASS;
}

testResultDNA_t testFreeNilDNA() {
  //errDNA_t freeDNA(dna_t *dna);
  return DNA_FAIL;
}

testResultDNA_t testFreeDNA() {
  //errDNA_t freeDNA(dna_t *dna);
  return DNA_FAIL;
}

testResultDNA_t testFitnessDNA() {
//errDNA_t setFitness(dna_t *dna, int (*fitness)(char *id, int *strand, int traits));
  //errDNA_t getFitness(dna_t *dna, char *id, int *fitness);
  return DNA_FAIL;
}

testResultDNA_t testMutationDNA() {
  //errDNA_t setMutation(dna_t *dna, int lbound, int ubound, double rate);
  //errDNA_t getMutation(dna_t *dna, int *lbound, int *ubound, double *rate);
  return DNA_FAIL;
}

testResultDNA_t testElitismDNA() {
  //errDNA_t setElitism(dna_t *dna, int elitism, double percent);
  //errDNA_t getElitism(dna_t *dna, int *elitism, double *percent);
  return DNA_FAIL;
}

testResultDNA_t testStrandDNA() {
  //errDNA_t setStrand(dna_t *dna, char *id, int *strand, int traits);
  //errDNA_t getStrand(dna_t *dna, char *id, int *strand, int *traits);
  return DNA_FAIL;
}

testResultDNA_t testChromosomesDNA() {
  //errDNA_t getChromosomes(dna_t *dna, int *strands, int *traits) {
  return DNA_FAIL;
}

testResultDNA_t testIDsDNA() {
  //errDNA_t getIDs(dna_t *dna, char ids[][36]);
  return DNA_FAIL;
}

testResultDNA_t testCrossoverDNA() {
  //errDNA_t crossover(dna_t *dna, char *father, char *mother, int *child, int *traits);
  return DNA_FAIL;
}

testResultDNA_t testMutateDNA() {
  //errDNA_t mutate(dna_t *dna, char *id);
  return DNA_FAIL;
}

testResultDNA_t testNextGenDNA() {
  //errDNA_t nextGeneration(dna_t *dna);
  return DNA_FAIL;
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
  { testStrErrDNA_INVALID_IDS,         "testStrErrDNA_INVALID_IDS"            },
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
  { testMakeDNA,                       "testMakeDNA"                          },
  { testMakeNilDNA,                    "testMakeNilDNA"                       },
  { testFreeNilDNA,                    "testFreeNilDNA"                       },
  { testFreeDNA,                       "testFreeDNA"                          },
  { testFitnessDNA,                    "testFitnessDNA"                       },
  { testMutationDNA,                   "testMutationDNA"                      },
  { testElitismDNA,                    "testElitismDNA"                       },
  { testStrandDNA,                     "testStrandDNA"                        },
  { testChromosomesDNA,                "testChromosomesDNA"                   },
  { testIDsDNA,                        "testIDsDNA"                           },
  { testCrossoverDNA,                  "testCrossoverDNA"                     },
  { testMutateDNA,                     "testMutateDNA"                        },
  { testNextGenDNA,                    "testNextGenDNA"                       },
};

int main() {

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
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}
