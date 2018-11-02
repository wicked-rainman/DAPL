#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char**argv) {
unsigned int ip_octet[4]={0,0,0,0};
int count=1,c;
long int ip_int=0;
	for(count=1;count<argc;count++) {
       		c=sscanf(argv[count], "%3u.%3u.%3u.%3u", &ip_octet[0],&ip_octet[1],&ip_octet[2],&ip_octet[3]);
                ip_int=(ip_octet[0] << 24)+(ip_octet[1] << 16)+(ip_octet[2] << 8)+ip_octet[3];
		fprintf(stdout,"\"%lu\" ",ip_int);
	}
	fprintf(stdout,"\n");
}
