set term x11 size 700,700
set view equal xyz
set ticslevel 0.1
set ytics .1
set xlabel 'x' ; set ylabel 'y' ; set zlabel 'z'
splot 'halos.txt' u 2:3:4 w l,'L1.txt' w p,'trr.txt' w p,'lln.txt' w p
pause mouse close
exit
