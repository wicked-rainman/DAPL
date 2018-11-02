#include "externs.h"
void build_target_list(char *fld) {
// *********************************************************************
// build_target_list
//
// This function is passed a fieldname string that represents the base
// value for (potentially) lots of fieldnames. For example, if the string
// "fred*" is passed, there could be fred_1, fred_2,fred_3 Etc.
// The code loops through, trying to find the additional fields, and 
// populates the struct tlist with those fields and a total field count.
// For some obscure reason, tlist ended up having to be a global. I presume
// it's too big to maintain on the stak and passed by reference. 
// tlist is defined as:
// typedef struct  {
//        char name[MAX_FIELD_COUNT][MAX_FIELDVALUE_LENGTH];
//        int position[MAX_FIELD_COUNT];
//        int count;
// } _target_list;
//
// ************************************************************************
int x,y,ctr;
char ctr_str[10];
char temp_fieldname[MAX_FIELDNAME_LENGTH];
char fieldname[MAX_FIELDNAME_LENGTH];
char head[MAX_FIELDNAME_LENGTH];
char tail[MAX_FIELDNAME_LENGTH];
	if(_drop==1) return;
	y=strpos(fld,"*");
	// ****************************************************************
	//If the fieldname parameter does not have an *, then just
	//copy the fieldname into the tlist and return. If the fieldname
	//doesn't exist, then just null out tlist and return
	// ****************************************************************
	if(y<0) {
		x=find_fieldname(fld);
		if(x>=0) {
			tlist.count=1;
			tlist.position[0]=x;
			strcpy(tlist.name[0], fld);
		}
		else {
			tlist.count=0;
			tlist.position[0]=0;
			tlist.name[0][0]='\0';
		}
		return;
	}
	// *********************************************************
	// Fieldname contains an * at the end. Drop the * off
	// to make a fieldname that can be searched for.
	// If the fieldname can't then be found, just return
	// ********************************************************
	strcpy(tail,&fld[y+1]);//The bit after an *
	strncpy(head,fld,(size_t) y);//The bit up to an *
	head[y]='\0';

	strcpy(fieldname,head);
	strcat(fieldname,tail);
	x=find_fieldname(fieldname);
	if(x<0) {
		tlist.count=0;
		tlist.position[0]=0;
		tlist.name[0][0]='\0';
		return;
	}
	// *******************************************************
	// Base fieldname found. Now start adding _n to the name
	// and whilst that's found, just populate the tlist
	// ******************************************************
	tlist.count=1;
	tlist.position[0]=x;
	strcpy(tlist.name[0],fieldname);
	temp_fieldname[0]='\0';
	ctr=1;
	// ***********************************************
	// While the constructed fieldname can be found
	// ***********************************************
	while(x>=0) {
        	strcpy(temp_fieldname,head);
                sprintf(ctr_str,"_%d",ctr);
                strcat(temp_fieldname,ctr_str);
		strcat(temp_fieldname,tail);
                x=find_fieldname(temp_fieldname);
		if(x>=0) {
			strcpy(tlist.name[tlist.count],temp_fieldname);
			tlist.position[tlist.count]=x;
			tlist.count++;
                	ctr++;
		}
	}
} 
