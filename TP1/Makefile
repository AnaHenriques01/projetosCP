CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

CFLAGS = -funroll-loops -o2 -Wall
#CFLAGS =  -ftree-vectorize -msse4 -O2 -Wall -I/share/apps/papi/5.4.1/include 

#LIBS = -lm -lpapi -mavx -L/share/apps/papi/5.4.1/lib
#LIBS = -lm -lpapi -L/share/apps/papi/5.4.1/lib

.DEFAULT_GOAL = k_means

k_means: $(SRC)k_means.c $(BIN)utils.o
	$(CC) $(CFLAGS) $(SRC)k_means.c $(BIN)utils.o -o $(BIN)$(EXEC)

$(BIN)utils.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)