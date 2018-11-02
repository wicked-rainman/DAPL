#include "externs.h"
void insert_new_field(char *suggested_fieldname, char *fieldvalue) {
int k,l,m;
char fieldname[MAX_FIELDNAME_LENGTH];
char temp_fieldname[MAX_FIELDNAME_LENGTH];
char head[MAX_FIELDNAME_LENGTH];
char tail[MAX_FIELDNAME_LENGTH];
int ctr;
char ctr_str[10];
	if(_drop==1) return;
	if(_field_count==MAX_FIELD_COUNT-1) {
		fprintf(stderr,"insert_new_field: Adding [%s]:\"%s\" failed. MAX_FIELD_COUNT reached\n",suggested_fieldname,fieldvalue);
		return;
	}
	m=strlen(fieldvalue);
	l=strpos(suggested_fieldname,"*");
	if(l<0) {
		k=find_fieldname(suggested_fieldname);
		if(k>=0) {
		//Fieldname exists so we have to make it a new unique name based on what is suggested.
			ctr=1;
			while(k>=0) {
				strcpy(temp_fieldname,suggested_fieldname);
				sprintf(ctr_str,"_%d",ctr);
				strcat(temp_fieldname,ctr_str);
                		if(strlen(temp_fieldname)>=MAX_FIELDNAME_LENGTH) {
                        		fprintf(stderr,"insert_new_field: WARNING Field \"%s\" exceeds maximum fieldname length(%d)\n",temp_fieldname,MAX_FIELDNAME_LENGTH);
                        		return;
                		}

				k=find_fieldname(temp_fieldname);
				ctr++;
			}
			strcpy(fieldname,temp_fieldname);
		}
		else {
			strcpy(fieldname,suggested_fieldname);
		}
		//This is a backstop check. The test should NEVER pass so it's a waste of time doing it..... but.....
		//For the sake of one strlen call, seems worth the peace of mind
        	if(strlen(fieldname)>=MAX_FIELDNAME_LENGTH) {
        		fprintf(stderr,"insert_new_field: WARNING Field \"%s\" exceeds maximum fieldname length(%d)\n",fieldname,MAX_FIELDNAME_LENGTH);
                	return;
        	}
		//This is another backstop check. The test should NEVER pass so it's a waste of time doing it..... but.....
		//For the sake of one strlen call, seems worth the peace of mind
		if(strlen(fieldvalue)>MAX_FIELDVALUE_LENGTH) {
			fprintf(stderr,"insert_new_field: WARNING Fieldvalue \"%s\" exceeds maximum field value length (%d) exceeded\n",fieldvalue,MAX_FIELDVALUE_LENGTH);
			return;
		}

		strcpy(_fieldnames_array[_field_count],fieldname);
		if(m>0) {
			strcpy(_fieldvalues_array[_field_count],"\"");
			strcat(_fieldvalues_array[_field_count],fieldvalue);
			strcat(_fieldvalues_array[_field_count],"\"");
		}
		else  _fieldvalues_array[_field_count][0]='\0';
		//fprintf(stdout,"insert_new_field : [%s] %s\n",_fieldnames_array[_field_count],_fieldvalues_array[_field_count]);
		_field_count++;
		return;
	}
	else {// asterix found in fieldname
		strcpy(tail,&suggested_fieldname[l+1]);
		strncpy(head,suggested_fieldname,l);
		head[l]='\0';
		temp_fieldname[0]='\0';
		strcpy(temp_fieldname,head);
		strcat(temp_fieldname,tail);
                if(strlen(temp_fieldname)>=MAX_FIELDNAME_LENGTH) {
                        fprintf(stderr,"insert_new_field: WARNING Field \"%s\" exceeds maximum fieldname length(%d)\n",temp_fieldname,MAX_FIELDNAME_LENGTH);
                        return;
                }

		k=find_fieldname(temp_fieldname);
		if(k<0) {
			strcpy(_fieldnames_array[_field_count],temp_fieldname);
			if(m>0) {
				strcpy(_fieldvalues_array[_field_count],"\"");
				strcat(_fieldvalues_array[_field_count],fieldvalue);
				strcat(_fieldvalues_array[_field_count],"\"");
			}
			else  _fieldvalues_array[_field_count][0]='\0';
			_field_count++;
			return;
		}
		ctr=1;
		while(k>=0) {
			strcpy(temp_fieldname,head);
			sprintf(ctr_str,"_%d",ctr);
			strcat(temp_fieldname,ctr_str);
			strcat(temp_fieldname,tail);
               		if(strlen(temp_fieldname)>=MAX_FIELDNAME_LENGTH) {
                        	fprintf(stderr,"insert_new_field: WARNING Field \"%s\" exceeds maximum fieldname length(%d)\n",temp_fieldname,MAX_FIELDNAME_LENGTH);
                        	return;
                	}
			k=find_fieldname(temp_fieldname);
			ctr++;
		}
                strcpy(_fieldnames_array[_field_count],temp_fieldname);
		if(m>0) {
                	strcpy(_fieldvalues_array[_field_count],"\"");
                	strcat(_fieldvalues_array[_field_count],fieldvalue);
                	strcat(_fieldvalues_array[_field_count],"\"");
		}
		else _fieldvalues_array[_field_count][0]='\0';
		//fprintf(stdout,"insert_new_field : [%s] %s\n",_fieldnames_array[_field_count],_fieldvalues_array[_field_count]);
                _field_count++;
		return;
	}
}
