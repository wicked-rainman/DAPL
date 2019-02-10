// ---------------------------------------------------------------------------------
// example5.c
//
// In example4.c not all of the input records are shown in the graphics render. This
// is because some of the IP addresses have been duplicated. Such duplicates are
// ignored by the graphics processing. For them to be included, the IP addresses
// must be made unique in some way. 
//
// The function "add_composite" temporarily makes the IP address unique by adding
// to it the date and the time from each input record. This just has an effect on
// the graphics rendering, and does not change the underlying data. 
//
// If event modeling is taking place, doing this effectively removes the de-dupe. 
//
//
// --------------------------------------------------------------------------------

#include "../src/externs.h"
void setup() {
	set_input(' ',"../input_data/input1.csv");
	set_graphics("../output_data/output5.dot","twopi");
}
void loop() {
	add_composite("source_ip","date, time");
	add_country("source_ip"); add_asn("source_ip");
	add_label("source_ip", "name * date,time");
	add_attributes("source_ip","color=red,shape=rectangle");
	add_attributes("source_ip.country","shape=diamond");
	draw_path("source_ip,source_ip.asn,source_ip.country");
}
