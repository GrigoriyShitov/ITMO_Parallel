#!/bin/bash

N2=75000
N1=1500
Nx=750
N=15000


delta=$(($((N - Nx))/10))

step=$((Nx))
echo "Test lab4 shedule"
./obj/generalInfo Results/Results.txt $((N1)) pthread $(((N1)/4)) 4 
for i in {1..11}
do 
    
    echo $step
    ./obj/lab4 $step 4
    #echo $i
    step=$((step + delta))
done

step=$((Nx))
for i in {1..11}
do 
    echo $step
    step=$((step + delta))
done


echo "Done______________________(1)"