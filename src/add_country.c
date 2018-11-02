#include "externs.h"
void add_country(char *tgt) {
ssize_t n;
char buffer[MAX_FIELDVALUE_LENGTH];
char tail[MAX_FIELDVALUE_LENGTH-7];
char ip[50];
char line[500];
char newname[MAX_FIELDNAME_LENGTH];
  
int nogo,c,found;
int target_count,line_count;
unsigned int ip_octet[4]={0,0,0,0};
//uint32_t ip_int=0;
//uint32_t stored_start=0;
//uint32_t stored_end=0;
size_t k;
size_t buflen;
long int stored_start=0;
long int stored_end=0;
long int ip_int=0;
char start_str[50];
char end_str[50];
char country_str[100];
bzero(ip,50);

	if(_drop==1) return;
        if(_countryfile==NULL) _countryfile = fopen(COUNTRY_FILE_NAME,"r");
        if(_countryfile==NULL) {
        	fprintf(stderr,"Could not open Country file \"%s\"\n",COUNTRY_FILE_NAME);
                exit(EXIT_SUCCESS);
        }

	target_count=0;
	build_target_list(tgt);
	while(target_count<tlist.count) {
                nogo=0; ;ip_octet[0]=0;ip_octet[1]=0;ip_octet[2]=0;ip_octet[3]=0,tail[0]='\0';
		strcpy(buffer, _fieldvalues_array[tlist.position[target_count]]);
		(void) remchars("\"",buffer);
		k=strlen(buffer);
		if((k> 15) || (k<7)) nogo=1;
		else {
			c=sscanf(buffer, "%3u.%3u.%3u.%3u%s", &ip_octet[0],&ip_octet[1],&ip_octet[2],&ip_octet[3],tail);
			if(c !=4 || tail[0] !='\0') nogo=1;
			for(k=0;k<4;k++) {
				if (ip_octet[k] > 255) nogo=1;
			}
   			ip_int=(ip_octet[0] << 24)+(ip_octet[1] << 16)+(ip_octet[2] << 8)+ip_octet[3];
			if(ip_int==0) nogo=1;
		}
		if(nogo==1) {
                        strcpy(newname,tlist.name[target_count]);
                        strcat(newname,".country");
                        country_str[0]='\0';
                        //fprintf(stdout,"add_country: Invalid IP, inserting [%s] %s for %s \n",newname,country_str,buffer);
                        insert_new_field(newname,country_str);
                }
		else {
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
		target_count++;
	}
        return;
}
