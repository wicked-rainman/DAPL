#include "core.h"
int main() {
int count=0;
	init_storage();
	setup();
	while (get_input_lines()==1) {
		if(find_field_defs()) set_input_fieldnames();
		if(_input_line[0]!='#') {
			if(_field_count>0) {
				if(strlen(_remstring)>0) input_clean(_remstring);
				if(extract_field_values()==1) {
					loop();
					if(_drop==1) _drop_count++;
					count=0;
					_drop=0;
				        while(count<_field_count) {
                                		_fieldvalues_array[count][0]='\0';
                                		_fieldlabels_array[count][0]='\0';
                                		_fieldattribs_array[count][0]='\0';
						_fieldcomps_array[count][0]='\0';
                                		count++;
                        		}
					count=0;
					_field_count=_restore_field_count;
					for(count=0;count<_field_count;count++) {
						strcpy(_fieldnames_array[count],_restore_fieldnames[count]);
					}
				}
			}
			//No fieldnames defined for this line, so ignore it.
			else {
				
				fprintf(stderr,"%s:Ignored \"%s\" No field definitions\n",_input_file_names[_files_processed], _input_line);
			}
		}
	}
	//All done. Clean up the mess and finish. 
	cleanup();
	fprintf(stderr,"Processed %d files. Read %d lines, rejected %d, dropped %d and written %d\n", 
		_input_files_processed, _lines_processed,_lines_rejected,_drop_count,_output_lines_written);
	return(EXIT_SUCCESS);
}
