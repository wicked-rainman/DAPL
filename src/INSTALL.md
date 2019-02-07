1. cd into your $HOME directory
2. Clone the repository using "git clone https://github.com/wicked-rainman/DAPL.git"
This should create a directory named "DAPL".

       $HOME/DAPL/
       
                    --------->Reference/
       
                    --------->src/
       
                    --------->lib/
       
                    --------->example_code
                    
                    --------->scripts
       
3. As root, run ./Configure to make sure system dependancies are present
4. cd into $HOME/DAPL/src and run "make".
5. When that has completed, run "sudo make Install". This should copy any binaries into /usr/local/bin, and move 
any libraries into $HOME/DAPL/lib.
6. Edit $HOME/.bashrc, and add the three following variables if this is a standalone installation:

                   WHITE_FILE= (home directory)/DAPL/Reference/whitelist.csv; export WHITE_FILE
  
                   ASN_FILE= (home directory)/DAPL/Reference/asn.csv; export ASN_FILE
  
                   COUNTRY_FILE= (home directory)/DAPL/Reference/country.csv; export COUNTRY_FILE
  
  These three variables point to the corresponding files in $HOME/DAPL/Reference
  
7. If the install is using the server functionality, add these variables to $HOME/.bashrc:

       GREFERENCE=/usr/local/Reference
       export GREFERENCE
       GDNS_PORT=32481
       export GDNS_PORT
       GASN_PORT=32482
       export GASN_PORT
       GCOUNTRY_PORT=32483
       export GCOUNTRY_PORT
       GRDNS_PORT=32484
       export GRDNS_PORT
       GHISTORY_PORT=32485
       export GHISTORY_PORT
       GSERVER= IP address for the server
       export GSERVER
       
8. If this is a server install, use systemctl to install gasnd.service, gdnsd.service, grdnsd.service
gcountryd.service and ghistoryd.service.

9. Create any programs in $HOME/DAPL/progs

10. To compile each program, use the command:

       "clang -Ofast prog.c ../lib/libdapl.a -o progname"

11. Any additional reference files you make use of should reside in $HOME/DAPL/Reference
