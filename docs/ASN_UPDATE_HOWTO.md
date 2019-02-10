How to update ./Reference/asn.csv

The asn.csv has the format:

    <START_INT>,<END_INT>,<ASN>,<ASN Name>
    
AS numbers are known to change over time, and the file itself is incomplete (Commercial - up to date versions
are available, but at cost). Functions such as add_asn() rely this file in order to resolve IP addresses to ASNs.

More often than not, add_asn() will return no value because the entries are simply just not there..

Rather than this file containing IP addresses, Start and end integers are recorded in order to make lookups quicker.
This note describes a way of keeping the file up to date:

1. For any given IP address, the CIDR notation and ASN can be obtained through Internet searches (E.G, using Hurrican Electric).
For example, IP 54.230.8.34 has a network mask of /22. and an ASN of AS16509 Using cidr2ip:

    cidr2ip 54.230.8.34
    returns 
    54.230.8.0 54.230.11.255
    
which is the start and end IP address for this network range.

2. Take the two IP addresses returned by cidr2ip, and past them into the command:
    ip2int 54.230.8.0 54.230.11.255
    which returns
    921044992 921046015
    
3. Records in asn.csv are stored in numeric order, so find the gap in which this fits, and insert
the record ensuring commas are placed in the correct place!

4. After performin an update, use the ip2asn utility to check the update was made properly.
        
