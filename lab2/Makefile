CC = gcc
BuildDir= build

DEFAULT.EXE=default
DEFAULT=./$(BuildDir)/$(DEFAULT.EXE) 
AUTO.EXE=auto
AUTO= ./$(BuildDir)/$(AUTO.EXE)
STATIC.EXE=static
STATIC= ./$(BuildDir)/$(STATIC.EXE)
DYNAMIC.EXE=dynamic
DYNAMIC= ./$(BuildDir)/$(DYNAMIC.EXE)
GUIDED.EXE=guided
GUIDED= ./$(BuildDir)/$(GUIDED.EXE)
INFO.EXE= generalInfo
INFO=./$(BuildDir)/$(INFO.EXE)
TESTS=tests/


NSIZE= 1350000
N1= 1500
N2= 1350000

all: building default auto static dynamic guided

building:
	$(CC) lab2.c -O3 -o $(BuildDir)/$(DEFAULT.EXE) -lm -fopenmp
	$(CC) lab2auto.c -O3 -o $(BuildDir)/$(AUTO.EXE) -lm -fopenmp
	$(CC) lab2static.c -O3 -o $(BuildDir)/$(STATIC.EXE) -lm -fopenmp
	$(CC) lab2dynamic.c -O3 -o $(BuildDir)/$(DYNAMIC.EXE) -lm -fopenmp
	$(CC) lab2guided.c -O3 -o $(BuildDir)/$(GUIDED.EXE) -lm -fopenmp
	$(CC) writefileN.c -O3 -o $(BuildDir)/$(INFO.EXE)
default:
	@echo "DEFAULT SHEDULE___________________________________"
	./$(TESTS)/testDefault.sh

auto:
	@echo "AUTO SHEDULE___________________________________"
	./$(TESTS)/testAuto.sh

static:
	@echo "STATIC SCHEDULE________________________________"
	./$(TESTS)/testStatic.sh

dynamic:
	@echo "DYNAMIC SCHEDULE________________________________"
	./$(TESTS)/testDynamic.sh

guided:
	@echo "GUIDED SCHEDULE________________________________"
	./$(TESTS)/testGuided.sh

clean:
	rm Results/*
	rm $(BuildDir)/*

parallelBenefit:
	$(CC) lab2.c -O3 -o $(BuildDir)/$(DEFAULT.EXE) -lm -fopenmp
	$(CC) lab2.c -O3 -o $(BuildDir)/$(DEFAULT.EXE)_without_parallel -lm
	./$(TESTS)/testForParallelBenefit.sh