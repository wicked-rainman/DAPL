#include "externs.h"
void draw_path(char *names) {
char output_list[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
char from_str[MAX_FIELDNAME_LENGTH];
char to_str[MAX_FIELDNAME_LENGTH];
int x,ctr,found=0,field_count;
size_t y;
	if(_drop==1) return;
	field_count=array_from_string(names,output_list);
	for(ctr=0;ctr<field_count;ctr++) {
		x=find_fieldname(output_list[ctr]);
		if(x>=0) {
			y=strlen(_fieldvalues_array[x]);
			if(y>0) {
				if(found==0) {
					strcpy(from_str,_fieldnames_array[x]);
					found=1;
				}
				else {
					strcpy(to_str,_fieldnames_array[x]);
					found=2;
				}
			}
		}
		if(found==2) {
			draw_node(from_str,to_str);
			strcpy(from_str,to_str);
			found=1;
		}
	}
}
