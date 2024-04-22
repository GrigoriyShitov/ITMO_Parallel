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


NSIZE= 55000
N1= 350
N2= 14000

all: build default auto static dynamic guided

build:
	$(CC) lab2.c -O3 -o $(BuildDir)/$(DEFAULT.EXE) -lm -fopenmp
	$(CC) lab2auto.c -O3 -o $(BuildDir)/$(AUTO.EXE) -lm -fopenmp
	$(CC) lab2static.c -O3 -o $(BuildDir)/$(STATIC.EXE) -lm -fopenmp
	$(CC) lab2dynamic.c -O3 -o $(BuildDir)/$(DYNAMIC.EXE) -lm -fopenmp
	$(CC) lab2guided.c -O3 -o $(BuildDir)/$(GUIDED.EXE) -lm -fopenmp

default:
	@echo "DEFAULT SHEDULE___________________________________"
	@echo "Test with N=1500000 and 4 threads"
	$(DEFAULT) 1500000 4
	@echo "Test with N=1500000 and 1 threads"
	$(DEFAULT) 1500000 1

auto:
	@echo "AUTO SHEDULE___________________________________"
	@echo "Test with N=1500000 and 4 threads"
	$(AUTO) 1500000 4
	@echo "Test with N=1500000 and 1 threads"
	$(AUTO) 1500000 1

static:
	@echo "STATIC SCHEDULE________________________________"
	
	@echo "CHUNKSIZE =1_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(STATIC) 1500000 4 1
	@echo "Test with N=1500000 and 1 threads"
	$(STATIC) 1500000 1 1

	@echo "CHUNKSIZE =2_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(STATIC) 1500000 4 2
	@echo "Test with N=1500000 and 1 threads"
	$(STATIC) 1500000 1 2

	@echo "CHUNKSIZE =4_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(STATIC) 1500000 4 4
	@echo "Test with N=1500000 and 1 threads"
	$(STATIC) 1500000 1 4

	@echo "CHUNKSIZE =8_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(STATIC) 1500000 4 8
	@echo "Test with N=1500000 and 1 threads"
	$(STATIC) 1500000 1 8

dynamic:
	@echo "DYNAMIC SCHEDULE________________________________"
	
	@echo "CHUNKSIZE =1_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(DYNAMIC) 1500000 4 1
	@echo "Test with N=1500000 and 1 threads"
	$(DYNAMIC) 1500000 1 1

	@echo "CHUNKSIZE =2_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(DYNAMIC) 1500000 4 2
	@echo "Test with N=1500000 and 1 threads"
	$(DYNAMIC) 1500000 1 2

	@echo "CHUNKSIZE =4_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(DYNAMIC) 1500000 4 4
	@echo "Test with N=1500000 and 1 threads"
	$(DYNAMIC) 1500000 1 4

	@echo "CHUNKSIZE =8_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(DYNAMIC) 1500000 4 8
	@echo "Test with N=1500000 and 1 threads"
	$(DYNAMIC) 1500000 1 8

guided:
	@echo "GUIDED SCHEDULE________________________________"
	
	@echo "CHUNKSIZE =1_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(GUIDED) 1500000 4 1
	@echo "Test with N=1500000 and 1 threads"
	$(GUIDED) 1500000 1 1

	@echo "CHUNKSIZE =2_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(GUIDED) 1500000 4 2
	@echo "Test with N=1500000 and 1 threads"
	$(GUIDED) 1500000 1 2

	@echo "CHUNKSIZE =4_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(GUIDED) 1500000 4 4
	@echo "Test with N=1500000 and 1 threads"
	$(GUIDED) 1500000 1 4

	@echo "CHUNKSIZE =8_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(GUIDED) 1500000 4 8
	@echo "Test with N=1500000 and 1 threads"
	$(GUIDED) 1500000 1 8



