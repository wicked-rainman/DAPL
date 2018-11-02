#include "externs.h"
static int extract_fieldname_value_pair(int, char*, char*);
//***********************************************************************
// Email importer - part of the process_email code.
// Attempts to convert an email (.eml format) into a CSV record.
// Note that this program get's called once for each input file - as 
// invoked by the email_processor routine. 
// The emails are more than likely to be spam, so this makes the whole
// process a nightmare as you can't really predict what curve balls are
// going to present themselves.
// Some guesswork rules are here:
// 1. Header lines start with a field: value pair. This is deteccted
//    by the presence of the separating ":" character.
// 2. Header lines can continue onto 1 or more continuation lines. To
//    detect this, there always appears to be a space in the first column.
// 3. Header fields seem to be terminated by two blank lines. What follows
//    is the email payload.
// 4. One email per file. I don't try to cope with multiple emails in a
//    single file. If that happens, then all subsequent emails (after the
//    first) will be considered a continuation of the email payload.
// 5. Some emails are going to have a large payload. The code should
//    just stop reading lines once the value FIELD_VALUE_LENGTH is 
//    exceeded. Overall, I currently stop after 1M. See the
//    defaults.h file - Change these values if you like.
//
// The only parameter to this routine is the name of the input file to 
// be read. 
// It populates the _fieldnames_array and fieldvalues_array (global) 
// defined in core.h. These eventually become CSV records as determined
// by the email_processor routine. Much of that processing is determined
// by the loop process which is user-defined.
//***********************************************************************

