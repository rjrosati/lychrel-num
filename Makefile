CC=g++
DEBUG=-g
CFLAGS=-c L/usr/local/lib -lgmpxx -lgmp $(DEBUG)
LFLAGS= -L/usr/local/lib -lgmpxx -lgmp $(DEBUG)
OBJS= lychrel-num.o 

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o findchain 

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

lychrel-num.o: lychrel-num.cpp 
