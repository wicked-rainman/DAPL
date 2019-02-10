// Build by linking with ../lib/libeml.a
#include "externs.h"
void setup() {
	set_input_directory(' ',"../data/spam/");
        set_output("../output/full_outfile.csv");
}
void loop() {
	add_country("X-Originating-IP");
	add_country("Received*.ip");
	add_asn("Received*.ip");

	write_csv_fields("Date Subject From To X-Env-Sender X-Originating-IP X-Originating-IP.country Return-Path \
		Received Received_1 Received_2 Received_3 Received_4 Received_5 Received_6 Received_7 Received_8 \
		Received_9 Received_10 Received_11 Received_12 Received_13 Received_14 \
		Received.ip Received_1.ip Received_2.ip Received_3.ip Received_4.ip Received_5.ip \
		Received_6.ip Received_7.ip Received_8.ip Received_9.ip Received_10.ip Received_11.ip \
		Received_12.ip Received_13.ip Received_14.ip \
		Received.ip.country Received_1.ip.country Received_2.ip.country Received_3.ip.country \
		Received_4.ip.country Received_5.ip.country Received_6.ip.country Received_7.ip.country \
		Received_8.ip.country Received_9.ip.country Received_10.ip.country Received_11.ip.country \
		Received_12.ip.country Received_13.ip.country Received_14.ip.country \
		Received.ip.asn Received_1.ip.asn Received_2.ip.asn Received_3.ip.asn Received_4.ip.asn \
		Received_5.ip.asn Received_6.ip.asn Received_7.ip.asn Received_8.ip.asn Received_9.ip.asn \
		Received_10.ip.asn Received_11.ip.asn Received_12.ip.asn Received_13.ip.asn Received_14.ip.asn \
		text.url text.url_1 text.url_2 text.url_3 text.url_4 text.url_5 text.url_6 text.url_7 text.url_8 \
		text.url_9 text.url_10 text.url_11 text.url_12 text.url_13 text.url_14 text");
