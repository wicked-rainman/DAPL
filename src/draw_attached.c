#include "externs.h"
void draw_chain(char *anchor, char *chain, char direction) {
int x,ctr;
	if(_drop==1) return;
	x=find_fieldname(anchor);
	if(x<0) return;
	build_target_list(chain);
	if(direction=='<') {
		draw_node(tlist.name[0],anchor);
		for(ctr=1;ctr<tlist.count;ctr++) {
			draw_node(tlist.name[ctr],tlist.name[ctr-1]);
		}
	}
	else {
		draw_node(anchor,tlist.name[0]);
		for(ctr=1;ctr<tlist.count;ctr++) {
			draw_node(tlist.name[ctr-1],tlist.name[ctr]);
		}
	}
}
