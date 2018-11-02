#include "externs.h" 
void add_concatenation(char *newfield, char *flds_str) {
char *pch;
char outstr[MAX_FIELDVALUE_LENGTH];
char fields_str[MAX_FIELDVALUE_LENGTH];
char field[MAX_FIELDVALUE_LENGTH];
size_t x,y;
int z;
	outstr[0]='\0';
	x=strlen(flds_str);
	if(x>MAX_FIELDVALUE_LENGTH) return;
	strcpy(fields_str,flds_str);
	outstr[0]='\0';
	pch=strtok(fields_str," ,\t");
	while(pch !=NULL) {
		if(pch[0]=='\'') {
			x=strlen(pch);
			if((x+strlen(outstr))>=MAX_FIELDVALUE_LENGTH) return;
			strncat(outstr,&pch[1],(strlen(pch)-2));
		}
		else {
			z=find_fieldname(pch);
			if(z>=0) {
				y=strlen(_fieldvalues_array[z]);
				if((y+strlen(outstr))>=MAX_FIELDVALUE_LENGTH) return;
				strcpy(field,_fieldvalues_array[z]);
				(void) remchars("\"",field);
				strcat(outstr,field);
			}
		}
		pch=strtok(NULL," ,\t");
	}
	add_field(newfield,outstr);
}
