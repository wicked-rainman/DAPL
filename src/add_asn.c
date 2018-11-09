#include "externs.h"
// ***********************************************************************
// Function add_asn                                                    
// Single parameter is a fieldname string, stored in _fieldnames_array[]
// Call made to function find_fieldname which returns the int position 
// at which the fieldname is located.
// Value for fieldname (stored in _fieldvalues_array[] with the same int
// position) is then extracted. This is expected to be an IP address.
// The IP address value is converted to an INT, which is used to locate
// the ASN number from within the ASN lookup file.
// ***********************************************************************
void add_asn(char *tgt) {
static FILE *_asnfile;
struct in_addr ip;
int n,target_count,found;
size_t buflen,k;
char line[500];
char start_str[50];
char end_str[50];
char asn_str[100];
static char previous_asn_str[100];
char *asn_file;
char buffer[MAX_FIELDVALUE_LENGTH];
static char previous_buffer[MAX_FIELDVALUE_LENGTH];
char newname[MAX_FIELDNAME_LENGTH];
long int stored_start=0;
long int stored_end=0;
uint32_t ip_int=0;
	if(_drop==1) return;
        if(_asnfile==NULL) {
        	asn_file=getenv("ASN_FILE");
		fprintf(stdout,"add_asn : Using file %s\n",asn_file);
                if(asn_file==NULL) {
                	fprintf(stderr,"add_asn : No ASN_FILE environment variable found\n");
                	exit(EXIT_FAILURE);
        	}
                _asnfile = fopen(asn_file,"r");
                // ********************************************
                // Can't open the file, then just bomb out
                // ********************************************
                if(_asnfile==NULL)  {
                	fprintf(stderr,"Could not open ASN file \"%s\"\n",ASN_FILE_NAME);
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
		strcpy(newname,tlist.name[target_count]);
		strcat(newname,".asn");
		strcpy(buffer,_fieldvalues_array[tlist.position[target_count]]);
        	(void)remchars("\"",buffer);
                if(strcmp(previous_buffer,buffer)==0) {
                        insert_new_field(newname,previous_asn_str);
                }
		else {
			strcpy(previous_buffer,buffer);
			if(inet_aton(buffer,&ip)) {
				// ********************************************
				// IP appears to be valid, convert it to an int
				// ********************************************
				ip_int=htonl(ip.s_addr);
				// *******************************************************
				// Rewind the ASN file and start reading lines from it
				// *******************************************************
				found=0;
				rewind(_asnfile);
        			while(fgets(line, 500, _asnfile)) {
                			buflen = strlen(line);
               				k=0;
					n=0;
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
                			asn_str[n] = '\0';
                			stored_end = atol(end_str);
                                	stored_start = atol(start_str);
					// ************************************************
					// If the IP address we've converted into an
					// int is greater than or equal to the start int
					// and is less than or equal to the end int, then
					// we have an ASN range that matches
					// *************************************************
                			if((ip_int >= stored_start) && (ip_int <= stored_end)) {
                               			n = 0;
                                		while((k<buflen) && (line[k]!=' ') && (line[k]!='\n')){
                                        		asn_str[n] = line[k++];
                                        		n++;
                                		}
                                		asn_str[n] = '\0';
                        			(void)remchars("\"",asn_str);
						strcpy(previous_asn_str,asn_str);
						insert_new_field(newname,asn_str);
						found=1;
                        			break;
                			}
				}
               			if(found==0) {
					asn_str[0]='\0';
					previous_asn_str[0]='\0';
                        		insert_new_field(newname,asn_str);
                		}
			}
                	else {
				// ****************************************************
				// The string didn't seem to be a valid IP address,
				// so just insert an empty asn value
				// ****************************************************
				asn_str[0]='\0';
				previous_asn_str[0]='\0';
                        	insert_new_field(newname,asn_str);
                	}
		}
		// **************************************************
		// Deal with the next fieldname in the target list
		// **************************************************
		target_count++;
	}
	return;
}
