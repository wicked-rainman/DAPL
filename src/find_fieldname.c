#include "externs.h"
int find_fieldname(char* fieldname) {
int k=0;
	if(_drop==1) return(-1);
	for(k=0;k<_field_count;k++) {
		if(strcmp(_fieldnames_array[k],fieldname)==0) return(k);
	}
        return(-1);
}
