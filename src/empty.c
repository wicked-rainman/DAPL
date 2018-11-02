#include "externs.h"
int empty(char* fieldname) {
int k;
        if(_drop==1) return(1);
	k=find_fieldname(fieldname);
 	if(k<0) return 1;
	if(strlen(_fieldvalues_array[k])>0) return 0;
	return 1;
}
