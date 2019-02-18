#include "externs.h"
void cleanup() {
char *hostname;
char *gasn_port;
char *gcountry_port;

        if(_ofile !=NULL) (void) fclose(_ofile);
        //if(_asnfile !=NULL) (void) fclose(_asnfile);
        //if(_countryfile !=NULL) (void) fclose(_countryfile);
	if(_dfile !=NULL) {
		fprintf(_dfile,"}\n");
		(void) fclose(_dfile);
	}
        if(_asn_sockfd!=0) {
                hostname = getenv("GSERVER");
                gasn_port = getenv("GASN_PORT");
                fprintf(stderr,"Closing connection to %s:%s\n",hostname,gasn_port);
                write(_asn_sockfd,"EXIT\n",5);
                (void) close(_asn_sockfd);
        }
       if(_country_sockfd!=0) {
                hostname = getenv("GSERVER");
                gcountry_port = getenv("GCOUNTRY_PORT");
                fprintf(stderr,"Closing connection to %s:%s\n",hostname,gcountry_port);
                (void) write(_country_sockfd,"EXIT\n",5);
                (void) close(_country_sockfd);
        }
}
