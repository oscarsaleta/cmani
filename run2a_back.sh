#!/bin/sh
make pendol_int
rm pendol_err_back.txt
rm pendol_back.txt
echo "0 0.3 -5 100 0 0.6 -5 100" | ./pendol_int 2>> pendol_err_back.txt 1>> pendol_back.txt
gnuplot plot_a_back.plt
echo "Fet"
