#include "externs.h"
void unix_time(char *tgt,  char *format) {
time_t t;
struct tm lt;
char res[32];
int target_count;
char newname[MAX_FIELDNAME_LENGTH];
char buffer[MAX_FIELDVALUE_LENGTH];
char newval[2];
	if(_drop==1) return;
	build_target_list(tgt);
	target_count=0;
	while(target_count<tlist.count) {
                strcpy(newname,tlist.name[target_count]);
		if((strlen(newname)+6)>MAX_FIELDNAME_LENGTH) {
			fprintf(stderr,"unix_time : Fieldname %s.udtg exceeds length MAX_FIELDNAME_LENGTH\n",newname);
			exit(EXIT_FAILURE);
		}
                strcat(newname,".udtg");
                strcpy(buffer,_fieldvalues_array[tlist.position[target_count]]);
                (void)remchars("\"",buffer);
        	t = (time_t) atoi(buffer);
        	(void) localtime_r(&t, &lt);
        	if (strftime(res, sizeof(res), format, &lt) == 0) {
			newval[0]='\0';
			insert_new_field(newname,newval);
		}
		else {
			insert_new_field(newname,res);
		}
		target_count++;
        }
        return;
}
