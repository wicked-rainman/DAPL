#include "externs.h"
char *last_value(char *fieldname) {
int k;
	if(_drop==1) return NULL;
	build_target_list(fieldname);
	for(k=(tlist.count-1);k>0;k--) {
		if(strlen(_fieldvalues_array[tlist.position[k]])>0) {
			//fprintf(stdout,"LAST %s=%s\n",_fieldnames_array[tlist.position[k]],_fieldvalues_array[tlist.position[k]]);
			return _fieldnames_array[tlist.position[k]];
		}
	}
	return NULL;
} 
