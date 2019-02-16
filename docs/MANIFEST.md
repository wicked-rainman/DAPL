

## Overview of utilities/functions/files provided by this package:

### Utilities

- __ip2int__ A simple C program that converts a IP address or range of addresses to their respective Integer value.
- __ip2asn__ Resolves the ASN associated with the specified IP address(s). Dependant on $ASN_FILE.
- __ip2country__ Resolves country code associated with the specified IP address(s). Dependant on $COUNTRY_FILE.
- __int2ip__ Converts an Int to an IP address.
- __cidr2ip__ Converts a CIDR to an IP address range. 
- __gasn__ Client that resolves the ASN associated with an IP address via a call to $GSERVER
- __gdns__ Client that resolves historic DNS entries for an IP address via a call to $GSERVER
- __grdns__ Client that resolves historic reverse DNS entries for an IP address via a call to $GSERVER
- __ghistory__ Client that queries a $GSERVER for historic records relating to an IP address
- __whitelist_convert__ Converts opensource whitelists into a DAPL compatible reference table
- __sslcat__ A simplistic version of netcat for SSL.
- __abuseipdb__ Client to look up and IP address over the Internet using the AbuseIPdb API
- __convert_emails__ Converts saved outlook messages into plain text
- __dns_auth_update__ Updates the DNS_INODES database for historic DNS resolution
- __dnsreg_update__ Create split versions of a dns update file to enable __dnsgrep__
- __rdns_update__ Updates the RDNS_INODES database for historic reverse DNS resolution
- __dns_prune__ Utility to remove rogue IP addresses or entries from the DNS_INODES database
- __dnsgep__ Regular expression pattern matching script for domain names
- __class_a_update__ Internal routine used by dns_auth_update
- __reverse_class_a_update__ Internal routine used by rdns_update
     
### Services

- __grdns_server__ A service running on $GSERVER port $GRDNS_PORT. Answers historic RDNS queries.
- __gasn_server__ A service running on $GSERVER port $GASN_PORT. Answers ASN queries.
- __ghistory_server__ A service running on $GSERVER port $GHISTORY_PORT. Answers IP seen before queries.
- __gcountry_server__ A service running on $GSERVER port $GCOUNTRY_PORT. Answers IP country code lookups.
- __gdns_server__ A service running on $GSERVER port $GDNS_PORT. Answers historic DNS queries.
- __gasnd__ systemd shell for gasn_server
- __gcountryd__ systemd shell for gcountry_server
- __gdnsd__ systemd shell for gdns_server
- __ghistoryd__ systemd shell for ghistory_server
- __grdnsd__ systemd shell for grdns_server
- __gasnd.service__ systemd service file for gasn_server
- __gcountryd.service__ systemd service file for gcountry_server
- __gdnsd.service__ systemd service file for gdns_server
- __grdnsd.service__ systemd service file for grdns_server
- __ghistoryd.service__ systemd service file for ghistory_server

### DAPL wrapper

Library __libdapl.a__ - DAPL Main routine wrapper and all associated function calls  

Library __libeml.a__ - E-Mail handler as Main routine wrapper and all associated DAPL function calls  

### Reference files

__asn.csv__ - An updatable file where each record represents an IP address range (as Ints) that relate to an ASN  

__country.csv__ - An updatable file where each record represents an IP address range (as Ints) that relate to country codes  

__whitelist.csv__ - An updatable file where each record represents an IP address range (as Ints) of whitelisted IP addresses  


