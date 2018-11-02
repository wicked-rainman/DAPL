#include "externs.h"
void create_label(FILE* ,int, char *) ;
void draw_node(char* from, char* to) {
int x,y;
char from_str[MAX_FIELDVALUE_LENGTH];
char to_str[MAX_FIELDVALUE_LENGTH];
	if(_drop==1) return;
	x=find_fieldname(from);
	//fprintf(stdout,"draw_node: Field %s is at position %d\n",from,x);
	if(x<0) return;
	y=find_fieldname(to);
	//fprintf(stdout,"draw_node: Field %s is at position %d\n",to,y);
	if(y<0) return;
	if(_dfile==NULL) {
		fprintf(stderr,"draw_node: No graphics output file defined. Aborting\n");
		exit(EXIT_FAILURE);
	}
	//fprintf(stdout,"draw_node : From [%s] %s\n",_fieldnames_array[x],_fieldvalues_array[x]);
	//fprintf(stdout,"draw_node : To [%s] %s\n",_fieldnames_array[y],_fieldvalues_array[y]);
	if(strlen(_fieldvalues_array[x])==0) return;
	if(strlen(_fieldvalues_array[y])==0) return;

		//From
		from_str[0]='\0';
		if(strlen(_fieldcomps_array[x])>0) strcat(from_str,_fieldcomps_array[x]);
		else  strcat(from_str,_fieldvalues_array[x]);

		//To
		to_str[0]='\0';
		if(strlen(_fieldcomps_array[y])>0) strcat(to_str,_fieldcomps_array[y]);
		else strcat(to_str,_fieldvalues_array[y]);
		create_label(_dfile,x,from_str);
		create_label(_dfile,y,to_str);
		fprintf(_dfile,"%s -> %s\n",from_str,to_str);

}
void create_label(FILE* outfile,int pos,char *dir_str) {
char label[MAX_FIELDVALUE_LENGTH];
int l;
	label[0]='\0';
	l=0;
	//If attribs have been allocated
	if(strlen(_fieldattribs_array[pos])>0) {
		strcpy(label,"[");
		if(strlen(_fieldattribs_array[pos])>MAX_FIELDVALUE_LENGTH+3) return;
		strcat(label,_fieldattribs_array[pos]);
		l=1;
	}
	//If label values have been allocated
	if(strlen(_fieldlabels_array[pos])>0) {
		if(l==1) {
			strcat(label,",label=");
			if(strlen(_fieldlabels_array[pos])+strlen(label)>MAX_FIELDVALUE_LENGTH+3) return ;
			strcat(label,_fieldlabels_array[pos]);
		}
		else {
			strcat(label,"[label=");
			if(strlen(_fieldlabels_array[pos])+strlen(label)>MAX_FIELDVALUE_LENGTH+3) return ;
			strcat(label,_fieldlabels_array[pos]);
		}
		strcat(label,"];\n");
		fprintf(outfile,"%s %s",dir_str,label);
	}
	//Label is just the field value
	else {
                if(l==1) {
                        strcat(label,",label=");
                        strcat(label,_fieldvalues_array[pos]);
                }
                else {
                        strcat(label,"[label=");
                        strcat(label,_fieldvalues_array[pos]);
                }
                strcat(label,"];\n");
                fprintf(outfile,"%s %s",dir_str,label);

	}
}

