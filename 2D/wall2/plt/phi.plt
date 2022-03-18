set terminal pngcairo size 1000, 1000 
set size ratio -1
set xrange [0:250]
set yrange [0:250]
set cbrange [-1:1]
set palette defined ( -1 "white", 0 "black", 1 "white" )
f= 0
while(f <= 9900){
	set output sprintf("phi-%d.png", f)
	plot sprintf("../dat/phi-%d.dat", f) u ($1+1):($2+1):3 matrix w image 
	unset output
	f=f+100
}
