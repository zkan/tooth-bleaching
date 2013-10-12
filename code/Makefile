#
#	Makefile for compiling all code in this directory.
#	Author: Kan Ouivirach
# 

CFLAGS = -g -Wall
CC = g++ $(CFLAGS)
PROG = tooth_shade_predictor
all: $(PROG)

linreg.o: linreg.cc linreg.h
	$(CC) -c linreg.cc

tooth_shade_predictor.o: tooth_shade_predictor.cc tooth_shade_predictor.h linreg.h
	$(CC) -c tooth_shade_predictor.cc

tooth_shade_predictor: main.o tooth_shade_predictor.o linreg.o
	$(CC) main.o tooth_shade_predictor.o linreg.o -o tooth_shade_predictor

clean:
	rm *.o $(PROG)







