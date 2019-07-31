CC = gcc
LDC = gcc
LD_FLAGS = -fopenmp
FLAGS = -fopenmp
RM= /bin/rm

all: neighbors.o
	$(CC) neighbors.o callneighbor.c -o callneighbor -lm -Wall -Wextra

obj: neighbors.c
	gcc -c neighbors.c -o neighbors.o -lm

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod
