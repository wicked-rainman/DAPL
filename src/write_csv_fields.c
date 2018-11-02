#include "externs.h"
void write_csv_fields(char *output_list) {
int k=0,matched=0,out_len,field_len;
char output_line[MAX_OUTPUT_LINE_LENGTH];
	if(_drop==1) {
		return;
	}
	if(_ofile==NULL) {
		_ofile=stdout;
		//fprintf(stderr,"CSV output file has not been defined!\n");
		//exit(EXIT_FAILURE);
	}
	//If the output field names have not been stored before, store them now
	if(_output_fields_defined==0) {
		_output_field_count=array_from_string(output_list, _output_field_list);
		_output_fields_defined=1;
		fprintf(_ofile,"#Fields: ");
		for(k=0;k<_output_field_count;k++) {
			fprintf(_ofile,"%s ",_output_field_list[k]);
		}
		fprintf(_ofile,"\n");
	}//Output field names stored


	//Now write out any required fields
	output_line[0]='\0';
	k=0;
	out_len=0;
	while(k<_output_field_count) {
		matched=find_fieldname(_output_field_list[k]);
		if(matched>=0) {
			field_len=(int)strlen(_fieldvalues_array[matched]);
			out_len=(int)strlen(output_line);
			if((out_len+field_len) > MAX_OUTPUT_LINE_LENGTH-2) {
				fprintf(stderr,"write_csv_fields : Maximum output line length (%d) has been exceeded\n",MAX_OUTPUT_LINE_LENGTH);
				fprintf(stderr,"write_csv_fields : If necessesary change MAX_OUTPUT_LINE_LENGTH and re-build\n");
				fprintf(stderr,"write_csv_fields : Output record lost!!!!\n");
				return;
			}
			else {
				out_len=out_len+field_len;
				strcat(output_line,_fieldvalues_array[matched]);
				strcat(output_line,",");
			}
		}
		else {
			strcat(output_line,",");
		}
		k++;
	}
	output_line[strlen(output_line)-1]='\n';
	fprintf(_ofile,"%s",output_line);
	_output_lines_written++;
	return;
}

