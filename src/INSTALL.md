1. cd into your $HOME directory
2. Clone the repository using "git clone https://github.com/wicked-rainman/DAPL.git"
This should create a directory named "DAPL".
       $HOME/DAPL/
       
                    --------->Reference/
       
                    --------->src/
       
                    --------->lib/
       
                    --------->example_code
       
3. As root, run ./Configure to make sure system dependancies are present
4. cd into $HOME/DAPL/src and run "make".
5. When that has completed, run "sudo make Install". This should copy any binaries into /usr/local/bin, and move 
any libraries into $HOME/DAPL/lib.
6. Edit $HOME/.bashrc, and add the three following variables:

                   WHITE_FILE= (home directory)/DAPL/Reference/whitelist.csv; export WHITE_FILE
  
                   ASN_FILE= (home directory)/DAPL/Reference/asn.csv; export ASN_FILE
  
                   COUNTRY_FILE= (home directory)/DAPL/Reference/country.csv; export COUNTRY_FILE
  
  These three variables point to the corresponding files in $HOME/DAPL/Reference

7. Create any programs in $HOME/DAPL/progs

8.To compile each program, use the command:

       "clang -Ofast prog.c ../lib/libdapl.a -o progname"

9. Any additional reference files you make use of should reside in $HOME/DAPL/Reference
