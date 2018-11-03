#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// *******************************************************
// Simple program to convert and IP address into an int
// One or more IP addresses can be specified on invocation.
// Results written to stdout.
// Intended for use while updating geipcountry and asn
// csv files. 
// ********************************************************
int main(int argc, char**argv) {
struct in_addr ip;
int count;
	for(count=1;count<argc;count++) {
		if(inet_aton(argv[count],&ip)) {
			fprintf(stdout,"\"%u\" ",htonl(ip.s_addr));
		}
	}
	fprintf(stdout,"\n");
}
