set terminal pngcairo size 1000, 1000 
set size ratio -1
set xrange [0:500]
set yrange [0:500]
#set cbrange [0:0.1]
#set palette defined ( 0 "white", 0.1 "black" )

f= 0
while(f <= 1){
	set output sprintf("ic2-%d.png", f)
	plot sprintf("ic2-%d.dat", f) u ($1+1):($2+1):3 matrix w image 
	unset output
	f=f+1
}
