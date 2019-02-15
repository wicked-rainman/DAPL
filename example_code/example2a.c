// ---------------------------------------------------------------------------------
// example2a.c
//
// Read in a small file that contains some IP addresses and other fields.
// Keep records where the name field is "TELEGRAPH" (The opposite of example2).
// Add the IP address country and asn values, ditch the unwanted fields and output
// the new records. 
// Note: As the input file has a csv field definition start tag of "#Fields:" (This is
// the default value for a definition line) we don't need to define it with a call
// to define_csv_tag(). 
//
// 1. Set the input file to be ../input_data/input1.csv
// 2. Set the output file to be ../output_data/output2.csv
//
// 3. Only process the record if the field "name" contains the string "TELEGRAPH"
// 4/5. For every record containing a "source_ip" field, add the IP country code and IP ASN
// 6. Write a CSV records that contains the source_ip, country and asn values
// --------------------------------------------------------------------------------
#include "../src/externs.h"
void setup() {
	set_input(' ',"../input_data/input1.csv");
	set_output("../output_data/output2a.csv");
}
void loop() {
	keep_if_match("name","TELEGRAPH");
	add_country("source_ip");
	add_asn("source_ip");
        write_csv_fields("source_ip source_ip.country,source_ip.asn, name");
}
