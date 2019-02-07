#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
int hostname_to_ip(char *,char *);
int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0,gdns_port_int = 0;
    char recvBuff[1024];
    char ip[16];
    char *hostname;
    char *gdns_port;
    struct sockaddr_in serv_addr; 

    if(argc != 2) {
        printf("\n Usage: %s dns_query \n",argv[0]);
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
    if((gdns_port = getenv("GRDNS_PORT"))) {;
        gdns_port_int = atoi(gdns_port);
    }
    
    else {   
        printf("No GDNS_PORT environment variable set\n");
        return 1;
    }
        memset(&serv_addr, '0', sizeof(serv_addr)); 

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(gdns_port_int); 
        if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
                printf("\n inet_pton error occured\n");
                return 1;
        } 

        if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
                printf("Could not connect to %s (%s):%d\n",hostname,ip,gdns_port_int);
                return 1;
        } 
        n = write(sockfd,argv[1],strlen(argv[1]));
        while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0){
                recvBuff[n] = 0;
                if(fputs(recvBuff, stdout) == EOF) printf("\n Error : Fputs error\n");
        } 
        if(n < 0) printf("\n Read error \n");
        

    return 0;
}
    
int hostname_to_ip(char * hostname , char* ip) {
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( hostname ) ) == NULL) 
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    return 1;
}

        printf("No GRDNS_PORT environment variable set\n");
        return 1;
    }
    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket for connection to %s (%s):%d\n",hostname,ip,gdns_port_int);
        return 1;
} 
