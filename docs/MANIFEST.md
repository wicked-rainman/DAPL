

An overview of the utilities and functions provided by this package:

Utilities

     ip2int -  A simple C program that converts a IP address or range of addresses to their respective Integer value.
     ip2asn -  Resolves the ASN associated with the specified IP address(s). Dependant on $ASN_FILE.
     ip2country - Resolves country code associated with the specified IP address(s). Dependant on $COUNTRY_FILE.
     int2ip - Converts an Int to an IP address.
     cidr2ip - Converts a CIDR to an IP address range. 
     gasn - Client that resolves the ASN associated with an IP address via a call to $GSERVER
     gdns - Client that resolves historic DNS entries for an IP address via a call to $GSERVER
     grdns - Client that resolves historic reverse DNS entries for an IP address via a call to $GSERVER
     ghistory - Client that queries a $GSERVER for historic records relating to an IP address
     whitelist_convert - Converts opensource whitelists into a DAPL compatible reference table
     sslcat - A simplistic version of netcat for SSL.
     abuseipdb - Client to look up and IP address over the Internet using the AbuseIPdb API
     convert_emails - Converts saved outlook messages into plain text
     dns_auth_update - Updates the DNS_INODES database for historic DNS resolution
     rdns_update - Updates the RDNS_INODES database for historic reverse DNS resolution
     dns_prune - Utility to remove rogue IP addresses or entries from the DNS_INODES database
     class_a_update - Internal routine used by dns_auth_update
     reverse_class_a_update - Internal routine used by rdns_update
     
Services

     grdns_server - A service running on $GSERVER port $GRDNS_PORT. Answers historic RDNS queries.
     gasn_server -  A service running on $GSERVER port $GASN_PORT. Answers ASN queries.
     ghistory_server - A service running on $GSERVER port $GHISTORY_PORT. Answers IP seen before queries.
     gcountry_server - A service running on $GSERVER port $GCOUNTRY_PORT. Answers IP country code lookups.
     gdns_server - A service running on $GSERVER port $GDNS_PORT. Answers historic DNS queries.
     gasnd - systemd shell for gasn_server
     gcountryd - systemd shell for gcountry_server
     gdnsd - systemd shell for gdns_server
     ghistoryd - systemd shell for ghistory_server
     grdnsd - systemd shell for grdns_server
     gasnd.service - systemd service file for gasn_server
     gcountryd.service - systemd service file for gcountry_server
     gdnsd.service - systemd service file for gdns_server
     grdnsd.service - systemd service file for grdns_server
     ghistoryd.service - systemd service file for ghistory_server

DAPL wrapper

      Library libdapl.a - DAPL Main routine wrapper and all associated function calls
      Library libeml.a - E-Mail handler as Main routine wrapper and all associated DAPL function calls

Reference files

     asn.csv - An updatable file where each record represents an IP address range (as Ints) that relate to an ASN
     country.csv - An updatable file where each record represents an IP address range (as Ints) that relate to country codes
     whitelist.csv - An updatable file where each record represents an IP address range (as Ints) of whitelisted IP addresses

DAPL functions

     add_asn                  - Local lookup and IP address to obtain ASN 
     add_attributes.c
     add_composite.c
     add_concatenation.c
     add_country.c
     add_field.c
     add_label.c
     add_quotes.c
     add_reverse_dns.c
     add_substring.c
     array_from_string.c
     build_target_list.c
     cidr2ip.c
     cleanup.c
     dedupe.c
     define_csv_tag.c
     define_input_fieldnames.c
     draw_attached.c
     draw_chain.c
     draw_node.c
     draw_path.c
     drop_rec.c
     email_handler.c
     email_tester.c
     empty.c
     extract_field_values.c
     extract_hrefs.c
     find_field_defs.c
     find_fieldname.c
     gasn_client.c
     gasn_server.c
     gcountry_client.c
     gcountry_server.c
     gdns_client.c
     gdns_server.c
     get_input_lines.c
     ghistory_client.c
     ghistory_server.c
     global_clean.c
     grdns_client.c
     grdns_server.c
     hostname_to_ip.c
     import_eml.c
     init_storage.c
     input_clean.c
     insert_new_field.c
     ipfind.c
     keep_rec.c
     last_fieldname.c
     last_value.c
     lookup.c
     main.c
     match.c
     pattern.c
     processor_email.c
     received_ip.c
     remchars.c
     remove_chars.c
     remove_string.c
     rename_field.c
     replace_char.c
     set_delimiter.c
     set_graphics.c
     set_input.c
     set_input_directory.c
     set_input_fieldnames.c
     set_output.c
     socketadd_asn.c
     socketadd_country.c
     strpos.c
     substring.c
     table.c
     unescape.c
     unix_time.c
     urldecode.c
     whitelist.c
     whitelist_convert.c
     write_csv_fields.c
     
