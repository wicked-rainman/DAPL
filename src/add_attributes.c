#include "externs.h"
void add_attributes(char* tgt, char* attribs) {
int x,target_count=0;
size_t z;
	if(_drop==1) return;
	build_target_list(tgt);
	//fprintf(stdout,"Add_attr : Base=%s\n",tgt);
	while(target_count<tlist.count) {
		//fprintf(stdout,"add_attr : Expanded field %s\n",tlist.name[target_count]);
		x=tlist.position[target_count];
		z=strlen(attribs);
		if(z>MAX_ATTRIB_LENGTH) {
			fprintf(stderr,
				"add_attributes : Not adding \"%s\" as an attrib to field \"%s\" as the attributes are oversized (%zu>%d)\n",
				attribs,tlist.name[target_count],z,MAX_ATTRIB_LENGTH);
			return;
		}
		else strcpy(_fieldattribs_array[x],attribs);
		//fprintf(stdout,"[%s] Attribs=%s\n",_fieldnames_array[x],_fieldattribs_array[x]);
		target_count++;
	}
}
