#!/bin/bash


function plot_1snapshot(){
Num_snap=$1
printf -v name "%02i" $1

gnuplot <<_EOF
set terminal gif
#dataFile="converge_arts.csv"
dataFile="../data/fig_data.csv"
set title "a pressure pulse in a circle of artery" offset 0,-2 
unset xtics
unset ytics
unset ztics
unset border
#set xlabel "distance (cm)"
#set ylabel "flux"
set style data lines
set o "../figures/anim/coverge_3D_${name}.gif"
set style line 1 lw 3
unset key

#set xyplane at 0
set view 70,0
splot [][][-6:16] dataFile u 1:2:3 w l ls 1, "" u 1:2:$((${Num_snap}+2))
_EOF

}

for i in {1..40}
do 
plot_1snapshot $i
done

convert -delay 15 -loop 0 "../figures/anim/*.gif" ../converg.gif
