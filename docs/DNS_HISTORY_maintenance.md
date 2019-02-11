
HISTORIC DNS

The DAPL DNS/RDNS server programs gdns_server and grdns_server are designed to deliver historic DNS records
to the gdns and grdns client utllities. The server components both read these records from a turnkey datastore 
that requires regular updates. After an initial DAPL install, the datastore need to be built from scratch (It is 
too big for a GIT repository). 

DATASTORE FORMAT

Answers to historical DNS queries are stored in dotted decimal IP address order. The records are stored in
a two depth directory structure:

    Level 1:  Most significant octet (Class A)
    Level 2:  Second most significant octet (Class B)

The level 1 and level 2 directory each contain 255 directories named "0" -"255" (65025 directories in total). 
The level 2 directories contains files with an "f" or an "r" prefix ("f" = forward DNS entries, "r", reverse), 
followed by a three digit number that represents the third most significant octet (Class C network). 

Each of these files contain records that carry an IP and DNS value pair. Obviously, duplicate IP addresses are 
present, but with different DNS values. 65025 * 255 * 2 (33162750) files. In effect, one inode for each /24 network.

The records in the datastore can be created or updated using the scripts dns_auth_update and rdns_update. Both
these scripts should be straight forward to understand, but note:

        1.  These scripts are long running and should probably be executed with nohup.
            Depending on record counts (which might exceed 3 billion), expect the update 
            process to run over a period of 4-20 hours. 
            
        2.  Both scripts call helper functions (class_a_update and reverse_class_a_update)
            which are forked to keep every available processor busy. Expect 100% CPU usage.

        3.  From time to time, unwanted DNS records will be collected (You will find randon 
            DNS entries that are machine generated for temporary use). Script dns_prune can be 
            used to clear out the dross.

NOTE:

The datastore has been designed to provide fast responses to DNS historic queries (The server code
basically changes to the directory that satisfies an IP address class B value, then just reads the
dns records for a single class C). It is therefore of significant benefit for the datastore to be
mounted on modern solid-state storage such as 3dXpoint or Vnand. 
