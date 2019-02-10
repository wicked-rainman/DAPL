// ---------------------------------------------------------------------------------
// example4.c
//
// Read in a small file that contains some IP addresses and other fields.
// Add the IP address country and asn values, ditch the unwanted fields and 
// graphically show the relationship between the IP addresses, countrys and ASNs.
//
// 1. Set the input file to be ../input_data/input1.csv
// 2. Set the graphics output file to be ../output_data/output4.dot and use the
//    "twopi" rendering algorythm.
//
// 3. For every record containing a "source_ip" field, add the IP country code and IP ASN
// 4. Add the IP address name field to the graphics node for the IP address field
// 5. Colour the country node red.
// 5. Draw the relationship between the fields source_ip, ASN and country using
//    the draw_path function instead of several draw_node calls. 
//
// --------------------------------------------------------------------------------

#include "../src/externs.h"
void setup() {
	set_input(' ',"../input_data/input1.csv");
	set_graphics("../output_data/output4.dot","twopi");
}
void loop() {
	add_country("source_ip"); add_asn("source_ip");
	add_label("source_ip", "name *");
	add_attributes("source_ip.country","color=red");
	draw_path("source_ip,source_ip.asn,source_ip.country");
}
