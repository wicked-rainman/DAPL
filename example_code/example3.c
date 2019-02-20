// ---------------------------------------------------------------------------------
// example3.c - Processing output from example1.c
//
// Show the relationship between the IP addresses, countrys and ASNs.
//
// 1. Set the input file to be ../output_data/output1.csv
// 2. Set the graphics output file to be ../output_data/output3.dot and use the
//    "neato" rendering algorythm.
// 3. Draw the relationship between source_ip and ASN
// 4. Draw the relationship between ASN and country
//
// NOTE:
// To create the graphic, the output .dot file needs to be processed using Graphviz -
//     dot -Tsvg output3.dot > output3.svg
// --------------------------------------------------------------------------------

#include "../src/externs.h"
void setup() {
	set_input(' ',"../output_data/output1.csv");
	set_graphics("../output_data/output3.dot","neato");
}
void loop() {
	draw_node("source_ip","source_ip.asn");
	draw_node("source_ip.asn","source_ip.country");
}
