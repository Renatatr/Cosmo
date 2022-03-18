set terminal pngcairo size 1000, 1000 
set size ratio -1
set xrange [0:500]
set yrange [0:500]
set cbrange [0:1]
set palette defined ( 0 "white", 1 "black" )
f= 1
while(f <= 1){
	set output sprintf("dw-%d.png", f)
	plot sprintf("../dat/dw-%d.dat", f) u ($1+1):($2+1):3 matrix w image 
	plot sprintf("c.dat") u ($1+1):($2+1):3 matrix w image
	unset output
	f=f+1
}
