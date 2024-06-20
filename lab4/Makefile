CC=gcc
PROG=lab4
PROG-DEFAULT=lab3-default
PROG_10=lab4_10
OBJ=obj
INFO.EXE= generalInfo
INFO=./$(OBJ)/$(INFO.EXE)
TESTS=tests

N1=8000
N=15000
THREADCOUNT=4
CHUNKSIZE=4

all:
	$(CC) -O2 -w $(PROG).c -o $(OBJ)/$(PROG) -lpthread -lm
	$(CC) writefileN.c -O3 -o $(OBJ)/$(INFO.EXE)
	./$(TESTS)/test.sh