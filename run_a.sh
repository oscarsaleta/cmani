#!/bin/sh
make pendol_int
rm pendol_err.txt
rm pendol.txt
echo "0 0.3 7 100 0 0.6 7 100" | ./pendol_int 2>> pendol_err.txt 1>> pendol.txt
gnuplot plot_a.plt
echo "Fet"
