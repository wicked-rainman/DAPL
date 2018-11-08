#include "externs.h"
int whitelist(char *tgt) {
struct in_addr ip;
static FILE *_whitefile;
int n,k,buflen,target_count;
char line[500];
char start_str[50];
char end_str[50];
char *white_file;
char buffer[MAX_FIELDVALUE_LENGTH];
uint32_t stored_start=0;
uint32_t stored_end=0;
uint32_t ip_int=0;
	if(_drop==1) return 0;
	target_count=0;
	build_target_list(tgt);
	// *************************************************
	// While fieldnames are left to process
	// *************************************************
	while(target_count<tlist.count) {
		// ***************************************
		// Try and convert the field value to an int
		// ******************************************
		strcpy(buffer,_fieldvalues_array[tlist.position[target_count]]);
        	remchars("\"",buffer);
		if(inet_aton(buffer,&ip)) {
			ip_int=htonl(ip.s_addr);
			// ***********************************************
			// If it appears like the IP string could be 
			// converted to an int, proceed to look it up.
			// ***********************************************
        		if(_whitefile==NULL) {
				white_file=getenv("WHITE_FILE");
				if(white_file==NULL) {
					fprintf(stderr,"whitelist : No WHITE_FILE environment variable found\n");
					exit(EXIT_FAILURE); 
				}
				 _whitefile = fopen(white_file,"r");
        			if(_whitefile==NULL)  {
					fprintf(stderr,"Could not open WHITE_FILE file \"%s\"\n",white_file);
					exit(EXIT_FAILURE);
				}
				fprintf(stdout,"whitelist_ip : Using file %s\n",white_file);
			}
			rewind(_whitefile);
        		while(fgets(line, 500, _whitefile)) {
                		buflen = strlen(line);
               			k=0;
				n=0;
				// *****************************************************
				// WHITE_FILE file has the format :
				// INT,INT,Comment
				// Extract the start and end int values
				// ******************************************************
                		while(line[k]!=',') {
                        		start_str[n] = line[k++];
					n++;
                		}
                		start_str[n] = '\0';
                		k++;
                		n = 0;
                		while(line[k] !=',') {
                        		end_str[n] = line[k++];
                        		n++;
                		}
                		end_str[n] = '\0';
                		stored_start = atol(start_str);
                		stored_end = atol(end_str);
                		if((ip_int >= stored_start) && (ip_int <= stored_end)) {
					//fprintf(stdout,"whitelist : Matched %s\n",buffer);
					return 1;
				} 
			}
		}
		target_count++;
	}
	return 0;
}
