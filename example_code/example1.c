// -----------------------------------------------------------------------------------------
// example1.c
//
// Read in a small file that contains some IP addresses and other fields.
// Add the IP address country and asn values, ditch the unwanted fields and output
// the new records. 
//
// 1. Set the string "#Fields:" to indicate the start of a csv field definition line 
// 2. Set the input file to be ../input_data/input1.csv
// 3. Set the output file to be ../output_data/output1.csv
//
// 4/5. For every record containing a "source_ip" field, add the IP country code and IP ASN
// 6. Write a CSV records that contains the source_ip, country and asn values
// ----------------------------------------------------------------------------------------
#include "../src/externs.h"
void setup() {
	define_csv_tag("#Fields:");
	set_input(' ',"../input_data/input1.csv");
	set_output("../output_data/output1.csv");
}
void loop() {
	add_country("source_ip");
	add_asn("source_ip");
        write_csv_fields("source_ip source_ip.country,source_ip.asn, name");
}
