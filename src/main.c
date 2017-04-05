/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 4/4/17
 Edited:  4/4/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <ini.h>
#include <risky.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  fprintf(stdout, "Risky\nv1.0\nRyan Rozanski\n\n");

  if(argc != 2) {
    fprintf(stderr, "error! must specify a conf file, exiting...\n");
    exit(EXIT_FAILURE);  
  }

  ini_t *ini;
  const char *err = readINI(&ini, argv[1]);
  if(err) {
    fprintf(stderr, "error! failure to parse conf\nirritant: %s\nexiting...\n", err);
    exit(EXIT_FAILURE);
  }

  risk(ini);

  char *isTraining = getINI(ini, "Gameplay", "training");
  if(isTraining && !strcmp(isTraining, "1")) { 
    if(writeINI(ini, argv[1])) {  
      fprintf(stderr, "error! failure to write conf to file");
    }
  }

  freeINI(ini);

  exit(EXIT_SUCCESS);
}
