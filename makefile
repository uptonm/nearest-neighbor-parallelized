CC = tau_cc.sh 
LDC = tau_cc.sh
LD_FLAGS = -fopenmp
FLAGS = -fopenmp
RM= /bin/rm

export TAU_MAKEFILE=/opt/sw/tau/x86_64/lib/Makefile.tau-mpi-pdt

all: obj
	$(CC) neighbors.o callneighbor.c -o callneighbor -lm -Wall -Wextra
	$(CC) neighbors.o parallelizedneighbor.c -o parallelizedneighbor -lm -Wall -Wextra

obj: neighbors.c
	$(CC) -c neighbors.c -o neighbors.o -lm
	$(CC) -c parallelizedneighbor.c -o parallelizedneighbor.o -lm

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod *.pomp.c 
