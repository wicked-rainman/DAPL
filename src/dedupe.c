#include <stdio.h>
#include <string.h>
void dedupe(char *line, char rem) {
int dupe=1;
size_t l,m,n;
	while(dupe==1) {
		dupe=0;
		l=strlen(line);
  		for(m = 1; m < l; m++) {
			if((line[m-1]==rem) && (line[m]==rem)) {
				n=m-1;
				while(line[m+1]==rem) m++;
				dupe=1;
				for(;m<l;m++) {
					line[n]=line[m];
					n++;
				}
				line[n]='\0';
				break;
			}
		}
	}	
}

