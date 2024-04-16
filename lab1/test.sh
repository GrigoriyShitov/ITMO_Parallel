#!/bin/bash

N1=21000
N2=1350000

delta=$(($((N2 - N1))/10))

step=$((N1))
echo "Test without paralleling"
for i in {1..10}
do 
    #echo $i
    step=$((step + delta))
    #echo $step
    ./build/lab1-seq $step
done

echo "Done______________________(0)"

step=$((N1))
echo "Test with paralleling K=1"
for i in {1..10}
do 
    #echo $i
    step=$((step + delta))
    #echo $step
    ./build/lab1-par-1 $step
done

echo "Done______________________(1)"


step=$((N1))
echo "Test with paralleling K=2"
for i in {1..10}
do 
    #echo $i
    step=$((step + delta))
    #echo $step
    ./build/lab1-par-2 $step
done

echo "Done______________________(2)"

step=$((N1))
echo "Test with paralleling K=4"
for i in {1..10}
do 
    #echo $i
    step=$((step + delta))
    #echo $step
    ./build/lab1-par-4 $step
done

echo "Done______________________(3)"

step=$((N1))
echo "Test with paralleling K=8"
for i in {1..10}
do 
    #echo $i
    step=$((step + delta))
    #echo $step
    ./build/lab1-par-8 $step
done

echo "Done______________________(4)"





