#include "externs.h"
void remove_string(char *fieldname, char *substring) {
int k,l;
size_t end_pos,start_pos,mainstring_length;
char newstring[MAX_FIELDVALUE_LENGTH];
	if(_drop==1) return;
	k=find_fieldname(fieldname);
	if(k>=0) {
		mainstring_length=strlen(_fieldvalues_array[k]);
		l=strpos(_fieldvalues_array[k],substring);
		if(l >= 0) {
			start_pos= (size_t) l;
			end_pos=start_pos+strlen(substring);
			newstring[0]='\0';
			strncat(newstring,_fieldvalues_array[k],start_pos);
			strncat(newstring,&_fieldvalues_array[k][end_pos], mainstring_length-end_pos);
			strcpy(_fieldvalues_array[k],newstring);
		}
	}
	
}
