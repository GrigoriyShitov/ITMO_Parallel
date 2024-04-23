#!/bin/bash

N1=1500
N2=1350000

delta=$(($((N2 - N1))/10))

echo "Test default shedule"
./build/generalInfo Results/Results_with_guided_shedule.txt $((N1)) guided 1 4
step=$((N1))
for i in {1..11}
do 
    
    #echo $step
    ./build/guided $step 4 1
    #echo $i
    step=$((step + delta))
done

./build/generalInfo Results/Results_with_guided_shedule.txt $((N1)) guided 2 4
step=$((N1))
for i in {1..11}
do 
    
    #echo $step
    ./build/guided $step 4 2
    #echo $i
    step=$((step + delta))
done

./build/generalInfo Results/Results_with_guided_shedule.txt $((N1)) guided 4 4
step=$((N1))
for i in {1..11}
do 
    
    #echo $step
    ./build/guided $step 4 4
    #echo $i
    step=$((step + delta))
done

./build/generalInfo Results/Results_with_guided_shedule.txt $((N1)) guided 8 4
step=$((N1))
for i in {1..11}
do 
    
    #echo $step
    ./build/guided $step 4 8
    #echo $i
    step=$((step + delta))
done
echo "Done______________________(2)"