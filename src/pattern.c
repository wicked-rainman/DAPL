#include "externs.h"
int pattern(char* fieldname, char* expression) {
int rc,target_count;
regex_t regex;
        if(_drop==1) return 0;
        rc=regcomp(&regex,expression,REG_EXTENDED);
        if(rc!=0) {
                fprintf(stdout,"pattern : Invalid expression \"%s\". Quitting\n",expression);
                exit(EXIT_FAILURE);
        }
        target_count=0;
        build_target_list(fieldname);
        while(target_count<tlist.count) {
                rc = regexec(&regex,_fieldvalues_array[tlist.position[target_count]],0,NULL,0);
                if(rc == 0) {
                        regfree(&regex);
                        return 1;
                }
                target_count++;
        }
        regfree(&regex);
	return 0;
}
