1.  cd into your $HOME directory

2.  Clone the repository using "git clone https://github.com/wicked-rainman/DAPL.git". This should create a directory named "DAPL".

3.  cd into $HOME/DAPL/src

4.  As root, run ./Configure to make sure system dependancies are present (Openssl-dev, clang, graphviz, detox, dos2unix and the perl script msgconvert). Clang and graphviz are critical, all the other dependancies are needed for any E-mail processing.

5.  exit root and as a user run make.

6.  When that has completed, run "sudo make Install". This should copy any binaries into /usr/local/bin, scripts into /usr/local/sbin and create archive libraries in $HOME/DAPL/Lib

7.  DAPL can be run in a standalone mode, with backend server support, or as a server. It requires environmental variables to be set, based on the installation use case. These variables are often placed in $HOME/.bashrc, or in the case of a server install, included in the systemd control files.

8.  In a standalone environment, Edit $HOME/.bashrc, and add the three following variables:

        WHITE_FILE= $HOME/DAPL/Reference/whitelist.csv; export WHITE_FILE
        ASN_FILE= $HOME/DAPL/Reference/asn.csv; export ASN_FILE
        COUNTRY_FILE= $HOME/DAPL/Reference/country.csv; export COUNTRY_FILE

9.  If the install is using the server functionality, add these variables to $HOME/.bashrc:

        GREFERENCE=/usr/local/Reference; export GREFERENCE
        GDNS_PORT=32481; export GDNS_PORT
        GASN_PORT=32482; export GASN_PORT
        GCOUNTRY_PORT=32483; export GCOUNTRY_PORT
        GRDNS_PORT=32484; export GRDNS_PORT
        GHISTORY_PORT=32485; export GHISTORY_PORT
        GSERVER= (IP address of the server); export GSERVER

10. If this is a server install, use systemctl to install edited versions of the provided control files gasnd.service, gdnsd.service, grdnsd.service, gcountryd.service and ghistoryd.service as required.

11. Create any user programs in $HOME/DAPL/progs. To compile each program, use the command:

    "clang -Ofast prog.c ../lib/libdapl.a -o progname"

12. Any additional reference files you make should reside in $HOME/DAPL/Reference. The DNS related files are too big to be stored in a GIT repository, and must all be built from scratch using the DNS related scripts in /usr/local/sbin.

12a.  For a list and brief description of the utilities produced by this Makefile, see Manifest.md
