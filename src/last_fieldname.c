#include "externs.h"
char *last_fieldname(char *fieldname) {
	if(_drop==1) return NULL;
	build_target_list(fieldname);
	return tlist.name[tlist.count-1];
} 
