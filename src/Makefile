CC = clang
CFLAGS = -Ofast -Wall  
.PHONY: all
all: libdapl.a libeml.a gasn gasn_server gcountry_server gcountry ip2int int2ip \
	ip2country ip2asn cidr2ip whitelist_convert sslcat gdns_server grdns_server \
	ghistory_server gdns grdns ghistory
	mkdir -p ../lib
	mkdir -p ../progs
	mkdir -p ../tables
	mkdir -p ../output_data
	mkdir -p ../graphics
	rm -f ../input_data/readme.txt
	rm -f ../example_code/README.md
libeml.a : add_attributes.o add_composite.o add_concatenation.o \
	add_country.o add_asn.o \
	add_field.o add_label.o add_quotes.o add_reverse_dns.o add_substring.o \
	array_from_string.o build_target_list.o cleanup.o dedupe.o \
	define_csv_tag.o define_input_fieldnames.o draw_chain.o draw_node.o \
	draw_path.o drop_rec.o empty.o extract_field_values.o \
	extract_hrefs.o find_field_defs.o find_fieldname.o get_input_lines.o \
	global_clean.o hostname_to_ip.o import_eml.o init_storage.o \
	input_clean.o insert_new_field.o ipfind.o keep_rec.o \
	last_fieldname.o last_value.o lookup.o match.o \
	pattern.o substring.o processor_email.o received_ip.o \
	remchars.o remove_chars.o remove_string.o rename_field.o \
	replace_char.o set_graphics.o set_input_directory.o set_input_fieldnames.o \
	set_input.o set_output.o socketadd_asn.o socketadd_country.o \
	strpos.o unescape.o unix_time.o urldecode.o whitelist.o write_csv_fields.o

	ar -rcs libeml.a add_attributes.o add_composite.o add_concatenation.o \
	add_field.o add_label.o add_quotes.o add_reverse_dns.o \
	add_country.o add_asn.o add_substring.o \
	array_from_string.o build_target_list.o cleanup.o dedupe.o \
	define_csv_tag.o define_input_fieldnames.o draw_chain.o draw_node.o \
	draw_path.o drop_rec.o empty.o extract_field_values.o \
	extract_hrefs.o find_field_defs.o find_fieldname.o get_input_lines.o \
	global_clean.o hostname_to_ip.o import_eml.o init_storage.o \
	input_clean.o insert_new_field.o ipfind.o keep_rec.o \
	last_fieldname.o last_value.o lookup.o match.o \
	pattern.o substring.o processor_email.o received_ip.o \
	remchars.o remove_chars.o remove_string.o rename_field.o \
	replace_char.o set_graphics.o set_input_directory.o set_input_fieldnames.o \
	set_input.o set_output.o socketadd_asn.o socketadd_country.o \
	strpos.o unescape.o unix_time.o urldecode.o whitelist.o write_csv_fields.o

libdapl.a : add_attributes.o add_composite.o add_concatenation.o \
	add_field.o add_label.o add_quotes.o add_reverse_dns.o \
	add_country.o add_asn.o add_substring.o \
	array_from_string.o build_target_list.o cleanup.o dedupe.o \
	define_csv_tag.o define_input_fieldnames.o draw_chain.o draw_node.o \
	draw_path.o drop_rec.o empty.o extract_field_values.o \
	find_field_defs.o find_fieldname.o get_input_lines.o global_clean.o \
	hostname_to_ip.o init_storage.o input_clean.o insert_new_field.o \
	ipfind.o keep_rec.o last_value.o lookup.o \
	main.o match.o pattern.o substring.o \
	remchars.o remove_chars.o remove_string.o rename_field.o \
	replace_char.o set_graphics.o set_input_directory.o set_input_fieldnames.o \
	set_input.o extract_hrefs.o set_output.o socketadd_asn.o socketadd_country.o \
	strpos.o table.o unescape.o unix_time.o urldecode.o whitelist.o write_csv_fields.o

	ar -rcs libdapl.a add_attributes.o add_composite.o add_concatenation.o \
	add_field.o add_label.o add_quotes.o add_reverse_dns.o \
	add_country.o add_asn.o add_substring.o \
	array_from_string.o build_target_list.o cleanup.o dedupe.o \
	define_csv_tag.o define_input_fieldnames.o draw_chain.o draw_node.o \
	draw_path.o drop_rec.o empty.o extract_field_values.o \
	find_field_defs.o find_fieldname.o get_input_lines.o global_clean.o \
	hostname_to_ip.o init_storage.o input_clean.o insert_new_field.o \
	ipfind.o keep_rec.o last_value.o lookup.o \
	main.o match.o pattern.o substring.o \
	remchars.o remove_chars.o remove_string.o rename_field.o \
	replace_char.o set_graphics.o set_input_directory.o set_input_fieldnames.o \
	set_input.o extract_hrefs.o set_output.o socketadd_asn.o socketadd_country.o \
	strpos.o table.o unescape.o unix_time.o urldecode.o whitelist.o write_csv_fields.o

