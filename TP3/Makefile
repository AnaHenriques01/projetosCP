CC = mpicc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

#CFLAGS = -O2 -fopenmp
CFLAGS = -O3 -fopenmp
#CFLAGS = -funroll-loops -O2 -fopenmp
#CFLAGS = -funroll-loops -O3 -fopenmp
#CFLAGS = -ftree-vectorize -msse4 -O2 -fopenmp
#CFLAGS = -ftree-vectorize -msse4 -O3 -fopenmp

.DEFAULT_GOAL = k_means

k_means: $(SRC)k_means.c $(BIN)utils.o
	$(CC) $(CFLAGS) $(SRC)k_means.c $(BIN)utils.o -o $(BIN)$(EXEC)

$(BIN)utils.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o

clean:
	rm -r bin/*
	rm -r out.txt

runseq:
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) 1

runpar:
	mpirun -np ${NTASKS} ./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) $(THREADS)

sbatch:
	@echo "#!/bin/sh" > run.sh
	@echo "#SBATCH --partition=cpar" >> run.sh
	@echo "#SBATCH --ntasks 2" >> run.sh
	@echo "#SBATCH -c 2" >> run.sh
	@echo "perf stat make runpar NTASKS=${NTASKS} CP_CLUSTERS=${CP_CLUSTERS} THREADS=${THREADS}" >> run.sh
	@echo "perf stat make runpar NTASKS=${NTASKS} CP_CLUSTERS=${CP_CLUSTERS} THREADS=${THREADS}"
	sbatch --output=out.txt run.sh
	@echo "Check if the file out.txt does already exist"
	@echo "Keep trying to open the file out.txt until the output is printed"