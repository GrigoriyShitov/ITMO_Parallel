#!/bin/bash

N2=1350000
N1=1500
Nx=750
N=15000


delta=$(($((N - Nx))/10))

step=$((Nx))
echo "Test auto shedule"
./obj/generalInfo Results/Results_10.txt $((N1)) guided 4 4
for i in {1..11}
do 
    for j in {1..11}
    do 
        echo $step
        ./obj/lab3_10 $step 4 4
        #echo $i
        
    done
    step=$((step + delta))
done

echo "Done______________________(1)"