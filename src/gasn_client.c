#include "externs.h" 
int main(int argc, char *argv[]) {
    int sockfd = 0,rv;
    ssize_t n=0;
    uint16_t gasn_port_int=0;
    char recvBuff[1024];
    char ip[16];
    char *hostname;
    char *gasn_port;
    struct sockaddr_in serv_addr; 
    fd_set set;
    struct timeval timeout;
    if(argc != 2) {
        printf("\n Usage: %s ip-address\n",argv[0]);
        return 1;
    } 
    if((hostname = getenv("GSERVER"))) {;
    	if(hostname_to_ip(hostname,ip)) {
        	printf("No IP address found for %s\n",hostname);
        	return 1;
    	}
    }
    else { 
	printf("No GSERVER environment variable set\n");
	return 1;
    }
    if((gasn_port = getenv("GASN_PORT"))) {;
    	gasn_port_int = atoi(gasn_port);
    }
    
    else {
     	printf("No GASN_PORT environment variable set\n");
        return 1;
    }
    memset(recvBuff, 0,sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket for connection to %s (%s):%hu\n",hostname,ip,gasn_port_int);
        return 1;
    } 

    memset(&serv_addr, 0, sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(gasn_port_int); 
    	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
        	printf("\n inet_pton error occured\n");
        	return 1;
    	} 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
       		printf("Could not connect to %s (%s):%d\n",hostname,ip,gasn_port_int);
       		return 1;
    } 
    n = write(sockfd,argv[1],strlen(argv[1]));
 	FD_ZERO(&set);
        FD_SET(sockfd, &set);
        timeout.tv_sec=5;
        timeout.tv_usec=0;
        rv=select(sockfd+1, &set, NULL,NULL,&timeout);
        if((rv==-1) || (rv==0)) {
		fprintf(stderr,"gasn: Server timed out\n");
                close(sockfd);
                return(0);
        }
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
       	recvBuff[n] = (char) 0x0;
       	if(fputs(recvBuff, stdout) == EOF) printf("\n Error : Fputs error\n");
	write(sockfd,"EXIT\n",5); 
	return(0);
}
