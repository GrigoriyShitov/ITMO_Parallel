CC=gcc
PROG=lab3
PROG-DEFAULT=lab3-default
PROG_10=lab3_10
PROG_Kth=lab3_Kth
OBJ=obj
INFO.EXE= generalInfo
INFO=./$(OBJ)/$(INFO.EXE)
TESTS=tests

N2= 1350000
N1=1500
Nx=750
N=15000
THREADCOUNT=4
CHUNKSIZE=4

all: building run

building:
	$(CC) -O3 $(PROG).c -o $(OBJ)/$(PROG) -fopenmp -lm
	$(CC) -O3 $(PROG).c -o $(OBJ)/$(PROG-DEFAULT) -lm
	$(CC) -O3 $(PROG_Kth).c -o $(OBJ)/$(PROG_Kth) -fopenmp -lm
	$(CC) -O3 $(PROG_10).c -o $(OBJ)/$(PROG_10) -fopenmp -lm
	$(CC) writefileN.c -O3 -o $(OBJ)/$(INFO.EXE)
	

	
run:
	./$(TESTS)/test.sh
	./$(TESTS)/test_10.sh