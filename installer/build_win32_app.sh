#!/bin/sh
DEPTH=../../..
rm -f ./mbrasetup.exe
lmk -m opt -b
$DEPTH/depend/InnoSetup5/ISCC.exe mbra.iss
cp mbrasetup.exe $DEPTH/MBRA-`cat $DEPTH/tmp/win32-opt/mbraapp/buildnumber.txt`.exe