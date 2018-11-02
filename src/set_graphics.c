#include "externs.h"
void set_graphics(char *fname, char*graph_engine) {
	_dfile=fopen(fname,"w");
        if(_dfile==NULL) {
        	sprintf(error_message,"Graphics file %s",fname);
                perror(error_message);
		exit(EXIT_FAILURE);
	}
	if(strlen(graph_engine)>19) {
		fprintf(stderr,"set_graphics: Invalid render engine definition\n");
		exit(EXIT_FAILURE);
	}
	if(strcmp(graph_engine,"neato")==0) strcpy(_graph_engine, graph_engine);
	if(strcmp(graph_engine,"twopi")==0) strcpy(_graph_engine, graph_engine);
	if(strcmp(graph_engine,"circo")==0) strcpy(_graph_engine, graph_engine);
	if(strcmp(graph_engine,"patchwork")==0) strcpy(_graph_engine, graph_engine);
	if(strcmp(graph_engine,"fdp")==0) strcpy(_graph_engine, graph_engine);
	if(strcmp(graph_engine,"sfdp")==0) strcpy(_graph_engine, graph_engine);
	if(strlen(_graph_engine)==0) {
		fprintf(stderr,"set_graphics: Invalid engine specified. Options are neato,twopi,circo,patchwork,fdp or sfdp\n");
		exit(EXIT_FAILURE);
	}
        fprintf(_dfile,"digraph Susan_Barlow {\n");
        fprintf(_dfile,"layout=%s;\n",_graph_engine);
        fprintf(_dfile,"overlap=false;\n");
        fprintf(_dfile,"center=1;\n");
        fprintf(_dfile,"concentrate=true;\n");

}
