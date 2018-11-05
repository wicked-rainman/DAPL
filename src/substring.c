#include "externs.h"
int substring(char* fieldname, char* substring) {
int start_pos,target_count;
	if(_drop==1) return(0);
	target_count=0;
	build_target_list(fieldname);
	while(target_count< tlist.count) {
		//fprintf(stdout,"substring : Searching for %s in %s\n",substring,_fieldvalues_array[tlist.position[target_count]]);
                start_pos=strpos(_fieldvalues_array[tlist.position[target_count]],substring);
                if(start_pos>=0)  {
			//fprintf(stdout,"substring : Found %s\n",substring);
			return(1);
		}
		target_count++;
	}
	return(0);	
}
