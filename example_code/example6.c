// ---------------------------------------------------------------------------------
// example6.c
//
// Same data as processed by example5, but flows shown grapically by date and time
// in order to demonstrate a different way of viewing the underlying data
//
// --------------------------------------------------------------------------------

#include "../src/externs.h"
void setup() {
	set_input(',',"../output_data/output1.csv");
	set_graphics("../output_data/output6.dot","neato");
}
void loop() {
	add_composite("time","date");
	add_composite("source_ip","date time");
	add_label("source_ip"," *, name,  *.asn  *.country ");
	draw_path("date, time, source_ip");
}
