#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#define PEM "/etc/pki/ca-trust/extracted/pem/tls-ca-bundle.pem"
void unescape(char *);
int main(int argc, char **argv) { 
	int retcode,c;  
	BIO *bio;
    	SSL_CTX *ctx;
    	SSL *ssl;
    	char buffer[4096];
	char port[100];
	char server_request[4096];
	char server_name[4096];
	char svr_name[4096];
	char *perm_path=PEM;
	port[0]='\0';
	svr_name[0]='\0';
	server_name[0]='\0';
	server_request[0]='\0';
  	while ((c = getopt (argc, argv, "h:p:u:")) != -1) {
    		switch (c) {
      			case 'h':
        			if(strlen(optarg)>0) strcpy(svr_name,optarg);
       			 	break;
			case 'p':
				if(strlen(optarg)>0) strcpy(port,optarg);
				break;
      			case 'u':
        			if(strlen(optarg)>0) strcpy(server_request,optarg);
        			break;
			default :
				fprintf(stdout,"Usage: %s -h<hostname> -p<port> -u<URL_string>\n",argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	if((strlen(server_request)==0) || (strlen(svr_name)==0)) {
		fprintf(stdout,"Usage: %s -h<hostname> -p<port> -u<URL_string>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if(strlen(port)==0) strcpy(port,"https");
	unescape(server_request);
	strcpy(server_name,svr_name);
	strcat(server_name,":");
	strcat(server_name,port);
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	SSL_library_init();
        ctx = SSL_CTX_new(SSLv23_client_method());
        if(! SSL_CTX_load_verify_locations(ctx, perm_path, NULL)) {
                fprintf(stdout,"Could not load trust store from %s\n",perm_path);
		ERR_print_errors_fp(stderr);
            	SSL_CTX_free(ctx);
                exit(EXIT_FAILURE);
        }

    	bio = BIO_new_ssl_connect(ctx);
        BIO_get_ssl(bio, & ssl);
        SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
        BIO_set_conn_hostname(bio,server_name);
	if(bio==NULL) {
	/*  if((bio==NULL) || (bio <=0)) { */
		fprintf(stdout,"BIO_new_ssl_connect allocation failed\n");
		exit(EXIT_FAILURE);
	}
	retcode = SSL_set_tlsext_host_name(ssl,svr_name);
	if(retcode !=1) {
		fprintf(stdout,"Set SNI for %s failed\n",svr_name);
		exit(EXIT_FAILURE);
	}
	retcode=BIO_do_connect(bio);
	if(retcode <= 0) {
    		fprintf(stdout,"BIO_do_connect to %s failed (%d).\n",svr_name,retcode);
               ERR_print_errors_fp(stderr);

		exit(EXIT_FAILURE);
	}
	if (BIO_do_handshake(bio) <= 0) {
               fprintf(stderr, "Error establishing SSL connection\n");
               ERR_print_errors_fp(stderr);
               exit(EXIT_FAILURE);
        }
	buffer[0]='\0';
	BIO_write(bio,server_request,strlen(server_request));
	while(BIO_read(bio,buffer,4096)>0) {
		fprintf(stdout,"%s",buffer);
		buffer[0]='\0';
	}
	SSL_CTX_free(ctx);
}
void unescape(char *instr) {
        int len=strlen(instr);
        int k,l=0;
        for(k=0;k<len;k++) {
                if (instr[k]=='\\') {
                        if(instr[k+1]=='n') {
                                instr[l]='\n';
                                k++;
                        }
                        else if(instr[k+1]=='r') {
                                instr[l]='\r';
                                k++;
                        }
                        else {}
                }
                else {
                        instr[l]=instr[k];
                }
                l++;
        }
        instr[l]='\0';
        return ;
}

