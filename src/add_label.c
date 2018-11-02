#include "externs.h"
void add_label(char* tgt, char* addfld) {
int v,w,x,y,z;
int field_count;
int added=0;
int target_count;
char output_list[MAX_FIELD_COUNT][MAX_FIELDNAME_LENGTH];
char temp_str[MAX_FIELDVALUE_LENGTH];
	if (_drop==1) return;
	build_target_list(tgt);
	target_count=0;
	while(target_count<tlist.count) {
		w=tlist.position[target_count];
		field_count=array_from_string(addfld,output_list);
		x=0;
		strcpy(_fieldlabels_array[w],"\"");
		while(x<field_count) {
			if(output_list[x][0]=='*') {
				if(strlen(output_list[x])==1) {
					strcpy(output_list[x],tlist.name[target_count]);
				}
				else {
					strcpy(temp_str,tlist.name[target_count]);
					strcat(temp_str,&output_list[x][1]);
					strcpy(output_list[x],temp_str);
				}
			}
			y=find_fieldname(output_list[x]);
			if(y>=0) {
				z=strlen(_fieldlabels_array[w]);
				v=strlen(_fieldvalues_array[y]);
				if(v>0) {
					if((z+v+2)<MAX_LABEL_LENGTH) {
						temp_str[0]='\0';
						strcpy(temp_str,_fieldvalues_array[y]);
						remchars("\"", temp_str);
						strcat(_fieldlabels_array[w],temp_str);
						strcat(_fieldlabels_array[w],"\\n");
						added=1;
					}	
					else {
						strcat(_fieldlabels_array[w],"\"");
						fprintf(stderr,"add_label : Not adding \"%s\" as a label to field \"%s\" as it will make it oversized\n",output_list[x],_fieldnames_array[w]);
						return;
					}	
				}
			}
			x++;
		}
		if(added==1) {
			x=strlen(_fieldlabels_array[w]);
			if(x>3) _fieldlabels_array[w][x-2]='\0';
		}
		strcat(_fieldlabels_array[w],"\"");
		target_count++;
	}
}
