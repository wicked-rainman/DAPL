#include "externs.h"
void remove_chars(char *fieldname, char* dels) {
size_t buflen,delcount,k,l;
char outstr[MAX_FIELDVALUE_LENGTH];
int n,x,found;
	if(_drop==1) return;
	x=find_fieldname(fieldname);
	if(x>=0) {
        	buflen = strlen(_fieldvalues_array[x]);
		if(buflen>3) { //Two quotes min, plus one char....
			buflen--; //Value should be in quotes!!
			delcount=strlen(dels);
        		n = 0;
			found=0;
        		for(k=1;k<buflen;k++) {
				for(l=0;l<delcount;l++) {
                			if(_fieldvalues_array[x][k] == dels[l]) {
						found=1;
						break;
					}
				}
				if(found==0) {
					outstr[n]=_fieldvalues_array[x][k];
					n++;
				}
				found=0;
			}
        		outstr[n]=(char)0x0;
			strcpy(_fieldvalues_array[x],"\"");
        		strcat(_fieldvalues_array[x],outstr);
			strcat(_fieldvalues_array[x],"\"");
		}
        	return;
	}
}
