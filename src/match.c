#include "externs.h"
int match(char* fieldname, char* substring) {
int start_pos,target_count;
char tmpstr[MAX_FIELDVALUE_LENGTH];
        if(_drop==1) return(0);
	tmpstr[0]='"';
	tmpstr[1]='\0';
	strcat(tmpstr,substring);
	strcat(tmpstr,"\"");
	build_target_list(fieldname);
	target_count=0;
	while(target_count< tlist.count) {
                start_pos=strcmp(_fieldvalues_array[tlist.position[target_count]],tmpstr);
                if(start_pos==0)  return 1;
		target_count++;
	}
	return(0);
}
