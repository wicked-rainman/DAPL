#include "externs.h"
void add_field(char* tgt, char* addfld) {
	if (_drop==1) return;
	if(_field_count>=MAX_FIELD_COUNT) {
		fprintf(stderr,"add_field : MAX_FIELD_COUNT exceeded. Field will not be added\n"); 
		return;
	}
	if(strlen(tgt)>=MAX_FIELDNAME_LENGTH) {
		fprintf(stderr,"add_field : Fieldname %s is too long\n", tgt);
		return;
	}
	if(strlen(addfld)>=MAX_FIELDVALUE_LENGTH) {
               fprintf(stderr,"add_field : Fieldname %s is too long\n", tgt);
               return;
	}
	if (find_fieldname(tgt)<0) {
		strcpy(_fieldnames_array[_field_count], tgt);
		strcpy(_fieldvalues_array[_field_count],"\"");
		strcat(_fieldvalues_array[_field_count],addfld);
		strcat(_fieldvalues_array[_field_count],"\"");
		_field_count++;
	}
	else {
		fprintf(stderr,"add_field : Field \"%s\" already exists. You've got something wrong. Fix it\n",tgt);
		fprintf(stderr,"add_field : This is an un-recoverable error so quitting\n");
		exit(EXIT_FAILURE);
	}
}
