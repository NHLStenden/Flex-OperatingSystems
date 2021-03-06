/***
  Dit programma laat zien hoe je eenvoudig input van STDIN of een bestand kunt lezen en voorzien van een regelnummer. Het regelnummer
  en de bestandsnaam geven we nu netjes op via de command-line options methode van Linux.
  
  Om dit programma te starten via Bash:
  
  user@host:~/programs$ addnumber -f mysourcefile -n 10
  user@host:~/programs$ addnumber < mysourcefile -n 33
  user@host:~/programs$ addnumber < mysourcefile
  user@host:~/programs$ addnumber -?

***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc,  char * const *argv){
  char *buffer = NULL;
  size_t len;
  ssize_t read;
  long linenumber; 
  FILE * fp;
  int opt;
  
  /* Set default values */
  fp = stdin;    /* Default input from Standard In (channel 0) */
  linenumber = 1;/* Default value for start of linenumber */

  /* Cycle through all command line parameters to override default values */
  while ((opt = getopt(argc, argv, "f:n:?")) != -1) {
	  switch (opt) {
		  case 'f':
		    fp = fopen(optarg, "r");
		    if (fp == NULL) {
			fprintf(stderr,"Cannot open file %s\n", optarg);
                        exit(EXIT_FAILURE);
                    }
		    break;
		  case 'n':
                    fprintf(stderr,"%s\n" , optarg);
		    linenumber = atoi(optarg);
		    break;
                 case '?':
		 default: /* '?' */
			fprintf(stderr, "Usage: %s [-f filename] [-n startnumber] \n",
			argv[0]);
			exit(EXIT_FAILURE);}
		  
  }/* switch */

  while ((read = getline(&buffer, &len, fp) != -1)){
    printf("%04d:%s" , linenumber++, buffer);
  }/*while*/

  free(buffer);

  if (fp != stdin) fclose(fp);

}/* main */
