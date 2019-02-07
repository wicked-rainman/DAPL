#include "../src/externs.h"
void setup() {
	set_input(',',"/shared/force4/output/force4.csv");
	set_graphics("/shared/force4/output/force4.dot","neato");
}
void loop() {
	add_field("server","Force4");

	add_attributes("server","color=red,shape=doublecircle");
	add_attributes("reason","color=red,shape=parallelogram");
	add_attributes("file","color=blue,shape=box");

	add_composite("source_ip.country","reason file ");
	add_composite("source_ip.asn","source_ip.country reason file ");
	add_composite("source_ip","reason file ");
	add_composite("reason","file");
	if(substring("history","TOR")) add_attributes("source_ip","color=red,shape=diamond");

	add_label("source_ip"," * *.rdns history hack-type");

	draw_path("server file reason source_ip.country source_ip.asn source_ip");
	//draw_path("server file reason res source_ip.country source_ip.asn ");
}
