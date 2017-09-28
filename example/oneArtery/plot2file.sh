#! /bin/bash
gnuplot <<EOF
set terminal postscript eps enhanced color
set output '$2.eps'
#unset key
set multiplot layout 2,1
set grid
#set key
set title 'A (cm^2)'
line=1
line_real=line+1
plot '$1/histA.csv' using 1:line_real w l title "Pos.-" .line, '' using 1:3 w l title "Pos.-" .(line+1), '' using 1:4 w l title "Pos.-" .(line+2), '' using 1:5 w l title "Pos.-" .(line+4), '' using 1:6 w l title "Pos.-" .(line+4)
 
set grid;
set title 'Q (cm^3/s)'
plot '$1/histQ.csv' using 1:line_real w l title "Pos.-" .line, '' using 1:3 w l title "Pos.-" .(line+1), '' using 1:4 w l title "Pos.-" .(line+2), '' using 1:5 w l title "Pos.-" .(line+3), '' using 1:6 w l title "Pos.-" .(line+4)
unset multiplot 
EOF
epstopdf $2.eps
rm $2.eps
