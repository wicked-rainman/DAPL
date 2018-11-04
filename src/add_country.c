#include "externs.h"
void add_country(char *tgt) {
ssize_t n;
struct in_addr ip;
char buffer[MAX_FIELDVALUE_LENGTH];
char line[500];
char newname[MAX_FIELDNAME_LENGTH];
  
int found;
int target_count,line_count;
size_t k;
size_t buflen;
long int stored_start=0;
long int stored_end=0;
uint32_t ip_int=0;
char start_str[50];
char end_str[50];
char country_str[100];
char *country_file;

	if(_drop==1) return;
        if(_countryfile==NULL) {
		country_file=getenv("COUNTRY_FILE");
		if(country_file==NULL) {
			fprintf(stderr,"add_country : No COUNTRY_FILE environmental variable found\n");
			exit(EXIT_FAILURE);
		}
		_countryfile = fopen(country_file,"r");
        	if(_countryfile==NULL) {
        		fprintf(stderr,"Could not open Country file \"%s\"\n",country_file);
                	exit(EXIT_SUCCESS);
        	}
	}
	target_count=0;
	build_target_list(tgt);
	while(target_count<tlist.count) {
		strcpy(buffer, _fieldvalues_array[tlist.position[target_count]]);
		(void) remchars("\"",buffer);
		if(inet_aton(buffer,&ip)) {
			ip_int=htonl(ip.s_addr);
			found=0;
        		rewind(_countryfile);
			line_count=0;
        		while(fgets(line, 500, _countryfile)) {
				line_count++;
                		(void) remchars("\"",line);
                		buflen = strlen(line);
                		k=0;
				n=0;
                		while((line[k]!=',') && (k<buflen)) {    //Numeric IP start
                        		start_str[n] = line[k++];
					n++;
                		}
                		start_str[n]='\0';
                		k++;
                		n = 0;
                		while((line[k] !=',') && (k<buflen)) {  //Numeric IP end
                        		end_str[n] = line[k++];
                        		n++;
                		}
                		end_str[n]='\0';
                		k++;
                		stored_start = atol(start_str);
                		stored_end = atol(end_str);
                		if((ip_int >= stored_start) && (ip_int <= stored_end)) {
					n=0;
                             		while((k<buflen) && (line[k]!=',')) {                      //Country data
                                        	country_str[n] = line[k++];
                                        	n++;
                                	}
                			country_str[n]='\0';
					strcpy(newname,tlist.name[target_count]);
					strcat(newname,".country");
					//fprintf(stdout,"add_country: %d Inserting [%s] %s for %s \n",line_count,newname,country_str,buffer);
					insert_new_field(newname,country_str);
					found=1;
                        		break;
                		}
			}
			if(found==0) {
                       		strcpy(newname,tlist.name[target_count]);
                        	strcat(newname,".country");
				country_str[0]='\0';
				//fprintf(stdout,"add_country: %d NOT FOUND [%s] %s for %s \n",line_count,newname,country_str,buffer);
                        	insert_new_field(newname,country_str);
        		}
		}
		else {
                        strcpy(newname,tlist.name[target_count]);
                        strcat(newname,".country");
                        country_str[0]='\0';
                        //fprintf(stdout,"add_country: Invalid IP, inserting [%s] %s for %s \n",newname,country_str,buffer);
                        insert_new_field(newname,country_str);
		}
		target_count++;
	}
        return;
}
