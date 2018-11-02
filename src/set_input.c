#include "externs.h"
void set_input(char delim, char *fnames) {
size_t pos=0, len=0,flen=0,spos=0;
int found=0;
	len=strlen(fnames);
	_field_delimiter=delim;
	for(pos=0;pos<len;pos++) {
		if(_input_file_count >= MAX_INPUT_FILE_COUNT-1) {
			fprintf(stderr,"Maximum input file count exceeded(%d). Aborting\n",MAX_INPUT_FILE_COUNT);
			exit(EXIT_FAILURE);
		}
		if(fnames[pos]==' ' || fnames[pos] == ',' || fnames[pos]=='\t' || fnames[pos]=='\n')  {
			if(found== 1) {  
				flen=pos-spos;
				memset(_input_file_names[_input_file_count],0x0,MAX_FILENAME_LENGTH);
				strncpy(_input_file_names[_input_file_count], &fnames[spos],flen);
				_input_file_count++;
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
	if(found==1) {
		flen=pos-spos;
		memset(_input_file_names[_input_file_count],0x0,MAX_FILENAME_LENGTH);
		strncpy(_input_file_names[_input_file_count], &fnames[spos],flen);
		_input_file_count++;
	}
	return;
}
