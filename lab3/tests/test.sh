#!/bin/bash

N2=1350000
N1=1500
Nx=750
N=15000


delta=$(($((N - Nx))/10))

step=$((Nx))
echo "Test lab3 shedule"
./obj/generalInfo Results/Results.txt $((N1)) guided 4 4
for i in {1..11}
do 
    
    echo $step
    ./obj/lab3 $step 4 4
    #echo $i
    step=$((step + delta))
done

step=$((Nx))
echo "Test lab3_Kth shedule"
./obj/generalInfo Results/Results_Kth.txt $((N1)) guided 4 4
for i in {1..11}
do 
    
    echo $step
    ./obj/lab3_Kth $step 4 4
    #echo $i
    step=$((step + delta))
done

echo "Done______________________(1)"