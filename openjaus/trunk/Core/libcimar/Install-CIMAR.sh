#! /bin/bash
# CIMAR Library Install Script

echo ;
echo CIMAR Library Install Begin
echo ;

cp -PpRfv ./include/* /usr/include/
rm -Rfv `find /usr/include/cimar/ -name .svn`
cp -PpRfv ./lib/libcimar.* /usr/lib

echo ;
echo CIMAR Library Install Complete
echo ;
