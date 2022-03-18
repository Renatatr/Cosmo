#!/bin/bash
for I in $(seq 52 1 100)
do
	pvbatch paper.py ../dat/phi-$I.csv phi-$I.png
done

