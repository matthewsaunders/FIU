#!/bin/bash

#check for filename arg
if(( $# != 2 )); then
	echo "usage:"
	echo "    ./plot.sh [data file] [output file]"
	exit 1
fi

FILE=$1
OUTPUT=$2

#check that file exists
if [ ! -f $FILE ]; then
	echo "File '$FILE' does not exist!"
	exit 1
fi

#plot file in gnuplot
gnuplot <<- EOF
	set terminal pngcairo size 1000,1000 enhanced font 'Verdana,10'
	set output 'plot-xy.png'
	set title "Galaxy Plot"
	set xlabel "X Axis"
	set ylabel "Y Axis"
	set output "${2}-xy.png"
	plot "${FILE}" using 2:3
	
	set title "Galaxy Plot XZ"
	set output "${2}-xz.png"
	plot "${FILE}" using 2:4
EOF

echo "Plotted XY and XZ plots to files:"
echo "    - ${OUTPUT}-XY.png"
echo "    - ${OUTPUT}-XZ.png"
