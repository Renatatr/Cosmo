#!/bin/bash
cd theta
rm *.dat
cd ../
rm *.dat
rm -rf dat
make
./a.out 1 
