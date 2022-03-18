#!/bin/bash
for I in $(seq 1 1 201)
do
	./a.out filtro/dw-1-$I.dat 99
	mv evolucao1/comp/comp.dat evolucao1/comp/comp-$I.dat
done
