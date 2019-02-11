// ---------------------------------------------------------------------------------
// example6.c
//
// Same data as processed by example5, but flows shown grapically by date and time
// in order to demonstrate a different way of viewing the underlying data
//
// --------------------------------------------------------------------------------

#include "../src/externs.h"
void setup() {
	set_input(' ',"../input_data/input1.csv");
	set_graphics("../graphics/output6.dot","neato");
}
void loop() {
	add_country("source_ip"); add_asn("source_ip");
	add_composite("time","date");
	add_composite("source_ip","date time");
	add_label("source_ip"," *, name,  *.asn  *.country ");
	draw_path("date, time, source_ip");
}
