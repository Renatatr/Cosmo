set terminal pngcairo size 1000, 1000 
set size ratio -1
set xrange [0:250]
set yrange [0:250]
set cbrange [-1:1]
set palette defined ( -1 "white", 1 "black" )
f= 1
while(f <= 10000){
	set output sprintf("dw-1-%d.png", f)
	plot sprintf("../dat/dw-1-%d.dat", f) u ($1+1):($2+1):3 matrix w image 
	unset output
	f=f+1
}
