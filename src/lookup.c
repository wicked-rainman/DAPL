#include "externs.h"
int lookup(FILE *table,char* fieldname,char* newfield) {
int v,match=0;
size_t t,u,w;
int target_count,found,chars_found;
char new_field[MAX_FIELDNAME_LENGTH];
char new_value[MAX_FIELDVALUE_LENGTH];
char search_str[MAX_FIELDVALUE_LENGTH];
char line[500];
	if(_drop==1) return 0;
	if(table==NULL) {
		fprintf(stderr,"lookup : Cannot lookup %s to add %s as the table file has not been defined\n",fieldname,newfield);
		exit(EXIT_FAILURE);
	}
	build_target_list(fieldname);
	target_count=0;
	//
	// While targets are left to process
	//
	while(target_count < tlist.count) {
		rewind(table);
		//
		//  Extract the field value that we are going to look for
		//
		strcpy(search_str,_fieldvalues_array[tlist.position[target_count]]);
		(void)remchars("\"",search_str);
		w=strlen(search_str);
		found=0;
		if(w>0) {
			rewind(table);
			chars_found=0;
			new_field[0]='\0';
			new_value[0]='\0';
			//
			// While lines in the file are left to compare
			//
			while(fgets(line,500,table)) {
				v=strncmp(line,search_str,w);
				//
				// Match found, starting in column 1
				//
				if(v==0) {
					found=1;
					match=1;
					u=strlen(line);
					//
					// pass over the match, and extract what follows spaces or tabs
					//
					for(t=w;t<u;t++) {
						if(line[t]!=' ' && line[t]!='\t') {
							strcpy(new_value, &line[t]);
							new_value[strlen(new_value)-1]='\0';
							break;
						}
					}
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
