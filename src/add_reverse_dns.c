#include "externs.h"
void add_reverse_dns(char *tgt) {
char newname[MAX_FIELDNAME_LENGTH];
char newval[MAX_FIELDVALUE_LENGTH];
static char previous_newval[MAX_FIELDVALUE_LENGTH];
char stored_val[MAX_FIELDVALUE_LENGTH];
static char previous_stored_val[MAX_FIELDVALUE_LENGTH];
int target_count;
struct in_addr ip;
struct hostent *hp;

        if (_drop==1) return;
        if(_field_count>=MAX_FIELD_COUNT) {
                fprintf(stderr,"add_reverse_dns : MAX_FIELD_COUNT exceeded. Field will not be added\n"); 
                return;
        }
	target_count=0;
	build_target_list(tgt);
	while(target_count<tlist.count) {
		// ***********************************************
		// Create the new fieldname
		// **********************************************
                strcpy(newname,tlist.name[target_count]);
                strcat(newname,".rdns");
		// *****************************************************
		// If the new fieldname is going to be too long, just
		// write an error message and return.
		// Note: This just discards all other fields in tlist.
		// Subsequent fieldnames can only get longer!
		// *****************************************************
		if(strlen(newname)>=MAX_FIELDNAME_LENGTH) {
			fprintf(stderr,"add_reverse_dns : Can not add new fieldname (%s) as it is too long\n",newname);
			return;
		}
		strcpy(stored_val,_fieldvalues_array[tlist.position[target_count]]);
		(void) remchars("\"",stored_val);
		if(strcmp(stored_val,previous_stored_val)==0) {
                	insert_new_field(newname,previous_newval);
		}
		else {
		strcpy(previous_stored_val,stored_val);
		// **************************************
		// If the field value can't be converted
		// (Not a valid IP address)
		// *************************************
		if (!inet_aton(stored_val, &ip)) {
			newval[0]='\0';
			previous_newval[0]='\0';
			insert_new_field(newname,newval);
		}
		else {
			// *********************************************
			// IP converted to an int okay. Try and get a
			// reverse dns entry for it.
			// *********************************************
    			if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) == NULL) {
				// ************************************
				// No reverse dns entry. Stick in an
				// empty value
				// ************************************
				newval[0]='\0';
				previous_newval[0]='\0';
				insert_new_field(newname,newval);
    			}
			else {
				// ***********************************************
				// Got there in the end. Stick the rdns value in
				// ***********************************************
				strcpy(newval,hp->h_name);
				strcpy(previous_newval, newval);
				insert_new_field(newname,newval);
			}
		}
		}
		target_count++;
	}
}
