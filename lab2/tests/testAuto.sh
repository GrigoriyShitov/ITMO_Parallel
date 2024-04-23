#!/bin/bash

N1=1500
N2=1350000

delta=$(($((N2 - N1))/10))

step=$((N1))
echo "Test auto shedule"
./build/generalInfo Results/Results_with_auto_shedule.txt $((N1)) auto 1 4
for i in {1..11}
do 
    
    #echo $step
    ./build/auto $step 4
    #echo $i
    step=$((step + delta))
done

echo "Done______________________(1)"