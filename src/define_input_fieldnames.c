#include "externs.h"
void define_input_fieldnames(char dlm, char *fdefs) {
size_t pos=0, len=0,flen=0,spos=0;
int found=0,k=0;
	_field_count=0;
        len=strlen(fdefs);
	_field_delimiter=dlm;
	//Loop through the line extracting fieldnames. Start after the #Fields string.
        for(pos=0;pos<len;pos++) {
                if(fdefs[pos]==' ' || fdefs[pos] == ',') {
                        if(found== 1) {
                                flen=pos-spos;
                                if(flen>=MAX_FIELDNAME_LENGTH) {
                                        fprintf(stderr,"define_input_fieldnames: Fieldname maximum length(%d) exceeded\n",MAX_FIELDNAME_LENGTH);
                                        exit(EXIT_FAILURE);
                                }

				memset(_fieldnames_array[_field_count],0x0,MAX_FIELDNAME_LENGTH);
                                strncpy(_fieldnames_array[_field_count], &fdefs[spos],flen);
                                _field_count++;
                                found=0;
                        }
                }
                else {
                        if(found == 0) {
                                spos=pos;
                                found = 1;
                        }
                }
        }
	//End of the line, so deal with any last field.
        if(found==1) {
                flen=pos-spos;
                if(flen>=MAX_FIELDNAME_LENGTH) {
                 	fprintf(stderr,"define_input_fieldnames: Fieldname maximum length(%d) exceeded\n",MAX_FIELDNAME_LENGTH);
                	exit(EXIT_FAILURE);
                }

		memset(_fieldnames_array[_field_count],0x0,MAX_FIELDNAME_LENGTH);
                strncpy(_fieldnames_array[_field_count], &fdefs[spos],flen);
                _field_count++;
        }
	_restore_field_count=_field_count;
        fprintf(stderr, "defined_input_fieldnames: Found %d ",_field_count);
	for(k=0;k<_field_count;k++) {
		strcpy(_restore_fieldnames[k],_fieldnames_array[k]);
		fprintf(stderr," \"%s\" ", _fieldnames_array[k]);
	}	
	fprintf(stderr,"\n");
	return;
}
