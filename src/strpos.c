#include <string.h>
int strpos(char *hay, char *needle)
{
//   char haystack[strlen(hay)];
//   strncpy(haystack, hay, strlen(hay));
//   char *p = strstr(haystack, needle);
//   if (p) return p - haystack;
//   return -1;
char *p;
	p = strstr(hay, needle);
	if (p) return (p - hay);
   	return -1;
}

