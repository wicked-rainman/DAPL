#!/bin/bash
cdir=`pwd`
cd $1
detox -v *
for filename in *.msg
do
	msgconvert --verbose $filename
done
dos2unix *.eml
rm -f *.msg 
cd $cdir
