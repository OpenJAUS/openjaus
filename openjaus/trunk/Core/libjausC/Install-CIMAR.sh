#! /bin/bash
# CIMAR C JAUS Library Install Script

echo ;
echo CIMAR C JAUS Library Install Begin
echo ;

cp -PpRfv ./include/* /usr/include/
rm -Rfv `find /usr/include/cimar/ -name .svn`
cp -PpRfv ./libjausC.* /usr/lib

echo ;
echo CIMAR C JAUS Library Install Complete
echo ;
