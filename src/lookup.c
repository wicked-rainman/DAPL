#include "externs.h"
int lookup(FILE *table,char* fieldname,char* newfield) {
int v,match=0;
size_t t,u,w;
int target_count,found,chars_found;
char new_field[MAX_FIELDNAME_LENGTH];
char new_value[MAX_FIELDVALUE_LENGTH];
char needle[MAX_FIELDVALUE_LENGTH];
char line[500];
char *sptr;
	if(_drop==1) return 0;
	if(table==NULL) {
		fprintf(stderr,"lookup : Cannot lookup %s to add %s as the table file has not been defined\n",fieldname,newfield);
		exit(EXIT_FAILURE);
	}
	build_target_list(fieldname);
	target_count=0;
	while(target_count < tlist.count) {
		found=0;
		if(strlen(_fieldvalues_array[tlist.position[target_count]])>0) {
			rewind(table);
			chars_found=0;
			new_field[0]='\0';
			new_value[0]='\0';
			//
			// While lines in the file are left to compare
			//
			while(fgets(line,500,table)) {
				w=strlen(line);
				t=0;
				while((t<w) && (line[t]!=' ') && (line[t]!='\t')) {
					needle[t]=line[t];
					t++;
				}
				needle[t]='\0';
				while((t<w) && (line[t]==' ' || line[t]=='\t')) t++;
				v=0;
				while(t<w) {
					new_value[v]=line[t];
					v++;
					t++;
				}
				new_value[v-1]='\0';
				sptr=strstr(_fieldvalues_array[tlist.position[target_count]],needle);
				//
				// Match found
				//
				if(sptr!=NULL) {
					found=1;
					match=1;
					u=strlen(line);
                                        if(newfield[0]!='*') {
                                        	strcpy(new_field,newfield);
                                        }
					else {
                                               	strcpy(new_field,_fieldnames_array[tlist.position[target_count]]);
                                              	strcat(new_field,&newfield[1]);
                                        }
					//fprintf(stdout,"lookup : adding [%s] %s\n",new_field,new_value);
                                        insert_new_field(new_field,new_value);
					break;
				}
			} //EOF
		} //Not empty search string
                if(found==0) {
                       	// Add a blank result.
                        new_value[0]='\0';
                       	if(newfield[0]!='*') strcpy(new_field,newfield);
                       	else {
                               	strcpy(new_field,_fieldnames_array[tlist.position[target_count]]);
                               	strcat(new_field,&newfield[1]);
                       	}
                       	//fprintf(stdout,"lookup : adding [%s] %s\n",new_field,new_value);
                       	insert_new_field(new_field,new_value);
                }
		target_count++;
	}
	return match;
}
