#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void add_asn(char *);
int remchars(char *, char *); 

int main(int argc, char**argv) {
int count=1;
	if(argc<2) return 0;
	for(count=1;count<argc;count++) {
		add_asn(argv[count]);
	}
}

void add_asn(char *buffer) {
ssize_t n;
struct in_addr ip;
static char line[500];
size_t k;
size_t buflen;
long int stored_start=0;
long int stored_end=0;
long int ip_int=0;
char *fname;
char start_str[50];
char end_str[50];
char asn_str[100];
FILE *asnfile;
	fname=getenv("COUNTRY_FILE");
	if(fname==NULL) {
		fprintf(stdout,"No COUNTRY_FILE environment variable set.\n");
		exit(EXIT_FAILURE);
	}
	asnfile=fopen(fname,"r");
	if(asnfile==NULL) {
		fprintf(stdout,"Could not open file %s\n",fname);
		exit(EXIT_FAILURE);
	}
	if(inet_aton(buffer,&ip)) {
		ip_int=htonl(ip.s_addr);
        	while(fgets(line, 500, asnfile)) {
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
                             	while(k<buflen)  {                      //asn data
                                        asn_str[n] = line[k++];
                                        n++;
                                }
                		asn_str[n]='\0';
				fprintf(stdout,"%s %s",buffer,asn_str);
                        	break;
                	}
		}
	}
	fclose(asnfile);
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

