OVERVIEW Data Analist Programming Language (DAPL)

DAPL is a program language wrapper intended to simplify the process of analysing large volumes of single-line 
records that contain delimited fields (for example HTTP, SSH and Audit logs, phone or building access logs and 
the like). The wrapper might be thought of as mysql for CSV files, but without the databases, or perhaps the 
query language components of Model 204. The primary focus is to keep things simple!

Provisions are made for dealing with other forms of data through a conversion process (Currently only one such 
converter exists - for processing spam E-mail). 

A small range of standalone utilities that aid dealing with IP related data have been included, albeit they are 
separate (but replicated) from the core DAPL wrapper. 

DAPL makes provisions for two code blocks within any main routine:

setup():

    Code within the setup block is executed once after program initialisation. It's purpose is to 
    allow the user to perform startup functions like opening input and output files, defining input 
    fields, identifying reference files Etc. Any failures within the setup block stops the whole process 
    running. The user is shielded from the complexities of performing these operations through the use
    of high level function calls. 

loop()

    Code within the loop block is executed once for each record contained in each input file identified 
    in setup(). An obscured global data structure is created for each record, populated with the fieldname and 
    field value pairs found. All functions within the loop block reference this structure. Once the record has 
    been processed it is reset to empty, ready to be populated with the fields from the next record. 
    
    Other than maintaining a count of input and output records and maintaining file or memory pointers for any 
    reference files, there is no state within the code block. This allows for processing of undefinably 
    large volumes of input, restricted only by the memory requirements for holding one single record at a time. 
    
    Code within the loop block is generally fault tollerant. For example, function 
    references to field names that are non-existant in the input result in the calling function failing 
    gracefully (This allows for the successful processing of files that have different fields - where not all 
    of the fields in one are present in the other). 
    
    Loop functions tend to fall into one of three categories:

         1. Those that Enable the selection or rejection of individual records, based on
         string matching, substring matching or through regular expression pattern matching. 
         Rejected records are internally assigned a "drop" flag. If a drop flag is 
         present, all sequentially following loop functions will exit without performing their 
         intended actions (I.E, the record is ignored). Early rejection of unwanted records can 
         obviously dramatically improve processing times.
         
         2. Value editing functions that can replace, sanitse, substring or add to the underlying
         data in some way. Field values can be looked up in locally held tables, or from external
         sources via socket calls with suitable APIs. Field values can be combined or added to in order
         to make them unique (such as adding DTGs Etc). 
         
         3. Graphical data modeling. Relationships between data fields can be defined and visualised
         by generating .dot output that can be rendered by graphviz in various ways (such as SVG, PDF 
         JPEG Etc). Duplicate relationships are set to be effectively de-duped by the .dot processor, 
         making large volumes of data easier to analyse.
         
Sample code can be found in the ./example_code directory, together with sample data in ./input. This 
may aid with the learning process. A brief description of the utilities/files produced by the included 
Makefile can be found in ./docs/Manifest.md. See INITIAL INSTALL section below.

FURTHER READING

        Graphviz        - https://graphviz.org
        Detox           - detox.sourceforge.net
        msgconvert      - https://github.com/mvz/email-outlook-message-perl
        abuseip         - https://www.abuseipdb.com/api.html
        Reverse DNS     - https://opendata.rapid7.com/sonar.rdns_v2/
        DNS             - https://opendata.rapid7.com/sonar.fdns_v2/
        Topology        - http://www.caida.org/data/active/ipv4_routed_24_topology_dataset.xml
        
        
------------------------------------------------------------------------------------------------

INITIAL INSTALL:

1.  cd into your $HOME directory

2.  Clone the repository using "git clone https://github.com/wicked-rainman/DAPL.git". This should create a 
directory named "DAPL".

3.  cd into $HOME/DAPL/src

4.  As root, run ./Configure to make sure system dependancies are present. Clang and Graphviz are critical for 
DAPL. Openssl-dev is needed for the  sslcat and abuseipdb standalone utilities, detox, dos2unix and the perl 
script msgconvert are needed for any E-mail processing.

5.  exit root and as a user run make. You shouldn't see any errors.

6.  DAPL can be run as a client or as a server. For the client install, run:

        "sudo make Client" 
      
or for the server (if you are happy with what actions it is going to perform), run:

        "sudo make Server".

7. After a server install, use systemctl to enable and start gasnd.service, gdnsd.service, grdnsd.service, 
ghistory.service and gcountryd.service as required. Ensure that the TCP ports specified in gasnd, gdnsd, 
grdnsd, gcountryd and ghistoryd (/usr/local/sbin) are allowed through any firewall.


8. In a client install, Edit $HOME/.bashrc, and add these BASH variables:

        WHITE_FILE= $HOME/DAPL/Reference/whitelist.csv; export WHITE_FILE
        ASN_FILE= $HOME/DAPL/Reference/asn.csv; export ASN_FILE
        COUNTRY_FILE= $HOME/DAPL/Reference/country.csv; export COUNTRY_FILE
        GDNS_PORT=32481; export GDNS_PORT
        GASN_PORT=32482; export GASN_PORT
        GCOUNTRY_PORT=32483; export GCOUNTRY_PORT
        GRDNS_PORT=32484; export GRDNS_PORT
        GHISTORY_PORT=32485; export GHISTORY_PORT
        GSERVER= (IP address of the server); export GSERVER
        
The ASN_FILE, COUNTRY_FILE and WHITE_FILE files are used within DAPL (functions add_asn(), add_country() 
and whitelist() ) for local resolution and provide non-server related answers. 

DAPL functions socketadd_asn() socketadd_country() and socketadd_history() will resolve answers through 
the related server ports. DAPL functions socketadd_dns() and socketadd_rdns() have not been written yet, 
although Standalone utilities gdns grdns reference these other ports. 

8. Create any user programs in $HOME/DAPL/progs. To compile each program, use the command:

        "clang -Ofast prog.c ../lib/libdapl.a -o progname" for files conaining single line "CSV" type records, or
        "clang -Ofast prog.c ../lib/libeml.a -o progname" to utilise the E-mail conversion handler

9. On a client, any additional reference files you make should reside in $HOME/DAPL/Reference. 

10. On a Server, DNS related files must all be built from scratch using the DNS related scripts in sbin - dns_auth_update() 
and rdns_update(). 



