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
int c,n,m,k,buflen,target_count,nogo,found;
char line[500];
char start_str[50];
char end_str[50];
char asn_str[100];
char buffer[MAX_FIELDVALUE_LENGTH];
char tail[MAX_FIELDVALUE_LENGTH-7];
char newname[MAX_FIELDNAME_LENGTH];
uint32_t stored_start=0;
uint32_t stored_end=0;
uint32_t ip_int=0;
unsigned int ip_octet[4]={0,0,0,0};
	if(_drop==1) return;
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
		// ************************************************
		// Initialise variables used to create an int out of
		// an IP address string
		// ************************************************
		nogo=0; ;ip_octet[0]=0;ip_octet[1]=0;ip_octet[2]=0;ip_octet[3]=0,tail[0]='\0';
		// ******************************************************
		// Copy (what should be) the string IP address out of the
		// global _fieldvalues_array
		// ******************************************************
		strcpy(buffer,_fieldvalues_array[tlist.position[target_count]]);
		// **********************************************************
		// All field values are encased in quotes. Remove the quotes
		// ***********************************************************
        	remchars("\"",buffer);
		// ********************************************
		// Try and convert the IP string into an int
		// ********************************************
		k=strlen(buffer);
		if((k> 15) || (k<7)) nogo=1;
		c=sscanf(buffer, "%3u.%3u.%3u.%3u%s", &ip_octet[0],&ip_octet[1],&ip_octet[2],&ip_octet[3],tail);
               	if(c !=4 || tail[0] !='\0') nogo=1;
                for(k=0;k<4;k++) {
                        if (ip_octet[k] > 255) nogo=1;
                }
        	ip_int=(ip_octet[0] << 24)+(ip_octet[1] << 16)+(ip_octet[2] << 8)+ip_octet[3];
		if(ip_int==0) nogo=1;
		// ***********************************************
		// If it appears like the IP string could be 
		// converted to an int, proceed to look it up.
		// ***********************************************
		if(nogo==0) {
			// *************************************************
			// If the ASN lookup file hasn't been opened yet, 
			// Open it....
			// *************************************************
        		if(_asnfile==NULL) {
				 _asnfile = fopen(ASN_FILE_NAME,"r");
				// ********************************************
				// Can't open the file, then just bomb out
				// ********************************************
        			if(_asnfile==NULL)  {
					fprintf(stderr,"Could not open ASN file \"%s\"\n",ASN_FILE_NAME);
					exit(EXIT_SUCCESS);
				}
			}
			// *******************************************************
			// Rewind the ASN file and start reading lines from it
			// *******************************************************
			found=0;
			rewind(_asnfile);
        		while(fgets(line, 500, _asnfile)) {
                		buflen = strlen(line);
               			k=0;
				n=0;
				// *****************************************************
				// ASN file has the format :
				// INT,INT,ASN_STRING
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
                		asn_str[n] = '\0';
                		stored_start = atol(start_str);
                		stored_end = atol(end_str);
				// ************************************************
				// If the IP address we've converted into an
				// int is greater than or equal to the start int
				// and is less than or equal to the end int, then
				// we have an ASN range that matches
				// *************************************************
                		if((ip_int >= stored_start) && (ip_int <= stored_end)) {
                               		n = 0;
                                	while(k<buflen) {
                                        	asn_str[n] = line[k++];
                                        	n++;
                                	}
                                	asn_str[n] = '\0';
					// *************************************************
					// The asn string in the ASN file is surrounded
					// by quotes. Remove them
					// *************************************************
					// The asn string in the ASN file is surrounded
                        		remchars("\"",asn_str);
                        		k = strlen(asn_str);
					m=0;
					n=0;
					while((m==0) && (n<k)) {
                                		if((asn_str[n] == ' ') || (asn_str[n] =='\n')) {
                                        		asn_str[n] = (char) 0x0;
                                        		m=1;
                                		}
						n++;
                        		}
					strcpy(newname,tlist.name[target_count]);
					strcat(newname,".asn");
					// *****************************************
					// Add the asn into the global structure.
					// It will have a fieldname of:
					// xxxxx.asn
					// where xxxxx = the original target field
					// specified when the function was called
					// ******************************************
					insert_new_field(newname,asn_str);
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
                        	strcat(newname,".asn");
				asn_str[0]='\0';
                        	insert_new_field(newname,asn_str);
                	}
		}
                else {
			// ****************************************************
			// The string didn't seem to be a valid IP address,
			// so just insert an empty asn value
			// ****************************************************
                        strcpy(newname,tlist.name[target_count]);
                        strcat(newname,".asn");
			asn_str[0]='\0';
                        insert_new_field(newname,asn_str);
                }
		// **************************************************
		// Deal with the next fieldname in the target list
		// **************************************************
		target_count++;
	}
	return;
}
