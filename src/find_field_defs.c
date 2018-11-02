#include "externs.h"
/*****************************************************************/
/* Function to detect if the current line defines field names in */
/* a CSV'esq input file. 1 is yes, 0 is no.                      */
/*****************************************************************/

int find_field_defs() {
	if(memcmp(_csv_definition_start,_input_line, (size_t) _csv_definition_start_length ) !=0) {
		 return(0); 
	}
	fprintf(stdout,"find_field_defs : %s found.\n",_csv_definition_start);
	return(1);
}
