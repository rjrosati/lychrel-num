CC=g++
DEBUG=-g
CFLAGS=-c -O2 -Wall -L/usr/local/lib -fopenmp -lgmpxx -lgmp $(DEBUG)
LFLAGS= -O2 -Wall -L/usr/local/lib -fopenmp -lgmpxx -lgmp $(DEBUG)
OBJS= findchain.o 

all: $(OBJS)
	$(CC) $(OBJS) -o findchain $(LFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

findchain.o: findchain.cpp

clean:
	rm findchain $(OBJS)
	rm .*.swp
