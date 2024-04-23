#!/bin/bash

N1=1500
N2=1350000

delta=$(($((N2 - N1))/10))

step=$((N1))
echo "Test default shedule"
./build/generalInfo Results/Results_without_shedule.txt $((N1)) default 1 1
for i in {1..11}
do 
    
    #echo $step
    ./build/default $step 1
    #echo $i
    step=$((step + delta))
done

./build/generalInfo Results/Results_without_shedule.txt $((N1)) default 1 2
step=$((N1))
for i in {1..11}
do     
    #echo $step
    ./build/default $step 2
    #echo $i
    step=$((step + delta))
done

./build/generalInfo Results/Results_without_shedule.txt $((N1)) default 1 4
step=$((N1))
for i in {1..11}
do 
    
    #echo $step
    ./build/default $step 4
    #echo $i
    step=$((step + delta))
done

./build/generalInfo Results/Results_without_shedule.txt $((N1)) default 1 6
step=$((N1))
for i in {1..11}
do 
    #echo $step
    ./build/default $step 6
    #echo $i
    step=$((step + delta))
done
echo "Done______________________(0)"







