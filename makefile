CC = mpicc
LDC = mpicc
LD_FLAGS = -fopenmp
FLAGS = -fopenmp
RM= /bin/rm

all: neighbors.o 
	$(CC) neighbors.o callneighbor.c -o callneighbor -lm -Wall -Wextra
	$(CC) neighbors.o parallelizedneighbor.c -o parallelizedneighbor -lm -Wall -Wextra

obj: neighbors.c
	$(CC) -c neighbors.c -o neighbors.o -lm

obj: neighbors.c
	$(CC) -c parallelizedneighbor.c -o parallelizedneighbor.o -lm

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod
