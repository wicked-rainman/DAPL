#include "externs.h"
int extract_field_values() {
int found=0, x;
size_t pos=0, len=0, flen=0,spos=0;
int field_count;
	field_count=0;
        len=strlen(_input_line);
	for(pos=0;pos<len;pos++) {
		if(_input_line[pos]==_field_delimiter) {
			if(found == 1) {

                                if(field_count>= MAX_FIELD_COUNT-1) {
                                        fprintf(stderr,"extract_field_values: Maximum field count exceeded. Limit is %d\n", MAX_FIELD_COUNT);
                                        exit(EXIT_FAILURE);
                                }

				flen=pos-spos;
				if(flen>MAX_FIELDVALUE_LENGTH-1) {
					fprintf(stderr,"extract_field_values: A field value in the input line is too long and will be truncated\n"); 
					fprintf(stderr,"extract_field_values: Field name=%s\n", _fieldnames_array[field_count]);
					fprintf(stderr,"extract_field_values: Line=\"%s\"\n",_input_line); 
					flen=MAX_FIELDVALUE_LENGTH-1;
				}
				_fieldvalues_array[field_count][0]='\0';
				if(_input_line[spos]!='"') strcpy(_fieldvalues_array[field_count],"\"");
				strncat(_fieldvalues_array[field_count], &_input_line[spos],flen);
				x=strlen(_fieldvalues_array[field_count]);
				if(_fieldvalues_array[field_count][x-1]!='"') strcat(_fieldvalues_array[field_count],"\"");
				//fprintf(stdout,"%s[%s]\n",_fieldnames_array[field_count],_fieldvalues_array[field_count]);
				field_count++;
				found=0;
			}
			else {
                                _fieldvalues_array[field_count][0]='\0';
				field_count++;
			}
		}
		else {
			if(found == 0) {
				spos=pos;
				found=1;
				if(_input_line[pos]=='"') {
					pos++;
					while((pos<len) && (_input_line[pos]!='"')) {
						pos++;
					}
				}
			}
		}
	}
	if(found==1) {
		flen=pos-spos;
                if(flen>MAX_FIELDVALUE_LENGTH-1) {
                	fprintf(stderr,"extract_field_values: A field value in the input line is too long and will be truncated\n");
                        fprintf(stderr,"extract_field_values: Field name=%s\n", _fieldnames_array[field_count]);
                        fprintf(stderr,"extract_field_values: Line=\"%s\"\n",_input_line);
			flen=MAX_FIELDVALUE_LENGTH-1;
                }

		_fieldvalues_array[field_count][0]='\0';
		if(_input_line[spos]!='"') strcpy(_fieldvalues_array[field_count],"\"");
	        strncat(_fieldvalues_array[field_count], &_input_line[spos],flen);
		x=strlen(_fieldvalues_array[field_count]);
                if(_fieldvalues_array[field_count][x-1]!='"') strcat(_fieldvalues_array[field_count],"\"");
		//fprintf(stdout,"[%d] %s[%s]\n",field_count,_fieldnames_array[field_count],_fieldvalues_array[field_count]);
		field_count++;
	}
	return(EXIT_FAILURE);
}
