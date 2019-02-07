#include "../src/externs.h"
FILE *history;
FILE *urls;
void setup() {
	define_input_fieldnames(' ',"source_ip dash1 dash2 dtg offset url retcode bytes referal browser");
	set_input_directory(' ',"/shared/input/web_server/");
	set_output("/shared/output/web.csv");
	history=table("/home/wr/dev/Reference/bad_ip.tbl");
	urls=table("/home/wr/dev/Reference/bad_url.tbl");
}
void loop() {
	if(match("retcode","200")) keep; else drop;

	if(lookup(history,"source_ip","history")) {
                add_field("reason","seen-before");
        }

	else if(lookup(urls,"url","hack-type")) {
		add_field("reason","hacking");
	}
	else {
		drop;
	}
	add_field("file","HTTP_logs");
	remove_string("dtg","[");
	add_country("source_ip");
	add_asn("source_ip");
	add_reverse_dns("source_ip");
        write_csv_fields("file reason dtg source_ip source_ip.rdns source_ip.country source_ip.asn url retcode referal history hack-type");
}