add_asn.o : add_asn.c build_target_list.o add_field.o remchars.o externs.h 
	$(CC) $(CFLAGS) add_asn.c -c -o add_asn.o
add_attributes.o : add_attributes.c externs.h defaults.h build_target_list.o
	$(CC) $(CFLAGS)  add_attributes.c -c -o add_attributes.o
add_country.o : add_country.c build_target_list.o add_field.o remchars.o externs.h 
	$(CC) $(CFLAGS) add_country.c -c -o add_country.o
add_composite.o : add_composite.c externs.h defaults.h build_target_list.o \
	array_from_string.o find_fieldname.o remchars.o
	$(CC) $(CFLAGS) add_composite.c -c -o add_composite.o
add_concatenation.o : add_concatenation.c add_field.o remchars.o externs.h find_fieldname.o
	$(CC) $(CFLAGS) add_concatenation.c -c -o add_concatenation.o
add_field.o : add_field.c externs.h find_fieldname.o
	$(CC) $(CFLAGS) add_field.c -c -o add_field.o
add_label.o : add_label.c externs.h defaults.h build_target_list.o remchars.o \
	array_from_string.o find_fieldname.o
	$(CC) $(CFLAGS) add_label.c -c -o add_label.o
add_quotes.o : add_quotes.c externs.h defaults.h find_fieldname.o
	$(CC) $(CFLAGS)  add_quotes.c -c -o add_quotes.o
add_reverse_dns.o : add_reverse_dns.c externs.h build_target_list.o insert_new_field.o
	$(CC) $(CFLAGS) add_reverse_dns.c -c -o add_reverse_dns.o
add_substring.o : add_substring.c build_target_list.o insert_new_field.o externs.h
	$(CC) $(CFLAGS) add_substring.c -c -o add_substring.o
array_from_string.o : array_from_string.c defaults.h externs.h
	$(CC) $(CFLAGS) array_from_string.c -c -o array_from_string.o
build_target_list.o : build_target_list.c defaults.h find_fieldname.o
	$(CC) $(CFLAGS) build_target_list.c -c -o build_target_list.o
cidr2ip : cidr2ip.c
	$(CC) $(CFLAGS) -lm cidr2ip.c -o cidr2ip
cleanup.o : cleanup.c defaults.h externs.h
	$(CC) $(CFLAGS)  cleanup.c -c -o cleanup.o
dedupe.o : dedupe.c
	$(CC) $(CFLAGS) dedupe.c -c -o dedupe.o
define_csv_tag.o : define_csv_tag.c defaults.h externs.h
	$(CC) $(CFLAGS)  define_csv_tag.c -c -o define_csv_tag.o
define_input_fieldnames.o : define_input_fieldnames.c externs.h defaults.h
	$(CC) $(CFLAGS)  define_input_fieldnames.c -c -o define_input_fieldnames.o
draw_chain.o : draw_chain.c draw_node.o externs.h find_fieldname.o build_target_list.o
	$(CC) $(CFLAGS) draw_chain.c -c -o draw_chain.o
draw_node.o : draw_node.c defaults.h externs.h find_fieldname.o
	$(CC) $(CFLAGS) draw_node.c -c -o draw_node.o
draw_path.o : draw_path.c externs.h array_from_string.o find_fieldname.o draw_node.o
	$(CC) $(CFLAGS) draw_path.c -c -o draw_path.o
drop_rec.o : drop_rec.c externs.h
	$(CC) $(CFLAGS)  drop_rec.c -c -o drop_rec.o
empty.o : empty.c defaults.h find_fieldname.o
	$(CC) $(CFLAGS) empty.c -c -o empty.o
extract_field_values.o : extract_field_values.c externs.h defaults.h
	$(CC) $(CFLAGS)  extract_field_values.c -c -o extract_field_values.o
extract_hrefs.o : extract_hrefs.c defaults.h externs.h insert_new_field.o find_fieldname.o
	$(CC) $(CFLAGS) extract_hrefs.c -c -o extract_hrefs.o
find_field_defs.o : find_field_defs.c externs.h
	$(CC) $(CFLAGS)  find_field_defs.c -c -o find_field_defs.o
find_fieldname.o : find_fieldname.c externs.h
	$(CC) $(CFLAGS)  find_fieldname.c -c -o find_fieldname.o
gdns : gdns_client.c 
	$(CC) $(CFLAGS) gdns_client.c -o gdns
gdns_server : gdns_server.c
	$(CC) $(CFLAGS) gdns_server.c -o gdns_server
grdns : grdns_client.c
	$(CC) $(CFLAGS) grdns_client.c -o grdns
