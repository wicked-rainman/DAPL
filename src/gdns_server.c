/**************************************************************************************/
/* File: gdns_server.c                                                                */
/* Version: 1                                                                         */
/* Server to return domain names when passed a IPV4                                   */
/* Author: WR                                                                         */
/* Compile: clang gdns_server.c -ofast -o gdns_server                                 */
/**************************************************************************************/

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
char fastpath[100];

   int main(/*@unused@*/ int argc, /*@unused@*/ char *argv[] ) {
   int sockfd, newsockfd;
   size_t clilen;
   struct sockaddr_in serv_addr, cli_addr;
   int pid;
   char *fastdns_port;
   char *fdns_path;
   int fastdns_port_int=0;
   setlogmask(LOG_UPTO (LOG_NOTICE));
   openlog("gdnsd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
   syslog(LOG_NOTICE,"Starting up\n");

   if((fdns_path = getenv("GREFERENCE"))) {
	strcpy(fastpath,fdns_path);
	strcat(fastpath,"/dns");
   }
   else {
        syslog (LOG_NOTICE,"$GREFERENCE environment not set.\n");
        syslog (LOG_NOTICE,"Aborting\n");
        exit(EXIT_FAILURE);
   }
   syslog(LOG_NOTICE,"Using inode structure at %s\n",fastpath);
   if ((fastdns_port = getenv("GDNS_PORT"))) fastdns_port_int = atoi(fastdns_port);
   else {
        syslog (LOG_NOTICE,"$GDNS_PORT environment not set.\n");
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
   serv_addr.sin_port = htons((uint16_t) fastdns_port_int);
   if (bind(sockfd, (struct sockaddr *) &serv_addr, (socklen_t) sizeof(serv_addr)) < 0) {
   	syslog(LOG_NOTICE,"Could not bind. Aborting\n");
   	exit(EXIT_FAILURE);
   }
   if(listen(sockfd,5)!=0) {
	syslog(LOG_NOTICE,"Could not listen on socket\n");
	exit(EXIT_FAILURE);
   }
   clilen = sizeof(cli_addr);
   syslog(LOG_NOTICE,"Listening on port %s\n",fastdns_port);
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



void doprocessing (int sock, /*@unused@*/ char* clip) {
   ssize_t n;
   char buffer[256];
   char exact[30];
   char ip[50];
   char outline[500];
   char line[500];
   struct in_addr taddr;
  
   bzero(buffer,256);
   bzero(ip,50);
   int k,buflen;
   int ip_octet[4]={0,0,0,0};
   char *p, *saveptr;
   FILE *dns;
   bzero(buffer,256);
  
   /***********************************************************************************/
   /* Read what's been passed to the server (Should be a proper query)                */
   /***********************************************************************************/
   n = read(sock,buffer,255);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(EXIT_FAILURE);
   }
   /***********************************************************************************/
   /*If the input query is too long or short, ignore the request                      */
   /***********************************************************************************/
   if(n > 16 || n < 7) exit_error(sock,"Invalid IP address - Too long or too short.\n");
   buflen = n; /*CR LF from Telnet?*/
   buffer[buflen] = (char) 0x0;
   /***********************************************************************************/
   /* Use network function to see if the IP address looks valid                       */
   /***********************************************************************************/
   if(inet_aton(buffer, &taddr)==0) exit_error(sock,"Invalid IP address - Not dotted decimal.\n");
   //setlogmask(LOG_UPTO (LOG_NOTICE));
   //syslog(LOG_NOTICE,"%s Queried %s\n",clip, buffer); 
   /***********************************************************************************/
   /*Parse the incomming line to extract IP address octet values                     */
   /***********************************************************************************/
   p = strtok_r(buffer,".",&saveptr);
   k = 0;
   while (p) {
		if(k == 4) exit_error(sock,"IP address is invalid\n");
        	ip_octet[k]= atoi(p);
		k++;
             	p=strtok_r(NULL,".",&saveptr);
   }

   /***********************************************************************************/
   /* Got validated IP address, so go look it up                                      */
   /***********************************************************************************/

        snprintf(outline, (size_t) 500,"%s/%d/%d/f%d",fastpath,ip_octet[0],ip_octet[1],ip_octet[2]);
	dns = fopen(outline,"r");
	if(dns==NULL)  exit(EXIT_SUCCESS);
        snprintf(exact, (size_t) 30,"%d.%d.%d.%d,", ip_octet[0],ip_octet[1],ip_octet[2],ip_octet[3]);

	while(fgets(line, 500, dns)) {
		if(strstr(line,exact)) {
	  		n = write(sock, line,strlen(line));
			if(n<0) {
				perror("Error writing to socket");
				fclose(dns);
				exit(EXIT_FAILURE);
			}
		}
	}
	fclose(dns);
	exit(EXIT_SUCCESS);
}


int exit_error(int sock, char *message) {
	write(sock, message, strlen(message));
  	exit(EXIT_FAILURE);	
}
