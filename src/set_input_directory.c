#include "externs.h"
void set_input_directory(char delim, char *dir_name) {
DIR *d;
char newname[MAX_FILENAME_LENGTH];
struct dirent *dir;
size_t fname_length;
size_t dirname_length;
	d = opendir(dir_name);
	dirname_length=strlen(dir_name);
	_field_delimiter=delim;
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (dir->d_type == DT_REG) {
				if(_input_file_count < MAX_INPUT_FILE_COUNT-1) {
					fname_length=strlen(dir->d_name);
					if(fname_length>(MAX_FILENAME_LENGTH - dirname_length)) {
						fprintf(stderr,"set_input_directory: File name \"%s\" is too long\n",dir->d_name);
						exit(EXIT_FAILURE);
					}
					else {
						strcpy(newname,dir_name);
						strcat(newname, dir->d_name);
						strcpy(_input_file_names[_input_file_count], newname);
						_input_file_count++;
					}
				}
				else {
					fprintf(stderr,"set_input_directory: Too many files in directory to process\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		(void) closedir(d);
	}
	else {
		fprintf(stderr,"set_input_directory: Failed to open directory \"%s\"\n", dir_name);
		exit(EXIT_FAILURE);
	}
	if(_input_file_count==0) {
		fprintf(stderr,"set_input_directory: Found no files to process!\n");
		exit(EXIT_FAILURE);
	}
	return;
}
