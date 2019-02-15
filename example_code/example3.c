// ---------------------------------------------------------------------------------
// example3.c
//
// Read in a small file that contains some IP addresses and other fields.
// Add the IP address country and asn values, ditch the unwanted fields and 
// graphically show the relationship between the IP addresses, countrys and ASNs.
//
// 1. Set the input file to be ../input_data/input1.csv
// 2. Set the graphics output file to be ../output_data/output3.dot and use the
//    "neato" rendering algorythm.
//
// 3. For every record containing a "source_ip" field, add the IP country code and IP ASN
// 4. Add the IP address name field to the graphics node for the IP address field
// 5. Draw the relationship between source_ip and ASN
// 6. Draw the relationship between ASN and country
//
// NOTE:
// To create the graphic, the output .dot file needs to be processed using Graphviz -
//     dot -Tsvg output3.dot > output3.svg
// --------------------------------------------------------------------------------

#include "../src/externs.h"
void setup() {
	set_input(' ',"../input_data/input1.csv");
	set_graphics("../output_data/output3.dot","neato");
}
void loop() {
	add_country("source_ip"); add_asn("source_ip");
	add_label("source_ip", "name *");
	draw_node("source_ip","source_ip.asn");
	draw_node("source_ip.asn","source_ip.country");
}
