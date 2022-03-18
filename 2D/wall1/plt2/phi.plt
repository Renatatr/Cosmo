set terminal pngcairo size 1000, 1000 
set size ratio -1
set xrange [0:250]
set yrange [0:250]
#set cbrange [0:0.05]
set palette rgb -21, -22, -23
f= 0
while(f <= 100000){
	set output sprintf("phi-%d.png", f)
	plot sprintf("../dat/phi-%d.dat", f) u ($1+1):($2+1):3 matrix w image 
	unset output
	f=f+100
}