### DAPL functions

     add_asn                  - Local lookup of an IP address in order to obtain an ASN
     add_attributes           - Add graphical attributes to a .dot node
     add_composite            - Add a temporary set of values to a field value in order to make it unique
     add_concatenation        - Concatenate fields onto an existing field value
     add_country              - Local lookup of an IP address in order to obtain a country diagraph
     add_field                - Add a fixed value field to a record
     add_label                - Add a graphical label to a .dot node
     add_quotes               - INTERNAL, add quotes to a string
     add_reverse_dns          - Wrapper for network call to gethostbyaddr. New value added to record as *.rdns
     add_substring            - Creates a new field based on a substring of an existing field
     array_from_string        - INTERNAL, creates a 2D array from a string based on delimiters " ,\t\n"
     build_target_list        - INTERNAL, builds fieldname chain from a base value
     cleanup                  - INTERNAL, Closing routine for MAIN code block
     dedupe                   - INTERNAL, dedupes char out of string.
     define_csv_tag           - Redefines the default csv start tag from being "#Fields:" to something else.
     define_input_fieldnames  - Defines fieldnames in an input file where there is no CSV tag line
     draw_chain               - Draws a graphics field chain starting at an anchor field.
     draw_node                - Draw the relationship between two field values
     draw_path                - Draw the relationship between a list of field values
     drop_rec                 - Set the drop record flag to halt any processing of the current record.
     empty                    - Test for fieldname with an empty value.
     extract_field_values     - INTERNAL, extract field values from an input record based on defined field names
     extract_hrefs            - Extract href values out of an existing field. Creates field chain text.url
     find_field_defs          - INTERNAL, detects new CSV field definition lines in an input file based on CSV tag string
     find_fieldname           - INTERNAL, returns the index int to a fieldname value pair in the global data structure.
     get_input_lines          - INTERNAL. Line reader for input file(s).
     global_clean             - INTERNAL. Sets a global remove string that is applied to input files.
     hostname_to_ip.c         - INTERNAL. Go figure.
     import_eml               - INTERNAL. Converts a .eml input file to a CSV.
     init_storage             - INTERNAL. Main startup routine to init storage.
     input_clean              - INTERNAL. Removes a substring from an input file record. 
     insert_new_field         - Insert a new fieldname/value pair into the global struct for the current record
     ipfind                   - INTERNAL. Regexp to match and extract an IP address from a string
     keep_rec                 - Dummy function 
     last_fieldname           - Returns the last fieldname from a field chain
     last_value.c             - Returns the last field value from a field chain
     lookup                   - Looks up a field value in a table, and adds a new field and value if match is found
     main                     - INTERNAL Main routine wrapper for DAPL
     match                    - Conditional field value test. See ./src/macro.h
     pattern                  - Conditional field value test. See ./src/macro.h
     processor_email          - INTERNAL Main routine wrapper in ../lib/libeml.a for email processing
     received_ip              - INTERNAL Email processing. Create chain of IP address fields from mail Receive lines.
     remchars                 - INTERNAL Remove unwanted characters from a string.
     remove_chars             - Remove unwanted characters from a field value.
     remove_string            - Remove a substring from within a field value.
     rename_field             - Rename an existing field.
     replace_char             - INTERNAL. Replace character in a string with another.
     set_graphics             - Defines the graphics output file and render engine
     set_input                - Defines the input file(s) to be processed
     set_input_directory      - Defines the input directory where input files reside for processing.
     set_input_fieldnames     - Defines input fieldnames where no CSV tag line is present.
     set_output               - Defines the output file where CSV records will be written
     socketadd_asn            - Use a remote server to look up an IP address to resolve ASN 
     socketadd_country        - Use a remote server to look up an IP address to resolve country diagraph 
     strpos                   - INTERNAL. Returns the position of a string within a string.
     substring                - Conditional field value test. See ../src/macro.h
     table                    - Defines the input file that contains lookup values - See function lookup.
     unescape                 - INTERNAL function used inside sslcat utility.
     unix_time                - Converts a unix time field to a specified format and inserts it as new field *.udtg
     urldecode                - URL decodes an existing field and replaces value.
     whitelist                - Allows for the conditional testing of an IP address to see if it is whitelisted.
     write_csv_fields         - Routine to write CSV output fields to a file. 
     
### EXAMPLE CODE

     example1                 - Read input file, write output file, add country and asn fields for each IP
     example2                 - Read and write files. Drop record based on field value.
     example2a                - Read and write files. Keep record based on field value.
     example3                 - Graphically show the relationship between two fields
     example4                 - Graphically show the relationship between multiple fields
     example5                 - Make fields unique when graphically displaying identical fields
     example6                 - Demonstrate a different view of the data when compared to other examples
     spam_email_handler       - Dealing with chained field values
     spam_email_processor     - Selecting specific spam e-mails baed on relay IP addresses
     ssh-input-handler        - Selecting authorised ssh session records
     webserver-input-handler  - Selecting successful HTTP requests and xreffing with external lookup records
     webserver-analysis       - View HTTP exchanges with known hostile IP addresses 
     
### INPUT DATA

     input1.csv               - Test input data for ./example_code/example1.c - example6.c
