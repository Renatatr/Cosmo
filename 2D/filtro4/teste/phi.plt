set terminal pngcairo size 1000, 1000 
set output "c.png"

set size ratio -1
set xrange [0:250]
set yrange [0:250]
set cbrange [0:1]
set palette defined ( 0 "white", 1 "black" )

plot "g.dat" u ($1+1):($2+1):3 matrix w image 

unset output
