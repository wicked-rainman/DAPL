
HISTORIC DNS

The DAPL DNS/RDNS server programs gdns_server and grdns_server are designed to deliver historic DNS records
to the gdns and grdns client utllities. The server components both read these records from a turnkey datastore 
that require regular updates. After an initial DAPL install, these datastores need to be built from scratch (They 
are too big for a GIT repository). 

DATASTORE FORMAT

Answers to historical DNS queries are stored in dotted decimal IP address order. The records are stored in
a two depth directory structure:

    Level 1:  Most significant octet (Class A)
    Level 2:  Second most significant octet (Class B)

The level 1 and level 2 directory each contain 255 directories (named 0-255). The level 2 directory contains
files with an "f" or an "r" prefix ("f" = forward DNS entries, "r", reverse), followed by a three digit number
that represents the third most significant octet (Class C network). Each of these files contain records that 
carry an IP and DNS value pair. Obviously, duplicate IP addresses are present, but with different DNS values. 
255*255 (65025) directories and up to  65025*255*2 (33162750) files. In effect, one inode for each /24 network.


