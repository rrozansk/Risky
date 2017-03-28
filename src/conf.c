/*******************************************************************************

    F I L E   I N F O R M A T I O N

*******************************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 3/27/17
 Edited:  3/27/17
*/

/*******************************************************************************

    I N C L U D E S

*******************************************************************************/
#include <conf.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************

    F U N C T I O N S

*******************************************************************************/
// [over]write a conf file reflecting the current games configuration
int writeConf(conf_t *conf, char *fname) {
  FILE *fp = fopen(fname, "w+"); // w+ overwrite files
  if(!fp) { 
    sprintf(conf->err, "error! failure to open conf file: %s, exiting...\n", fname); 
    return 1;
  }

  fprintf(fp,
   "# type := int (0-8)\n"
   "# keys:\n"
   "#   - human:    [number of human players]\n"
   "#   - computer: [number of computer players]\n"
   "[Players]\n"
   "human:%d\n"
   "computer:%d\n\n"
   
   "# type := bool (0/1)\n"
   "# keys:\n"
   "#   - regions: [randomly distribute the regions among the players]\n"
   "#   - armies:  [randomly distribute armies among the players regions]\n"
   "[Random]\n"
   "regions:%d\n"
   "armies:%d\n\n"
   
   "# type := char[10]\n"
   "# keys:\n"
   "#   - ATTR1:  [description]\n"
   "#   - ATTR2:  [description]\n"
   "#   - ATTR3:  [description]\n"
   "#   - ATTR4:  [description]\n"
   "#   - ATTR5:  [description]\n"
   "#   - ATTR6:  [description]\n"
   "#   - ATTR7:  [description]\n"
   "#   - ATTR8:  [description]\n"
   "#   - ATTR9:  [description]\n"
   "#   - ATTR10: [description]\n"
   "[Chromosomes]\n",
    conf->hp, conf->cp, conf->randRegion, conf->randArmies);

  int c, i;
  for(c = 0; c < 8; c++) { // FIXME: const @CHROMOSOMES?
    fprintf(fp, "c%d:{", c);
    for(i = 0; i < 10; i++) { // FIXME: const @ATTRIBUTES?
      fprintf(fp, "%d", conf->chromosomes[c][i]);
      if(i < 9) { fprintf(fp, ","); }
    }
    fprintf(fp, "}\n");
  }

  if(fclose(fp)) {
    sprintf(conf->err, "error! failure to close conf file: %s, exiting...\n", fname);
    return 1;
  }

  return 0;
}

// read in and error check a conf file to configure the current game
int parseConf(conf_t *conf, char *fname) {
  FILE *fp = fopen(fname, "r"); // r reads files
  if(!fp) { 
    sprintf(conf->err, "error! failure to open conf file: %s, exiting...\n", fname); 
    return 1;
  }

  char line[81]; // include str teminator
  while(fgets(line, 81, fp) != NULL) { // read until EOF
    //  # is line comment
    //  [headers]
    //  key:value pairs accepted under header
  }

  if(fclose(fp)) {
    sprintf(conf->err, "error! failure to close conf file: %s, exiting...\n", fname);
    return 1;
  }
    
  // error checking conf
  if(conf->hp < 0) {
    sprintf(conf->err, "error! invalid input (arg 1), expected 0-8, given: %d\n", conf->hp);
    return 1;
  }

  if(conf->cp < 0) {
    sprintf(conf->err, "error! invalid input (arg 2), expected 0-8, given: %d\n", conf->cp);
    return 1;
  }

  if(!conf->hp && !conf->cp) {
    sprintf(conf->err, "error! you cannot play a game with no players\n");
    return 1;
  }

  if(conf->hp + conf->cp > 8) {
    sprintf(conf->err, "error! you cannot have more than 8 players in a single game\n");
    return 1;
  }

  if(!(conf->randRegion == 0 || conf->randRegion == 1)) {
    sprintf(conf->err, "error! invalid input (arg 3), expected 0-1, given: %d\n", conf->randRegion);
    return 1;
  }

  if(!(conf->randArmies == 0 || conf->randArmies== 1)) {
    sprintf(conf->err, "error! invalid input (arg 4), expected 0-1, given: %d\n", conf->randArmies);
    return 1;
  }

  return 0;
}
