#include "externs.h"
void add_substring(char *tgt, char *addfld, int start, int end) {
int target_count;
int x,endpos;
char newval[MAX_FIELDVALUE_LENGTH];
char newname[MAX_FIELDNAME_LENGTH];
	if(_drop==1) return;
	if(end < start ) {
		fprintf(stderr,"add_substring : Start position(%d) is after end position(%d)\n",start,end);
		exit(EXIT_FAILURE);
	}
	build_target_list(tgt);
	target_count=0;
	while(target_count<tlist.count) {
		strcpy(newname,tlist.name[target_count]);
		strcat(newname,".");
		if(strlen(newname)+strlen(addfld)>MAX_FIELDNAME_LENGTH) {
			fprintf(stderr,"add_substring : %s%s exceeds maximum field name lenght\n",
				newname,addfld);
			return;
		}
		strcat(newname,addfld);
		x=strlen(_fieldvalues_array[tlist.position[target_count]]);
		if(end>x) end=x;
		endpos=(end-start)+1;
		strncpy(newval,&_fieldvalues_array[tlist.position[target_count]][start],endpos);
		newval[endpos]='\0';
		insert_new_field(newname,newval);
		target_count++;
	}
}
