#! /bin/bash
# CIMAR Node Manager Library Uninstall Script

echo ;
echo CIMAR Node Manager Library Uninstall Begin
echo ;

if [ "$OPENJAUS_HOME" = "" ]; then
    echo OPENJAUS_HOME not set...  Using /usr
    echo ;
    OPENJAUS_HOME=/usr
fi

rm -fv $OPENJAUS_HOME/include/cimar/nodeManager.h
rm -fv $OPENJAUS_HOME/lib/libnodeManager.*

echo ;
echo CIMAR Node Manager Library Uninstall Complete
echo ;
