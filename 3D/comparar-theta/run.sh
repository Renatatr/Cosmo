#!/bin/bash
for I in $(seq 1 1 201)
do
	./a.out filtro/theta-$I.dat 99
	mv evolucao1/diff-theta/diff-theta.dat evolucao1/diff-theta/diff-theta-$I.dat
done
