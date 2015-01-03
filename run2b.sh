#!/bin/sh
make lorenz_int
rm lorenz_err.txt
rm lorenz.txt
echo "0.416460744911 0.908936263452 0.0143831116293 150 25000" | ./lorenz_int 10=sgm 28=rho 2.66666666666667=bet 2>> lorenz_err.txt 1>> lorenz.txt
gnuplot plot_b.plt
echo "Fet"
