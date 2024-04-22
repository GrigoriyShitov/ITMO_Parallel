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


NSIZE= 55000
N1= 350
N2= 14000

all: building default auto static dynamic guided

building:
	rm Results/*
	$(CC) lab2.c -O3 -o $(BuildDir)/$(DEFAULT.EXE) -lm -fopenmp
	$(CC) lab2auto.c -O3 -o $(BuildDir)/$(AUTO.EXE) -lm -fopenmp
	$(CC) lab2static.c -O3 -o $(BuildDir)/$(STATIC.EXE) -lm -fopenmp
	$(CC) lab2dynamic.c -O3 -o $(BuildDir)/$(DYNAMIC.EXE) -lm -fopenmp
	$(CC) lab2guided.c -O3 -o $(BuildDir)/$(GUIDED.EXE) -lm -fopenmp
	$(CC) writefileN.c -O3 -o $(BuildDir)/$(INFO.EXE)
default:
	@echo "DEFAULT SHEDULE___________________________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_without_shedule.txt 1500000 default 1 4
	$(DEFAULT) 1500000 4
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_without_shedule.txt 1500000 default 1 1
	$(DEFAULT) 1500000 1

auto:
	@echo "AUTO SHEDULE___________________________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_auto_shedule.txt 1500000 auto 1 4
	$(AUTO) 1500000 4
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_auto_shedule.txt 1500000 auto 1 1
	$(AUTO) 1500000 1

static:
	@echo "STATIC SCHEDULE________________________________"
	
	@echo "CHUNKSIZE =1_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 1 4
	$(STATIC) 1500000 4 1
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 1 1
	$(STATIC) 1500000 1 1

	@echo "CHUNKSIZE =2_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 2 4
	$(STATIC) 1500000 4 2
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 2 1
	@echo "Test with N=1500000 and 1 threads"
	$(STATIC) 1500000 1 2

	@echo "CHUNKSIZE =4_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 4 4
	$(STATIC) 1500000 4 4
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 4 1
	$(STATIC) 1500000 1 4

	@echo "CHUNKSIZE =8_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 8 4
	$(STATIC) 1500000 4 8
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_static_shedule.txt 1500000 static 1 1
	$(STATIC) 1500000 1 8

dynamic:
	@echo "DYNAMIC SCHEDULE________________________________"
	
	@echo "CHUNKSIZE =1_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 1 4
	$(DYNAMIC) 1500000 4 1
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 1 1
	$(DYNAMIC) 1500000 1 1

	@echo "CHUNKSIZE =2_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 2 4
	$(DYNAMIC) 1500000 4 2
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 2 1
	$(DYNAMIC) 1500000 1 2

	@echo "CHUNKSIZE =4_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 4 4
	$(DYNAMIC) 1500000 4 4
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 4 1
	$(DYNAMIC) 1500000 1 4

	@echo "CHUNKSIZE =8_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 8 4
	$(DYNAMIC) 1500000 4 8
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_dynamic_shedule.txt 1500000 dynamic 8 1
	$(DYNAMIC) 1500000 1 8

guided:
	@echo "GUIDED SCHEDULE________________________________"
	
	@echo "CHUNKSIZE =1_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 1 4
	$(GUIDED) 1500000 4 1
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 1 1
	$(GUIDED) 1500000 1 1

	@echo "CHUNKSIZE =2_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 2 4
	$(GUIDED) 1500000 4 2
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 2 1
	$(GUIDED) 1500000 1 2

	@echo "CHUNKSIZE =4_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 4 4
	$(GUIDED) 1500000 4 4
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 4 1
	$(GUIDED) 1500000 1 4

	@echo "CHUNKSIZE =8_____________________"
	@echo "Test with N=1500000 and 4 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 8 4
	$(GUIDED) 1500000 4 8
	@echo "Test with N=1500000 and 1 threads"
	$(INFO) Results/Results_with_guided_shedule.txt 1500000 guided 8 1
	$(GUIDED) 1500000 1 8



