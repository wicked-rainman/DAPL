#include "externs.h"
void add_quotes(char *fieldname) {
int k;
char newstr[MAX_FIELDVALUE_LENGTH];
size_t len;
	if(_drop==1) return;
	k=find_fieldname(fieldname);
	if(k>=0) {
		len=strlen(_fieldvalues_array[k]);
		if ((len+3)>=MAX_FIELDVALUE_LENGTH) {
			fprintf(stderr,"add_quotes: Can't add quotes round the value for \"%s\" as it will make it too long (%zu).\n",_fieldnames_array[k],len);
			return;
		}
		else {
			strcpy(newstr,"\"");
			strcat(newstr,_fieldvalues_array[k]);
			strcat(newstr,"\"");
			strcpy(_fieldvalues_array[k], newstr);
		}
	}
}
