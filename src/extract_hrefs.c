#include "externs.h"
void extract_hrefs(char *fieldname) {
int k;
int spos=0;
int len;
char *p;
char haystack[MAX_FIELDVALUE_LENGTH];
char url[MAX_FIELDVALUE_LENGTH];
char fname[MAX_FIELDNAME_LENGTH];
	if(_drop==1) return;
	k=find_fieldname(fieldname);
	if(k<0) return;
	strcpy(fname,fieldname);
	strcat(fname,".hrefs");
	strcpy(haystack,_fieldvalues_array[k]);
	len=strlen(haystack);
	url[0]='\0';
	p=strstr(haystack,"href=");
	k=0;
	if(p!=NULL) {
		spos=p-haystack;
		spos+=5;
	}
	while(p!=NULL) {
		while((haystack[spos]==' ') && (spos<len)) {
			spos++;
		}
		for(k=spos;k<len;k++) {
			if((haystack[k]=='>') || (haystack[k]==' ')) {
				strncpy(url, &haystack[spos],(k-spos));
				url[k-spos]='\0';
				insert_new_field("text.url",url);
				url[0]='\0';
				k++;
				break;
			}
		}
		p=strstr(&haystack[k],"href=");
		if(p!=NULL) {
			spos=p-&haystack[k]+k;
			spos+=5;
		}
		
	}
}
