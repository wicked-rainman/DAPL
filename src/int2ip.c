#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char**argv) {
int count=1;
long int ip_int=0;
	for(count=1;count<argc;count++) {
       		ip_int=atol(argv[count]);
		fprintf(stdout,"\"%lu.%lu.%lu.%lu\" ",
  			(ip_int >> 24) & 0xFF,
  			(ip_int >> 16) & 0xFF,
  			(ip_int >>  8) & 0xFF,
  			(ip_int      ) & 0xFF);
	}
	fprintf(stdout,"\n");
}
