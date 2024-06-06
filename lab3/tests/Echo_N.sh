#!/bin/bash

N2=1350000
N1=1500
Nx=750
N=15000


delta=$(($((N - Nx))/10))

step=$((Nx))
for i in {1..11}
do 
    echo $step
    step=$((step + delta))
done

echo "Done______________________(1)"