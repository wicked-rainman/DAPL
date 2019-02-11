

                    How to update ./Reference/asn.csv and ./Reference/country.csv files

Each record in file asn.csv has the format: 

    START_INT,END_INT,"ASN AS_Name" 

Country.csv is similar, but with a country diagraph and country name as the last two fields:

    START_INT,END_INT,Diagraph,name
 
The IP addresses related to AS numbers and country diagraphs are known to change over time, and both of these files 
are incomplete (Commercial up to date versions are available, but at cost). Functions such as add_asn() and 
add_country() rely on these files being up to date.

Rather than start and end IP addresses, integers are recorded in order to make lookups quicker. This note describes 
a way of keeping the files up to date:

1. For any given IP address, the CIDR notation,country code and ASN can be obtained through Internet searches 
(E.G, using Hurrican Electric). For example, IP 54.230.8.34 has a network mask of /22, an ASN of AS16509 and
is in the US. 

2. Using the cidr2ip utility, 54.230.8.34/22 returns 54.230.8.0 54.230.11.255 (which is the start and 
end IP address for this network range).

3 Take the two IP addresses returned by cidr2ip, and past them into the command "ip2int 54.230.8.0 54.230.11.255" 
which returns 921044992 921046015

4. Records in the asn and country csv files are stored in numeric order, so find the gap in which this fits
and insert the record, ensuring the new entry is placed in the correct place, and has the right format. Note
that sometimes you will find overlapping ranges with adjacent entries. If that's the case some further hand
editing and checking will be required. 

5. After performing an update, use the ip2asn/ip2country utilities to check the update was made properly.

