CC = gcc
BuildDir= build
LAB1SEQ= ./$(BuildDir)/lab1-seq 
LAB1PAR= ./$(BuildDir)/lab1-par-
NSIZE= 1350000
N1= 1500
N2= 1350000

all: seq par N1SIZE N2SIZE

seq:
	$(CC) -O3 -Wall -Werror lab1.c -o $(BuildDir)/lab1-seq -lm
par:
	$(CC) -O3 -Wall -floop-parallelize-all -ftree-parallelize-loops=1 lab1.c -o $(BuildDir)/lab1-par-1 -lm 
	$(CC) -O3 -Wall -floop-parallelize-all -ftree-parallelize-loops=2 lab1.c -o $(BuildDir)/lab1-par-2 -lm 
	$(CC) -O3 -Wall -floop-parallelize-all -ftree-parallelize-loops=4 lab1.c -o $(BuildDir)/lab1-par-4 -lm 
	$(CC) -O3 -Wall -floop-parallelize-all -ftree-parallelize-loops=8 lab1.c -o $(BuildDir)/lab1-par-8 -lm

N1SIZE:
	echo "without paralleling:" 
	$(LAB1SEQ) $(N1)
	echo "paralleling K=1 "
	$(LAB1PAR)1 $(N1)
	echo "paralleling K=2 "
	$(LAB1PAR)2 $(N1)
	echo "paralleling K=4 "
	$(LAB1PAR)4 $(N1)
	echo "paralleling K=8 "
	$(LAB1PAR)8 $(N1)

N2SIZE:
	echo "without paralleling:" 
	$(LAB1SEQ) $(N2)
	echo "paralleling K=1 "
	$(LAB1PAR)1 $(N2)
	echo "paralleling K=2 "
	$(LAB1PAR)2 $(N2)
	echo "paralleling K=4 "
	$(LAB1PAR)4 $(N2)
	echo "paralleling K=8 "
	$(LAB1PAR)8 $(N2)

run:
	echo "without paralleling:" 
	$(LAB1SEQ) $(NSIZE)
	echo "paralleling K=1 "
	$(LAB1PAR)1 $(NSIZE)
	echo "paralleling K=2 "
	$(LAB1PAR)2 $(NSIZE)
	echo "paralleling K=4 "
	$(LAB1PAR)4 $(NSIZE)
	echo "paralleling K=8 "
	$(LAB1PAR)8 $(NSIZE)

clean:
	rm $(BuildDir)/*




