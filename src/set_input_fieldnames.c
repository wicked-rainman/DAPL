#include "externs.h"
int set_input_fieldnames() {
size_t pos=0, len=0,flen=0,spos=0;
int found=0,k=0;

	_field_count=0;
        len=strlen(_input_line);
	//Loop through the line extracting fieldnames. Start after the #Fields string.
        for(pos= (size_t) _csv_definition_start_length;pos<len;pos++) {
                if(_input_line[pos]==' ' || _input_line[pos] == ',') {
                        if(found== 1) {
				if(_field_count>= MAX_FIELD_COUNT-1) {
					fprintf(stderr,"set_input_fieldnames: Maximum field count exceeded. Limit is %d\n",
						MAX_FIELD_COUNT);
					exit(EXIT_FAILURE);
				}
                                flen=pos-spos;
				if(flen>=MAX_FIELDNAME_LENGTH) {
					fprintf(stderr,"set_input_fieldnames: Fieldname maximum length(%d) exceeded\n",MAX_FIELDNAME_LENGTH);
					exit(EXIT_FAILURE);
				}
				memset(_fieldnames_array[_field_count],0x0,MAX_FIELDNAME_LENGTH);
                                memcpy(_fieldnames_array[_field_count], &_input_line[spos],flen);
				_fieldnames_array[_field_count][flen]=(char)0x0;
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
                	fprintf(stderr,"set_input_fieldnames: Fieldname maximum length(%d) exceeded\n",MAX_FIELDNAME_LENGTH);
                	exit(EXIT_FAILURE);
                }

		memset(_fieldnames_array[_field_count],0x0,MAX_FIELDNAME_LENGTH);
                memcpy(_fieldnames_array[_field_count], &_input_line[spos],flen);
		_fieldnames_array[_field_count][flen]=(char)0x0;
                _field_count++;
        }
	_restore_field_count=_field_count;
        fprintf(stderr,
	"File %s defines %d field names:",_input_file_names[_files_processed],_field_count);
	for(k=0;k<_field_count;k++)  {
                strcpy(_restore_fieldnames[k],_fieldnames_array[k]);
		fprintf(stderr," \"%s\"", _fieldnames_array[k]);
	}
	fprintf(stderr,"\n");
	return(EXIT_SUCCESS);
}
