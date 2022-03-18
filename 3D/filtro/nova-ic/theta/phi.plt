set terminal pngcairo size 1000, 1000 
set size ratio -1
set xrange [0:500]
set yrange [0:500]
set cbrange [0:6.29]
set palette model HSV rgbformulae 3,2,2

f= 1
while(f <= 100000){
	set output sprintf("theta-%d.png", f)
	plot sprintf("theta-%d.dat", f) u ($1+1):($2+1):3 matrix w image 
	unset output
	f=f+1
}
