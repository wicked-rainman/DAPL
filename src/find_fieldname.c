#include "externs.h"
int find_fieldname(char* fieldname) {
int k=0;
	if(_drop==1) return(-1);

	//while(k<_field_count) {
        //        if(strcmp(_fieldnames_array[k],fieldname)==0) return(k);
        //        k++;
        //}
	for(k=0;k<_field_count;k++) if(strcmp(_fieldnames_array[k],fieldname)==0) return(k);
        return(-1);
}
