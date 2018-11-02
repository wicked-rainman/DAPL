#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <signal.h>
#define TRUE 1
#define FALSE 0
static void doprocessing (int ,char*);
static int exit_error(int, char*);
void remchars(char*,char*);
char asnpath[100];

int main() {
   int sockfd, newsockfd;
   size_t clilen;
   struct sockaddr_in serv_addr, cli_addr;
   int pid;
   char *gasn_port;
   char *asn_path;
   int asn_port_int=0;
   setlogmask(LOG_UPTO (LOG_NOTICE));
   openlog("gasnd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
   syslog(LOG_NOTICE,"Starting the fuck up\n");

   if((asn_path = getenv("GREFERENCE"))) {
	strcpy(asnpath,asn_path);
	strcat(asnpath,"/GeoIPASNum2.csv");
   }
   else {
        syslog (LOG_NOTICE,"$GREFERENCE environment not set.\n");
        syslog (LOG_NOTICE,"Aborting\n");
        exit(EXIT_FAILURE);
   }
   syslog(LOG_NOTICE,"Using ASN lookup table in %s\n",asnpath);
   if ((gasn_port =getenv("GASN_PORT"))) asn_port_int = atoi(gasn_port);
   else {
        syslog (LOG_NOTICE,"$GASN_PORT environment not set.\n");
        syslog (LOG_NOTICE,"Aborting\n");
        exit(EXIT_FAILURE);
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)  perror("ERROR opening socket");
   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, (socklen_t) sizeof(int)) < 0) {
        syslog(LOG_NOTICE,"Could not open a listening socket. Aborting\n");
	exit(EXIT_FAILURE);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons((uint16_t) asn_port_int);
   if (bind(sockfd, (struct sockaddr *) &serv_addr, (socklen_t) sizeof(serv_addr)) < 0) {
   	syslog(LOG_NOTICE,"Could not bind. Aborting\n");
   	exit(EXIT_FAILURE);
   }
   if(listen(sockfd,5)!=0) {
	syslog(LOG_NOTICE,"Could not listen on socket\n");
	exit(EXIT_FAILURE);
   }
   clilen = sizeof(cli_addr);
   syslog(LOG_NOTICE,"Listening on port %s\n",gasn_port);
   while ((bool) 1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
		
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(EXIT_FAILURE);
      }
      signal(SIGCHLD, SIG_IGN);
      pid = fork();
      if (pid < 0) {
         syslog(LOG_NOTICE,"Could not fork listening child\n");
         exit(EXIT_FAILURE);
      }
      
      if (pid == 0) {
         (void) close(sockfd);
         doprocessing(newsockfd,inet_ntoa(cli_addr.sin_addr));
         exit(EXIT_SUCCESS);
      }
      else (void) close(newsockfd);
   }
   syslog(LOG_NOTICE,"Ended\n");
}



void doprocessing (int sock, char* clip) {
   ssize_t n;
   char buffer[256];
   char ip[50];
   char line[500];
  
   bzero(buffer,256);
   bzero(ip,50);
   int k,buflen,found;
   int ip_octet[4]={0,0,0,0};
   uint32_t ip_int=0;
   uint32_t stored_start=0;
   uint32_t stored_end=0;
   char start_str[50];
   char end_str[50];
   char asn_str[100];
   char *p, *saveptr;
   FILE *asn=NULL;
   bzero(buffer,256);
   bzero(ip,50);
  
   	/***********************************************************************************/
   	/* Read what's been passed to the server (Should be a proper query)                */
   	/***********************************************************************************/
  	n = read(sock,buffer,255);
	while(n>=0) {	
   		buflen = n;
		if(n>0) {
   			buffer[buflen] = (char) 0x0;
			if(buffer[buflen-1]=='\n') buffer[buflen-1] = (char) 0x0;
			if(strncmp(buffer,"EXIT",4)==0) {
				fclose(asn);
				return;
			}
   			//setlogmask(LOG_UPTO (LOG_NOTICE));
   			//syslog(LOG_NOTICE,"%s Queried %s\n",clip, buffer); 
   			/***********************************************************************************/
   			/*Parse the incomming line to extract IP address value                             */
   			/***********************************************************************************/
   			p = strtok_r(buffer,".",&saveptr);
   			k = 0;
   			while (p) {
				if(k == 4) exit_error(sock,"IP address is invalid\n");
        			ip_octet[k]= atoi(p);
        			if (ip_octet[k]<0 || ip_octet[k]>255) exit_error(sock,"IP address is invalid\n");
				k++;
             			p=strtok_r(NULL,".",&saveptr);
   			}
        		ip_int=(ip_octet[0] << 24)+(ip_octet[1] << 16)+(ip_octet[2] << 8)+ip_octet[3];
   			/***********************************************************************************/
   			/* Go look it up                                                                   */
   			/***********************************************************************************/
			if(asn==NULL) {
				asn = fopen(asnpath,"r");
				if(asn<0)  {
					exit(EXIT_SUCCESS);
				}
			}
			rewind(asn);
			found=0;
			while((fgets(line, 500, asn)) && (found!=1)) {
				buflen = strlen(line);
				k=0;
				while(line[k]!=',') {
					start_str[k] = line[k];
					k++;
				}
				start_str[k] = 0x00;
				k++;
				n = 0;
				while(line[k] !=',') {
					end_str[n] = line[k++];
					n++;
				}
				end_str[n] = 0x00;
				k++;
				n = 0;
				while(k<buflen) {
					asn_str[n] = line[k++];
					n++;
				}
				asn_str[n] = 0x00;
				stored_start = atol(start_str);
				stored_end = atol(end_str);
				if((ip_int >= stored_start) && (ip_int <= stored_end)) {
					found=1;
					remchars("\"",asn_str);
					k = strlen(asn_str);
					for(n=0;n<k;n++) {
						if(asn_str[n] == ' ') {
							asn_str[n] = ',';
							break;
						}
					}
					n = write(sock, asn_str,strlen(asn_str));
					if(n<0) {
						perror("Error writing to socket");
						return;
					}
				}
			}
			if(found==0) {
				write(sock,"UNKNOWN,UNKNOWN\n",20);
			}
		}
  		n = read(sock,buffer,255);
	}
	fclose(asn);
	return;
}

int exit_error(int sock, char *message) {
	write(sock, message, strlen(message));
  	exit(EXIT_FAILURE);	
}

