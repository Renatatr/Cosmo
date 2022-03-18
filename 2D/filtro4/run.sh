#!/bin/bash
for I in $(seq 0 1 200)
do
echo $I
	./a.out g.dat ic/ic-$I.dat
	cd dat
		mv dw-1.dat dw-1-$((I+1)).dat
		cp dw-1-$((I+1)).dat ../ic/ic-$((I+1)).dat
		cd ../
done
cd plt
	gnuplot phi.plt
