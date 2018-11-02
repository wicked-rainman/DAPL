#include "externs.h" 
int remchars(char *dels, char *instr) {
size_t buflen,k;
char outstr[MAX_INPUT_LINE_LENGTH];
int n,l,delcount,found;
        buflen = strlen(instr);
	delcount = strlen(dels);
        n = 0;
	found=0;
        for(k=0;k<buflen;k++) {
		for(l=0;l<delcount;l++) {
                	if(instr[k] == dels[l]) {
				found=1;
				break;
			}
		}
		if(found==0) {
			outstr[n]=instr[k];
			n++;
		}
		found=0;
        }
        outstr[n]='\0';
        strcpy(instr,outstr);
        return n;
}
