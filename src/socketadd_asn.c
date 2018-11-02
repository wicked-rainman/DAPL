#include "externs.h"
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
void socketadd_asn(char *fieldname) {
int x, n = 0,gasn_port_int = 0, pos=0;
char recvBuff[MAX_FIELDVALUE_LENGTH-1];
char ip[16];
char *hostname;
char *gasn_port;
char newfield[MAX_FIELDNAME_LENGTH];
char newvalue[MAX_FIELDVALUE_LENGTH];
struct sockaddr_in serv_addr; 
fd_set set;
struct timeval timeout;
int rv;
	if(_drop==1) return;
	x=find_fieldname(fieldname);
	if (x>=0) {
		if(_asn_sockfd==0) {
    			hostname = getenv("GSERVER");
    			if(hostname==NULL) {
				fprintf(stderr,"No environment variable GSERVER set\n");
				exit(EXIT_FAILURE);
			}
    			if(hostname_to_ip(hostname,ip)) {
        			fprintf(stderr, "No IP address found for %s\n",hostname);
        			exit(EXIT_FAILURE);
    			}
    			gasn_port = getenv("GASN_PORT");
			if(gasn_port==NULL) {
				fprintf(stderr,"No environment variable GASN_PORT set\n");
				exit(EXIT_FAILURE);
			}
    			gasn_port_int = atoi(gasn_port);
			fprintf(stderr,"socketadd_asn: Opening new connection to %s:%s\n", hostname,gasn_port);
    
			memset(recvBuff, '0',sizeof(recvBuff));
    			if((_asn_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        			fprintf(stderr,"Could not create socket for connection to %s (%s):%d\n",hostname,ip,gasn_port_int);
        			exit(EXIT_FAILURE);
    			} 

    			memset(&serv_addr, '0', sizeof(serv_addr)); 

    			serv_addr.sin_family = AF_INET;
    			serv_addr.sin_port = htons(gasn_port_int); 
    			if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
        			fprintf(stderr,"inet_pton error occured\n");
        			exit(EXIT_FAILURE);
    			} 

    			if( connect(_asn_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
       				fprintf(stderr,"Could not connect to %s (%s):%d\n",hostname,ip,gasn_port_int);
       				exit(EXIT_FAILURE);
    			}
		} 
    		n = write(_asn_sockfd,_fieldvalues_array[x],strlen(_fieldvalues_array[x]));
		//n=0;
		FD_ZERO(&set);	
		FD_SET(_asn_sockfd, &set);
		timeout.tv_sec=5;
		timeout.tv_usec=0;
		rv=select(_asn_sockfd+1, &set, NULL,NULL,&timeout);
		if((rv==-1) || (rv==0)) {
			fprintf(stderr,"sockadd_asn: Server timed out looking up \"%s\".\n",_fieldvalues_array[x]);
			close(_asn_sockfd);
			_asn_sockfd=0;
			insert_new_field(newfield,"ERROR");
			return;
		}
    		//while (n==0)  n = read(_asn_sockfd, recvBuff, sizeof(recvBuff)-1);
    		n = read(_asn_sockfd, recvBuff, sizeof(recvBuff)-1);
		if(n<=0) {
			fprintf(stderr,"sockadd_asn: Received 0 byte reply for \"%s\" from server.\n",_fieldvalues_array[x]);
			close(_asn_sockfd);
			_asn_sockfd=0;
			insert_new_field(newfield,"ERROR");
			return;
		}
		recvBuff[n]=0;
		strcpy(newfield,fieldname);
		strcat(newfield,".asn");
		pos=strpos(recvBuff,",");
		strncpy(newvalue,recvBuff,pos);
		newvalue[pos]=(char) 0x0;
		if (strlen(newvalue)>= (size_t) (MAX_FIELDVALUE_LENGTH-1)) {
			fprintf(stderr,"socketadd_asn: value for \"%s\" is too big to insert\n",_fieldvalues_array[x]);
			insert_new_field(newfield,"ERROR");
			return;
		}
		insert_new_field(newfield,newvalue);
		return; 
	}
}
