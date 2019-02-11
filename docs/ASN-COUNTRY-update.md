

How to update ./Reference/asn.csv and ./Reference/country.csv files

ASN file:

Each record in file asn.csv has the format "START_INT,END_INT,ASN,AS_Name"

AS numbers are known to change over time, and the file itself is incomplete (Commercial up to date versions are available, but at cost). Functions such as add_asn() rely this file in order to resolve IP addresses to ASNs.

Sometimes, add_asn() will return no value because the entries are simply just not there..

Rather than this file containing start and end IP addresses, integers are recorded in order to make lookups quicker. This note describes a way of keeping the file up to date:

1. For any given IP address, the CIDR notation country code and ASN can be obtained through Internet searches 
(E.G, using Hurrican Electric). For example, IP 54.230.8.34 has a network mask of /22. and an ASN of AS16509.

2. Using the cidr2ip utility, looking up 54.230.8.34/22 returns 54.230.8.0 54.230.11.255 which is the start and 
end IP address for this network range.

3 Take the two IP addresses returned by cidr2ip, and past them into the command "ip2int 54.230.8.0 54.230.11.255" 
which returns 921044992 921046015

4. Records in asn.csv are stored in numeric order, so find the gap in which this fits, and insert the record 
ensuring commas are placed in the correct place!

5. After performing an update, use the ip2asn utility to check the update was made properly.

COUNTRY file:

The country.csv file is much the same as the asn.csv file, only it holds country diagraph codes. The 
validity of the update can be confirmed using the ip2country utility.

NOTE:
There is minimal checking of the consistency of these files. If you don't get the format right, it's
highly likely you code will start to return wrong results.
