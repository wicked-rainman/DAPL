#include "externs.h"
void input_clean(char *substring) {
char newstring[MAX_INPUT_LINE_LENGTH];
int start_pos,end_pos;
size_t substring_length;
	substring_length=strlen(substring);
	start_pos=strpos(_input_line,substring);
	while(start_pos>=0) {
		end_pos=start_pos+substring_length;
		strncpy(newstring,_input_line,(size_t)start_pos);
		newstring[start_pos]=(char)0x0;
		strcat(newstring,&_input_line[end_pos]);
		strcpy(_input_line,newstring);
	        start_pos=strpos(_input_line,substring);
	}
}
