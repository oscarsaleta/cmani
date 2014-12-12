#!/bin/sh
make rtbps_int
./rtbps_int 1.215058560962404e-2 < halos.inp 2>> halos_err.txt 1>> halos.txt 
gnuplot plot_c.plt
echo "Fet"