int import_eml(char *filename) {
FILE *filep;
int k,l;
int nread;
int fieldname_len;
int text_block_len;
char fieldval[MAX_FIELDVALUE_LENGTH];
char fieldname[MAX_FIELDNAME_LENGTH];
char text_block[MAX_FIELDVALUE_LENGTH];

	filep=fopen(filename,"r");
	if(filep==NULL) {
		fprintf(stderr,"import_eml: Could not open file \"%s\"\n",filename);
		exit(EXIT_FAILURE);
	}
        fieldname[0]='\0';
        fieldval[0]='\0';
	fprintf(stderr,"import_eml: Processing \"%s\"\n", filename);
	nread=getline(&_input_line,&_input_line_length,filep);
	// *******************************************************************************
	// The eml format appears to be a block of header lines followed by two blanks, 
	// and then the message text. 
	// Deal with header lines first.
	//
	// *******************************************************************************
	//*******************************************************
	// Read a line from the input file (just opened).
	// Continue doing this until
	// 1. You get a read error (EOF)
	// 2. You get a line of length 1 (This should be the first
	//    blank line indicating the end of header fields).
	//*******************************************************
	while((nread!=1) && (nread!=-1)) {
		//*****************************************************
		// We're creating values that will populate a CSV file.
		// Remove all \" characters in the input else it will
		// confuse any spread-sheet software later....
		//*****************************************************
		nread=remchars("\"",_input_line);
		//***************************************************
		// If the input line is too big, then we'll just give
		// up processing this input file.
		//****************************************************
		if(nread>=MAX_INPUT_LINE_LENGTH) {
			fprintf(stderr,"import_eml : FATAL! An input line in file \"%s\" exceeded maximum length (%d>%d)\n",filename,nread,MAX_INPUT_LINE_LENGTH);
			(void) fclose(filep);
			return(0);
		}
		//**************************
		// Line not too big
		//***************************
		else {
			//****************************************************
			// If the line doesn't start with a blank, it's not
			// a continuation line. Must be a new field definition
			//******************************************************
			if(_input_line[0]!=' ') { //This isn't a file continuation line
				//********************************************************
				//If already have a fieldname, output it and it's values
				//********************************************************
				fieldname_len=(int) strlen(fieldname);	
				if(fieldname_len>0) {
					//*********************************
					//Store away the one we've started
					//*********************************
					insert_new_field(fieldname,fieldval);
                                        fieldname[0]='\0';
                                        fieldval[0]='\0';
					//*****************************
					//Now deal with the new one.
					//*****************************
					k=extract_fieldname_value_pair(nread, fieldname,fieldval);
				}
				else { 
					//*****************************
					//No fieldname stored yet
					//*****************************
					k=extract_fieldname_value_pair(nread,fieldname,fieldval);
				}
			}
			//*******************************************
			// Else, first char in line is a blank, so
			// it's a Continuation field content line
			//*******************************************
			else {
				//**************************************
				// Add the line to the field value
				//**************************************
				l=(int)strlen(fieldval);
				k=0;
				while((k<=nread) && (l<MAX_FIELDVALUE_LENGTH)) {
					fieldval[l]=_input_line[k];
					l++;
					k++;
				}
				l--;
				fieldval[l-1]='\0'; //0x0d
			}
		}
		//*********************************
		//* Get the next line in the file
		//*********************************
		nread=getline(&_input_line,&_input_line_length,filep);
	}
	//************************************************
	// EOF, or just read a line with nowt in it..
	// If we've got a fieldname value pair that's not
	// been written out yet, do so now.
	//***********************************************
	if(strlen(fieldname)>0) {
		insert_new_field(fieldname,fieldval); 
	} 
	//**************************************************
	// Read the (expected) second blank line, then
	// deal with the message text..........  
	//**************************************************
	nread=getline(&_input_line,&_input_line_length,filep); //Second blank line
	nread=getline(&_input_line,&_input_line_length,filep); //First of email payload
	text_block[0]='\0';
	text_block_len=0;
	//*******************************************************
	// Keep sticking any remaining lines into the text block
	// or bug out if the message gets toooooo big..
	//*******************************************************
	while((nread!=-1) && (text_block_len<MAX_FIELDVALUE_LENGTH-2)) {
		//****************************************************
		// Replace any quotes with spaces, and do ditto
		// with any new line chars. We just don't want them 
		// appearing in a csv file!
		//****************************************************
 		replace_char('"',' ',_input_line);
		replace_char('\n',' ',_input_line);
		if((strlen(_input_line)+strlen(text_block))>= MAX_FIELDVALUE_LENGTH-2) {
			fprintf(stderr,"import_eml: WARNING    message text in \"%s\" is too long and will be truncated\n",filename);
			break;
		}
		else {
			strcat(text_block, _input_line);
			text_block_len=strlen(text_block);
			nread=getline(&_input_line,&_input_line_length,filep);
		}
	}
	//*************************************
	// Dun reading dat dere file, so store
	// the message text, and close the 
	// input file. How tidy.
	//************************************
	insert_new_field("text",text_block);
	(void) fclose(filep);
	//***************************************************
	//Call received_ip to extract all the IP adddresses
	//out of all the "received by" lines
	//****************************************************
	received_ip();
	//*****************************************
	// Go through the text block, and extract
	// out any embedded href links... being
	// as this is probably spam, they ain't arf
	// interesting to have store separately
	//*****************************************
	extract_hrefs("text");
	//*******************************************
	//I don't know why they stick the X-Originatin_IP
	//value in square brackets. take em off,
	//*******************************************
        remove_chars("X-Originating-IP","[]");
	//*******************************************************
	//_field_count is the number of field/value pairs stored
	// (It get's incremented by insert_new_field)
	//********************************************************
	return(_field_count);
}

//***************************************************************************
// extract_fieldname_value_pair, as a function, does kind of what you would
// expect. All works round looking for a colon.......
//**************************************************************************
int extract_fieldname_value_pair(int nread, char* fieldname, char* fieldval) {
int k,l,found;
	_input_line[nread-1]='\0'; //0x0d 0x0a ???
	nread-=2;
	k=0;
	found=0;
	while((found==0) && (k<=nread) && (k<MAX_FIELDNAME_LENGTH)) {
		if(_input_line[k]!=':') {
			fieldname[k]=_input_line[k];
			k++;
		}
		else {
			found=1;
		}
	}
	if(found==1) {
		fieldname[k]='\0';
	}
	else {
		//Joe is awesome!!!
		fprintf(stderr,"No fieldname delimiter found on line \"%s\" Terminating\n",_input_line);
		return(0);
	}
        l=0;
        k+=2;
        while((k<=nread) && (l<MAX_FIELDVALUE_LENGTH-1)) {
        	fieldval[l]=_input_line[k];
        	k++;
        	l++;
        }
        fieldval[l]='\0';
	if(l==MAX_FIELDVALUE_LENGTH) {
		fprintf(stderr,"Value for field \"%s\" exceeds maximum length permitted\n",fieldname);
		return(0);
	}
	return(1);
}