grdns_server : grdns_server.c
	$(CC) $(CFLAGS) grdns_server.c -o grdns_server
ghistory : ghistory_client.c 
	$(CC) $(CFLAGS) ghistory_client.c -o ghistory
ghistory_server : ghistory_server.c
	$(CC) $(CFLAGS) ghistory_server.c -o ghistory_server
gasn : gasn_client.c defaults.h funcs.h hostname_to_ip.c
	$(CC) $(CFLAGS)  gasn_client.c hostname_to_ip.c  -o gasn
gasn_server: gasn_server.c remchars.o
	$(CC) $(CFLAGS)  gasn_server.c remchars.o -o gasn_server
gcountry : gcountry_client.c defaults.h funcs.h hostname_to_ip.c
	$(CC) $(CFLAGS)  gcountry_client.c hostname_to_ip.c -o gcountry
gcountry_server: gcountry_server.c remchars.c 
	$(CC) $(CFLAGS)  gcountry_server.c remchars.o -o gcountry_server
get_input_lines.o : get_input_lines.c externs.h defaults.h
	$(CC) $(CFLAGS)  get_input_lines.c -c -o get_input_lines.o
global_clean.o : global_clean.c externs.h defaults.h
	$(CC) $(CFLAGS)  global_clean.c -c -o global_clean.o
hostname_to_ip.o : hostname_to_ip.c
	$(CC) $(CFLAGS)  hostname_to_ip.c -c -o hostname_to_ip.o
import_eml.o : import_eml.c externs.h defaults.h remchars.o insert_new_field.o \
	remove_chars.o extract_hrefs.o received_ip.o remchars.o
	$(CC) $(CFLAGS)  import_eml.c -c -o import_eml.o
init_storage.o : init_storage.c externs.h defaults.h
	$(CC) $(CFLAGS)  init_storage.c -c -o init_storage.o
input_clean.o : input_clean.c externs.h defaults.h
	$(CC) $(CFLAGS)  input_clean.c -c -o input_clean.o
insert_new_field.o : insert_new_field.c externs.h defaults.h find_fieldname.o
	$(CC) $(CFLAGS)  insert_new_field.c -c -o insert_new_field.o
int2ip : int2ip.c
	$(CC) $(CFLAGS) int2ip.c -o int2ip
ip2asn : ip2asn.c
	$(CC) $(CFLAGS) ip2asn.c -o ip2asn
ip2country : ip2country.c
	$(CC) $(CFLAGS) ip2country.c -o ip2country
ip2int : ip2int.c
	$(CC) $(CFLAGS) ip2int.c -o ip2int
ipfind.o : ipfind.c externs.h
	$(CC) $(CFLAGS) ipfind.c -c -o ipfind.o
keep_rec.o : keep_rec.c externs.h
	$(CC) $(CFLAGS)  keep_rec.c -c -o keep_rec.o
last_fieldname.o : last_fieldname.c externs.h build_target_list.o
	$(CC) $(CFLAGS) last_fieldname.c -c -o last_fieldname.o
last_value.o : last_value.c externs.h build_target_list.o
	$(CC) $(CFLAGS) last_value.c -c -o last_value.o
lookup.o : lookup.c externs.h build_target_list.o insert_new_field.o
	$(CC) $(CFLAGS) lookup.c -c -o lookup.o
main.o : main.c core.h defaults.h funcs.h get_input_lines.o find_field_defs.o input_clean.o \
	extract_field_values.o cleanup.o set_input_fieldnames.o
	$(CC) $(CFLAGS)  main.c -c -o main.o
match.o : match.c externs.h
	$(CC) $(CFLAGS)  match.c -c -o match.o
pattern.o : pattern.c externs.h defaults.h build_target_list.o
	$(CC) $(CFLAGS)  pattern.c -c -o pattern.o
substring.o : substring.c externs.h build_target_list.o
	$(CC) $(CFLAGS)  substring.c -c -o substring.o
processor_email.o : processor_email.c core.h init_storage.o import_eml.o cleanup.o
	$(CC) $(CFLAGS)  processor_email.c -c -o processor_email.o
received_ip.o : received_ip.c externs.h defaults.h build_target_list.o remchars.o strpos.o \
	insert_new_field.o ipfind.o insert_new_field.o
	$(CC) $(CFLAGS)  received_ip.c -c -o received_ip.o
remchars.o : remchars.c defaults.h externs.h
	$(CC) $(CFLAGS)  remchars.c -c -o remchars.o
remove_chars.o : remove_chars.c externs.h defaults.h
	$(CC) $(CFLAGS)  remove_chars.c -c -o remove_chars.o
remove_string.o : remove_string.c externs.h defaults.h find_fieldname.o
	$(CC) $(CFLAGS)  remove_string.c -c -o remove_string.o
