#!/bin/sh
make apartat3
rm apartat3.txt
rm apartat3_err.txt
./apartat3 1.215058560962404e-2 < apartat3.inp 2>> apartat3_err.txt 1>> apartat3.txt 
echo "Fet"
