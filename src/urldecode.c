#include "externs.h"
void urldecode(char *fieldname) {
char a, b;
int k,l;
char *src, *dst;
	if(_drop==1) return;
	k=find_fieldname(fieldname);
	if(k>=0) {
		src = _fieldvalues_array[k];
		dst = _fieldvalues_array[k];
		while (*src) {
			if ((*src == '%') && ((a = src[1]) && (b = src[2])) && (isxdigit(a) && isxdigit(b))) {
				if (a >= 'a') a -= 'a'-'A';
				if (a >= 'A') a -= ('A' - 10);
				else a -= '0';
				if (b >= 'a') b -= 'a'-'A';
				if (b >= 'A') b -= ('A' - 10);
				else b -= '0';
				l=16*a+b;
				if(l<32) l=0x20;
				*dst++ = l;
				src+=3;
			} 
			else if (*src == '+') {
				*dst++ = ' ';
				src++;
			} 
			else {
				*dst++ = *src++;
			}
		
		}
		*dst++ = '\0';
		//add_quotes(fieldname);
	}
}
