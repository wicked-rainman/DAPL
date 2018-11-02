#include "externs.h"
void received_ip() {
int x,y,target_count;
char temp_str[MAX_FIELDVALUE_LENGTH];
char ip_str[50];
	// ******************************************
	//Build up a list of all the received fields
	// ******************************************
	build_target_list("Received*");
	target_count=0;
	// ******************************************
	//Loop through all the found fields
	// ******************************************
	while(target_count<tlist.count) {
		x=tlist.position[target_count];
		// ******************************************
		//Try and extract an IP address
		// ******************************************
		y=ipfind(_fieldvalues_array[x],ip_str);
		// ******************************************
		//Found a match, so insert it as a new field
		// ******************************************
		if(y>0) insert_new_field("Received*.ip",ip_str);
		// ******************************************
		//Didn't find a match. See if it's qmail, and 
		//if it is add qmail as a substitution for an IP
		// ******************************************
                else if(strpos(_fieldvalues_array[x],"(qmail")>=0) insert_new_field("Received*.ip","[Qmail]");
		// ******************************************
		//Couldn't find an IP so stuff a substring of 
		//the received line in, chopping it off after 
		//';' (Removes the trailing date)
		// ******************************************
		else { 
			temp_str[0]='\0';
                        strcpy(temp_str,_fieldvalues_array[x]);
                        (void) remchars("\"",temp_str);
                        y=strpos(temp_str,";"); //Should remove any trailing date field (Just makes the rubbish line a bit shorter!!)
                        if(y>0) {
                                temp_str[y]='\0';
                                insert_new_field("Received*.ip",temp_str);
                        }
			//It's a crap shoot. Just copy the received line in - Nothing better to do!!!
                        else insert_new_field("Received*.ip",temp_str);

		}
		target_count++;
	}
}
