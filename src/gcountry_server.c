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
void remchars(char*, char*);
char countrypath[100];

int main() {
   int sockfd, newsockfd;
   size_t clilen;
   struct sockaddr_in serv_addr, cli_addr;
   int pid;
   char *gcountry_port;
   char *country_path;
   int country_port_int=0;
   setlogmask(LOG_UPTO (LOG_NOTICE));
   openlog("gcountryd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
   syslog(LOG_NOTICE,"Starting up\n");

   if((country_path = getenv("GREFERENCE"))) {
	strcpy(countrypath,country_path);
	strcat(countrypath,"/GeoIPCountry.csv");
   }
   else {
        syslog (LOG_NOTICE,"$GREFERENCE environment not set.\n");
        syslog (LOG_NOTICE,"Aborting\n");
        exit(EXIT_FAILURE);
   }
   syslog(LOG_NOTICE,"Using Country lookup table in %s\n",countrypath);
   if ((gcountry_port =getenv("GCOUNTRY_PORT"))) country_port_int = atoi(gcountry_port);
   else {
        syslog (LOG_NOTICE,"$GCOUNTRY_PORT environment not set.\n");
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
   serv_addr.sin_port = htons((uint16_t) country_port_int);
   if (bind(sockfd, (struct sockaddr *) &serv_addr, (socklen_t) sizeof(serv_addr)) < 0) {
   	syslog(LOG_NOTICE,"Could not bind. Aborting\n");
   	exit(EXIT_FAILURE);
   }
   if(listen(sockfd,5)!=0) {
	syslog(LOG_NOTICE,"Could not listen on socket\n");
	exit(EXIT_FAILURE);
   }
   clilen = sizeof(cli_addr);
   syslog(LOG_NOTICE,"Listening on port %s\n",gcountry_port);
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
  
int k,buflen,found;
int ip_octet[4]={0,0,0,0};
uint32_t ip_int=0;
uint32_t stored_start=0;
uint32_t stored_end=0;
char start_str[50];
char end_str[50];
char country_str[100];
char *p, *saveptr;
FILE *country=NULL;
bzero(buffer,256);
bzero(ip,50);
  
/***********************************************************************************/
/* Read what's been passed to the server (Should be a proper query)                */
/***********************************************************************************/
	n = read(sock,buffer,255);
	while(n>0) {
		buflen = n;
		if (n>0) {
			buffer[buflen] ='\0' ;
			if(buffer[buflen-1]=='\n') buffer[buflen-1] = '\0';
			if(strncmp(buffer,"EXIT",4)==0) {
				fclose(country);
				return;
			}

   		}
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
   		/* File format looks like this.....                                                */
   		/* "1.11.0.0","1.11.255.255","17498112","17563647","KR","Korea, Republic of"       */
   		/***********************************************************************************/
		if(country==NULL) {
			country = fopen(countrypath,"r");
			if(country<0) {
				 exit(EXIT_SUCCESS);
			}
		}
		rewind(country);
		found=0;
		while((fgets(line, 500, country)) && (found!=1)) {
			remchars("\"",line);
			buflen = strlen(line);
			k=0;
			n=0;
			while((line[k]!=',') && (k<buflen)) {    //Numeric IP start
				start_str[n] = line[k++];
				n++;
			}
			start_str[k] = '\0';
			k++;
			n = 0;
			while((line[k] !=',') && (k<buflen)) {  //Numeric IP end
				end_str[n] = line[k++];
				n++;
			}
			end_str[n] = '\0';
			k++;
			n = 0;
			while(k<buflen) {		       //Country data
				country_str[n] = line[k++];
				n++;
			}
			country_str[n] = '\0';
			stored_start = atol(start_str);
			stored_end = atol(end_str);
			if((ip_int >= stored_start) && (ip_int <= stored_end)) {
				found=1;
				n = write(sock, country_str,strlen(country_str));
				if(n<0) {
					perror("Error writing to socket");
					return;
				}
			}
		}
		if(found==0) {
			write(sock,"UNKNOWN,UNKNOWN\n",20);
		}
		n=read(sock,buffer,255);
	}
	fclose(country);
	return;
}

int exit_error(int sock, char *message) {
	write(sock, message, strlen(message));
  	exit(EXIT_FAILURE);	
}


