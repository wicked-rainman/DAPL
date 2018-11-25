#include <string.h> 
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
