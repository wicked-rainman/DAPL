#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void add_country(char *);
int remchars(char *, char *); 

int main(int argc, char**argv) {
int count=1;
	if(argc<2) return 0;
	for(count=1;count<argc;count++) {
		add_country(argv[count]);
	}
}

void add_country(char *buffer) {
ssize_t n;
char ip[50];
static char line[500];
int c;
unsigned int ip_octet[4]={0,0,0,0};

size_t k;
size_t buflen;
long int stored_start=0;
long int stored_end=0;
long int ip_int=0;
char start_str[50];
char end_str[50];
char country_str[100];
bzero(ip,50);
FILE *countryfile;
	countryfile=fopen("/home/damian/dev/Reference/ipcountry.csv","r");
	k=strlen(buffer);
	c=sscanf(buffer, "%3u.%3u.%3u.%3u", &ip_octet[0],&ip_octet[1],&ip_octet[2],&ip_octet[3]);
                        ip_int=(ip_octet[0] << 24)+(ip_octet[1] << 16)+(ip_octet[2] << 8)+ip_octet[3];
        		while(fgets(line, 500, countryfile)) {
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
                             		//while((k<buflen) && (line[k]!=',')) {                      //Country data
                             		while(k<buflen)  {                      //Country data
                                        	country_str[n] = line[k++];
                                        	n++;
                                	}
                			country_str[n]='\0';
					fprintf(stdout,"%s %s",buffer,country_str);
                        		break;
                		}
			}
	fclose(countryfile);
}
int remchars(char *dels, char *instr) {
size_t buflen,k;
char outstr[1000];
int n,l,delcount,found;
        buflen = strlen(instr);
        delcount = strlen(dels);
        n = 0;
        found=0;
        for(k=0;k<buflen;k++) {
                for(l=0;l<delcount;l++) {
                        if(instr[k] == dels[l]) {
                                found=1;
                                break;
                        }
                }
                if(found==0) {
                        outstr[n]=instr[k];
                        n++;
                }
                found=0;
        }
        outstr[n]='\0';
        strcpy(instr,outstr);
        return n;
}

