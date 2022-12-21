CC = mpicc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means
THREADS = 2

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

runseq: k_means
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) 1

runpar: k_means
	mpirun -np 1 ./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) $(THREADS)