rename_field.o : rename_field.c externs.h defaults.h
	$(CC) $(CFLAGS)  rename_field.c -c -o rename_field.o
replace_char.o : replace_char.c
	$(CC) $(CFLAGS)  replace_char.c -c -o replace_char.o
set_graphics.o : set_graphics.c externs.h
	$(CC) $(CFLAGS)  set_graphics.c -c -o set_graphics.o
set_input_directory.o : set_input_directory.c externs.h defaults.h
	$(CC) $(CFLAGS)  set_input_directory.c -c -o set_input_directory.o
set_input_fieldnames.o : set_input_fieldnames.c externs.h defaults.h
	$(CC) $(CFLAGS)  set_input_fieldnames.c -c -o set_input_fieldnames.o
set_input.o : set_input.c externs.h defaults.h
	$(CC) $(CFLAGS)  set_input.c -c -o set_input.o
set_output.o : set_output.c externs.h defaults.h
	$(CC) $(CFLAGS)  set_output.c -c -o set_output.o
socketadd_asn.o : socketadd_asn.c externs.h defaults.h insert_new_field.o find_fieldname.o
	$(CC) $(CFLAGS)  socketadd_asn.c -c -o socketadd_asn.o
socketadd_country.o : socketadd_country.c externs.h defaults.h insert_new_field.o find_fieldname.o
	$(CC) $(CFLAGS)  socketadd_country.c -c -o socketadd_country.o
sslcat : sslcat.c
	$(CC) $(CFLAGS) sslcat.c -lssl -lcrypto -o sslcat
strpos.o : strpos.c
	$(CC) $(CFLAGS)  strpos.c -c -o strpos.o
table.o : table.c externs.h
	$(CC) $(CFLAGS) table.c -c -o table.o
unescape.o : unescape.c
	$(CC) $(CFLAGS) -c unescape.c -o unescape.o
unix_time.o : unix_time.c build_target_list.o insert_new_field.o externs.h remchars.o
	$(CC) $(CFLAGS) unix_time.c -c -o unix_time.o
urldecode.o : urldecode.c externs.h find_fieldname.o
	$(CC) $(CFLAGS)  urldecode.c -c -o urldecode.o
whitelist.o : whitelist.c build_target_list.o externs.h
	$(CC) $(CFLAGS) whitelist.c -c -o whitelist.o
whitelist_convert : whitelist_convert.c
	$(CC) $(CFLAGS) -lm whitelist_convert.c -o whitelist_convert 
write_csv_fields.o : write_csv_fields.c externs.h defaults.h find_fieldname.o array_from_string.o
	$(CC) $(CFLAGS)  write_csv_fields.c -c -o write_csv_fields.o
Server :
	mkdir -p /usr/local/bin
	mkdir -p /usr/local/sbin
	mkdir -p /usr/local/Reference
	cp ../Reference/* /usr/local/Reference
	chown root *.service
	chgrp root *.service
	chmod 644 *.service
	mv class_a_update /usr/local/sbin
	mv reverse_class_a_update /usr/local/sbin
	mv dns_auth_update /usr/local/sbin
	mv rdns_update /usr/local/sbin
	mv dns_prune /usr/local/sbin/sbin
	mv gdnsd /usr/local/sbin
	mv gdns_server /usr/local/bin
	mv gdnsd.service /etc/systemd/system
	mv grdnsd /usr/local/sbin
	mv grdns_server /usr/local/bin
	mv grdnsd.service /etc/systemd/system
	mv gasnd /usr/local/sbin
	mv gasn_server /usr/local/bin
	mv gasnd.service /etc/systemd/system
	mv gcountryd /usr/local/sbin
	mv gcountry_server /usr/local/bin
	mv gcountryd.service /etc/systemd/system
	mv ghistoryd /usr/local/sbin
	mv ghistory_server /usr/local/bin
	mv ghistoryd.service /etc/systemd/system
	/sbin/restorecon -v /usr/local/sbin/gasnd
	/sbin/restorecon -v /usr/local/sbin/gcountryd
Client :
	mkdir -p /usr/local/sbin
	mkdir -p /usr/local/bin
	mv *.a ../lib
	mv abuseipdb /usr/local/sbin
	mv convert_emails /usr/local/sbin
	chmod 755 /usr/local/sbin/abuseipdb
	chmod 755 /usr/local/sbin/convert_emails
	mv ip2asn /usr/local/bin
	mv ip2country /usr/local/bin
	mv ip2int /usr/local/bin
	mv int2ip /usr/local/bin
	mv ghistory /usr/local/bin
	mv gcountry /usr/local/bin
	mv gasn /usr/local/bin
	mv grdns /usr/local/bin
	mv gdns /usr/local/bin
	mv cidr2ip /usr/local/bin
	mv whitelist_convert /usr/local/bin
	mv sslcat /usr/local/bin
	rm *.o
