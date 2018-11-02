#include "externs.h"
void set_output(char *fname) {
	_ofile=fopen(fname,"w");
        if(_ofile==NULL) {
        	fprintf(stdout,"set_output : Could not open file  \"%s\"\n",fname);
		exit(EXIT_FAILURE);
	}
}
