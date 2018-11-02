#include "externs.h" 
void replace_char(char del, char ins, char *instr) {
size_t buflen,k;
//char outstr[MAX_INPUT_LINE_LENGTH];
//int n;
        buflen = strlen(instr);
//	if(buflen>MAX_INPUT_LINE_LENGTH) {
//		fprintf(stderr, "replace_char: WARNING String exceeds MAX_INPUT_LINE_LENGTH. Results will be truncated\n");
//		buflen=MAX_INPUT_LINE_LENGTH-1;
//	}
        //n = 0;
        for(k=0;k<buflen;k++) {
		if(instr[k]==del) instr[k]=ins;
                //if(instr[k] != del)outstr[n++] = instr[k];
		//else outstr[n++] = ins;
        }
        //outstr[n]=(char)0x0;
        //strcpy(instr,outstr);
        return;
}
