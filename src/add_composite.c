#include "externs.h"
void add_composite(char* tgt, char* addfld) {
int v,w,x,y,z;
int field_count,target_count;
char output_list[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
char temp_str[MAX_FIELDVALUE_LENGTH];
	if (_drop==1) return;
	target_count=0;
	build_target_list(tgt);
	while(target_count<tlist.count) {
		w=tlist.position[target_count];	
		field_count=array_from_string(addfld,output_list);
		x=0;
		strcpy(_fieldcomps_array[w],"\"");
		strcpy(temp_str,_fieldvalues_array[w]);
		(void) remchars("\"",temp_str);
		strcat(_fieldcomps_array[w],temp_str);
		strcat(_fieldcomps_array[w],"|");
		while(x<field_count) {
			y=find_fieldname(output_list[x]);
			if(y>=0) {
				z= (int) strlen(_fieldcomps_array[w]);
				v= (int) strlen(_fieldvalues_array[y]);
				if((z+v+2)<MAX_COMPOSITE_LENGTH) {
					temp_str[0]='\0';
					strcpy(temp_str,_fieldvalues_array[y]);
					(void) remchars("\"", temp_str);
					strcat(_fieldcomps_array[w],temp_str);
					strcat(_fieldcomps_array[w],"|");
				}	
				else {
					strcat(_fieldcomps_array[w],"\"");
					fprintf(stderr,"add_composite : Not adding \"%s\" as composite to field \"%s\". %d bytes + %d bytes would make it longer than MAX_COMPOSITE_LENGTH (%d).\n",output_list[x],_fieldnames_array[w],z,v,MAX_COMPOSITE_LENGTH);
					return;
				}	
			}
			x++;
		}
		_fieldcomps_array[w][strlen(_fieldcomps_array[w])-1]='\0';
		strcat(_fieldcomps_array[w],"\"");
		target_count++;
	}
}
