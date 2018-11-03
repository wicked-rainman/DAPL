#define DEBUG 0
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <regex.h>
#include <dirent.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "defaults.h"
typedef struct  {
        char name[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
	int position[MAX_FIELD_COUNT];
        int count;
} _target_list;
extern _target_list tlist;
#include "funcs.h"
#include "macros.h"
extern char _output_field_list[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
extern int _output_field_count;
extern int _output_fields_defined;
extern int _output_lines_written;
extern int _input_file_count; 
extern int _files_processed;
extern int _fieldnames_count;
extern int _lines_processed;
extern int _lines_rejected;
extern int _input_files_processed;
extern int _drop;
extern int _drop_count;
extern char _input_file_names[MAX_INPUT_FILE_COUNT][MAX_FILENAME_LENGTH];
extern char _fieldnames_array[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
extern char _fieldvalues_array[MAX_FIELD_COUNT][MAX_FIELDVALUE_LENGTH];
extern char _fieldlabels_array[MAX_FIELD_COUNT][MAX_INPUT_LINE_LENGTH];
extern char _fieldattribs_array[MAX_FIELD_COUNT][MAX_ATTRIB_LENGTH];
extern char _fieldcomps_array[MAX_FIELD_COUNT][MAX_FIELDVALUE_LENGTH];
extern char _restore_fieldnames[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
extern int _field_count;
extern int _restore_field_count;
extern char _csv_definition_start[12];
extern char *outfile_name;
extern char _remstring[MAX_REMSTR_LENGTH];
extern char*_input_line;
extern char _field_delimiter;
extern char error_message[500];
extern char _graph_engine[20];
extern char _render[20];
extern FILE *_ifile;
extern FILE *_ofile;
extern FILE *_dfile;
extern FILE *_asnfile;
extern FILE *_countryfile;
extern size_t _input_line_length;
extern int _asn_sockfd;
extern int _country_sockfd;
extern size_t _csv_definition_start_length;
extern int _pseudo_rand_number;
