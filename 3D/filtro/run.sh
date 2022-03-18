#!/bin/bash
#rm -r dat
#mkdir dat
#cd normalizacao
#	rm *.dat
#	cd ../
#cd nova-ic
#	rm -r dat
#	mkdir dat
#	cd plt
#	rm *.png
#	cd ../	
#	cd theta
#	rm *.dat
#	rm *.png
#	cd ../

for I in $(seq 0 1 200)
do
echo $I
	./a.out c.dat ic/ic1-$I.dat
	cd dat
#		echo $((I+1))
		mv cplx-1.dat cplx-phi1-$((I+1)).dat
		cd ../
	./a.out c.dat ic/ic2-$I.dat
	cd dat
		mv cplx-1.dat cplx-phi2-$((I+1)).dat
		cd ../
	cd normalizacao
		./a.out ../dat/cplx-phi1-$((I+1)).dat ../dat/cplx-phi2-$((I+1)).dat
		mv ic1-0.dat ../ic/ic1-$((I+1)).dat
		mv ic2-0.dat ../ic/ic2-$((I+1)).dat 
		cd ../
	cd nova-ic
		./a.out ../ic/ic1-$((I+1)).dat ../ic/ic2-$((I+1)).dat
		cd dat/
			mv phi1-1.dat phi-$I.csv
			cd ../
		cd theta
			./a.out ../../ic/ic1-$((I+1)).dat ../../ic/ic2-$((I+1)).dat
			mv theta-0.dat theta-$((I+1)).dat
			cd ../../
done
