#!/bin/bash
for I in $(seq 15 1 100)
do
	pvbatch paper.py ../dat/phi-$I.csv phi-$I.png
done

