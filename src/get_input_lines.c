#include "externs.h"
int get_input_lines() {
int count;
int nread;
	// While filenames are still available in the array for processing
	while (_files_processed < _input_file_count) {
		//If no file is opened, then we have to open one.
		if (_ifile == NULL) {
			fprintf(stderr,"Processing file \"%s\"\n",_input_file_names[_files_processed]);
			_ifile = fopen(_input_file_names[_files_processed],"r");
			//If we can't open the input file, then warn about it and carry on to the next file
			if(_ifile==NULL) {
				sprintf(error_message,"File %s",_input_file_names[_files_processed]);
				perror(error_message);
				_files_processed++;
			}
		}
		else {
			nread=getline(&_input_line,&_input_line_length,_ifile);
			if(nread<MAX_INPUT_LINE_LENGTH) {
				if(nread !=-1) {
					_input_line[nread-1]='\0';
					dedupe(_input_line,' ');
					_lines_processed++;
					count=0;
					//Null out the values storage array to wipe previous values
					while(_fieldvalues_array[count][0]!=(char)0x0) {
						_fieldvalues_array[count][0]=(char)0x0;
						count++;
					}
					return(EXIT_FAILURE);
				}
                        	//Must have come to EOF, so close the file so we can move on to the next one
                        	//(If there is still any to do)...
                        	else {
                                	(void) fclose(_ifile);
                                	_ifile = NULL;
                                	_files_processed++;
                        	}

			}
			else {
				fprintf(stderr,"get_input_lines: Rejected too long line (%d>%d). \"%s\"\n",
					 nread,MAX_INPUT_LINE_LENGTH,_input_line);
			}
		}
	}
	return (EXIT_SUCCESS);
}
