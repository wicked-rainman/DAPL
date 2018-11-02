#include "externs.h"
void define_csv_tag(char *tag) {
size_t length;
	length=strlen(tag);
	if(length> CSV_MAX_TAG_LENGTH ) {
		fprintf(stderr,"define_csv_tag: String must be less than %d long\n", CSV_MAX_TAG_LENGTH);
			exit(EXIT_FAILURE);
	}
	memcpy(_csv_definition_start, tag, length);
	_csv_definition_start[length]='\0';
	_csv_definition_start_length=length;
	fprintf(stdout,"define_csv_tag : Tag set to \"%s\"\n",_csv_definition_start);
}
