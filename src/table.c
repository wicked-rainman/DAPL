#include "externs.h"
FILE* table(char* fname) {
FILE *infile;
	infile=fopen(fname,"r");
	if(infile==NULL) {
		fprintf(stderr,"Could not open file \"%s\". Quitting!\n",fname);
		exit(EXIT_FAILURE);
	}
	return infile;
}
