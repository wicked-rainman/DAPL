
### Storing the replies to historic DNS requests seems a huge resource-expensive task. Why on earth would you want to do this ?

-   In web-hosting environments, a single machine with 1 IP address may deliver the content for many web sites. Storing historical DNS replies allows you to find out what websites (or other entities with a DNS entry) are being hosted on that single machine.

-   If someone hosts a website from home on a dynamic IP address, storing historic DNS associates the dynamically allocated IP addresses (and therefore the rdns entry) with the website name.

-   Having a store of DNS replies enables threaded regular expression pattern matching agains domain names. This is useful for understanding what assets are associated with a company or organisation.


The DAPL DNS/RDNS server programs gdns_server and grdns_server are designed to deliver historic DNS records
to the gdns and grdns client utllities. The server components both read these records from a turnkey datastore 
that requires regular updates. After an initial DAPL install, the datastore need to be built from scratch (It is 
too big for a GIT repository). 

### DATASTORE FORMAT

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
            
        2.  Both scripts call helper functions (class_a_update is called by dns_auth_update and
            reverse_class_a_update called by rdns_update) which are forked to keep every available 
            processor busy. Expect 100% CPU usage.

        3.  From time to time, unwanted forward DNS records will be collected (You will find randon 
            DNS entries that are machine generated for temporary use). Script dns_prune can be 
            used to clear out the dross.

        4.  Before running these scripts you will need to set or change some BASH shell variables in
            both .bashrc and the shell scripts gdnsd and grdnsd (/usr/local/sbin). There are three
            directories used by this whole process, and sometimes these directories might need to 
            be on different physical volumes:
            
                a.  Somewhere to store incomming raw DNS records (You might want to keep these
                    files so you can re-build the datastore at any time should you wish) - 
                    DNS_HISTORY

                b.  Some temporary workspace for efficient sorting and creation of intermediate
                    files- DNS_TEMP

                c.  Somewhere for the datastore itself - GREFERENCE/dns

            The gdnsd and grdnsd scripts both contain a shell variable $GREFERENCE. This should
            point to a mount point for a disk volume, eg: GREFERENCE=/xpoint1 (Forward and Reverse
            DNS entries occupy the same datastore). The gdns_server and grdns_server both expect
            to access the datastore in a directory $GREFERENCE/dns, so you now need to make that
            directory. 
            
            The dns_auth_update and rdns_update scripts both use .bashrc shell variables:
                
                $DNS_HISTORY - Directory (somewhere)/dns_history For storage of new incomming data to parse
                $DNS_TEMP - Directory (somewhere)/dns_temp Used for sorting records and other functions
                $DNS_INODES - Directory (which should be the same as $GREFERENCE/dns).

            Again, it is probably a good idea that $DNS_HISTORY and $DNS_TEMP are NOT the same physical
            volume as $GREFERENCE if possible. 
                
You can now run dns_auth_update [input file] and when that is completed, rdns_update [input file]. Don't
be surprised if these scripts take anything from 3 to 27 hours to complete. Stick ear plugs in, and open
the windows. When the filtering is complete and this really gets going, expect all cores to be running 
at 100%

When updates have completed, script dnsreg_update can be run against the input just processed
by dns_auth_update. It creates 100Mb chunks of unordered data that can be used by the dnsgrep utility. 
Again, related BASH variables in this script will need to be modified.

### NOTES:

The datastore has been designed to provide fast responses to queries (The server code basically changes to 
the directory that satisfies an IP address class B value, then just reads the dns records for a single 
class C). It is therefore of significant benefit for the datastore to be mounted on 3dXpoint solid-state 
storage. Vnand will wear out too quickly running this process, so if you can't afford some 3dXpoint drives
then I would stick with spinning rust. 

Suitable input for this process can be obtained from:

        https://opendata.rapid7.com/sonar.fdns_v2/ 
        
        and 
        
        https://opendata.rapid7.com/sonar.rdns_v2/


