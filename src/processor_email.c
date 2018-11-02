#define DEBUG 1
#include "core.h"

// *********************************************************
// This is the main email processor routine. 
// It acts as a wrapper for user level code, which must
// appear as "setup()" and "loop()" code..
// The user code is fed by the repeated calls to import_eml
// Nothing much to see here....
// **********************************************************
int main() {
int count;
	// ****************************************************
	//Initialise storage (including the bunch of globals)
	// ****************************************************
	init_storage();
	//Run the user level setup code
	setup();
	//Read all the input files defined by the user 
	while (_files_processed < _input_file_count) {
		// ************************************
		//Process each file... Each one must
		//just contain a single email
		// ************************************
		(void) import_eml(_input_file_names[_files_processed]);
		_files_processed++;
		// ************************************
		//If the file processed okay, _field_count
		//will be set
		// ************************************
		if(_field_count>0) {
			// ************************************
			// Do the user loop process
			// ************************************
			loop();
               		count=0;
        		while(count<_field_count) {
                                _fieldnames_array[count][0]='\0';
                                _fieldvalues_array[count][0]='\0';
                                _fieldlabels_array[count][0]='\0';
                                _fieldattribs_array[count][0]='\0';
				_fieldcomps_array[count][0]='\0';
				count++;
        		}
                	_field_count=0;
                	_drop=0;
                }
		else {
			fprintf(stderr,"processor_email : Failed to process file \"%s\"\n",_input_file_names[_files_processed]);
		}
	}
	//All done. Clean up the mess and finish. 
	cleanup();
	fprintf(stderr,"Processed %d files, dropped %d records and wrote %d\n", 
		_files_processed,_drop_count,_output_lines_written);
	return(EXIT_SUCCESS);
}
