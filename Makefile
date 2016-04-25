CC=g++
DEBUG=-g
CFLAGS=-c -O3 -std=c++11 -Wall -L/usr/local/lib -fopenmp -lgmpxx -lgmp $(DEBUG)
LFLAGS= -O3 -std=c++11 -Wall -L/usr/local/lib -fopenmp -lgmpxx -lgmp $(DEBUG)
OBJS= findchain.o bigint.o

all: $(OBJS)
	$(CC) $(OBJS) -o findchain $(LFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

findchain.o: findchain.cpp bigint.h

bigint.o: bigint.cpp bigint.h

clean:
	rm findchain $(OBJS)
	rm .*.swp
