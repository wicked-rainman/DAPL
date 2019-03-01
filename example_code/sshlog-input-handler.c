// ----------------------------------------------------------------------------
// Simple input handler for processing SSH logs.
// ASN, Country code, reverse dns and history are added to each input record.
// DTG field is created out of the month,day and time fields.
// Only records that relate to a successful login are kept. 
// -----------------------------------------------------------------------------

#include "../src/externs.h"
FILE *history;
void setup() {
	define_input_fieldnames(' ',"month day time www sshd accepted password for reason from source_ip ");
	set_input_directory(' ',"/shared/input/security/");
	set_output("/shared/output/security.csv");
	history=table("/home/susan/dev/Reference/bad_ip.tbl");

}
void loop() {
	if(match("accepted","Accepted") and match("password","password")) keep; else drop;
	add_field("file","ssh_logs");
	lookup(history,"source_ip","history");
	add_asn("source_ip");
	add_country("source_ip");
	add_reverse_dns("source_ip");
	add_concatenation("dtg"," day '/' month '/2018:' time");
	write_csv_fields("file reason dtg source_ip source_ip.asn source_ip.country source_ip.rdns history");
}
