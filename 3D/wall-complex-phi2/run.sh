#!/bin/bash
rm *.dat
rm -rf dat
rm -rf theta
mkdir theta
make
rm theta/*.dat
rm theta/*.png
./a.out 1 
