#!/bin/sh
make cmani_rtbp
rm cmani_rtbp_mine.out
./cmani_rtbp 1.215058560962404e-2 1e-12=tolnwt 10=maxitnwt < cmani_rtbp.inp > cmani_rtbp_mine.out
echo "Fet"

