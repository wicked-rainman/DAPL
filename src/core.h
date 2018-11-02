#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <regex.h>
#include "defaults.h"
typedef struct  {
        char name[MAX_FIELD_COUNT][MAX_FIELDVALUE_LENGTH];
	int position[MAX_FIELD_COUNT];
        int count;
} _target_list;
_target_list tlist;
#include "funcs.h"
int _output_fields_defined=0;
int _output_field_count=0;
int _output_lines_written=0;
int _input_file_count=0; 
int _files_processed=0;
int _fieldvalues_count=0;
int _lines_processed=0;
int _lines_rejected=0;
int _input_files_processed=0;
int _drop=0;
int _drop_count=0;
size_t _csv_definition_start_length=0;
char _input_file_names[MAX_INPUT_FILE_COUNT][MAX_FILENAME_LENGTH];
//Start of base storage
char _fieldnames_array[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
char _fieldvalues_array[MAX_FIELD_COUNT][MAX_FIELDVALUE_LENGTH];
char _fieldattribs_array[MAX_FIELD_COUNT][MAX_ATTRIB_LENGTH];
char _fieldlabels_array[MAX_FIELD_COUNT][MAX_INPUT_LINE_LENGTH];
char _fieldcomps_array[MAX_FIELD_COUNT][MAX_FIELDVALUE_LENGTH];
char _restore_fieldnames[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
int _field_count=0;
int _restore_field_count=0;

//End of base storage
char _remstring[MAX_REMSTR_LENGTH];
char _render[20];
char _graph_engine[20];
char _output_field_list[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
char *outfile_name=NULL; 
char *_input_line=NULL;
char _field_delimiter;
char error_message[500];
char _csv_definition_start[CSV_MAX_TAG_LENGTH];
FILE *_ifile=NULL, *_ofile=NULL, *_dfile=NULL, *_asnfile=NULL,*_countryfile=NULL;
int _asn_sockfd=0;
int _country_sockfd;
size_t _input_line_length=0;
