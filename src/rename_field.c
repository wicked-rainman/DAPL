#include "externs.h"
void rename_field(char* fieldname, char* newname) {
int y, z;
size_t v,w,x;
char new_name[MAX_FIELDNAME_LENGTH];
        if(_drop==1) return;
	w=strlen(fieldname);
	x=strlen(newname);
	if(x>=MAX_FIELDNAME_LENGTH) {
		fprintf(stderr,"rename_field : New fieldname is too long. Quitting\n");
		exit(EXIT_FAILURE);
	}
	for(y=0;y<_field_count;y++) {
		z=strpos(_fieldnames_array[y], fieldname);
		if(z==0) { //Matched at the begining of the fileld name!! Anchor to start of field name, not substring
			v=strlen(_fieldnames_array[y]);
			strcpy(new_name, newname);
			strncat(new_name,&_fieldnames_array[y][w],(v-w));
			strcpy(_fieldnames_array[y],new_name);
		}		
	}
}
