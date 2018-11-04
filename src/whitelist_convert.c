#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
void cidr2_ip(char *, char *, FILE *); 
// *************************************************************************
// Program  whitelist_convert - A very quick bodge
// Parameters are:
// argv[1]= a file containing a list of cidr's, one per line, starting col1.
// argv[2]= an appended output file that can become a whitelist
// argv[3]= a "tag" name for each cidr - Like google or duckduck Etc
//
// Output file contains long int start and long int end values that
// reflect the IP address range from the CIDR.
//
// Painful, but it works and saves time :-) Can't be bothered to do this
// with any finess.... WR.
// *************************************************************************


int main(int argc, char** argv) {
FILE *infile, *outfile;
char input_line[500];
char cidr[40];
int j,k;
	if(argc!=4) {
		fprintf(stdout,"Parameters are %s INPUT_FILE OUTPUT_FILE name_tag\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	infile=fopen(argv[1],"r");
	if(infile==NULL) {
		fprintf(stdout,"Could not open file %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}
	outfile=fopen(argv[2],"a");
	if(outfile==NULL) {
		fprintf(stdout,"Could not open output file %s\n",argv[3]);
		exit(EXIT_FAILURE);
	}
	if(strlen(argv[3])>100) {
		fprintf(stdout,"Name tag %lu is too long!\n",strlen(argv[1]));
		exit(EXIT_FAILURE);
	}
	while(fgets(input_line,500,infile)) {
		j=0;
		k=strlen(input_line);
		while((j<k) && (input_line[j]!=' ') && (j<39)) {
			cidr[j]=input_line[j];
			j++;
		}
		cidr[j-1]='\0';
		fprintf(stdout,"Passing %s %s\n",cidr,argv[3]);
		cidr2_ip(cidr,argv[3],outfile);	
	}
	fclose(outfile);
	fclose(infile);
}

void cidr2_ip(char *string, char *name, FILE *outfile) {
unsigned int ip[4],ip_min[4],ip_max[4],netmask,tmp1,tmp2;
char start_ip[40];
char end_ip[40];
struct in_addr _ip;
long int start_int,end_int;
    	sscanf(string,"%d.%u.%u.%u/%u",&ip[0],&ip[1],&ip[2],&ip[3],&netmask);
    	for (tmp1=tmp2=netmask/8;tmp1>0;tmp1--){
    		ip_min[tmp1-1] = ip[tmp1-1];
    		ip_max[tmp1-1] = ip[tmp1-1];
    	}
    	for(tmp1 = tmp2,++tmp2;tmp2< 4;tmp2++){
    		ip_min[tmp2]=0;
    		ip_max[tmp2]=255;
    	}
    	if( tmp1 < 4){
    		tmp2 = 8-netmask%8;
    		ip_min[tmp1]=ip[tmp1]>>tmp2;
    		ip_min[tmp1]<<=tmp2;
    		ip_max[tmp1]=ip_min[tmp1]+pow(2,tmp2)-1;
    	}
	sprintf(start_ip,"%u.%u.%u.%u",ip_min[0],ip_min[1],ip_min[2],ip_min[3]);
	sprintf(end_ip,"%u.%u.%u.%u",ip_max[0],ip_max[1],ip_max[2],ip_max[3]);
	if(inet_aton(start_ip,&_ip)) {
		start_int=htonl(_ip.s_addr);
	}
	else {
		fprintf(stdout,"Error coverting %s to an int!\n",start_ip);
		exit(EXIT_FAILURE);
	}
        if(inet_aton(end_ip,&_ip)) {
                end_int=htonl(_ip.s_addr);
        }
        else {
                fprintf(stdout,"Error coverting %s to an int!\n",end_ip);
                exit(EXIT_FAILURE);
        }
	fprintf(outfile,"%lu,%lu,%s\n",start_int,end_int,name);
    	return;
    }
