CC=mpic++
DEBUG=
OPT=-O3 -ffast-math -fp-model fast
CFLAGS=-c $(OPT) -std=c++11 -Wall -L/usr/local/lib -fopenmp $(DEBUG)
LFLAGS= $(OPT) -std=c++11 -Wall -L/usr/local/lib -fopenmp $(DEBUG)
OBJS= findchain.o bigint.o

all: $(OBJS)
	$(CC) $(OBJS) -o findchain $(LFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

findchain.o: findchain.cpp bigint.h

bigint.o: bigint.cpp bigint.h

clean:
	rm -f findchain $(OBJS)
	rm -f .*.swp
