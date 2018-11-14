#include "externs.h"
int match(char* fieldname, char* substring) {
int start_pos,target_count;
char haystack[MAX_FIELDVALUE_LENGTH];
        if(_drop==1) return(0);
	build_target_list(fieldname);
	target_count=0;
	while(target_count< tlist.count) {
		strcpy(haystack,_fieldvalues_array[tlist.position[target_count]]);
		remchars("\"",haystack);		
                start_pos=strcmp(haystack,substring);
                if(start_pos==0)  return 1;
		target_count++;
	}
	return(0);
}
