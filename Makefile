CC=mpic++
DEBUG= -g
OPT= -DQUIET -O3 -ffast-math -funroll-loops -msse4 -mtune=native
CFLAGS=-c $(OPT) -std=c++11 -Wall -L/usr/local/lib -fopenmp $(DEBUG)
LFLAGS= $(OPT) -std=c++11 -flto -Wall -L/usr/local/lib -fopenmp $(DEBUG)
OBJS= findchain.o bigint.o


all: $(OBJS)
	$(CC) $(OBJS) -o findchain $(LFLAGS)

icc: OPT=-O3 -fp-model fast -ipo -DQUIET -DNO_MPI_THREADS
icc: LFLAGS= $(OPT) -std=c++11 -Wall -L/usr/local/lib -openmp -lmpi $(DEBUG)
icc: $(OBJS)
	$(CC) $(OBJS) -o findchain $(LFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

findchain.o: findchain.cpp bigint.h

bigint.o: bigint.cpp bigint.h

clean:
	rm -f findchain $(OBJS)
	rm -f .*.swp
.PHONY: clean
