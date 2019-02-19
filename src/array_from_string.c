//
//
// This function needs to be converted to produce a chain of fields rather than an array
//
//
#include "externs.h"
int array_from_string(char *source, char dest[][MAX_FIELDNAME_LENGTH]) {
char source_str[MAX_INPUT_LINE_LENGTH];
int x, output_ctr;
char *pch;
	x=(int)strlen(source); 
	if(x>MAX_INPUT_LINE_LENGTH) {
		fprintf(stderr,"array_from_string: Your list of fieldnames is greater than MAX_INPUT_LINE_LENGTH (>%d)\n",MAX_INPUT_LINE_LENGTH);
		exit(EXIT_FAILURE);
	}
	output_ctr=0;
      strcpy(source_str,source);
        pch=strtok(source_str," ,\t\n");
        while((pch !=NULL) && (output_ctr<MAX_FIELD_COUNT)) {
		if(strlen(pch)>MAX_FIELDNAME_LENGTH) {
			fprintf(stderr,"Field \"%s\" exceeds MAX_FIELDNAME_LENGTH (%d>%d)\n", pch, (int) strlen(pch),MAX_FIELDNAME_LENGTH);
			exit(EXIT_FAILURE);
		}
              strcpy(dest[output_ctr],pch);
                pch=strtok(NULL," ,\t\n");
                output_ctr++;
	}
	if(output_ctr==MAX_FIELD_COUNT) {
		fprintf(stderr, "array_from_string: WARNING Maximum field count reached. %d fields extracted.\n",output_ctr);
	}
	return(output_ctr);
}
