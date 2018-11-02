#include "externs.h" 
int ipfind(char* target, char* res) {
int rc,rd;
int len;
regmatch_t match;
regex_t * myregex = calloc(1, sizeof(regex_t));
	rc=regcomp(myregex,"[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}", REG_EXTENDED);
	if(rc!=0)  {
		regfree(myregex);
		return -1;
	}
	rd=regexec(myregex,target,1,&match,0);
	if(rd==0) {
		if((int) match.rm_so<0)  {
			free(myregex);
			//regfree(myregex);
			return -1;
		}
		len = (int) match.rm_eo - (int) match.rm_so;
		memcpy(res,target+match.rm_so,len);
		res[len]='\0';
		regfree(myregex);
		return 1;
	}
	regfree(myregex);
	return -1;
}
