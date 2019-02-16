
### How to update ./Reference/asn.csv and ./Reference/country.csv files

Each record in file asn.csv has a 3 field format `START_INT,END_INT,"ASN AS_Name"` 

Country.csv is similar with a country diagraph and country name as the last 2 of the 4 fields: `START_INT,END_INT,Diagraph,name`
 
The IP addresses related to AS numbers and country diagraphs are known to change over time, and both of these files 
are incomplete (Commercial up to date versions are available, but at cost). Functions such as add_asn() and 
add_country() rely on these files being right.

Rather than start and end IP addresses, integers are recorded in order to make lookups quicker. This note describes 
a way of keeping the files up to date:

1. For any given IP address, the CIDR notation,country code and ASN can be obtained through Internet searches 
(E.G, using Hurrican Electric). For example, IP 54.230.8.34 has a network mask of /22, an ASN of AS16509 and
is located in the US. 

2. Using the cidr2ip utility, 54.230.8.34/22 returns 54.230.8.0 54.230.11.255 (which is the start and 
end IP address for this network range).

3. Take the two IP addresses returned by cidr2ip, and past them into the command "ip2int 54.230.8.0 54.230.11.255" 
which returns 921044992 921046015

4. Records in the asn and country csv files are stored in numeric order, so find the gap in which this new 
record fits, carefully making sure you use the correct format when doing the edit. Note that sometimes you 
will find adjacent overlapping ranges. This is normal and having to edit the adjacent start or end entries is 
quite common. The int2ip utility can be used to get a neighbour IP address, and allows you to re-check that 
values are valid by doing another Internet search. These ranges will change with time! 

5. After performing an update, use the ip2asn/ip2country utilities to check the update was made correctly.

