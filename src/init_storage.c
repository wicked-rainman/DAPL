#include "externs.h"
void init_storage() {
int k;

	_render[0]='\0';
	_graph_engine[0]='\0';
	_files_processed=0;
	_drop_count=0;
	//Initialise storage used by global_clean (The raw input line cleaner)
	memset(_remstring,0x0,MAX_REMSTR_LENGTH);
	//Initialise the arrays used for storing fieldname value pairs.
	for(k=0;k<MAX_FIELD_COUNT;k++) {
		memset(_fieldnames_array[k],0,MAX_FIELDNAME_LENGTH);
		memset(_fieldvalues_array[k],0,MAX_FIELDVALUE_LENGTH);
		memset(_fieldlabels_array[k],0,MAX_INPUT_LINE_LENGTH);
		memset(_fieldattribs_array[k],0,MAX_ATTRIB_LENGTH);
	}
	//Initialise csv start definition tag value
		memcpy(_csv_definition_start,"#Fields:",8);
		_csv_definition_start[8]=0x0;
		_csv_definition_start_length=8;

	//Initialise storage for holding input filenames in
	for(k=0;k<MAX_INPUT_FILE_COUNT;k++) {
		memset(_input_file_names[k],0,MAX_FILENAME_LENGTH);
	}
}
