#include "externs.h"
// ***********************************************************************
// Function intip_lookup
//
// Parameters:
// tgt - A string. The target field in the global _fieldnames_array[]
// extension - A string. String get's appended to the target fieldname
//	when the new field is created.
// infile - A global file pointer to the file that will be searched through
// env_name - The environmental string that indicates what the search file
//	name is.
//
// This function replaces add_country() and add_asn(). They both performed
// the same actions, but against different search input files. Nobody
// likes to have to maintain two very similar functions when one slightly 
// larger one can do the same thing..........
//
// The target fieldname should have a fieldvalue that is an IP address.
// The function takes the IP address and converts it to an int.
// The search input file has three fields:
// Start_int,End_int,Some_string_value
// The ip INT is compared to the start_int on each line. If the ip INT
// is greater than this, a comparison is made to the end_int. If the end_int
// is smaller, then the IP address fits inside the range. The string value
// is then copied into the new target field, and the global _fieldnames_array
// and _fieldvalues_ array updated.
// The infile FILE * is returned by this function to be stored by the calling
// routine. This saves re-opening infile each time this function is called.
// 
// ***********************************************************************
FILE* intip_lookup(char *tgt, char *extension, FILE *infile, char *env_name) {
struct in_addr ip;
int n,target_count,found;
size_t buflen,k;
char line[500];
char start_str[50];
char end_str[50];
char out_str[100];
char *file_str;
char buffer[MAX_FIELDVALUE_LENGTH];
char newname[MAX_FIELDNAME_LENGTH];
long int stored_start=0;
long int stored_end=0;
uint32_t ip_int=0;
	if(_drop==1) return infile;
        if(infile==NULL) {
        	file_str=getenv(env_name);
                if(file_str==NULL) {
                	fprintf(stderr,"%s : No environment variable set\n",env_name);
                	exit(EXIT_FAILURE);
        	}
		fprintf(stdout,"%s : Using %s\n",env_name, file_str );
                infile = fopen(file_str,"r");
                // ********************************************
                // Can't open the file, then just bomb out
                // ********************************************
                if(infile==NULL)  {
                	fprintf(stderr,"%s : Could not open file \"%s\"\n",env_name, file_str);
                	exit(EXIT_FAILURE);
                }
        }

	target_count=0;
	// ********************************************************
	// A target fieldname can be wild-carded. This enables
	// multiple values to be stored for any one single filename
	// This is achieved by appending "_n" to a fieldname where
	// n= a one up number. Function build_target_list updates
	// a global structure (type tlist) that contains an array
	// of fieldnames, matched with an array of position indicators
	// that shows effectively each wildcarded fieldname and it's
	// position within the _fieldvalues_array _fieldnames_array
	// global structures. An overall count of found fieldnames
	// is returned.
	// ********************************************************
	build_target_list(tgt);
	// *************************************************
	// While fieldnames are left to process
	// *************************************************
	while(target_count<tlist.count) {
		// ******************************************************
		// Copy (what should be) the string IP address out of the
		// global _fieldvalues_array and try to convert it
		// ******************************************************
		strcpy(buffer,_fieldvalues_array[tlist.position[target_count]]);
        	(void)remchars("\"",buffer);
		if(inet_aton(buffer,&ip)) {
			// ********************************************
			// IP appears to be valid, convert it to an int
			// ********************************************
			ip_int=htonl(ip.s_addr);
			// *******************************************************
			// Rewind the ASN file and start reading lines from it
			// *******************************************************
			found=0;
			rewind(infile);
        		while(fgets(line, 500, infile)) {
                		buflen = strlen(line);
               			k=0;
				n=0;
				// *****************************************************
				// File has the format :
				// INT,INT,SOME_STRING
				// Extract the start and end int values
				// ******************************************************
                		while(line[k]!=',') {
                        		start_str[n] = line[k++];
					n++;
                		}
                		start_str[n] = (char) 0x00;
                		k++;
                		n = 0;
                		while(line[k] !=',') {
                        		end_str[n] = line[k++];
                        		n++;
                		}
                		end_str[n] = (char) 0x00;
                		k++;
                		stored_start = atol(start_str);
                		stored_end = atol(end_str);
				out_str[0]='\0';
				// ************************************************
				// If the IP address we've converted into an
				// int is greater than or equal to the start int
				// and is less than or equal to the end int, then
				// we have an range that matches
				// *************************************************
                		if((ip_int >= stored_start) && (ip_int <= stored_end)) {
                               		n = 0;
                                	while((k<buflen) && (line[k]!=',') && (line[k]!=' ')){
                                        	out_str[n] = line[k++];
                                        	n++;
                                	}
                                	out_str[n] = '\0';
                        		(void)remchars("\"",out_str);
					strcpy(newname,tlist.name[target_count]);
					strcat(newname,extension);
					// *****************************************
					// Add the new string into the global structure.
					// It will have a fieldname of:
					// xxxxx.extension
					// where xxxxx = the original target field
					// specified when the function was called
					// ******************************************
					insert_new_field(newname,out_str);
					found=1;
                        		break;
                		}
			}
			// *************************************************
			// Nothing found that matches. Add the new fieldname
			// in to the global array, but leave the fieldvalue
			// as null....
			// *************************************************
               		if(found==0) {
                        	strcpy(newname,tlist.name[target_count]);
                        	strcat(newname,extension);
				out_str[0]='\0';
                        	insert_new_field(newname,out_str);
                	}
		}
                else {
			// ****************************************************
			// The string didn't seem to be a valid IP address,
			// so just insert an empty value
			// ****************************************************
                        strcpy(newname,tlist.name[target_count]);
                        strcat(newname,extension);
			out_str[0]='\0';
                        insert_new_field(newname,out_str);
                }
		// **************************************************
		// Deal with the next fieldname in the target list
		// **************************************************
		target_count++;
	}
	return infile;
}
