CC=g++
DEBUG=-g
CFLAGS=-c -Wall -L/usr/local/lib -fopenmp -lgmpxx -lgmp $(DEBUG)
LFLAGS= -Wall -L/usr/local/lib -fopenmp -lgmpxx -lgmp $(DEBUG)
OBJS= findchain.o 

all: $(OBJS)
	$(CC) $(OBJS) -o findchain $(LFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

findchain.o: findchain.cpp

clean:
	rm findchain $(OBJS)
	rm .*.swp
